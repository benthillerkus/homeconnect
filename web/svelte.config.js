import adapter from "@sveltejs/adapter-auto";

/** @type {import('@sveltejs/kit').Config} */
const config = {
  kit: {
    adapter: adapter(),

    vite: {
      envPrefix: "NEXT_", // lol
      define: {
        "process.env": process.env
      }
    }
  }
};

export default config;
