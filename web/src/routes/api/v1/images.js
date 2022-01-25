import { supabase } from "$lib/_db.js"
import { v4 as uuidv4 } from "uuid"

const bucketName = "images"

/** @type {import('@sveltejs/kit').RequestHandler} */
export async function post({ request }) {
  if (request.headers.authorization === `Bearer ${import.meta.env.VITE_HOMECONNECT_ALLOW_POST}`) {
    const { data, error } = await supabase.storage
      .from(bucketName)
      .upload(uuidv4(), request.rawBody, {
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

/** @type {import('@sveltejs/kit').RequestHandler} */
export async function get({request}) {
  let headers = (await request).headers
  if (headers.get("authorization") === `Bearer ${import.meta.env.VITE_HOMECONNECT_ALLOW_VIEW}`) {
    const res = await supabase.storage.from(bucketName).list("", {
      sortBy: { column: "created_at", order: "desc" }
    })

    res.data?.forEach(image => {
      // image.url = supabase.storage.from("images").getPublicUrl(image.id).publicURL
      image.url = `${
        import.meta.env.VITE_PUBLIC_SUPABASE_URL
      }/storage/v1/object/public/${bucketName}/${image.name}`
      delete image.id
      delete image.last_accessed_at
      delete image.last_modified_at
      delete image.updated_at
    })

    return {
      status: res.status,
      headers: new Headers({
        "content-type": "application/json"
      }),
      body: JSON.stringify(res)
    }
  } else {
    return {
      status: 401,
      body: "Invalid Authorization Token"
    }
  }
}
