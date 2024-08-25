#include "gpio.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#define TX_PIN 15
#define SYNC_PIN 13

void send_bit(int bit)
{
	gpio_write(TX_PIN, bit);
	gpio_write(SYNC_PIN, 1);
	printf("Sent bit: %d\n", bit);
	usleep(500000);
	gpio_write(SYNC_PIN, 0);
	usleep(500000);
}

void transmit_data(uint8_t data)
{
	for (int i = 7; i >= 0; i--)
	{
		int bit = (data >> i) & 1;
		send_bit(bit);
	}
}

int main()
{
	gpio_export(TX_PIN);
	gpio_export(SYNC_PIN);

	gpio_set_direction(TX_PIN, "out");
	gpio_set_direction(SYNC_PIN, "out");

	uint8_t message[] = {'H', 'i', '!'};
	size_t len = sizeof(message);

	for (size_t i = 0; i < len; i++)
	{
		printf("Transmitting byte: %c\n", message[i]);
		transmit_data(message[i]);
		usleep(1000000);
	}

	gpio_write(TX_PIN, 0);
	gpio_write(SYNC_PIN, 0);

	gpio_unexport(TX_PIN);
	gpio_unexport(SYNC_PIN);

	return 0;
}
