#include "gpio.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#define RX_PIN 14
#define SYNC_PIN 13

uint8_t receive_data() {
	uint8_t data = 0;
	for (int i = 7; i >= 0; i--) {
		while (gpio_read(SYNC_PIN) == 0);
		int bit = gpio_read(RX_PIN);
		data |= (bit << i);
		printf("Received bit: %d\n", bit);
		while (gpio_read(SYNC_PIN) == 1);
		usleep(500000);
	}
	return data;
}

int main() {
	gpio_export(RX_PIN);
	gpio_export(SYNC_PIN);

	gpio_set_direction(RX_PIN, "in");
	gpio_set_direction(SYNC_PIN, "out");

	for (int i = 0; i < 3; i++)
	{
		printf("Receiving byte %d...\n", i + 1);
		uint8_t received = receive_data();
		printf("Received byte: %c\n", received);
		usleep(1000000);
	}

	gpio_unexport(RX_PIN);
	gpio_unexport(SYNC_PIN);

	return 0;
}

