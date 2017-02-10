#include <RASLib/inc/common.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/uart.h>
#include "PSX.h"
#include <stdint.h>
//#include <StellarisWare/driverlib/watchdog.h>
//#include <StellarisWare/driverlib/sysctl.h>

#define WATCHDOG0_BASE (*((volatile unsigned long *)0x40000000))
extern uint32_t Lx, Ly, Rx, Ry, X, Square, Triangle, Circle,
       Up, Down, Left, Right, L1, L2, R1, R2;

static tMotor * motors[4];
static int ledState1 = 0;
static volatile unsigned char g_watchdog = 0;

void ToggleLED1(void){
    SetPin(PIN_F2, ledState1 & 1);
    ++ledState1;
}

void doMotorState (float x, float y, float w) {
        SetMotor(motors[0], - w - x - y);
        SetMotor(motors[1], - w - x + y);
        SetMotor(motors[2], - w + x + y);
        SetMotor(motors[3], - w + x - y);
}

int HoloMain (void) {
        int i = 0;
        for (; i < 4; ++i) {
                motors[i] = InitializeServoMotor(i + PIN_D0, false);
        }
       CallEvery(ToggleLED1, 0, 0.75);
       while (1) {
                PSX_Poll();
               // if (Square != 255 && Triangle != 255 && Circle != 255 && Circle != 255)
               //     WatchdogIntClear(WATCHDOG0_BASE);
                float x, y, w;
                signed char wC = Rx - 0x80;
                signed char xC = Ly - 0x80;
                signed char yC = Lx - 0x80;
                if (wC == -128) wC = -127;
                wC = -wC;
                if (xC == -128) xC = -127;
                xC = -xC;
                if (xC * xC < 400) xC = 0;
                if (yC * yC < 400) yC = 0;
                if (wC * wC < 400) wC = 0;
                x = xC * 0.25f/127.0f;
                y = yC * 0.25f/127.0f;
                w = wC * 0.25f/127.0f;
                doMotorState(x,y,w);
        }
}

