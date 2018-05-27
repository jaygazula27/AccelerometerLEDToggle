#include "stm32f4xx.h"
#include "led.h"

void led_clock_enable(void) {
    RCC_TypeDef *rcc = RCC;
    rcc->AHB1ENR |= (1 << 3);
}

void led_init(LED_ENUM led) {
    GPIO_TypeDef *gpio = GPIOD;
    gpio->MODER |= (01 << (led * 2));
}

void led_turn_on(LED_ENUM led) {
    GPIO_TypeDef *gpio = GPIOD;
    gpio->ODR |= (1 << led);
}

void led_turn_off(LED_ENUM led) {
    GPIO_TypeDef *gpio = GPIOD;
    gpio->ODR &= ~(1 << led);
}

void led_toggle(LED_ENUM led) {
    GPIO_TypeDef *gpio = GPIOD;
    gpio->ODR ^= (1 << led);
}
