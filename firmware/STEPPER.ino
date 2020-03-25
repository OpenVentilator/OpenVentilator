void _init_steppers()
{
    pinMode( _S._en_pin , OUTPUT);
    pinMode( _S._dir_pin , OUTPUT);
    pinMode( _S._pulse_pin , OUTPUT);
    digitalWrite( _S._en_pin , _S._en);
    digitalWrite( _S._dir_pin, _S._dir);
    digitalWrite( _S._pulse_pin , LOW);
    pinMode(  _S._limit_switch_pin , INPUT_PULLUP );

    update_stepper_speed(&_S);
}

int instant_check_limit_switch(STEPPER *S)
{
    if( digitalRead(S->_limit_switch_pin) == LOW ) return 1; 
    else return 0;
}

int check_limit_switch(STEPPER *S, int _dt)
{
    if( get_input(S->_limit_switch_pin, _dt) == LOW ) return 1; 
    else return 0;
}


void print_stepper_info(STEPPER *S)
{ 
    Serial.print("Enable: "); Serial.println(S->_en); 
    Serial.print("Direction: "); Serial.println(S->_dir); 
    Serial.print("Steps: "); Serial.println(S->_steps_actual); 
    Serial.print("Speed: "); Serial.println(S->_speed); 
}


long convert_speed_to_delay( int s)
{
    return  round (100000 / s) ; 
}

void update_stepper_direction(STEPPER *S)
{
    digitalWrite( S->_dir_pin , S->_dir);
}

void update_enable(STEPPER *S)
{
    digitalWrite( S->_en_pin, S->_en);
}


void update_stepper_speed(STEPPER *S)
{
      S->_cs = convert_speed_to_delay( S->_speed);
}

void update_stepper_speed(STEPPER *S, int sss)
{
      S->_speed= sss;
      S->_cs = convert_speed_to_delay( S->_speed);
}
  


void pulse_stepper( STEPPER *S)
{
    digitalWrite(S->_pulse_pin,HIGH);
    delayMicroseconds(S->_cs);
    digitalWrite(S->_pulse_pin,LOW);
    delayMicroseconds( S->_cs); 

    if( S->_dir == HIGH ) S->_steps_actual ++ ;
    else if( S->_dir == LOW ) S->_steps_actual --;
}

void home_stepper(STEPPER *S, int Vmax , int Vmin)
{
    int old_speed = S->_speed ; 
    
    S->_en = HIGH; 
    update_enable(S);
    
    S->_dir = LOW ;
    S->_speed = Vmax;
    update_stepper_speed(S); 
    update_stepper_direction(S);
    
    while(  true)
    {      
        if(  instant_check_limit_switch(S) == 1 )
        {
              S->_steps_actual = 0;
              break;
        }
    
        pulse_stepper(S);
    }
    
    delay(50);
    
    S->_speed  =  old_speed ;
    update_stepper_speed(S);

    S->_en = LOW; 
    update_enable(S);
    
} 

void run_stepper( STEPPER *S , long stp_desired)
{ 
    S->_steps_desired = stp_desired;
    long delta_steps = S->_steps_desired - S->_steps_actual ;

    if(delta_steps >0 ) S->_dir = HIGH;
    else if( delta_steps <0 ) S->_dir = LOW;

    S->_en =HIGH; 
    update_enable(S);
    update_stepper_direction(S);

    while( true )
    {
         delta_steps = S->_steps_desired- S->_steps_actual ;
         if( delta_steps == 0 )
         {
             if( show_logs == HIGH )
             {
                  Serial.print("MVT DONE"); Serial.println( S->_steps_actual);
             }
             break;
         }
         
         pulse_stepper(S);
    }   

    S->_en = LOW; 
    update_enable(S);
}


void run_stepper( STEPPER *S , long stp_desired , int brake)
{ 
    S->_en = LOW; 
    update_enable(S);
    
    S->_steps_desired = stp_desired;
    long delta_steps = S->_steps_desired - S->_steps_actual ;

    if(delta_steps >0 ) S->_dir = HIGH;
    else if( delta_steps <0 ) S->_dir = LOW;

    if( S->id == 1 ) S->_en = HIGH; 
    else S->_en = LOW ; 
    update_enable(S);
    
    update_stepper_direction(S);

    while( true )
    {
         delta_steps = S->_steps_desired- S->_steps_actual ;
         if( delta_steps == 0 )
         {
             if( show_logs == HIGH )
             {
                  Serial.print("MVT DONE"); Serial.println( S->_steps_actual);
             }
             break;
         }
         
         pulse_stepper(S);
    }    

    if ( brake == LOW )
    {
        if( S->id == 1 ) S->_en = LOW; 
        else S->_en = HIGH ; 
        update_enable(S);
    }
    else if( brake == HIGH )
    {
        if( S->id == 1 ) S->_en = HIGH; 
        else S->_en = LOW ; 
        update_enable(S);
    }

}

void run_stepper( STEPPER *S , long steps_d , int sp , int dd , int brake)
{ 
    S->_dir = dd;
    S->_speed = sp;
    update_stepper_speed(S);
    
    if( dd == HIGH)  S->_steps_desired =  S->_steps_actual + steps_d  ;
    else if (dd == LOW)  S->_steps_desired = S->_steps_actual -steps_d  ;

    S->_en = LOW;
    update_enable(S);
    update_stepper_direction(S);

    while( true )
    {
         if( S->_steps_actual == S->_steps_desired )
         {
             if( show_logs == HIGH ) 
             {
                  Serial.print("MVT DONE "); Serial.println( S->_steps_actual);
             }
             break;
         }
         
         pulse_stepper(S);        
    }    


    if( brake == LOW )
    {
        S->_en = HIGH;
        update_enable(S);
    }
    else if( brake == HIGH )
    {
        S->_en = LOW ;
        update_enable(S);
    }
  
}


void run_stepper_3( STEPPER *S , long stp  )
{ 
    if(S->_dir ==HIGH) S->_steps_desired = stp + S->_steps_actual ;
    else S->_steps_desired = - stp + S->_steps_actual ;
    long delta_steps = S->_steps_desired - S->_steps_actual ;

    S->_en = LOW;
    update_enable(S);

    while( true )
    {
         delta_steps = S->_steps_desired - S->_steps_actual ;

         if( delta_steps == 0 )
         {
             if( show_logs == HIGH )
             {
                 Serial.print("MVT DONE"); Serial.println( S->_steps_actual);
             }
             break;
         }
         
         pulse_stepper(S);
    }    

    S->_en = HIGH;
    update_enable(S);
    
}





