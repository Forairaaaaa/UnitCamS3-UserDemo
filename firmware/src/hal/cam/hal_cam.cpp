/**
 * @file hal_cam.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-11-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <mooncake.h>
#include <Arduino.h>
#include "../hal.h"

using namespace HAL;

#include <esp_camera.h>

//
// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//
//            You must select partition scheme from the board menu that has at least 3MB APP space.
//            Face Recognition is DISABLED for ESP32 and ESP32-S2, because it takes up from 15
//            seconds to process single frame. Face Detection is ENABLED if PSRAM is enabled as well

#define CAMERA_MODEL_ESP_EYE
#include "camera_pins.h"

#define CAMERA_MODULE_NAME "M5Stack-Unit-CamS3"
#define CAMERA_PIN_PWDN -1
#define CAMERA_PIN_RESET 21

#define CAMERA_PIN_VSYNC 42
#define CAMERA_PIN_HREF 18
#define CAMERA_PIN_PCLK 12
#define CAMERA_PIN_XCLK 11

#define CAMERA_PIN_SIOD 17
#define CAMERA_PIN_SIOC 41

#define CAMERA_PIN_D0 6
#define CAMERA_PIN_D1 15
#define CAMERA_PIN_D2 16
#define CAMERA_PIN_D3 7
#define CAMERA_PIN_D4 5
#define CAMERA_PIN_D5 10
#define CAMERA_PIN_D6 4
#define CAMERA_PIN_D7 13

#define XCLK_FREQ_HZ 20000000

void hal::_cam_init()
{
    spdlog::info("cam init");

    // camera_config_t config;
    // config.ledc_channel = LEDC_CHANNEL_0;
    // config.ledc_timer = LEDC_TIMER_0;
    // config.pin_d0 = Y2_GPIO_NUM;
    // config.pin_d1 = Y3_GPIO_NUM;
    // config.pin_d2 = Y4_GPIO_NUM;
    // config.pin_d3 = Y5_GPIO_NUM;
    // config.pin_d4 = Y6_GPIO_NUM;
    // config.pin_d5 = Y7_GPIO_NUM;
    // config.pin_d6 = Y8_GPIO_NUM;
    // config.pin_d7 = Y9_GPIO_NUM;
    // config.pin_xclk = XCLK_GPIO_NUM;
    // config.pin_pclk = PCLK_GPIO_NUM;
    // config.pin_vsync = VSYNC_GPIO_NUM;
    // config.pin_href = HREF_GPIO_NUM;
    // config.pin_sccb_sda = SIOD_GPIO_NUM;
    // config.pin_sccb_scl = SIOC_GPIO_NUM;
    // config.pin_pwdn = PWDN_GPIO_NUM;
    // config.pin_reset = RESET_GPIO_NUM;
    // config.xclk_freq_hz = 20000000;

    // // config.frame_size = FRAMESIZE_UXGA;
    // config.frame_size = FRAMESIZE_VGA;
    // // config.frame_size = FRAMESIZE_QVGA;

    // config.pixel_format = PIXFORMAT_JPEG; // for streaming
    // // config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
    // config.grab_mode = CAMERA_GRAB_LATEST;
    // config.fb_location = CAMERA_FB_IN_PSRAM;
    // config.jpeg_quality = 16;
    // config.fb_count = 1;

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = CAMERA_PIN_D0;
    config.pin_d1 = CAMERA_PIN_D1;
    config.pin_d2 = CAMERA_PIN_D2;
    config.pin_d3 = CAMERA_PIN_D3;
    config.pin_d4 = CAMERA_PIN_D4;
    config.pin_d5 = CAMERA_PIN_D5;
    config.pin_d6 = CAMERA_PIN_D6;
    config.pin_d7 = CAMERA_PIN_D7;
    config.pin_xclk = CAMERA_PIN_XCLK;
    config.pin_pclk = CAMERA_PIN_PCLK;
    config.pin_vsync = CAMERA_PIN_VSYNC;
    config.pin_href = CAMERA_PIN_HREF;
    config.pin_sscb_sda = CAMERA_PIN_SIOD;
    config.pin_sscb_scl = CAMERA_PIN_SIOC;
    config.pin_pwdn = CAMERA_PIN_PWDN;
    config.pin_reset = CAMERA_PIN_RESET;
    config.xclk_freq_hz = XCLK_FREQ_HZ;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        // Serial.printf("Camera init failed with error 0x%x", err);
        printf("Camera init failed with error 0x%x\n", err);

        // Retry
        spdlog::info("reboot..");
        delay(1000);
        esp_restart();
    }

    // sensor_t* s = esp_camera_sensor_get();
    // s->set_vflip(s, 1);
    // s->set_hmirror(s, 1);

    spdlog::info("cam init ok");
    delay(100);

    // /* -------------------------------------------------------------------------- */
    // /*                                    Test                                    */
    // /* -------------------------------------------------------------------------- */
    // while (1)
    // {
    //     delay(500);

    //     camera_fb_t* fb = esp_camera_fb_get();
    //     if (fb == NULL)
    //     {
    //         printf("Camera frame failed\n");
    //     }
    //     else
    //     {
    //         printf("cap ok\n");
    //         esp_camera_fb_return(fb);
    //     }
    // }
}
