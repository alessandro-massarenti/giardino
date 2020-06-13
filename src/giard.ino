#define pumpPin 3
#define zoneOnePin 4
#define zoneTwoPin 5
#define userPin 7
#define buttonOnePin 8
#define buttonTwoPin 9

void setup()
{
    // put your setup code here, to run once:
    pinMode(userPin, INPUT_PULLUP);
    pinMode(buttonOnePin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{

    Relay pump(pumpPin, 0, 5000);
    Relay zoneOne(zoneOnePin, 0, 5000);

    bool user;
    while (true)
    {
        !digitalRead(userPin) ? pump.on() : pump.off();
        !digitalRead(buttonOnePin) ? zoneOne.on() : zoneOne.off();

        pump.routine();
        zoneOne.routine();
    }
}
