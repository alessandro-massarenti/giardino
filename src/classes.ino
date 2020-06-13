const unsigned long debounceDelay = 50;

class Button
{
private:
    int _pin;
    bool _prev_state, state;
    unsigned long _prev_time;

public:
    Button(int button_pin) : _pin(button_pin), _prev_state(HIGH), _prev_time(0)
    {
        pinMode(_pin, INPUT_PULLUP);
    }

    bool buttonRoutine()
    {
        bool change = false;
        int button_state = digitalRead(_pin);

        Serial.print(String(button_state));

        if (button_state != _prev_state)
            _prev_time = millis();

        if ((millis() - _prev_time) > debounceDelay)
        {
            // if the button state has changed:
            if (button_state != state)
            {
                state = button_state;

                // only toggle the LED if the new button state is HIGH
                if (state == HIGH)
                {
                    change = true;
                }
            }
        }
        Serial.println(String(change));
        return change;
    }
};

class Relay
{

private:
    int _pin;
    unsigned long _on_delay, _off_delay, _action_time = 0;
    bool _state = false, _next_state = false;

public:
    Relay(int pin, unsigned long on_delay = 0, unsigned long off_delay = 0) : _pin(pin), _on_delay(on_delay), _off_delay(off_delay)
    {
        pinMode(_pin, OUTPUT);
        pinMode(_pin, HIGH);
    }

    void on()
    {
        if (!_next_state)
        {
            _next_state = true;
            _action_time = millis();
        }
    }

    void off()
    {
        if (_next_state)
        {
            _next_state = false;
            _action_time = millis();
        }
    }

    void routine()
    {
        unsigned long time = millis();
        if (_next_state && (_action_time + _on_delay) < time)
            _state = true;
        else if (!_next_state && (time - _action_time) > _off_delay)
            _state = false;
        _state ? digitalWrite(_pin, LOW) : digitalWrite(_pin, HIGH);
    }
};
