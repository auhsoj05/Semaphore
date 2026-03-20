#pragma once
struct vector {float x,y;};
extern struct vector leftstick, rightstick;
extern bool isRunning;
extern float deadzone;
extern pthread_t gui;
