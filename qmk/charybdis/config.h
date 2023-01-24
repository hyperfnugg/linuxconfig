#pragma once



#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 1

// The Leader key allows to flexibly assign macros to key sequences.
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 350

#define TAPPING_TERM 200

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

// #define NO_CHARYBDIS_KEYCODES

#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#define ROTATIONAL_TRANSFORM_ANGLE -60
