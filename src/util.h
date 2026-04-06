#pragma once
#include "math.h"

extern double deadzone;
struct vector {double x,y ;};
extern struct vector leftstick,rightstick;

void updateLetter();
void updateSticks(int gamepadfd);
int open_gamepad();
void normalize(int gamepadfd);
char getletter();
u_int8_t getActiveSector(double x,double y);
