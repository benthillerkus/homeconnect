<script context="module">
  /** @type {import('@sveltejs/kit').Load} */
  export async function load({ page, fetch }) {
    const res = await fetch("/api/v1/images", {
      headers: {
        authorization: `Bearer ${page.params.feed}`
      }
    })

    if (res.status !== 200) {
      return {
        status: 302,
        redirect: "/"
      }
    }

    const content = await res.json()

    return {
      status: 200,
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

<main>
  {#if data}
    {#each data as data, i}
      <Card {data} />
    {/each}
  {:else}
    <code>{JSON.stringify(error)}</code>
  {/if}
</main>

<style>
  main {
    position: absolute;
    padding-top: 70px;
    padding-bottom: 70px;
    height: 100vh;
    position: sticky;
    display: flex;
    gap: 3rem;
    flex-direction: column;
    align-items: center;
    overflow-y: auto;
    scrollbar-gutter: stable both-edges;
    scrollbar-width: thin;
  }

  main:focus {
    outline: none;
  }

  main::-webkit-scrollbar {
    width: 0px;
  }

  @media only screen and (min-width: 500px) {
    main {
      margin-inline: 8px;
    }

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
</style>
