// EEPROM STUFF //
void EEPROMWritelong(int address, long _value)
{
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (_value & 0xFF);
      byte three = ((_value >> 8) & 0xFF);
      byte two = ((_value >> 16) & 0xFF);
      byte one = ((_value >> 24) & 0xFF);
  
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
}

long EEPROMReadlong(long address)
{
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);
      
      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
// EEPROM STUFF //

int get_input(int pin , int dt)
{
     int reading = digitalRead(pin);
     long c=0;
     long c2 = 0;
     long t = millis();
     while (millis() - t < dt)
     {
         if (reading==digitalRead(pin)) c2++;
         c++;
     }
     if(c2 >= (0.9*c)) return reading;   
     else if( reading == HIGH) return LOW;
     else if( reading == LOW) return HIGH;
}

int get_analog_input(int pin,int dt)
{
     unsigned long c = 0 ;
     unsigned long t = millis();
     unsigned long analog_value = analogRead(pin);
     while (millis() - t < dt)
     {
         analog_value = analog_value + analogRead(pin);
         c++;
     }
     
     analog_value =  (analog_value / (c+1));
     
     return analog_value;
}

void custom_delay(long dt)
{
     int seconds = dt / 1000 ; 
     int rest = dt % 1000;

     Serial.print("Sec: "); Serial.println(seconds);
     Serial.print("Rest: "); Serial.println(rest);

     long t = millis();

     for( int i=0 ; i< seconds ; i++)
     {
         delay(1000);
     }

     delay( rest ); 

     Serial.println(millis()-t);
}


