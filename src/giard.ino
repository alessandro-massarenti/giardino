#define pumpPin 3
#define zoneOnePin 4
#define zoneTwoPin 5
#define userPin 7
#define buttonOnePin 8
#define buttonTwoPin 9

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
    // put your setup code here, to run once:
    pinMode(userPin, INPUT_PULLUP);
    Serial.begin(9600);
    lcd.init();
}

void loop()
{

    Relay pump(pumpPin, 1000, 5000);
    Relay zoneOne(zoneOnePin, 0, 0);
    Relay zoneTwo(zoneTwoPin, 0, 0);

    Button buttonOne(buttonOnePin);
    Button buttonTwo(buttonTwoPin);

    bool uno = false, due = false, prev = false;
    unsigned long start = 0;

    bool user;
    while (true)
    {
        user = !digitalRead(userPin);
        uno = buttonOne.read();
        due = buttonTwo.read();

        if (user)
        {
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("Ciao Alessandro");
            prev = true;
            pump.on();
            uno ? zoneOne.on() : zoneOne.off();
            due ? zoneTwo.on() : zoneTwo.off();
        }
        else
        {
            if(prev){
                lcd.clear();
                lcd.noBacklight();
                prev = false;
            }
            
            pump.off();
            buttonOne.reset();
            buttonTwo.reset();
            zoneOne.off();
            zoneTwo.off();
        }

        delay(10);
    }
}
