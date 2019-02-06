#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

static int counter = 0;

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->bProgramExit = 0;
}

void init_sensors(SharedVariable* sv) {
	softPwmCreate(PIN_DIP_RED, 0, 100);
	softPwmCreate(PIN_DIP_GRN, 50, 100);
	softPwmCreate(PIN_DIP_BLU, 100, 100);
	softPwmCreate(PIN_SMD_RED, 0, 0xFF);
	softPwmCreate(PIN_SMD_GRN, 0, 0xFF);
	softPwmCreate(PIN_SMD_BLU, 0, 0xFF);
}

void body_button(SharedVariable* sv) {
	counter = (counter + 1)%1000;
	// Exit if button pressed
	// pressed = 0
	// not pressed = 1
	int pressed = !digitalRead(PIN_BUTTON);
	if (pressed) sv->bProgramExit = 1;
}

void body_threecolor(SharedVariable* sv) {
	static int red = 0;
	static int grn = 500;
	static int blu = 1000;
	static int red_incr = 1;
	static int grn_incr = 1;
	static int blu_incr = 1;

	if (red >= 1000) {
		red_incr = -1;
	} else if (red <= 0) {
		red_incr = 1;
	}
	if (grn >= 1000) {
		grn_incr = -1;
	} else if (grn <= 0) {
		grn_incr = 1;
	}
	if (blu >= 1000) {
		blu_incr = -1;
	} else if (blu <= 0) {
		blu_incr = 1;
	}
	red += red_incr;
	grn += grn_incr;
	blu += blu_incr;
	softPwmWrite(PIN_DIP_RED, red/10);
	softPwmWrite(PIN_DIP_GRN, grn/10);
	softPwmWrite(PIN_DIP_BLU, blu/10);
}

void body_big(SharedVariable* sv) {
	int big_sound = digitalRead(PIN_BIG);
	if (!counter) printf("big: %d\n", big_sound);
}

void body_small(SharedVariable* sv) {
	int small_sound = digitalRead(PIN_SMALL);
	if (!counter) printf("small: %d\n", small_sound);
}

void body_touch(SharedVariable* sv) {
	int touch = digitalRead(PIN_TOUCH);
}

void body_rgbcolor(SharedVariable* sv) {
	if (counter == 0) {
		softPwmWrite(PIN_SMD_RED, 0xFF);
		softPwmWrite(PIN_SMD_GRN, 0x00);
		softPwmWrite(PIN_SMD_BLU, 0x00);
	} else if (counter == 333) {
		softPwmWrite(PIN_SMD_RED, 0x00);
		softPwmWrite(PIN_SMD_GRN, 0xFF);
		softPwmWrite(PIN_SMD_BLU, 0x00);
	} else if (counter == 666) {
		softPwmWrite(PIN_SMD_RED, 0x00);
		softPwmWrite(PIN_SMD_GRN, 0x00);
		softPwmWrite(PIN_SMD_BLU, 0xFF);
	}
}

void body_aled(SharedVariable* sv) {
	if (counter == 0) {
		digitalWrite(PIN_ALED, HIGH);
	} else if (counter == 500) {
		digitalWrite(PIN_ALED, LOW);
	}
}

void body_buzzer(SharedVariable* sv) {
	if (counter == 500) {
		digitalWrite(PIN_BUZZER, HIGH);
	} else if (counter == 0) {
		digitalWrite(PIN_BUZZER, LOW);
	}
}