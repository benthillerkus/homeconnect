<script context="module">
  /** @type {import('@sveltejs/kit').Load} */
  export async function load({ fetch }) {
    const res = await fetch("index.json")
    const content = await res.json()

    return {
      props: {
        data: content.data,
        error: content.error
      }
    }
  }
</script>

<script>
  import Card from "$lib/card.svelte"

  export let data
  export let error
</script>

<svelte:head>
  <title>Homeconnect</title>
</svelte:head>

<section id="page">
  <header>
    <h1>Homeconnect</h1>
  </header>
  <main>
    {#if data}
      <div style="scroll-snap-align: start;" class="divider" />
      <div class="divider" />
      {#each data as { name, id }, i}
        <div class="divider" />
        <Card {name} />
      {/each}
    {:else}
      <code>{JSON.stringify(error)}</code>
    {/if}
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

  header {
    z-index: 1;
    position: absolute;
    width: 100%;
    grid-row: header;
    text-align: center;
    background: linear-gradient(white, white, transparent);
  }

  main {
    position: absolute;
    top: 0;
    height: 100vh;
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

  main:focus {
    outline: none;
  }

  main::-webkit-scrollbar {
    width: 0px;
  }

  @media only screen and (min-width: 500px) {
    main::-webkit-scrollbar {
      width: 20px;
    }

    main::-webkit-scrollbar-track {
      margin-top: 54px;
      margin-bottom: 26px;
    }

    main::-webkit-scrollbar-thumb {
      background-color: aliceblue;
      border-radius: 18px;
      border: solid 4px #f1f1f1;
    }

    main::-webkit-scrollbar-thumb:hover {
      background-color: #b3b3b3;
    }
  }

  main > * {
    margin-block: 15px;
  }

  main > code {
    color-scheme: dark;
    position: absolute;
    top: 45%;
    color: lightcoral;
    background: rgb(52, 45, 66);
    padding: 20px;
    border-radius: 10px;
    border: solid 4px rgba(255, 187, 0, 0.664);
  }

  .divider {
    width: 70%;
    background-color: black;
    opacity: 0.1;
    border-radius: 2px;
  }

  footer {
    display: none;
  }

  @media only screen and (min-width: 500px) {
    footer {
      display: block;
      position: absolute;
      bottom: 0%;
      height: 40px;
      width: 100%;
      background: linear-gradient(transparent, white, white);
    }

    footer small nav {
      display: flex;
      height: 100%;
      justify-content: center;
      align-items: center;
    }

    footer small nav a {
      padding: 0.2rem;
      opacity: 0.5;
      text-decoration: none;
      color: black;
    }
  }
</style>
