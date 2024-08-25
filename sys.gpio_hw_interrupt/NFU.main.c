#include "gpio.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#define TX_PIN 15
#define RX_PIN 14
#define SYNC_PIN 13 // sync-pin --> bit-banging model with software interrupt

void send_bit(int bit)
{
    gpio_write(TX_PIN, bit);
    gpio_write(SYNC_PIN, 1);
    usleep(500);
    gpio_write(SYNC_PIN, 0);
    usleep(500);
}

void transmit_data(uint8_t data)
{
    for (int i = 7; i >= 0; i--)
    {
        int bit = (data >> i) & 1;
        send_bit(bit);
    }
}

uint8_t receive_data()
{
    uint8_t data = 0;
    for (int i = 7; i >= 0; i--)
    {
        while (gpio_read(SYNC_PIN) == 0)
            ;

        int bit = gpio_read(RX_PIN);
        data |= (bit << i);

        while (gpio_read(SYNC_PIN) == 1)
            ;

        usleep(500);
    }
    return data;
}

int main()
{
    gpio_export(TX_PIN);
    gpio_export(RX_PIN);
    gpio_export(SYNC_PIN);

    gpio_set_direction(TX_PIN, "out");
    gpio_set_direction(RX_PIN, "in");
    gpio_set_direction(SYNC_PIN, "out");

    uint8_t message[] = {'H', 'i', '!'};
    size_t len = sizeof(message);

    for (size_t i = 0; i < len; i++)
    {
        transmit_data(message[i]);
        usleep(1000000);
        uint8_t received = receive_data();
        printf("Received: %c\n", received);
    }

    gpio_unexport(TX_PIN);
    gpio_unexport(RX_PIN);
    gpio_unexport(SYNC_PIN);

    return 0;
}
