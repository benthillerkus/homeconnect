import { createClient } from "@supabase/supabase-js";

console.log(import.meta.env.NEXT_PUBLIC_SUPABASE_URL, import.meta.env.NEXT_PUBLIC_SUPABASE_ANON_KEY)

export const supabase = createClient(
  import.meta.env.NEXT_PUBLIC_SUPABASE_URL,
  import.meta.env.NEXT_PUBLIC_SUPABASE_ANON_KEY
);
