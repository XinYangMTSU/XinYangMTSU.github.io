import './App.css'; // Import CSS for styling

function App() {
  return (
    <div className="app-container">
      {/* Header Section */}
      <header className="header">Header</header>

      {/* Main Layout (Left & Right Columns) */}
      <div className="main-content">
        <aside className="left-column">
        <h3>Did You Know?</h3>
          <ul className="cat-facts">
            <li>Cats sleep for about 13–16 hours a day.</li>
            <li>A cat’s purr can have healing properties.</li>
            <li>The oldest known pet cat existed 9,500 years ago.</li>
            <li>Cats can rotate their ears 180 degrees.</li>
            <li>The world's largest cat breed is the Maine Coon.</li>
          </ul>
        </aside>
        <section className="right-column">
        <h2>Maine Coon Cat</h2>
        <img 
            src="https://cdn2.thecatapi.com/images/MTY3ODIyMQ.jpg" 
            alt="Maine Coon Cat" 
            className="cat-image"
        />
          <p>
            The Maine Coon is one of the largest domesticated cat breeds. It has 
            a distinctive appearance with a long, luxurious coat, tufted ears, and 
            a bushy tail. Known for its friendly and intelligent nature, this breed 
            is often referred to as the "gentle giant" of the cat world.
          </p>
        </section>
      </div>

      {/* Footer Section */}
      <footer className="footer">Footer</footer>
    </div>
  );
}

export default App;
