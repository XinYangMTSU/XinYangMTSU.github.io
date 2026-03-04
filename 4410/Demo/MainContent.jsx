import {useState} from "react";

function HandleForm(){

    const [name, setName] = useState("");
    const [email, setEmail] = useState("");

    function handleSubmit(event){
        event.preventDefault();
        alert(`Name: ${name} \nEmail: ${email}`);
        setName("");
        setEmail("");
    }


    return(
        <div style={{textAlign: "center", marginTop: "20px"}}>
          <h1>Simple Form</h1>
          <form onSubmit={handleSubmit}>
              <input type="text" value={name} onChange={(event) => setName(event.target.value)} placeholder="Enter your name" style={{display: "block", margin: "10px auto", padding: "8px"}}/>
              <input type="email" value={email} onChange={(event) => setEmail(event.target.value)} placeholder="Enter your email" style={{display: "block", margin: "10px auto", padding: "8px"}}/>
              <button type="submit">Submit</button>
          </form>
        </div>
    );
}

function HandleInput(){
    const [text, setText] = useState("");

    function handleChange(event){
      setText(event.target.value);
    }

    return(
        <div>
            <h2>Type Something: </h2>
            <input type="text" value={text} onChange={handleChange} />
            <p>You typed: {text} </p>
        </div>
    );
}

function handleClick(name){
    alert(`Hello, ${name}!`);
}

function Counter(){
    const [count, setCount] = useState(0);

    return(
        <div>
            <h2>React Counter</h2>
            <p>Count: {count}</p>
            <button onClick={() => setCount(count + 1)}>Increase</button>
            <button onClick={() => setCount(count - 1)}>Decrease</button>
            <button onClick={() => setCount(0)}>Reset</button>
        </div>
    );
}

function Welcome({name = "Guest", age, profession}){
  return(
      <div>
        <h2>Hello, {name}</h2>
        <p>Age: {age}</p>
        <p>Profession: {profession}</p>
      </div>
  );
}

function MainContent(){
  return(
      <main style={{padding: "20px", textAlign: "center", minHeight: "400px"}}>
        <h2>Welcome to My Website</h2>
        <p>This is a simple React app demonstrating component structure.</p>
        <Welcome name="Alice" age={18} profession="student"/>
        <Welcome age={18} profession="student"/>
        <Counter />
        <h2>Click Event Example</h2>
        <button onClick={() => handleClick("Alice")}>Click Me!</button>
        <br />
        <HandleInput />
        <HandleForm />
      </main>
  );
}

export default MainContent;
