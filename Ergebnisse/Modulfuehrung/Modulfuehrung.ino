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

int dLenS = 864; // 86400 = 1 day
int rTimeS = 48;
int sTimeS = dLenS/4;
int intervals = 8;
int intervalTimeS = rTimeS/intervals;
float opsFactor = (float)rTimeS/(float)sTimeS;
int modS = intervalTimeS/opsFactor;
void setup() 
{

    Serial.begin(9600);
    Serial.println("Hello, World!");
    pinMode(turnL, OUTPUT);
    pinMode(turnR, OUTPUT);

    pinMode(leftSideHitS, INPUT_PULLUP);
    pinMode(rightSideHitS, INPUT_PULLUP);

    pinMode(turnLbutton, INPUT_PULLUP);
    pinMode(turnRbutton, INPUT_PULLUP);
    Calibrate();
    loopbegin = millis();
}

void loop() 
{
    if(( millis() - loopbegin <= 500 || ((millis()/1000) % modS >= -1 && (millis()/1000) % modS <= 1)) && (!digitalRead(rightSideHitS)) && autoTurn)
    {
        delay(50); // debounce
        if(!digitalRead(rightSideHitS))
        {
            digitalWrite(turnR, HIGH);
            int startR = millis();
            Serial.println("Autorotating...");
            while(((millis() - startR)/1000) < intervalTimeS)
            {
                if(digitalRead(rightSideHitS))
                {
                    delay(50); // debounce
                    if(digitalRead(rightSideHitS))
                    {
                        autoTurn = false;
                        digitalWrite(turnR, LOW); // disables auto turn when hit
                        Serial.println("Autorotation cancelled (sensor hit)");
                        return;
                    }
                }
            }
            digitalWrite(turnR, LOW);
            Serial.println("Autorotation finished!");
        }
    }
    if((millis()/1000) % (dLenS-50) == 0)
    {
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
                Serial.println("Autorotation reset!");
                break;
            }
        }

    }
    if(!digitalRead(leftSideHitS) && !digitalRead(turnLbutton) && !bLPressed)
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

    // --- Knopfbetrieb: ---
    // if(!digitalRead(leftSideHitS) && !digitalRead(turnLbutton) && !bLPressed)
    // {
    //     digitalWrite(turnL, HIGH);
    //     bLPressed = true;
    // }
    // if(!digitalRead(rightSideHitS) && !digitalRead(turnRbutton) && !bRPressed)
    // {
    //     digitalWrite(turnR, HIGH);
    //     bRPressed = true;
    // }

    // if(bLPressed && (digitalRead(turnLbutton) || digitalRead(leftSideHitS)))
    // {
    //     digitalWrite(turnL, LOW);
    //     bLPressed = false;
    // }
    // if(bRPressed && (digitalRead(turnRbutton) || digitalRead(rightSideHitS)))
    // {
    //     digitalWrite(turnR, LOW);
    //     bRPressed = false;
    // }
