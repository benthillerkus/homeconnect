<script context="module">
</script>

<script>
  import Card from "$lib/card.svelte";
</script>

<section id="page">
  <header>
    <h1>Homeconnect</h1>
  </header>
  <main>
    <Card />
  </main>
  <footer>
    <small>
      <nav>
        <a>about</a>
        <a href="https://github.com/benthillerkus/homeconnect">source</a>
        <a>licenses</a>
      </nav>
    </small>
  </footer>
</section>

<style>
  :global(body) {
    margin: 0;
    padding: 0;
    font-family: sans-serif;
    color-scheme: light;
  }

  #page {
    display: grid;
    height: 100vh;
    width: 100vw;
    grid-template: "header" 10% "main" auto "footer" 30px;
  }
  header {
    grid-row: header;
    text-align: center;
  }

  main {
    grid-row: main;
    display: flex;
    flex-direction: column;
    align-items: center;
  }

  footer {
    grid-row: footer;
    display: flex;
    justify-content: center;
  }

  footer small nav a {
    padding: 0.2rem;
    opacity: 0.5;
    text-decoration: none;
    color: black;
  }
</style>
