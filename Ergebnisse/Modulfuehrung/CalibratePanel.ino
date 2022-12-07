void Calibrate()
{
    digitalWrite(turnL, HIGH);
    while(true) 
    {
        if(digitalRead(leftSideHitS))
        {
            delay(50); // debounce
            if(digitalRead(leftSideHitS)) { break; }
        }            
    }
    digitalWrite(turnL, LOW);
} 
