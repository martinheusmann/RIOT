/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_stm32f1
 * @{
 *
 * @file
 * @brief           CPU specific definitions for internal peripheral handling
 *
 * @author          Hauke Petersen <hauke.peterse@fu-berlin.de>
 */

#ifndef PERIPH_CPU_H
#define PERIPH_CPU_H

#include "periph_cpu_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Available number of ADC devices
 */
#define ADC_DEVS            (2U)

/**
 * @brief   Overwrite the default gpio_t type definition
 * @{
 */
#define HAVE_GPIO_T
typedef uint32_t gpio_t;
/** @} */

/**
 * @brief   Definition of a fitting UNDEF value
 */
#define GPIO_UNDEF          (0xffffffff)

/**
 * @brief   Define a CPU specific GPIO pin generator macro
 */
#define GPIO_PIN(x, y)      ((GPIOA_BASE + (x << 10)) | y)

/**
 * @brief   All timers for the STM32F1 have 4 CC channels
 */
#define TIMER_CHANNELS      (4U)

/**
 * @brief   All timers have a width of 16-bit
 */
#define TIMER_MAXVAL        (0xffff)

/**
 * @brief   Override values for pull register configuration
 * @{
 */
#define HAVE_GPIO_PP_T
typedef enum {
    GPIO_NOPULL = 4,        /**< do not use internal pull resistors */
    GPIO_PULLUP = 9,        /**< enable internal pull-up resistor */
    GPIO_PULLDOWN = 8       /**< enable internal pull-down resistor */
} gpio_pp_t;
/** @} */

/**
 * @brief   Override flank configuration values
 * @{
 */
#define HAVE_GPIO_FLANK_T
typedef enum {
    GPIO_RISING = 1,        /**< emit interrupt on rising flank */
    GPIO_FALLING = 2,       /**< emit interrupt on falling flank */
    GPIO_BOTH = 3           /**< emit interrupt on both flanks */
} gpio_flank_t;
/** @} */

/**
 * @brief   Available ports on the STM32F1 family
 */
enum {
    PORT_A = 0,             /**< port A */
    PORT_B = 1,             /**< port B */
    PORT_C = 2,             /**< port C */
    PORT_D = 3,             /**< port D */
    PORT_E = 4,             /**< port E */
    PORT_F = 5,             /**< port F */
    PORT_G = 6,             /**< port G */
};

/**
 * @brief   Define alternate function modes
 *
 * On this CPU, only the output pins have alternate function modes. The input
 * pins have to be configured using the default gpio_init() function.
 */
typedef enum {
    GPIO_AF_OUT_PP = 0xb,   /**< alternate function output - push-pull */
    GPIO_AF_OUT_OD = 0xf,   /**< alternate function output - open-drain */
} gpio_af_out_t;

/**
 * @brief   ADC channel configuration data
 */
typedef struct {
    gpio_t pin;             /**< pin connected to the channel */
    uint8_t dev;            /**< ADCx - 1 device used for the channel */
    uint8_t chan;           /**< CPU ADC channel connected to the pin */
} adc_conf_t;

/**
 * @brief   Timer configuration
 */
typedef struct {
    TIM_TypeDef *dev;       /**< timer device */
    uint8_t bus;            /**< APBx bus the timer is clock from */
    uint8_t rcc_bit;        /**< corresponding bit in the RCC register */
    uint8_t irqn;           /**< global IRQ channel */
} timer_conf_t;

/**
 * @brief   Configure the alternate function for the given pin
 *
 * @note    This is meant for internal use in STM32F1 peripheral drivers only
 *
 * @param[in] pin       pin to configure
 * @param[in] af        alternate function to use
 */
void gpio_init_af(gpio_t pin, gpio_af_out_t af);

/**
 * @brief   Configure the given pin to be used as ADC input
 *
 * @param[in] pin       pin to configure
 */
void gpio_init_analog(gpio_t pin);

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CPU_H_ */
/** @} */
