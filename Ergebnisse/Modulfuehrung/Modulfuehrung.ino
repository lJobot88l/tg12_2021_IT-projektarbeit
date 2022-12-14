int turnL = 11; // Pin for the motor to turn right
int turnR = 12; // * left

int leftSideHitS = 10; // Turn limit sensor on the left
int rightSideHitS = 9; // Turn limit sensor on the right

int turnLbutton = 2;
int turnRbutton = 3;
int photoResistor = 14; // Photo resistor pin (WIP)

float secondsForRotation; // Time the solar panel needs to rotate from all the way left to all the way right in seconds

bool bLPressed = false;
bool bRPressed = false;
int autoTurn = true; // 1 = autoturn engaged

int loopbegin = 0;

unsigned long startRotation; // Has to be ulong because int would overflow after ~2 intervals, now overflows after 50 days (like millis())

// All timespans in seconds
int dLenS = 86400; // 86400 = 1 day
int rTimeS = 45; // Time taken for a full rotation
int sTimeS = dLenS/4; // Fraction of the day that has sun (1/4 of the full day)
int intervals = 8; // Times the panel rotates
int intervalTimeS = rTimeS/intervals; // The length of one rotation interval
float opsFactor = (float)rTimeS/(float)sTimeS; // Ratio from time taken for a rotation to the hour time. Used to convert between actual time and the equivalent rotating interval time
int modS = intervalTimeS/opsFactor; // Length of the break between the starts of two intervals
void setup() 
{

    Serial.begin(9600);
    Serial.println("Hello, World!");
    Serial.print("Interval time is "); Serial.print(modS); Serial.println(" seconds");
    pinMode(turnL, OUTPUT);
    pinMode(turnR, OUTPUT);

    pinMode(leftSideHitS, INPUT_PULLUP);
    pinMode(rightSideHitS, INPUT_PULLUP);

    pinMode(turnLbutton, INPUT_PULLUP);
    pinMode(turnRbutton, INPUT_PULLUP);
    
    digitalWrite(turnL, HIGH); // Turn the panel all the way left
    while(true) 
    {
        if(digitalRead(leftSideHitS))
        {
            delay(50); // debounce
            if(digitalRead(leftSideHitS)) { break; }
        }            
    }
    digitalWrite(turnL, LOW);
    loopbegin = millis();
}

void loop() 
{
    if( (( millis() - loopbegin <= 500 || ((millis() - loopbegin)/1000) % modS <= 1)) && (!digitalRead(rightSideHitS)) && autoTurn)
    {
        delay(50); // debounce
        if(!digitalRead(rightSideHitS))
        {
            digitalWrite(turnR, HIGH);
            startRotation = millis();
            Serial.println("Autorotating..."); // Rotates automatically every modS seconds for intervalTimeS seconds
            while(((millis() - startRotation)/1000) < intervalTimeS)
            {

                if(digitalRead(rightSideHitS))
                {
                    delay(50); // debounce
                    if(digitalRead(rightSideHitS))
                    {
                        autoTurn = false;
                        digitalWrite(turnR, LOW); // disables auto turn when hit
                        Serial.println("Autorotation cancelled (sensor hit)");
                        Serial.println("Sleeping..."); // Sleeps until the end of the day when the sensor was hit
                        return;
                    }
                }
            }
            digitalWrite(turnR, LOW);
            Serial.println("Autorotation finished!");
        }
    }
    if((millis()/1000) % (dLenS-50) == 0) // Resets the rotation after a full day
    {
        Serial.println("Waking...");
        digitalWrite(turnL, HIGH);
        Serial.println("Resetting autorotation...");
        Serial.println((millis()/1000) % (dLenS-50));
        while(true)
        {
            if(digitalRead(leftSideHitS))
            {
                delay(50);
                if(digitalRead(leftSideHitS))
                {
                    digitalWrite(turnL, LOW); // turns fully left 50 seconds before 24 hours are over to give it time
                }
            }
            if((millis()/1000 % dLenS) == 0)
            {
                autoTurn = true;
                Serial.println("Autorotation reset!"); // Turns autoturn back on once the day begins anew
                break;
            }
        }

    }
    if(!digitalRead(leftSideHitS) && !digitalRead(turnLbutton) && !bLPressed) // Following 4 if blocks are for using buttons
    {
        delay(50);
        if(!digitalRead(turnLbutton))
        {
            digitalWrite(turnL, HIGH);
            bLPressed = true;
            Serial.println("Start L");
        }
    }
    if(!digitalRead(rightSideHitS) && !digitalRead(turnRbutton) && !bRPressed)
    {
        delay(50);
        if(!digitalRead(turnRbutton))
        {
            digitalWrite(turnR, HIGH);
            bRPressed = true;
            Serial.println("Start R");        
        }
    }

    if(bLPressed && (digitalRead(turnLbutton) || digitalRead(leftSideHitS)))
    {
        delay(50);
        if(digitalRead(turnLbutton) || digitalRead(leftSideHitS))
        {
            digitalWrite(turnL, LOW);
            bLPressed = false;
            Serial.println("End L");
        }
    }
    if(bRPressed && (digitalRead(turnRbutton) || digitalRead(rightSideHitS)))
    {
        delay(50);
        if(digitalRead(turnRbutton) || digitalRead(rightSideHitS))
        {
            digitalWrite(turnR, LOW);
            bRPressed = false;
            Serial.println("End R");
        }
    }
}
