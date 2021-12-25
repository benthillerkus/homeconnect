/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-cam-post-image-photo-server/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>

#include "env.h"
#include "less_verbose_camera.h"

WiFiClientSecure client;

uint64_t seconds_to_uS(uint64_t seconds)
{
  return seconds * 1000000;
}

void connect_to_wifi()
{
  Serial.println("Connecting to wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi connected");
  client.setCACert(rootCACert);
}

void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  esp_sleep_enable_timer_wakeup(seconds_to_uS(20 * 60)); // Take a picture every 15 minutes
  Serial.begin(115200);
  pinMode(esp32cam_pins.internal_led, OUTPUT);

#ifdef TEST_FOR_OPEN_FRIDGE // Be stealthy by not taking a picture when the fridge is open
  // setup camera to take a grayscale image to check if the fridge is currently open
  camera_config.pixel_format = PIXFORMAT_GRAYSCALE;
  camera_config.frame_size = FRAMESIZE_CIF;
  camera_config.fb_count = 1;

  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }
  camera_fb_t *fb = NULL;

  // take the image
  Serial.println("Testing light conditions...");
  fb = esp_camera_fb_get();
  if (!fb)
  {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }

  int num_times_too_bright = 0;
  for (size_t i = 1; i < fb->len; i *= 2)
  {
    Serial.print(fb->buf[i]);
    Serial.print(", ");
    if (fb->buf[i] > 32)
    {
      num_times_too_bright++;
    }
  }
  esp_camera_fb_return(fb);
  esp_camera_deinit();

  Serial.printf("The value was %d times too bright\n", num_times_too_bright);
  if (num_times_too_bright > 5)
  {
    Serial.println("Too bright, restarting");
    delay(10000); // wait 10 seconds
    ESP.restart();
  }
#else
  esp_err_t err = NULL;
  camera_fb_t *fb = NULL;
#endif

  // at this point we know we're safe to take a picture with the flashlight
  // init with high specs to pre-allocate larger buffers
  if (psramFound())
  {
    camera_config.frame_size = FRAMESIZE_SVGA;
    camera_config.jpeg_quality = 9; //0-63 lower number means higher quality
    camera_config.fb_count = 2;
    Serial.println("PSRAM found, initializing camera with FRAMESIZE_SVGA and jpeg quality 9");
  }
  else
  {
    camera_config.frame_size = FRAMESIZE_CIF;
    camera_config.jpeg_quality = 12; //0-63 lower number means higher quality
    camera_config.fb_count = 1;
    Serial.println("PSRAM not found, initializing camera with FRAMESIZE_CIF and jpeg quality 12");
  }
  camera_config.pixel_format = PIXFORMAT_JPEG;

  // camera init
  err = esp_camera_init(&camera_config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }

  Serial.println("Taking picture...");
  digitalWrite(esp32cam_pins.internal_led, HIGH);
  delay(100);
  fb = esp_camera_fb_get();
  delay(100);
  digitalWrite(esp32cam_pins.internal_led, LOW);
  if (!fb)
  {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
  }

  // wifi drains the battery quite a bit, so we do it as late as we can
  connect_to_wifi();

  Serial.println("Connecting to server");
  if (!client.connect(host.c_str(), port))
  {
    Serial.println("Connection to server failed!");
  }
  else
  {
    Serial.println("Posting image");
    client.println("POST " + path + " HTTP/1.1");
    client.println("Host: " + host);
    client.println("Content-Type: image/jpeg");
    client.println("Content-Length: " + String(fb->len));
    client.println("Authorization: Bearer " + token);
    client.println("Connection: close");
    client.println();

    uint8_t *fbBuf = fb->buf;
    size_t fbLen = fb->len;
    for (size_t n = 0; n < fbLen; n = n + 1024)
    {
      if (n + 1024 < fbLen)
      {
        client.write(fbBuf, 1024);
        fbBuf += 1024;
      }
      else if (fbLen % 1024 > 0)
      {
        size_t remainder = fbLen % 1024;
        client.write(fbBuf, remainder);
      }
    }

    esp_camera_fb_return(fb);
    esp_camera_deinit();

    Serial.println("Response:");
    while (client.connected())
    {
      String line = client.readStringUntil('\n');
      Serial.println(line);
      if (line == "\r")
      {
        Serial.println("headers received");
        break;
      }
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available())
    {
      char c = client.read();
      Serial.write(c);
    }

    Serial.println("Great Success!");
  }

  Serial.println("BRAVO TANGO DELTA GOING DARK");
  esp_deep_sleep_start();
}

void loop() {}
