// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

#define PIXEL_PIN D0
#define PIXEL_COUNT 1
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int buttonState = 0;
int analogVal = 0;
double voltage = 0.0;
double temperature = 0.0;
int rawTemp = 0;
int lightVal = 0;
int rawTempMapped = 0;
int rawTempConstrained = 0;
void setup() {
    pinMode(7, OUTPUT);
    pinMode(1, INPUT_PULLUP);
    pinMode(2, OUTPUT);
    //RGB.control(true);
    //RGB.color(255,255,255);
    Particle.variable("analogVal", analogVal);
    Particle.variable("voltage", voltage);
    Particle.variable("tempC", temperature);
    Particle.variable("rawTemp", rawTemp);
    Particle.variable("lightVal", lightVal);
    Particle.variable("rawMapped", rawTempMapped);
    strip.begin();
    strip.show();
}

void loop() {
    strip.setPixelColor(0, 0,rawTempMapped,255-rawTempMapped);
    strip.show();
    buttonState = digitalRead(1);
    analogVal = analogRead(0);
    rawTemp = analogRead(1);
    rawTempConstrained = constrain(rawTemp, 920, 980);
    rawTempMapped = map(rawTempConstrained, 920, 980, 0, 255);
    lightVal = analogRead(2);
    temperature = ((3300.0/4096*rawTemp)-500)/10;
    voltage = 3.3/4096*analogVal;
    //RGB.brightness(analogVal/16);
    if(buttonState == 0){
        digitalWrite(7, HIGH);
        tone(2, 5000, 1000);
        delay(1000);
        tone(2, 8000, 1000);
        delay(1000);
        tone(2, 3000, 1000);
        delay(1000);
        Particle.publish("Message", "HELLO!");
    }
    else{
        digitalWrite(7, LOW);
    }
}
