#include <esp_camera.h>

const constexpr struct esp32cam_pins
{
  const int pwdn_gpio_num = 32;
  const int reset_gpio_num = -1;
  const int xclk_gpio_num = 0;
  const int siod_gpio_num = 26;
  const int sioc_gpio_num = 27;
  const int y9_gpio_num = 35;
  const int y8_gpio_num = 34;
  const int y7_gpio_num = 39;
  const int y6_gpio_num = 36;
  const int y5_gpio_num = 21;
  const int y4_gpio_num = 19;
  const int y3_gpio_num = 18;
  const int y2_gpio_num = 5;
  const int vsync_gpio_num = 25;
  const int href_gpio_num = 23;
  const int pclk_gpio_num = 22;
  const int internal_led = 4;
} esp32cam_pins;

camera_config_t camera_config = {
    .pin_pwdn = esp32cam_pins.pwdn_gpio_num,
    .pin_reset = esp32cam_pins.reset_gpio_num,
    .pin_xclk = esp32cam_pins.xclk_gpio_num,
    .pin_sscb_sda = esp32cam_pins.siod_gpio_num,
    .pin_sscb_scl = esp32cam_pins.sioc_gpio_num,
    .pin_d7 = esp32cam_pins.y9_gpio_num,
    .pin_d6 = esp32cam_pins.y8_gpio_num,
    .pin_d5 = esp32cam_pins.y7_gpio_num,
    .pin_d4 = esp32cam_pins.y6_gpio_num,
    .pin_d3 = esp32cam_pins.y5_gpio_num,
    .pin_d2 = esp32cam_pins.y4_gpio_num,
    .pin_d1 = esp32cam_pins.y3_gpio_num,
    .pin_d0 = esp32cam_pins.y2_gpio_num,
    .pin_vsync = esp32cam_pins.vsync_gpio_num,
    .pin_href = esp32cam_pins.href_gpio_num,
    .pin_pclk = esp32cam_pins.pclk_gpio_num,

    .xclk_freq_hz = 20000000,

    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_GRAYSCALE,
    .frame_size = FRAMESIZE_SVGA,

    .jpeg_quality = 10,
    .fb_count = 2};
