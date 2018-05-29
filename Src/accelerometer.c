#include "stm32f4xx.h"
#include "accelerometer.h"

static void gpio_clock_enable(void);
static void gpio_init(void);
static void accelerometer_clock_enable(void);
static void accelerometer_init(void);

void accelerometer_init(void) {
    gpio_clock_enable();
    gpio_init();

    accelerometer_clock_enable();
    accelerometer_init();
}

void gpio_clock_enable(void) {
    RCC_TypeDef *rcc = RCC;
    rcc->AHB1ENR |= (1 << 0);
}

void gpio_init(void) {
    GPIO_TypeDef *gpio_a = GPIOA;

    // Reset mode and set as alternate function
    gpio_a->MODER &= ~(111111 << 10);
    gpio_a->MODER |= (101010 << 10);

    // Set output to PP (reset state)
    gpio_a->OTYPER &= ~(111 << 5);

    // Set speed to low
    gpio_a->OSPEEDR &= ~(111111 << 10);

    // Reset pull-up/pull-down and set to pull-down
    gpio_a->PUPDR &= ~(111111 << 10);
    gpio_a->PUPDR |= (101010 << 10);

    // Reset alternate function and set to SPI
    gpio_a->AFR[0] &= ~(0xFFF << 20);
    gpio_a->AFR[0] |= (0x555 << 20);
}

void accelerometer_clock_enable(void) {
    RCC_TypeDef *rcc = RCC;
    rcc->APB2ENR |= (1 << 12);
}

void accelerometer_init(void) {
    SPI_TypeDef *spi_1 = SPI1;

    // Reset baud rate and set
    spi_1->CR1 &= ~(111 << 3);
}
