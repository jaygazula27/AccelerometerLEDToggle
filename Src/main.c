#include "stm32f4xx.h"
#include "led.h"
#include "accelerometer.h"

int main(void) {
    led_clock_enable();

    led_init(LED_GREEN);
    led_init(LED_ORANGE);
    led_init(LED_RED);
    led_init(LED_BLUE);

    led_turn_on(LED_GREEN);
    led_turn_on(LED_ORANGE);
    led_turn_on(LED_RED);
    led_turn_on(LED_BLUE);

    accelerometer_init();

    while(1);

    return 0;
}

void SPI1_IRQHandler(void) {
    int i = 5;
    i += 10;
    i += 20;
}
