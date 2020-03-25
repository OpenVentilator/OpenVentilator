#include <Stepper.h>
#include <EEPROM.h>
#include <math.h>
#include "STEPPER.H"

///////////////Stepper///////////////// 
STEPPER _S   = {1,22,LOW,24,LOW,25,16,0,0,480,0};          
///////////////Stepper/////////////////

int show_logs = HIGH;

int frequency_pin = A1;
int freq = 0;
int Volume_pin = A0;
int vol = 0;

int max_travel = 3500;
int min_travel = 600;

void setup() 
{
    Serial.begin(9600); 
    _init_steppers();
    home_stepper(&_S,_S._speed,_S._speed);  

    freq  = read_frequency_knob () ; 
    vol = read_volume_knob ();
     
    Serial.print("VOLUME: "); Serial.println(read_volume_knob ());
    Serial.print("FREQ: "); Serial.println(read_frequency_knob ());
    delay(50);
}


void test_stepper()
{
    if(Serial.available()>0)
    {
         int x = Serial.parseInt();
       
         if ( x >=0 )
         {
             run_stepper( &_S,  x );
         }
         else 
         {
             home_stepper(&_S, _S._speed ,_S._speed/2);
         }

         while (Serial.available()>0)
         {
             Serial.read();
         }
    }
}

void loop() 
{    
     freq  = read_frequency_knob () ; 
     vol = read_volume_knob ();
     
     Serial.print("VOLUME: "); Serial.println(read_volume_knob ());
     Serial.print("FREQ: "); Serial.println(read_frequency_knob ());
     delay(50);

           
     long timer1 = millis();
     if(vol ==1 ) run_stepper( &_S,  max_travel - 300 );
     else if (vol == 2 ) run_stepper( &_S,  max_travel - 150 );
     else run_stepper( &_S,  max_travel );  
     run_stepper( &_S,  min_travel);
     long timer2 = millis() - timer1;
     Serial.print("Timer: ");Serial.println(timer2 );

     calculate_delay_and_wait( freq , timer2 );
}



