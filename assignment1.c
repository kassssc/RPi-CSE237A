#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>
#include <softPwm.h>
#include <stdint.h>

static int print = 0;

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->bProgramExit = 0;
}

void init_sensors(SharedVariable* sv) {
	sv->state = 1;	// running
	sv->sound_big = 0; 
	sv->sound_small = 0;
	sv->touch = 0;
	// Init DIP RGB
	softPwmCreate(PIN_DIP_RED, 0, 0xFF);
	softPwmCreate(PIN_DIP_GRN, 0, 0xFF);
	softPwmCreate(PIN_DIP_BLU, 0, 0xFF);
	// Init SMD RGB
	softPwmCreate(PIN_SMD_RED, 0, 0xFF);
	softPwmCreate(PIN_SMD_GRN, 0, 0xFF);
	softPwmCreate(PIN_SMD_BLU, 0, 0xFF);

	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_BIG, INPUT);
	pinMode(PIN_SMALL, INPUT);
	pinMode(PIN_TOUCH, INPUT);
	pinMode(PIN_ALED, OUTPUT);
	pinMode(PIN_BUZZER, OUTPUT);

	digitalWrite(PIN_ALED, HIGH);
	softToneCreate(PIN_BUZZER);
}

void body_button(SharedVariable* sv) {
	static int debounce = 0;
	 static int debounce_counter = 0;
	// pressed = 0
	// not pressed = 1
	int pressed = !digitalRead(PIN_BUTTON);
	if (pressed && !debounce) {
		sv->state = !sv->state;
		debounce = 1;
	}
	if (debounce) {
		debounce_counter++;
	}
	if (debounce_counter >= 250) {
		debounce = 0;
		debounce_counter = 0;
	}
}

void body_threecolor(SharedVariable* sv) {

	// Off when state is paused
	if (!sv->state) {
		softPwmWrite(PIN_DIP_RED, 0x00);
		softPwmWrite(PIN_DIP_BLU, 0x00);

	// RED when small sound gives 1
	} else if (sv->sound_small) {
		softPwmWrite(PIN_DIP_RED, 0xFF);
		softPwmWrite(PIN_DIP_BLU, 0x00);

	// BLUE when small sound gives 0
	} else if (!sv->sound_small) {
		softPwmWrite(PIN_DIP_RED, 0x00);
		softPwmWrite(PIN_DIP_BLU, 0xFF);
	}
}

void body_big(SharedVariable* sv) {
	sv->sound_big = digitalRead(PIN_BIG);
}

void body_small(SharedVariable* sv) {
	sv->sound_small = digitalRead(PIN_SMALL);
}

void body_touch(SharedVariable* sv) {
	sv->touch = digitalRead(PIN_TOUCH);
}

void body_rgbcolor(SharedVariable* sv) {
	// Off when state is paused
	if (!sv->state) {
		softPwmWrite(PIN_SMD_RED, 0x00);
		softPwmWrite(PIN_SMD_GRN, 0x00);
		softPwmWrite(PIN_SMD_BLU, 0x00);

	// Small Sound 0 --- Touch 0
	} else if (!sv->sound_small && !sv->touch) {
		// Red
		softPwmWrite(PIN_SMD_RED, 0xFF);
		softPwmWrite(PIN_SMD_GRN, 0x00);
		softPwmWrite(PIN_SMD_BLU, 0x00);

	// Small Sound 1 --- Touch 0
	} else if (sv->sound_small && !sv->touch) {
		// Purple
		softPwmWrite(PIN_SMD_RED, 0xEE);
		softPwmWrite(PIN_SMD_GRN, 0x00);
		softPwmWrite(PIN_SMD_BLU, 0xC8);

	// Small Sound 0 --- Touch 1
	} else if (!sv->sound_small && sv->touch) {
		// Yellow
		softPwmWrite(PIN_SMD_RED, 0x80);
		softPwmWrite(PIN_SMD_GRN, 0xFF);
		softPwmWrite(PIN_SMD_BLU, 0x00);

	// Small Sound 1 --- Touch 1
	} else if (sv->sound_small && sv->touch) {
		// Cyan
		softPwmWrite(PIN_SMD_RED, 0x00);
		softPwmWrite(PIN_SMD_GRN, 0xFF);
		softPwmWrite(PIN_SMD_BLU, 0xFF);
	}
}

void body_aled(SharedVariable* sv) {
	if (sv->state) {
		digitalWrite(PIN_ALED, HIGH);
	} else {
		digitalWrite(PIN_ALED, LOW);
	}
}

void body_buzzer(SharedVariable* sv) {
	static int buzzing = 0;
	static int counter = 0;

	// Initially detect
	if (sv->sound_big) {
		buzzing = 1;
		counter = 0;
	}
	if (buzzing) {
		softToneWrite(PIN_BUZZER, 2000);
		counter++;
		// Buzzed for 0.5s already
		if (counter > 500) {
			counter = 0;
			buzzing = 0;
		}
	} else {
		softToneWrite(PIN_BUZZER, 0);
	}
}