#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "max72xx.h"
#include "analogRead.h"
#include "millis.h"
#include "uart.h"

#define VEC2_ADD(a, b) (Vec2){ (a).x + (b).x, (a).y + (b).y }
#define TICDURATION 500

#define BIT(bit)              (1 << (bit))
#define REG_SET(reg, bit)     ((reg) |=  BIT(bit))
#define REG_CLEAR(reg, bit)   ((reg) &= ~BIT(bit))
#define REG_CHECK(reg, bit)   ((reg) &   BIT(bit))
#define REG_FLIP(reg, bit)    ((reg) ^   BIT(bit))

#define VERT_INP PC0
#define HORZ_INP PC1

#define GRID_W 16
#define GRID_H 8

typedef struct {
    int x, y;
} Vec2;

Vec2 positions[4] = { // 0 head 2 tail.
    {2, 2},
    {1, 2},
    {0, 2},
	{0,0}
};

Vec2 GetInput()
{
    Vec2 toReturn;
    int x = analogRead(HORZ_INP);
    int y = analogRead(VERT_INP);

    toReturn.x = (x < 512) ? 1 : (x > 512) ? -1 : 0;
    toReturn.y = (y < 512) ? 1 : (y > 512) ? -1 : 0;
	printf("x is %d y is %d", toReturn.x, toReturn.y);
    return toReturn;
}

void MoveSnake(Vec2 newInput) {
	positions[3] = positions[2];
    positions[2] = positions[1];
    positions[1] = positions[0];
    positions[0] = VEC2_ADD(positions[0], newInput);

	if (positions[0].x >= GRID_W) positions[0].x = 0;
    if (positions[0].x < 0)       positions[0].x = GRID_W - 1;
    if (positions[0].y >= GRID_H) positions[0].y = 0;
    if (positions[0].y < 0)       positions[0].y = GRID_H - 1;
}

void UpdateGrid()
{
	for (int i = 0; i < 4; i++){
		max7219b_set(positions[i].x, positions[i].y);
		if (i == 3){
			max7219b_clr(positions[i].x, positions[i].y);
		}
	}
	max7219b_out();
}

int main() {
	init_serial();
	millis_init();
	max7219_init();
	sei();

	REG_SET(DDRC, VERT_INP);
	REG_SET(DDRC, HORZ_INP);

	uint16_t count = 0;
	int previous;
	Vec2 prevInput = {1,0};
	while (1) {

		count = millis_get();
		if(count - previous >= TICDURATION)
		{
			Vec2 input = GetInput();
			if(input.x == 0 && input.y == 0)
			{
				input = prevInput;
			}
			prevInput = input;
			MoveSnake(prevInput);
			UpdateGrid();
			previous = count;
		}
	}
	return 0;
}
