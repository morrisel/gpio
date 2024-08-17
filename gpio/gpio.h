#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


struct GPIO
{
    int number;
    char gpioPath[64];
};

#define GPIO struct GPIO


/* gpio_init */
void gpio_init(GPIO *gpio, int number);

/* gpio_deinit */
void gpio_deinit(GPIO *gpio);

/* gpio_export */
void gpio_export(GPIO *gpio);

/* gpio_unexport */
void gpio_unexport(GPIO *gpio);

/* gpio_set_direction */
void gpio_set_direction(GPIO *gpio, const char *direction);

/* gpio_set_value */
void gpio_set_value(GPIO *gpio, int value);


/* gpio_get_direction */
const char* gpio_get_direction(GPIO *gpio);

/* gpio_get_value */
int gpio_get_value(GPIO *gpio);


#endif  /* GPIO_H */
