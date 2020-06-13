/*
class Button
{
private:
    int _pin;
    bool _last_state;

    bool pressed()
    {
        return digitalRead(_pin);
    }

public:
    Relay(int pin) : _pin(pin)
    {
        pinMode(_pin, INPUT_PULLUP);
    }

    bool state_change()
    {
        pressed() != _last_state ? return true : return false;
    }

    bool click()
    {
        if (state_change())
    }
};

*/