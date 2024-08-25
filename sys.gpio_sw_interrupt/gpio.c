#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 256

void gpio_export(int pin) {
    char buffer[BUFFER_SIZE];
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0)
    {
        perror("Failed to export GPIO");
        exit(1);
    }
    snprintf(buffer, BUFFER_SIZE, "%d", pin);
    write(fd, buffer, sizeof(buffer));
    close(fd);
}

void gpio_unexport(int pin)
{
    char buffer[BUFFER_SIZE];
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0)
    {
        perror("Failed to unexport GPIO");
        exit(1);
    }
    snprintf(buffer, BUFFER_SIZE, "%d", pin);
    write(fd, buffer, sizeof(buffer));
    close(fd);
}

void gpio_set_direction(int pin, const char *direction)
{
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "/sys/class/gpio/gpio%d/direction", pin);
    int fd = open(buffer, O_WRONLY);
    if (fd < 0)
    {
        perror("Failed to set GPIO direction");
        exit(1);
    }
    write(fd, direction, strlen(direction));
    close(fd);
}

void gpio_write(int pin, int value)
{
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "/sys/class/gpio/gpio%d/value", pin);
    int fd = open(buffer, O_WRONLY);
    if (fd < 0)
    {
        perror("Failed to write to GPIO");
        exit(1);
    }
    snprintf(buffer, BUFFER_SIZE, "%d", value);
    write(fd, buffer, sizeof(buffer));
    close(fd);
}

int gpio_read(int pin)
{
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "/sys/class/gpio/gpio%d/value", pin);
    int fd = open(buffer, O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to read from GPIO");
        exit(1);
    }
    read(fd, buffer, sizeof(buffer));
    close(fd);
    return atoi(buffer);
}

