

void initilize_Haptic(){
  pinMode(MOTOR, OUTPUT); //setup haptic motor pins
}

void Haptic_Output_kill(){
  analogWrite(MOTOR, OFF);
}

int get_haptic_level(){
  if(gbl_hapticIntensity <= 0)
  {
    return 100;
  }
  else if(gbl_hapticIntensity <= 0)
  {
    return 170;
  }
  else if(gbl_hapticIntensity <= 0)
  {
    return 255;
  }
}

void triggerHaptic_HIGH(){
  analogWrite(MOTOR, get_haptic_level());
}
