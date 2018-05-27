#ifndef LED_H_
#define LED_H_

typedef enum {
    LED_GREEN = 12,
    LED_ORANGE = 13,
    LED_RED = 14,
    LED_BLUE = 15
} LED_ENUM;

void led_clock_enable(void);

void led_init(LED_ENUM);

void led_turn_on(LED_ENUM);

void led_turn_off(LED_ENUM);

void led_toggle(LED_ENUM);

#endif /* LED_H_ */
