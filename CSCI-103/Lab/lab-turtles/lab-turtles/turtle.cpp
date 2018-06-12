#include "turtle.h"
#include <cmath>

Turtle::Turtle(double x0, double y0, double dir0){
	x1 = x0;
	y1 = y0;
	direc = 0.0;
	draw = true; 
	c_new = draw::BLACK;
	direc += dir0;
}

void Turtle::move(double dist) {
	draw::setcolor(c_new.red, c_new.green, c_new.blue);
	if (draw == true) {
		draw::line(x1, y1, x1+dist*cos(direc * M_PI / 180), y1+dist*sin(direc * M_PI / 180));
	}
	x1 += dist*cos(direc * M_PI / 180);
	y1 += dist*sin(direc * M_PI / 180);
}

void Turtle::turn(double deg) {
	direc += deg;
}

void Turtle::setColor(Color c) {
	c_new = c;
}

void Turtle::off() {
	draw = false;	
}

void Turtle::on() {
	draw = true;
}