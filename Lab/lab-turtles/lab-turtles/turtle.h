#include "draw.h"

class Turtle {
public: 
	Turtle(double x0, double y0, double dir0); // constructor 
	void move(double dist);
	void turn(double deg);
	void setColor(Color c);
	void off();
	void on();

private: 
	double direc;
	double x1;
	double y1;
	bool draw;
	Color c_new;
};