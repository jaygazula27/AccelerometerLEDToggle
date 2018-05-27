#include "stm32f4xx.h"
#include "led.h"

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

    while(1);

    return 0;
}
