/** Cloudflare Worker: receives lab results, writes to a PRIVATE GitHub repository.
 * Set secrets/vars: GITHUB_TOKEN (secret), GH_OWNER, GH_REPO, ALLOWED_ORIGIN.
 * Never publish the GitHub token in HTML or GitHub repository.
 */
export default {
  async fetch(request, env) {
    const origin = request.headers.get('Origin') || '';
    const allowed = (env.ALLOWED_ORIGIN || '').replace(/\/$/, '');
    const cors = {
      'Access-Control-Allow-Origin': allowed,
      'Access-Control-Allow-Methods': 'POST, OPTIONS',
      'Access-Control-Allow-Headers': 'Content-Type',
      'Vary': 'Origin',
      'Content-Type': 'application/json; charset=utf-8',
      'Cache-Control': 'no-store'
    };
    const reply = (body, status=200) => new Response(JSON.stringify(body), {status, headers:cors});
    if (!allowed || origin !== allowed) return reply({error:'Origin not allowed'},403);
    if (request.method === 'OPTIONS') return new Response(null,{status:204,headers:cors});
    if (request.method !== 'POST') return reply({error:'Use POST'},405);
    const size = Number(request.headers.get('content-length') || 0);
    if (size > 30000) return reply({error:'Submission too large'},413);
    let data;
    try {
      const raw = await request.text();
      if (raw.length > 30000) return reply({error:'Submission too large'},413);
      data = JSON.parse(raw);
    } catch {return reply({error:'Invalid JSON'},400)}
    const safeStr = (s,max) => typeof s==='string' && s.trim().length>0 && s.length<=max;
    if (data?.lab !== 'clustering-algorithms-v1' ||
        !safeStr(data.student_name,100) || !safeStr(data.student_identifier,120) ||
        (typeof data.section !== 'string' || data.section.length>80) ||
        !Array.isArray(data.answers) || data.answers.length!==10 ||
        !Number.isInteger(data.quiz_score) || data.quiz_score<0 || data.quiz_score>10 ||
        data.quiz_total!==10 || !data.written ||
        !['comparison','initialization','linkage','divisive'].every(k=>safeStr(data.written[k],8000)))
       return reply({error:'Missing or invalid fields'},400);
    // Client scores can be manipulated. Recalculate from selected option indices on server.
    const keys=[[1],[0],[2],[3],[1],[1],[0,1,3],[0,1,3],[0],[1]];
    let score=0;
    for(let i=0;i<10;i++){
      const row=data.answers[i];
      if(row?.number!==i+1 || !Array.isArray(row.selected))return reply({error:'Invalid answers'},400);
      const expectedLabels=[
        ['Merge the closest clusters','Update each centroid to the mean of its assigned points','Split the cluster with the most points','Choose each centroid as the farthest point'],
        ['(4,4)','(4,6)','(6,4)','(3,4)'],
        ['One cluster containing all n observations','K randomly chosen centroids','One singleton cluster per observation','Two clusters of equal size'],
        ['Distance between their centroids','Maximum distance between a cross-cluster pair','Average distance between all cross-cluster pairs','Minimum distance between a cross-cluster pair'],
        ['Start with singletons and repeatedly merge','Start with one cluster and recursively split','Repeatedly update K fixed centroids','Assign every point to its nearest medoid'],
        ['3','4','5','6'],
        ['It requires selecting K before fitting','Its squared-error objective can have local minima','It always returns a hierarchical dendrogram','Its results can depend on initialization'],
        ['Agglomerative is bottom-up','Divisive is top-down','All divisive algorithms must use K-Means for splitting','Agglomerative clustering can be represented using a dendrogram'],
        ['True','False'],['True','False']
      ][i];
      const selected=row.selected;
      if(selected.length>4 || new Set(selected).size!==selected.length || selected.some(x=>!expectedLabels.includes(x)))return reply({error:'Invalid selected answers'},400);
      const got=selected.map(s=>expectedLabels.indexOf(s)).sort((a,b)=>a-b);
      const correct=JSON.stringify(got)===JSON.stringify(keys[i]);
      row.correct=correct;
      if(correct)score++;
    }
    data.quiz_score=score;
    data.quiz_total=10;
    data.received_at=new Date().toISOString();
    data.submitted_at=data.received_at;
    const receipt=crypto.randomUUID();
    data.receipt=receipt;
    const bytes=new TextEncoder().encode(JSON.stringify(data,null,2));
    let binary='';for(let offset=0;offset<bytes.length;offset+=8192)binary+=String.fromCharCode(...bytes.slice(offset,offset+8192));
    const content=btoa(binary);
    const day=data.received_at.substring(0,10);
    const path=`submissions/${day}/${receipt}.json`;
    if(!env.GITHUB_TOKEN || !env.GH_OWNER || !env.GH_REPO)return reply({error:'Instructor backend configuration incomplete'},503);
    let api;
    try {
      api=await fetch(`https://api.github.com/repos/${encodeURIComponent(env.GH_OWNER)}/${encodeURIComponent(env.GH_REPO)}/contents/${path}`,{
        method:'PUT',headers:{'Authorization':`Bearer ${env.GITHUB_TOKEN}`,'Accept':'application/vnd.github+json','Content-Type':'application/json','User-Agent':'ClusteringLabReceiver','X-GitHub-Api-Version':'2022-11-28'},
        body:JSON.stringify({message:`Save lab submission ${receipt}`,content})
      });
    } catch {return reply({error:'Could not reach storage; retry later'},502)}
    if(!api.ok)return reply({error:'GitHub storage request failed; instructor should check Worker logs and token permissions'},502);
    return reply({ok:true,receipt,score});
  }
};
