#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/servo.h>
#include <StellarisWare/driverlib/gpio.h>
#include <stdint.h>
//#include "PLL.h"
#include <math.h>
#include "PSX.h"
#include "Holonomic.h"

tBoolean blink_on = true;
tBoolean initialized = false;


void blink(void) {
    SetPin(PIN_F3, blink_on);
    blink_on = !blink_on;
}



// The 'main' function is the entry point of the program
int main(void) {
    InitializeGPIO();
    //PLL_Init(Bus80MHz)
    CallEvery(blink, 0, 0.5);
    PSX_Initialize();
    HoloMain();
}
