long interval = 250; 
long previousMillis = 0;
int ledState = HIGH;

void LED_Output_blink(){
  //blinks LED based on previous state and current time
  //Delay() cant be used becuase multitasking needs to happen
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval){
    previousMillis = currentMillis;
    if(ledState == LOW){
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
    digitalWrite(LED_PIN, ledState);
  }
}

void LED_Output_continuous(){
  //Continuously sets LED Output to On
  digitalWrite(LED_PIN, HIGH);
}

void LED_Output_killLED(){
  //kills the LED Output
  digitalWrite(LED_PIN, LOW);
}
