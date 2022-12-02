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
}

void loop() 
{
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

int HourToOpTime(int Hour)
{
    return 0;
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
