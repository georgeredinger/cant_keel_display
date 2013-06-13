/*
   LED bar graph - decay version
   break into 2 ranges mapped to 4 leds each
   port and starboard
   light just one led 
 */

const int portLedPins[] = { 2, 3, 4, 5};
const int starboardLedPins[] = { 6, 7, 8, 9};
const int NbrLEDs = 4;

void setup() {
	  Serial.begin(115200);
    for (int led = 0; led < NbrLEDs; led++)
        pinMode(portLedPins[led], OUTPUT);

    for (int led = 0; led < NbrLEDs; led++)
        pinMode(starboardLedPins[led], OUTPUT);

   pinMode(9, OUTPUT); // how come pin 9 is not being set in loop?

}

int readkeel() {
  static int angle=0;
	static int inc=1;
	angle+=inc;
	if(abs(angle) > 45 )
		inc=-inc;
  return angle;
}
void allOff(){
	for(int led=0;led<NbrLEDs;led++) digitalWrite(portLedPins[led], LOW);   
	for(int led=0;led<NbrLEDs;led++) digitalWrite(starboardLedPins[led], LOW);   
}

void loop() {
	  delay(100);
    int keelAngle = readkeel();
		Serial.println(keelAngle);
		int ledLevel;
		allOff();
    if(keelAngle <= 0 ) { //port?
			keelAngle = -keelAngle;
        ledLevel = map(keelAngle, 0,45 , 0, NbrLEDs); // map to number of LEDs
        for (int led = 0; led < NbrLEDs; led++) {
            if (led <= ledLevel ) {
                digitalWrite(portLedPins[NbrLEDs-led-1], HIGH);  // turn on pins less than the level
            }
            else {
                digitalWrite(portLedPins[NbrLEDs-led-1], LOW);   // turn off pins higher than the level
            }
        }
    }
    else //starboard??
    {
        ledLevel = map(keelAngle, 0,45 , 0, NbrLEDs); // map to number of LEDs
        for (int led = 0; led < NbrLEDs; led++) {
            if (led <= ledLevel ) {
                digitalWrite(starboardLedPins[led], HIGH);  // turn on pins less than the level
            }
            else {
                digitalWrite(starboardLedPins[led], LOW);   // turn off pins higher than the level
            }
        }
    }

}
