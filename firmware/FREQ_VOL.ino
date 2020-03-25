int read_volume_knob ()
{
      int temp_vol = analogRead(Volume_pin);
      int volume_setting = 0 ;
      if (temp_vol < 250) volume_setting= 1 ; 
      else if( temp_vol >550 ) volume_setting= 3;
      else volume_setting = 2;
      return volume_setting;
}


int read_frequency_knob()
{
     int temp_freq = analogRead( frequency_pin );
     int freq_setting = map(temp_freq , 0 ,1023 ,12 ,24);
     return freq_setting;
}


int calculate_delay_and_wait(int freq , long tt)
{
     long time_for_interval = 60000 / freq;
     Serial.print("time for interval= "); Serial.println(time_for_interval );
     int difference_timer =  time_for_interval - tt;
     Serial.print("Difference timer=  "); Serial.println(difference_timer);
     if ( difference_timer  <= 0) return 0 ;
     delay(difference_timer);

      
}

