#include <Adafruit_NeoPixel.h>
/*
   LED bar graph - decay version
   break into 2 ranges mapped to 4 leds each
   port and starboard
   light just one led 
 */

const int portLedPins[] = { 2, 3, 4, 5};
const int starboardLedPins[] = { 6, 7, 8, 9};
const int NbrLEDs = 4;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);

void setup() {
	  Serial.begin(115200);
    for (int led = 0; led < NbrLEDs; led++)
        pinMode(portLedPins[led], OUTPUT);

    for (int led = 0; led < NbrLEDs; led++)
        pinMode(starboardLedPins[led], OUTPUT);

   pinMode(9, OUTPUT); // how come pin 9 is not being set in loop?
   pinMode(11, OUTPUT); // how come pin 9 is not being set in loop?

   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
	 Serial.println("LED demo");
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
	  bool port=false;
		long color;
	  int red,green;	

	  delay(200);
    int keelAngle = readkeel();
		Serial.println(keelAngle);
		int ledLevel;
		allOff();
    if(keelAngle <= 0 ) { //port?
			port=true;
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
			port=false;
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
//drive neopixels
		if(port) {
			color = 0x00f00;
			red=0;green=1;
		}else {
			color = 0x0f0000;
			green=0;red=1;
		}
		for (int led = 0; led < NbrLEDs; led++) {
			if (led < ledLevel ) {
			  	  strip.setPixelColor(led, red*0xff,green*0xff,0);
			}
			else {
				strip.setPixelColor(led, 0);
			}
		}
		strip.setPixelColor(ledLevel, abs(keelAngle-ledLevel*11)*23*red,abs(keelAngle-ledLevel*11)*23*green,0);
		strip.show();
}

