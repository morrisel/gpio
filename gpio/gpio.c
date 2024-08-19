#include "gpio.h"

//#define BASE_PATH "/sys/class/gpio"
#define BASE_PATH "gpio"
#define EXP_PATH BASE_PATH "/export"
#define UNEXP_PATH BASE_PATH "/unexport"


/* gpio_init */
void gpio_init(GPIO *gpio, int number)
{
    gpio->number = number;
    int ret;

    ret = snprintf(gpio->gpioPath, sizeof(gpio->gpioPath), "%s/gpio%d/", BASE_PATH, number);
    if (ret < 0 || ret >= sizeof(gpio->gpioPath))
    {
        printf("Buffer size too small for gpio path\n");
        return;
    }
    gpio_export(gpio);
}

/* gpio_deinit */
void gpio_deinit(GPIO *gpio)
{
    gpio_unexport(gpio);
}

/* gpio_export */
void gpio_export(GPIO *gpio)
{
    FILE *exportFile = fopen(EXP_PATH, "w");
    if (exportFile)
    {
        fprintf(exportFile, "%d", gpio->number);
        fclose(exportFile);
    }
    else
    {
        printf("Unable to export gpio %d\n", gpio->number);
    }
}

/* gpio_unexport */
void gpio_unexport(GPIO *gpio)
{
    FILE *unexportFile = fopen(UNEXP_PATH, "w");
    if (unexportFile)
    {
        fprintf(unexportFile, "%d", gpio->number);
        fclose(unexportFile);
    }
    else
    {
        printf("Unable to unexport gpio %d\n", gpio->number);
    }
}

/* gpio_set_direction */
void gpio_set_direction(GPIO *gpio, const char *direction)
{
    char directionPath[256];
    int ret;

    ret = snprintf(directionPath, sizeof(directionPath), "%s%s", gpio->gpioPath, "direction");
    if (ret < 0 || ret >= sizeof(directionPath))
    {
        printf("Buffer size too small for direction path\n");
        return;
    }

    FILE *directionFile = fopen(directionPath, "w");
    if (directionFile)
    {
        fprintf(directionFile, "%s", direction);
        fclose(directionFile);
    }
    else
    {
        printf("Unable to set direction for gpio %d\n", gpio->number);
    }
}

/* gpio_set_value */
void gpio_set_value(GPIO *gpio, int value)
{
    char valuePath[256];
    int ret;
    ret = snprintf(valuePath, sizeof(valuePath), "%s%s", gpio->gpioPath, "value");
    if (ret < 0 || ret >= sizeof(valuePath))
    {
        printf("Buffer size too small for value path\n");
        return;
    }


    FILE *valueFile = fopen(valuePath, "w");
    if (valueFile)
    {
        fprintf(valueFile, "%d", value);
        fclose(valueFile);
    }
    else
    {
        printf("Unable to set value for gpio %d\n", gpio->number);
    }
}

/* gpio_get_direction */
const char* gpio_get_direction(GPIO *gpio)
{
    static char direction[16];
    char directionPath[256];
    int ret;

    ret = snprintf(directionPath, sizeof(directionPath), "%s%s", gpio->gpioPath, "direction");
    if (ret < 0 || ret >= sizeof(directionPath))
    {
        printf("Buffer size too small for direction path\n");
        return NULL;
    }


    FILE *directionFile = fopen(directionPath, "r");
    if (directionFile)
    {
        if (fgets(direction, sizeof(direction), directionFile) == NULL)
        {
            strcpy(direction, "unknown");
        }

        fclose(directionFile);
    }
    else
    {
        strcpy(direction, "unknown");
    }

    return direction;
}

/* gpio_get_value */
int gpio_get_value(GPIO *gpio)
{
    char valuePath[256];
    int ret;
    ret = snprintf(valuePath, sizeof(valuePath), "%s%s", gpio->gpioPath, "value");
    if (ret < 0 || ret >= sizeof(valuePath))
    {
        printf("Buffer size too small for value path\n");
        return -1;
    }


    FILE *valueFile = fopen(valuePath, "r");
    int value = -1;

    if (valueFile)
    {
        if (fscanf(valueFile, "%d", &value) != 1)
        {
            printf("Error reading value for gpio %d\n", gpio->number);
            value = -1;
        }
        fclose(valueFile);
    }
    else
    {
        printf("Unable to get value for gpio %d\n", gpio->number);
    }

    return value;
}
