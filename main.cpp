#include "pigpio.h"

#include <cstdio>

// This is a total hack but demonstrates that we can read from a glass scale quite easily
// from a Rapsberry Pi using the pigpio library. We will be able to incorporate this into
// the latheControl software to allow it to determine position on the axes without relying
// on dead reckoning (which could fail if the stepper motors miss steps)

const int PIN_A = 20;
const int PIN_B = 21;
int g_pinA = 0;
int g_pinB = 0;
long counter = 0;
int newPhase = 0;
int oldPhase = 0;

void callback(int gpio, int level, uint32_t /*tick*/, void* /*userData*/)
{
    if(gpio==PIN_A) g_pinA = level;
    if(gpio==PIN_B) g_pinB = level;
    newPhase = g_pinA ? (g_pinB ? 3 : 4) : (g_pinB ? 2 : 1);

    if (oldPhase == 4 && newPhase == 1) {
        counter -= 1;
    } else if (oldPhase == 1 && newPhase == 4) {
        counter += 1;
    } else if (newPhase > oldPhase) {
        counter -= 1;
    } else if (newPhase < oldPhase) {
        counter += 1;
    }
    oldPhase = newPhase;
    printf("%.2f mm\n", counter/200.0);
}

int main()
{
    if ( gpioInitialise() < 0 )
    {
        printf("Could not initialise pigpio library");
        return 1;
    }
    gpioSetMode( PIN_A, PI_INPUT );
    gpioSetMode( PIN_B, PI_INPUT );
    gpioSetPullUpDown( PIN_A, PI_PUD_UP );
    gpioSetPullUpDown( PIN_B, PI_PUD_UP );
    void* user = nullptr;
    gpioSetAlertFuncEx( PIN_A, callback, user );
    gpioSetAlertFuncEx( PIN_B, callback, user );
    for(;;);
    return 0;
}
