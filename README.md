# homeconnect

> Gilt das auch für den Kühlschrank, Herr Schöllhorn?

Inoffizielle Implementierung des use-cases "Inhalt des Kühlschranks *quasi* in Realtime auf dem Handy sehen".

# Setup

## Embedded

## Web

Vorraussetzungen:
- Es wird ein Account / Projekt bei Supabase benötigt
  - Stell sicher, dass ein Storage-Bucket mit dem Namen `images` vorhanden ist
  - Die Sicherheitseinstellungen für den Bucket müssen öffentlichen Zugriff erlauben 
- Für's Hosten bietet sich Vercel oder Netlify[^1] an
- NodeJS muss installiert sein

```Bash
cd web
npm install
npm run dev
```

### Umgebungsvariablen

Ein `.env`-File mit Umgebungsvariablen wird im `web`-Verzeichnis platziert.
Bei Vercel kann man die dann in den Projekteinstellungen auch eintragen und sich über die Supabase-Integration auch automatisch holen.

```
|_ embedded
|_ web
  |_ src
  |_ .gitignore
  | //
  |_ .env
 ```
 
 Die Schlüssel brauchen den Präfix `VITE_` um von Vite gesehen zu werden.
 
 ```
 VITE_PUBLIC_SUPABASE_ANON_KEY=""
 SUPABASE_SERVICE_ROLE_KEY="" // Wird nicht benutzt; trotzdem vorsichtig mit dem!
 VITE_PUBLIC_SUPABASE_URL=""
 VITE_HOMECONNECT_ALLOW_POST="" // Nicht von Supabase; denk dir einen aus.
 ```

# Weblinks

- [Original](https://youtu.be/5EVf9a-nji4)
- [Figma](https://www.figma.com/file/rZGK06YEz8hBJKbGzTQDFX/homeconnect)
- [Webapp](https://www.homeconnect.bent.party)

[^1]: Nicht ausprobiert. Wahrscheinlich geht sogar auch Cloudflare; man kann das ganze aber auch natürlich selber hosten oder lokal laufen lassen.
