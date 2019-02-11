#ifndef _ASSIGNMENT_BODY_
#define _ASSIGNMENT_BODY_

// A. Pin number definitions (DO NOT MODIFY)
// Important! USE the pin numbers and WIRE.
// We use 8 sensors.
//
// 1. Button
#define PIN_BUTTON 0

// 2. Big audio sensor
#define PIN_BIG 4

// 3. Small audio sensor
#define PIN_SMALL 5

// 4. Touch Sensor
#define PIN_TOUCH 6

// 5. DIP RGB LED (Dual In-line Package)
#define PIN_DIP_RED 7
#define PIN_DIP_GRN 8
#define PIN_DIP_BLU 9

// 6. SMD RGB LED (Surface Mount Device)
#define PIN_SMD_RED 27
#define PIN_SMD_GRN 28
#define PIN_SMD_BLU 29

// 7. Auto-flash Red
#define PIN_ALED 12

// 8. Buzzer
#define PIN_BUZZER 13

// B. Shared structure
// All thread fuctions get a shared variable of the structure
// as the function parameter.
// If needed, you can add anything in this structure.
typedef struct shared_variable {
	int bProgramExit; // Once it is set to 1, the program will be terminated.
	int state;				// 1 = running | 0 = pause
	int sound_big;			// Output of big sound sensor
	int sound_small;		// Output of small sound sensor
	int touch;					// Output of temperature touch sensor

	// Measured thread durations
	long long dur_button, dur_threecolor, dur_big, dur_small, dur_touch, dur_rgbcolor, dur_aled, dur_touch;
} SharedVariable;


// C. Functions
// You need to implement following functions.
// Do not change any function name here.
void init_shared_variable(SharedVariable* sv);
void init_sensors(SharedVariable* sv);

void body_button(SharedVariable* sv);
void body_threecolor(SharedVariable* sv);
void body_big(SharedVariable* sv);
void body_small(SharedVariable* sv);
void body_touch(SharedVariable* sv);
void body_rgbcolor(SharedVariable* sv);
void body_aled(SharedVariable* sv);
void body_buzzer(SharedVariable* sv);

#endif
