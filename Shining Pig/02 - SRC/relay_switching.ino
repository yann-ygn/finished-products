#include <arduino.h>

#define FOOTSWITCH 4
#define RELAY 3
#define OK 2
#define STARTUPSTATE 0

long int now;
int switchState;
int lastSwitchState = 0;
int relayState = 0;
long int lastPressTime = 0;

int footSwitchPress();

void setup()
{
    pinMode(FOOTSWITCH, INPUT_PULLUP);
    pinMode(STARTUPSTATE, INPUT_PULLUP);
    pinMode(RELAY, OUTPUT);
    pinMode(OK, OUTPUT);

    relayState = digitalRead(STARTUPSTATE);
    digitalWrite(RELAY, relayState);
}

void loop()
{
    now = millis();

    if (footSwitchPress())
    {
        lastPressTime = now;
        relayState = !relayState;

        digitalWrite(OK, HIGH);
        delay(5);
        digitalWrite(RELAY, relayState);
        delay(5);
        digitalWrite(OK, LOW);
    }
}

int footSwitchPress()
{
    switchState = digitalRead(FOOTSWITCH);

    if (switchState == LOW && now - lastPressTime > 300)
    {
        lastSwitchState = switchState;
        return 1;
    }

    lastSwitchState = switchState;
    return 0;
}
