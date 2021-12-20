# homeconnect

Inoffizielle Implementierung des use-cases "Inhalt des Kühlschranks *quasi* in Realtime auf dem Handy sehen".

# Setup

## Web

Vorraussetzungen:
- Es wird ein Account / Projekt bei [Supabase](https://supabase.com) benötigt
  - Stell sicher, dass ein Storage-Bucket mit dem Namen `images` vorhanden ist
  - Die Sicherheitseinstellungen für den Bucket müssen öffentlichen Zugriff erlauben 
- Für's Hosten bietet sich [Vercel](https://vercel.com) oder [Netlify](https://www.netlify.com)[^1] an
- [NodeJS](https://nodejs.org) muss installiert sein

```Bash
cd web
npm install
npm run dev
```

### Umgebungsvariablen

Ein `.env`-File mit Umgebungsvariablen wird im [`web`](web)-Verzeichnis platziert.
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
 VITE_HOMECONNECT_ALLOW_VIEW="" // ^^
 ```
 
 ## Embedded

Vorraussetzungen:
- [PlatformIO](https://platformio.org) muss installiert sein

### Umgebungsvariablen

Im Header [`embedded/include/env.h`](embedded/include/env.h) liegen alle Konfigurationsvariablen.

```
|_ embedded
  |_ include
    |_ env.h
    |_ README
  | //
  |_ src
    |_ main.cpp
|_ web
 ```
 
 ```C++
// Für HTTPS wird das Root-Zertifikat des Webservers gebraucht. In meinem Fall ist die Kette Vercel -> Cloudflare -> Let's Encrypt
const constexpr char *rootCACert = R"(-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
// ....
// ....
-----END CERTIFICATE-----
)";

const constexpr char *ssid = "mySSID"; // Die SSID des WLANs in dem der ESP32-Cam laufen soll
const constexpr char *password = "myPASS"; // Das Wifipasswort
const String token = "bearerTOKEN"; // Der Wert aus VITE_HOMECONNECT_ALLOW_POST
const String host = "bla.com"; // In meinem Fall homeconnect.bent.party
const String path = "https://" + host + "/api/v1/images";
const constexpr uint16_t port = 443;

 ```

# Weblinks

- [Original](https://youtu.be/5EVf9a-nji4)
- [Figma](https://figma.com/file/rZGK06YEz8hBJKbGzTQDFX/homeconnect)
- [Webapp](https://homeconnect.bent.party)

[^1]: Nicht ausprobiert. Wahrscheinlich geht sogar auch Cloudflare; man kann das ganze aber auch natürlich selber hosten oder lokal laufen lassen.
