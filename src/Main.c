#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/adc.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/servo.h>
#include <StellarisWare/driverlib/gpio.h>
#include <stdint.h>
#include <math.h>
#include "PSX.h"
#include "Holonomic.h"
//#include <StellarisWare/inc/hw_sysctl.h>
//#include <StellarisWare/driverlib/sysctl.h>
//#include <StellarisWare/inc/hw_watchdog.h>
//#include <StellarisWare/driverlib/watchdog.h>
//#include <StellarisWare/inc/hw_memmap.h>
#include <RASLib/inc/timeout.h>

tBoolean blink_on = true;
tBoolean initialized = false;
int tid;

void blink(void) {
    SetPin(PIN_F3, blink_on);
    blink_on = !blink_on;
}


/*void WatchdogHandler(void){
    WatchdogIntClear(WATCHDOG_BASE);
    WatchdogResetDisable(WATCHDOG_BASE);

    doMotorState(0,0,0);
    SetPin(PIN_F1, true);
    SetPin(PIN_F2, true);
    SetPin(PIN_F3, true);
    //while (true){}
}*/

/*void WatchDog_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG);
    WatchdogIntClear(WATCHDOG_BASE);
    //WatchdogStallEnable(WATCHDOG_BASE); //Enable for breakpoint debugging
    if(WatchdogLockState(WATCHDOG_BASE) == true) {
        WatchdogUnlock(WATCHDOG_BASE);
    }
    WatchdogIntRegister(WATCHDOG_BASE, WatchdogHandler);
    WatchdogReloadSet(WATCHDOG_BASE, 25000000);
    WatchdogIntEnable(WATCHDOG_BASE);
    WatchdogResetDisable(WATCHDOG_BASE); //second interrupt doesn't reset processor
    WatchdogEnable(WATCHDOG_BASE);
}*/

// The 'main' function is the entry point of the program
int main(void) {
    InitializeGPIO();
    CallEvery(blink, 0, 0.5);
   // WatchDog_Init();
	InitializeSystemTimeout();
    tid = CallOnTimeout(StopMotors, NULL, 0.1f);
    PSX_Initialize();
    HoloMain();
}
