#include <util/delay.h>
#include "max72xx.h"


int main()
{
	max7219_init();

	while (1) {
		// Clear an 'I'
		max7219b_clr(3, 2);
		max7219b_clr(3, 3);
		max7219b_clr(3, 4);
		max7219b_clr(3, 5);
		max7219b_clr(3, 6);

		// Draw an 'H'
		max7219b_set(1, 2);
		max7219b_set(1, 3);
		max7219b_set(1, 4);
		max7219b_set(1, 5);
		max7219b_set(1, 6);

		max7219b_set(5, 2);
		max7219b_set(5, 3);
		max7219b_set(5, 4);
		max7219b_set(5, 5);
		max7219b_set(5, 6);

		max7219b_set(2, 4);
		max7219b_set(3, 4);
		max7219b_set(4, 4);

		max7219b_out(); // Push to LED-matrix
		_delay_ms(1000);



		// Clear an 'H'
		max7219b_clr(1, 2);
		max7219b_clr(1, 3);
		max7219b_clr(1, 4);
		max7219b_clr(1, 5);
		max7219b_clr(1, 6);

		max7219b_clr(5, 2);
		max7219b_clr(5, 3);
		max7219b_clr(5, 4);
		max7219b_clr(5, 5);
		max7219b_clr(5, 6);

		max7219b_clr(2, 4);
		max7219b_clr(3, 4);
		max7219b_clr(4, 4);

		// Draw an 'I'
		max7219b_set(3, 2);
		max7219b_set(3, 3);
		max7219b_set(3, 4);
		max7219b_set(3, 5);
		max7219b_set(3, 6);

		max7219b_out(); // Push to LED-matrix
		_delay_ms(1000);
	}
	return 0;
}