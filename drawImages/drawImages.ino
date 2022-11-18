/* Simple firmware for a ESP32 displaying a static image on an EPaper Screen.
 *
 * Write an image into a header file using a 3...2...1...0 format per pixel,
 * for 4 bits color (16 colors - well, greys.) MSB first.  At 80 MHz, screen
 * clears execute in 1.075 seconds and images are drawn in 1.531 seconds.
 */

#include <Arduino.h>
#include "epd_driver.h"
#include "pic1.h"
#include "pic2.h"
#include "pic3.h"
#include "pic4.h"
/*#include "pic5.h"
#include "pic6.h"
#include "pic7.h"
#include "pic8.h"
#include "pic9.h"
#include "pic10.h"*/

uint8_t *framebuffer;

void setup()
{
    Serial.begin(115200);

    epd_init();

    framebuffer = (uint8_t *)heap_caps_malloc(EPD_WIDTH * EPD_HEIGHT / 2, MALLOC_CAP_SPIRAM);
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

}

void update(uint32_t delay_ms)
{
    epd_poweron();
    epd_clear();
    volatile uint32_t t1 = millis();
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    volatile uint32_t t2 = millis();
    Serial.printf("EPD draw took %dms.\n", t2 - t1);
    epd_poweroff();
    delay(delay_ms);
}

void loop()
{
    Rect_t area = {
        .x = 0,
        .y = 0,
        .width = pic1_width,
        .height =  pic1_height
    };
    epd_poweron();
    epd_clear();
    epd_draw_grayscale_image(area, (uint8_t *) pic1_data);
    epd_poweroff();
    delay(3000);

    Rect_t area1 = {
        .x = 0,
        .y = 0,
        .width = pic2_width,
        .height =  pic2_height
    };
    epd_copy_to_framebuffer(area1, (uint8_t *) pic2_data, framebuffer);

    update(3000);

    Rect_t area2 = {
        .x = 0,
        .y = 0,
        .width = pic3_width,
        .height =  pic3_height
    };
    epd_copy_to_framebuffer(area2, (uint8_t *) pic3_data, framebuffer);

    update(3000);

    Rect_t area3 = {
        .x = 0,
        .y = 0,
        .width = pic4_width,
        .height =  pic4_height
    };
    epd_copy_to_framebuffer(area3, (uint8_t *) pic4_data, framebuffer);

    update(3000);

    /*Rect_t area4 = {
        .x = 0,
        .y = 0,
        .width = pic5_width,
        .height =  pic5_height
    };
    epd_copy_to_framebuffer(area4, (uint8_t *) pic5_data, framebuffer);

    update(3000);

    Rect_t area5 = {
        .x = 0,
        .y = 0,
        .width = pic6_width,
        .height =  pic6_height
    };
    epd_copy_to_framebuffer(area5, (uint8_t *) pic6_data, framebuffer);

    update(3000);

    Rect_t area6 = {
        .x = 0,
        .y = 0,
        .width = pic7_width,
        .height =  pic7_height
    };
    epd_copy_to_framebuffer(area6, (uint8_t *) pic7_data, framebuffer);

    update(3000);

    Rect_t area7 = {
        .x = 0,
        .y = 0,
        .width = pic8_width,
        .height =  pic8_height
    };
    epd_copy_to_framebuffer(area7, (uint8_t *) pic8_data, framebuffer);

    update(3000);

    Rect_t area8 = {
        .x = 0,
        .y = 0,
        .width = pic9_width,
        .height =  pic9_height
    };
    epd_copy_to_framebuffer(area8, (uint8_t *) pic9_data, framebuffer);

    update(3000);

    Rect_t area9 = {
        .x = 0,
        .y = 0,
        .width = pic10_width,
        .height =  pic10_height
    };
    epd_copy_to_framebuffer(area9, (uint8_t *) pic10_data, framebuffer);

    update(3000);*/
}
