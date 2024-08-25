#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>


void gpio_export(int pin);
void gpio_unexport(int pin);
void gpio_set_direction(int pin, const char *direction);
void gpio_write(int pin, int value);
int gpio_read(int pin);


#endif // GPIO_H
