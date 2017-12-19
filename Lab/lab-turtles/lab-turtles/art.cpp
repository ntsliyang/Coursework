#include "turtle.h"
#include <cmath>
#include <iostream>

void draw_lines(Turtle, int);

int main() {
	draw::setpenwidth(3); // thick lines
	draw::setrange(-100, 100);

	Turtle first(0, 0, 0);
	Turtle second(0, 60, 0);
	Turtle third(0, -60, 0);
	Turtle fourth(-60, 0, 0);
	Turtle fifth(60, 0, 0);

	first.setColor(draw::BLUE);
	second.setColor(draw::ORANGE);
	third.setColor(draw::RED);
	fourth.setColor(draw::GREEN);
	fifth.setColor(draw::VIOLET);

	draw_lines(first, 1);
	draw_lines(second, 1);
	draw_lines(third, 1);
	draw_lines(fourth, 1);
	draw_lines(fifth, 1);

	return 0;
}

void draw_lines(Turtle one, int rad) {
	one.off();
	one.move(rad);
	one.on();
	one.turn(120);
	for (int i = 0; i < 100; i++) {
		one.move(rad + i * rad);
		one.turn(60);
	}
}