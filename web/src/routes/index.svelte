<script context="module">
</script>

<script>
  import Card from "$lib/card.svelte";

  let cards = [3, 4, 5, 6, 7];
</script>

<svelte:head>
  <title>Homeconnect</title>
</svelte:head>

<section id="page">
  <header>
    <h1>Homeconnect</h1>
  </header>
  <main>
    <div class="divider" />
    <Card />
    {#each cards as { card }, i}
      <div class="divider" />
      <Card />
    {/each}
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
    width: 100%;
    grid-template: "header" 10% "main" auto "footer" 30px;
  }
  header {
    z-index: 1;
    position: absolute;
    width: 100%;
    grid-row: header;
    text-align: center;
    background: linear-gradient(white, white, transparent);
  }

  main {
    margin-top: 30px;
    grid-row-start: header;
    grid-row-end: main;
    position: sticky;
    display: flex;
    flex-direction: column;
    align-items: center;
    scroll-snap-type: y proximity;
    overflow-y: auto;
    scrollbar-gutter: stable both-edges;
    scrollbar-width: thin;
    margin-inline: 8px;
  }

  footer::before {
    content: "";
    position: absolute;
    bottom: 0;
    width: 100%;
    height: 100px;
    background: linear-gradient(transparent, white, white);
    pointer-events: none;
  }

  main::-webkit-scrollbar {
    width: 20px;
  }

  main::-webkit-scrollbar-thumb {
    background-color: aliceblue;
    border-radius: 18px;
    border: solid 4px #f1f1f1;
  }

  main::-webkit-scrollbar-thumb:hover {
    background-color: #b3b3b3;
  }

  main > * {
    margin-block: 30px;
  }

  .divider {
    width: 70%;
    height: 5px;
    background-color: black;
    opacity: 0.1;
    border-radius: 2px;
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
