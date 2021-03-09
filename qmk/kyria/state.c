#include "state.h"

bool accelrated_1 = false;
bool accelrated_2 = false;
bool accelrated_3 = false;
bool accelrated_4 = false;


enum directive active_directive = TEXTMOTION;

enum os active_os = MAC;

static uint16_t directive_timer;
