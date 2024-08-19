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

#define DIRECTION_PATH "direction"
#define VALUE_PATH "value"
//#define BASE_PATH "/sys/class/gpio"
#define BASE_PATH "gpio"



int main()
{

    char path[128];
    int gpio_dir_id=71;

//    snprintf(path, sizeof(path), "%s/gpio%d/%s", BASE_PATH, gpio_dir_id, DIRECTION_PATH);
//    printf("directon: %s\n", path);
//
//
//    snprintf(path, sizeof(path), "%s/gpio%d/%s", BASE_PATH, gpio_dir_id, VALUE_PATH);
//    printf("value: %s\n", path);

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
