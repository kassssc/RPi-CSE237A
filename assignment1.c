#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->bProgramExit = 0;
}

void init_sensors(SharedVariable* sv) {
	softPwmCreate(PIN_DIP_RED, 0);
	softPwmCreate(PIN_DIP_BLU, 100);
}

void body_button(SharedVariable* sv) {
	sv->bProgramExit = 1;
}

void body_threecolor(SharedVariable* sv) {
	static int red = 0;
	static int blu = 100;
	red = (red + 1)%100;
	blu = (blu + 1)%100;
	softPwmWrite(PIN_DIP_RED, red);
	softPwmWrite(PIN_DIP_BLU, blu);
}

void body_big(SharedVariable* sv) {
}

void body_small(SharedVariable* sv) {
}

void body_touch(SharedVariable* sv) {
}

void body_rgbcolor(SharedVariable* sv) {
}

void body_aled(SharedVariable* sv) {
}

void body_buzzer(SharedVariable* sv) {
}