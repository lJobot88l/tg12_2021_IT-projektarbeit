void Calibrate()
{
    Serial.println("Calibration started");
    Serial.println("Turning left");
    digitalWrite(turnL, HIGH);
    while(true) 
    {
        if(digitalRead(leftSideHitS))
        {
            delay(50); // debounce
            if(digitalRead(leftSideHitS)) { break; }
        }            
    }
    Serial.println("Left sensor hit");
    digitalWrite(turnL, LOW);

    float testStartTime = millis(); // Actual begin of the rightrotation time
    Serial.println("Turning right");
    digitalWrite(turnR, HIGH);
    while(true) 
    {
        if(digitalRead(rightSideHitS))
        {
            delay(50); // debounce
            if(digitalRead(rightSideHitS)) { break; }
        }            
    }
    Serial.println("Right sensor hit");
    digitalWrite(turnR, LOW);
    
    secondsForRotation = (millis() - testStartTime) / 1000;
 
    Serial.print("Time taken for full rotation: "); Serial.println(secondsForRotation);
    Serial.print("OpsFactor: "); Serial.println((float)(secondsForRotation/28800.00), 8);
}
