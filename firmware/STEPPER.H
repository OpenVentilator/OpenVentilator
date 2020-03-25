#ifndef STEPPER_H
#define STEPPER_H

typedef struct
{  
    int id;
    int _en_pin;
    int _en;
    int _dir_pin;
    int _dir;
    int _pulse_pin;
    int _limit_switch_pin;
    long _steps_actual;
    long _steps_desired;
    int _speed;
    int _cs;

} STEPPER;


#endif
