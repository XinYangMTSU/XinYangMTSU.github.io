
/** Cloudflare Worker: receives lab results, writes to a PRIVATE GitHub repository.
 * Set secrets/vars: GITHUB_TOKEN (secret), GH_OWNER, GH_REPO, ALLOWED_ORIGIN.
 * Never publish the GitHub token in HTML or GitHub repository.
 */
export default {
  async fetch(request, env) {
    const origin = request.headers.get('Origin') || '';
    // Origin is a browser CORS boundary, NOT student identity verification.
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
    const isTsne = data?.lab === 'tsne-dimensionality-reduction-v1';
    const isIca = data?.lab === 'ica-independent-component-analysis-v1';
    const expectedTotal = (isTsne || isIca) ? 7 : 10;
    if ((!isTsne && !isIca && data?.lab !== 'clustering-algorithms-v1') ||
        !safeStr(data.student_name,100) || !safeStr(data.student_identifier,120) ||
        (typeof data.section !== 'string' || data.section.length>80) ||
        !Array.isArray(data.answers) || data.answers.length!==expectedTotal ||
        !Number.isInteger(data.quiz_score) || data.quiz_score<0 || data.quiz_score>expectedTotal ||
        data.quiz_total!==expectedTotal || !data.written ||
        !((isTsne || isIca) ? (typeof data.written === 'object' && !Array.isArray(data.written)) : ['comparison','initialization','linkage','divisive'].every(k=>safeStr(data.written[k],8000))))
       return reply({error:'Missing or invalid fields'},400);
    // Client scores can be manipulated. Recalculate from selected option indices on server.
    const keys=isIca ? [[1],[1],[0],[2],[1],[2],[1]] : isTsne ? [[1],[0],[2],[1],[3],[2],[1]] : [[1],[0],[2],[3],[1],[1],[0,1,3],[0,1,3],[0],[1]];
    let score=0;
    for(let i=0;i<keys.length;i++){
      const row=data.answers[i];
      if(row?.number!==i+1 || !Array.isArray(row.selected))return reply({error:'Invalid answers'},400);
      const expectedLabels=(isIca ? [
      ['Find directions of maximum variance','Recover statistically independent latent sources','Preserve local neighborhoods for visualization','Assign observations to K clusters'],
      ['Zero covariance always implies independence','Independence implies zero covariance when covariance exists, but not conversely','Independence means two variables must have the same distribution','Uncorrelated variables cannot have nonlinear relationships'],
      ['The mixing matrix','The whitening transformation only','The vector of independent sources','The recovered component labels'],
      ['To make all sources Gaussian','To remove all nonlinear dependence','To decorrelate and standardize the observed features','To determine the true order of the sources'],
      ['All sources are Gaussian','At most one source is Gaussian','Sources must have equal amplitudes','A single mixture always identifies two sources'],
      ['The separation is necessarily incorrect','The signal must have been mixed nonlinearly','It may be a valid ICA solution because sign is ambiguous','Whitening was skipped'],
      ['True','False']
    ] : isTsne ? [["To predict class labels", "To visualize local neighborhoods in low-dimensional space", "To find statistically independent components", "To maximize global variance with a linear projection"], ["Gaussian kernel", "Student-t kernel with one degree of freedom", "Linear kernel", "Laplacian eigenvector kernel"], ["The exact number of clusters in the data", "The number of gradient-descent iterations", "The effective scale of a point’s neighborhood", "The target number of embedding dimensions"], ["To make the mapping linear", "To reduce the crowding problem", "To avoid computing pairwise similarities", "To guarantee equal distances between clusters"], ["Explained variance ratio", "Reconstruction mean squared error", "KL(Q ∥ P)", "KL(P ∥ Q)"], ["Their axes must have the same orientation", "The optimization must return identical coordinates", "They may produce different layouts while preserving similar local neighborhoods", "The larger-looking cluster is always more variable in the source space"], ["True", "False"]] : [
        ['Merge the closest clusters','Update each centroid to the mean of its assigned points','Split the cluster with the most points','Choose each centroid as the farthest point'],
        ['(4,4)','(4,6)','(6,4)','(3,4)'],
        ['One cluster containing all n observations','K randomly chosen centroids','One singleton cluster per observation','Two clusters of equal size'],
        ['Distance between their centroids','Maximum distance between a cross-cluster pair','Average distance between all cross-cluster pairs','Minimum distance between a cross-cluster pair'],
        ['Start with singletons and repeatedly merge','Start with one cluster and recursively split','Repeatedly update K fixed centroids','Assign every point to its nearest medoid'],
        ['3','4','5','6'],
        ['It requires selecting K before fitting','Its squared-error objective can have local minima','It always returns a hierarchical dendrogram','Its results can depend on initialization'],
        ['Agglomerative is bottom-up','Divisive is top-down','All divisive algorithms must use K-Means for splitting','Agglomerative clustering can be represented using a dendrogram'],
        ['True','False'],['True','False']
      ])[i];
      const selected=row.selected;
      if(selected.length>4 || new Set(selected).size!==selected.length || selected.some(x=>!expectedLabels.includes(x)))return reply({error:'Invalid selected answers'},400);
      const got=selected.map(s=>expectedLabels.indexOf(s)).sort((a,b)=>a-b);
      const correct=JSON.stringify(got)===JSON.stringify(keys[i]);
      row.correct=correct;
      if(correct)score++;
    }
    data.quiz_score=score;
    data.quiz_total=expectedTotal;
    data.received_at=new Date().toISOString();
    data.submitted_at=data.received_at;
    const receipt=crypto.randomUUID();
    data.receipt=receipt;
    const bytes=new TextEncoder().encode(JSON.stringify(data,null,2));
    let binary='';for(let offset=0;offset<bytes.length;offset+=8192)binary+=String.fromCharCode(...bytes.slice(offset,offset+8192));
    const content=btoa(binary);
    const day=data.received_at.substring(0,10);
    const path=isIca ? `submissions/ica/${day}/${receipt}.json` : isTsne ? `submissions/tsne/${day}/${receipt}.json` : `submissions/${day}/${receipt}.json`;
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
