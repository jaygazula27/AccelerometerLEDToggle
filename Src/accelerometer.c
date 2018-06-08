#include "stm32f4xx.h"
#include "accelerometer.h"
#include "core_cm4.h"

static void gpio_clock_enable(void);
static void gpio_a_init(void);
static void gpio_e_init(void);
static void accelerometer_clock_enable(void);
static void configure_accelerometer(void);
static void select_slave(void);

void accelerometer_init(void) {
    gpio_clock_enable();
    gpio_a_init();
    gpio_e_init();

    accelerometer_clock_enable();
    configure_accelerometer();

    NVIC_EnableIRQ(SPI1_IRQn);
}

void gpio_clock_enable(void) {
    RCC_TypeDef *rcc = RCC;
    rcc->AHB1ENR |= (1 << 0);
}

void gpio_a_init(void) {
    GPIO_TypeDef *gpio_a = GPIOA;

    // Reset mode and set as alternate function
    gpio_a->MODER &= ~(0x3 << 10) & ~(0x3 << 12) & ~(0x3 << 14);
    gpio_a->MODER |= (0x2 << 10) | (0x2 << 12) | (0x2 << 14);

    // Set output to PP
    gpio_a->OTYPER &= ~(1 << 5) & ~(1 << 6) & ~(1 << 7);

    // Set speed to high
    gpio_a->OSPEEDR |= (0x3 << 10) | (0x3 << 12) | (0x3 << 14);

    // Reset pull-up/pull-down and set to pull-down
    gpio_a->PUPDR &= ~(0x3 << 10) & ~(0x3 << 12) & ~(0x3 << 14);
    gpio_a->PUPDR |= (0x2 << 10) | (0x2 << 12) | (0x2 << 14);

    // Reset alternate function and set to SPI
    gpio_a->AFR[0] &= ~(0xF << 20) & ~(0xF << 24) & ~(0xF << 28);
    gpio_a->AFR[0] |= (0x5 << 20) | (0x5 << 24) | (0x5 << 28);
}

void gpio_e_init(void) {
    GPIO_TypeDef *gpio_e = GPIOE;

    // Set as general purpose output mode
    gpio_e->MODER &= ~(0x3 << 6);
    gpio_e->MODER |= (1 << 6);

    // Set as push pull
    gpio_e->OTYPER &= ~(1 << 3);

    // Set as high speed
    gpio_e->OSPEEDR |= (0x3 << 6);

    // Set as pull-up
    gpio_e->PUPDR &= ~(0x3 << 6);
    gpio_e->PUPDR |= (1 << 6);
}

void accelerometer_clock_enable(void) {
    RCC_TypeDef *rcc = RCC;
    rcc->APB2ENR |= (1 << 12);
}

void configure_accelerometer(void) {
    SPI_TypeDef *spi_1 = SPI1;

    // First disable it while we configure SPI
    spi_1->CR1 &= ~(1 << 6);

    // 2-line unidirectional data mode enabled
    spi_1->CR1 &= ~(1 << 15);

    // Reset baud rate and set to fPCLK/16
    // because APB2 peripheral clock currently is 84 MHz
    // and the max clock of the accelerometer is 10 MHz.
    spi_1->CR1 &= ~(0x7 << 3);
    spi_1->CR1 |= (0x3 << 3);

    // Set clock phase to 1
    spi_1->CR1 |= (1 << 0);

    // Set clock polarity to 1
    spi_1->CR1 |= (1 << 1);

    // 8 bit data frame format
    spi_1->CR1 &= ~(1 << 11);

    // MSB first
    spi_1->CR1 &= ~(1 << 7);

    // Software slave management disabled
    spi_1->CR1 &= ~(1 << 9);

    // Master configuration enabled
    spi_1->CR1 |= (1 << 2);

    // Enable RX buffer not empty interrupt
    spi_1->CR2 |= (1 << 6);

    // SS output enabled
    spi_1->CR2 |= (1 << 2);

    // Pull the CS (slave select) low
    select_slave();

    // Enable SPI
    spi_1->CR1 |= (1 << 6);
}

/* Pulls the slave select line low */
void select_slave(void) {
    GPIO_TypeDef *gpio_e = GPIOE;
    gpio_e->BSRR |= (1 << 3);
}
