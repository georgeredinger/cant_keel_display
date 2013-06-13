/*
   LED bar graph - decay version
   break into 2 ranges mapped to 4 leds each
   port and starboard
   light just one led 
 */

const int portLedPins[] = { 2, 3, 4, 5};
const int starboardLedPins[] = { 6, 7, 8, 9};
const int NbrLEDs = sizeof(portLedPins)

void setup() {
    for (int led = 0; led < NbrLEDs; led++)
        pinMode(portLedPins[led], OUTPUT);
    for (int led = 0; led < NbrLEDs; led++)
        pinMode(starbordLedPins[led], OUTPUT);
}


void loop() {
    keelAngle = readkeel();
    if(keelAngle <= 45 and keelAngle) { //port?
        ledLevel = map(keelAngle, 0, 45, 0, NbrLEDs); // map to number of LEDs
        for (int led = 0; led < NbrLEDs; led++)
        {
            if (led < ledLevel ) {
                digitalWrite(portLedPins[led], HIGH);  // turn on pins less than the level
            }
            else {
                digitalWrite(portLedPins[led], LOW);   // turn off pins higher than the level
            }
        }
    }
    else //starboard??
    {
        ledLevel = map(keelAngle, 270, 360, 0, NbrLEDs); // map to number of LEDs
        for (int led = 0; led < NbrLEDs; led++)
        {
            if (led < ledLevel ) {
                digitalWrite(starboardLedPins[led], HIGH);  // turn on pins less than the level
            }
            else {
                digitalWrite(starboardLedPins[led], LOW);   // turn off pins higher than the level
            }
        }
    }

}
