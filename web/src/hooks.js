import { supabase } from "$lib/_db.js"

/** @type {import('@sveltejs/kit').Handle} */
export async function handle({ request, resolve }) {
  if (request.method === "POST") {
    if (request.headers.authorization === `Bearer ${import.meta.env.VITE_HOMECONNECT_ALLOW_POST}`) {
      const { data, error } = await supabase.storage
        .from("images")
        .upload(request.headers.name, request.rawBody, {
          contentType: request.headers["content-type"]
        })

      if (error) {
        console.error(error)
        return {
          status: 500
        }
      }

      return {
        status: 200,
        body: JSON.stringify(data)
      }
    } else {
      return {
        status: 401,
        body: "Invalid Authorization Token"
      }
    }
  }

  const response = await resolve(request)

  return {
    ...response
  }
}
