//int randomSong(int readingMicroSwitch, int previousMicroSwitch, int microSwitchState, long debounce){
//  
//  //the micro switch to play a random song.
//  if (readingMicroSwitch != previousMicroSwitch && millis() - time > debounce) {
//    if (microSwitchState == HIGH) {
//      microSwitchState = LOW;
//      //Serial.println(switchState);
//    } else {
//      microSwitchState = HIGH;
//      Serial.println("random song");
//    }
//    time = millis();
//  }
//  previousMicroSwitch = readingMicroSwitch;
//  int result[] = {previousMicroSwitch, microSwitchState};
//  return result;
//}

