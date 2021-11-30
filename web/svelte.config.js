import adapter from "@sveltejs/adapter-auto"

/** @type {import('@sveltejs/kit').Config} */
const config = {
  kit: {
    adapter: adapter(),

    vite: {
      define: {
        "process.env": process.env
      }
    },
    trailingSlash: "never",
    serviceWorker: {
      files: _ => true
    }
  }
}

export default config
