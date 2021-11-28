const constexpr char *rootCACert = R"(-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
-----END CERTIFICATE-----
)";

const constexpr char *ssid = "mySSID";
const constexpr char *password = "myPASS";
const String token = "bearerTOKEN";
const String host = "bla.com";
const String path = "https://" + host + "/api/v1/images";
const constexpr uint16_t port = 443;
