#include <RASLib/inc/common.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/uart.h>
#include "PSX.h"
#include <stdint.h>

extern uint32_t Lx, Ly, Rx, Ry, X, Square, Triangle, Circle,
       Up, Down, Left, Right, L1, L2, R1, R2;

static tMotor * motors[4];

void doMotorState (float x, float y, float w) {
        SetMotor(motors[0], - w - x + y);
        SetMotor(motors[1], - w - x - y);
        SetMotor(motors[2], - w + x + y);
        SetMotor(motors[3], - w + x - y);
}

int HoloMain (void) {
        int i = 0;
        for (; i < 4; ++i) {
                motors[i] = InitializeServoMotor(i + PIN_D0, false);
        }
       SetPin(PIN_F2, 1);
       while (1) {
                PSX_Poll();
                float x, y, w;
                signed char wC = Rx - 0x80;
                signed char xC = Ly - 0x80;
                signed char yC = Lx - 0x80;
                if (w == -128) w = -127;
                w = -w;
                if (x == -128) x = -127;
                x = -x;
                if (x * x < 400) x = 0;
                if (y * y < 400) y = 0;
                if (w * w < 400) w = 0;
                x = xC * 0.25f/127.0f;
                y = yC * 0.25f/127.0f;
                w = wC * 0.25f/127.0f;
                doMotorState(x,y,w);
        }
}
