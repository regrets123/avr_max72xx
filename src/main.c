#include <avr/interrupt.h>
#include <stdbool.h>
#include "millis.h"
#include "max72xx.h"

int main()
{
 	millis_init();
    sei();

	max7219_init();

	millis_t antalMilliSekunderSenasteBytet = 0;
	millis_t current_millis = 0;
    bool shouldShowH = true;
	bool first = true;

	while (true) {
		current_millis = millis();

		if (first || current_millis - antalMilliSekunderSenasteBytet > 1000) {
			first = false;

			if (shouldShowH) {
				// Clear an 'I'
				max7219b_clr(3,2);
				max7219b_clr(3,3);
				max7219b_clr(3,4);
				max7219b_clr(3,5);
				max7219b_clr(3,6);


				// Draw an 'H'
				max7219b_set(1,2);
				max7219b_set(1,3);
				max7219b_set(1,4);
				max7219b_set(1,5);
				max7219b_set(1,6);

				max7219b_set(5,2);
				max7219b_set(5,3);
				max7219b_set(5,4);
				max7219b_set(5,5);
				max7219b_set(5,6);

				max7219b_set(2,4);
				max7219b_set(3,4);
				max7219b_set(4,4);

				max7219b_out();
			}
			else {
				// Clear an 'H'
				max7219b_clr(1,2);
				max7219b_clr(1,3);
				max7219b_clr(1,4);
				max7219b_clr(1,5);
				max7219b_clr(1,6);

				max7219b_clr(5,2);
				max7219b_clr(5,3);
				max7219b_clr(5,4);
				max7219b_clr(5,5);
				max7219b_clr(5,6);

				max7219b_clr(2,4);
				max7219b_clr(3,4);
				max7219b_clr(4,4);


				// Draw an 'I'
				max7219b_set(3,2);
				max7219b_set(3,3);
				max7219b_set(3,4);
				max7219b_set(3,5);
				max7219b_set(3,6);

				max7219b_out();
			}

			shouldShowH = !shouldShowH;
			antalMilliSekunderSenasteBytet = current_millis;
		}
	}
	return 0;
}
