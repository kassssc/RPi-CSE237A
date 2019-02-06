#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

#define PIN_TOUCH_RESPONSE 1

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->bProgramExit = 0;
}

void init_sensors(SharedVariable* sv) {
	softPwmCreate(PIN_DIP_RED, 0, 100);
	softPwmCreate(PIN_DIP_BLU, 100, 100);
}

void body_button(SharedVariable* sv) {
	// Exit if button pressed
	// pressed = 0
	// not pressed = 1
	int pressed = !digitalRead(PIN_BUTTON);
	if (pressed) sv->bProgramExit = 1;
}

void body_threecolor(SharedVariable* sv) {
	static int red = 0;
	static int blu = 1000;
	static int red_incr = 1;
	static int blu_incr = 1;

	if (red >= 1000) {
		red_incr = -1;
	} else if (red <= 0) {
		red_incr = 1;
	}
	if (blu >= 1000) {
		blu_incr = -1;
	} else if (blu <= 0) {
		blu_incr = 1;
	}
	red += red_incr;
	blu += blu_incr;
	softPwmWrite(PIN_DIP_RED, red/10);
	softPwmWrite(PIN_DIP_BLU, blu/10);
}

void body_big(SharedVariable* sv) {
}

void body_small(SharedVariable* sv) {
}

void body_touch(SharedVariable* sv) {
	int touch = digitalRead(PIN_TOUCH);
	printf("touch: %d\n", touch);
	if (touch) digitalWrite(PIN_TOUCH_RESPONSE, HIGH);
	else digitalWrite(PIN_TOUCH_RESPONSE, LOW);
}

void body_rgbcolor(SharedVariable* sv) {
}

void body_aled(SharedVariable* sv) {
}

void body_buzzer(SharedVariable* sv) {
}