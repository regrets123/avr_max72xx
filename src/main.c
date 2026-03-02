#include <stdio.h>
#include <util/delay.h>
#include "max72xx.h"
#include "uart.h"

int main() {
	init_serial();
	max7219_init();

	int y = 0;

	while (1) {
		for(int i = 0; i < 16; i++) {
			printf("%d\n", i);

			max7219b_set(i, y);
			max7219b_out();
			
			_delay_ms(500);
		}
	}
	return 0;
}
