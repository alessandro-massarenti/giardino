

class Button
{
private:
    const unsigned long debounceDelay = 50;
    int _pin;
    bool _state = false, _prev_state = false;
    unsigned long _action_time = 0;

public:
    Button(int button_pin) : _pin(button_pin)
    {
        pinMode(_pin, INPUT_PULLUP);
    }

    bool read()
    {
        bool button_state = digitalRead(_pin);

        if (button_state != _prev_state)
        {
            if (button_state == LOW)
            {
                if ((_action_time + debounceDelay) < millis())
                {
                    _state = !_state;
                    _action_time = millis();
                }
            }
            _prev_state = button_state;
        }
        return _state;
    }

    void reset(){
        _state = false;
    }
};

class Relay
{

private:
    int _pin;
    unsigned long _on_delay, _off_delay, _action_time = 0;
    bool _state = false, _next_state = false;

    void routine()
    {
        unsigned long time = millis();
        if (_next_state && (_action_time + _on_delay) < time)
            _state = true;
        else if (!_next_state && (time - _action_time) > _off_delay)
            _state = false;
        _state ? digitalWrite(_pin, LOW) : digitalWrite(_pin, HIGH);
    }

public:
    Relay(int pin, unsigned long on_delay = 0, unsigned long off_delay = 0) : _pin(pin), _on_delay(on_delay), _off_delay(off_delay)
    {
        pinMode(_pin, OUTPUT);
        pinMode(_pin, HIGH);
        off();
    }

    void on()
    {
        if (!_next_state)
        {
            _next_state = true;
            _action_time = millis();
        }

        routine();
    }

    void off()
    {
        if (_next_state)
        {
            _next_state = false;
            _action_time = millis();
        }
        routine();
    }
};
