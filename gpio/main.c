#include <stdio.h>

#include "gpio.h"

/* gpio_init */
/* gpio_deinit */
/* gpio_export */
/* gpio_unexport */

/* gpio_set_direction */
/* gpio_set_value */

/* gpio_get_direction */
/* gpio_get_value */



int main()
{
    GPIO g;
    int input = 0;

    gpio_init(&g, 71);
    gpio_set_direction(&g, "in");

    while(1)
    {
        input = gpio_get_value(&g);
        printf("%d\n", input);
        sleep(1);
    }

    gpio_deinit(&g);


    return 0;
}
