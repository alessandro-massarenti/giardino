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
    Serial.begin(9600);
}

void loop()
{

    Relay pump(pumpPin, 1000, 5000);
    Relay zoneOne(zoneOnePin, 0, 0);
    Relay zoneTwo(zoneTwoPin, 0, 0);

    Button buttonOne(buttonOnePin);
    Button buttonTwo(buttonTwoPin);

    bool user;
    while (true)
    {
        user = !digitalRead(userPin);

        if(user){
            pump.on();
            buttonOne.read() ? zoneOne.on() : zoneOne.off();
            buttonTwo.read() ? zoneTwo.on() : zoneTwo.off();

        }else{
            pump.off();
            buttonOne.reset();
            buttonTwo.reset();
            zoneOne.off();
            zoneTwo.off();
        }
        
        
        delay(10);
    }
}
