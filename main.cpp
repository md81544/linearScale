#include "pigpio.h"

#include <cstdio>

void callback(int gpio, int level, uint32_t /*tick*/, void* /*userData*/)
{
    printf("GPIO %d = %d\n", gpio, level);
}

int main()
{
    if ( gpioInitialise() < 0 )
    {
        printf("Could not initialise pigpio library");
        return 1;
    }
    const int pinA = 20;
    const int pinB = 21;
    gpioSetMode( pinA, PI_INPUT );
    gpioSetMode( pinB, PI_INPUT );
    gpioSetPullUpDown( pinA, PI_PUD_UP );
    gpioSetPullUpDown( pinB, PI_PUD_UP );
    void* user = nullptr;
    gpioSetAlertFuncEx( pinA, callback, user );
    gpioSetAlertFuncEx( pinB, callback, user );
    for(;;);
    return 0;
}
