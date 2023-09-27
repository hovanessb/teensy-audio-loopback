#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SerialFlash.h>

AudioInputI2S            i2s2;    
AudioMixer4              mixer1;
AudioMixer4              mixer2;
AudioInputUSB            usb1;  
AudioOutputUSB           usb2;  

AudioAnalyzePeak     peak_L;
AudioAnalyzePeak     peak_R;

AudioConnection          patchCord1(usb1, 0, mixer1, 0);
AudioConnection          patchCord2(usb1, 1, mixer2, 0);
AudioConnection          patchCord3(i2s2, 0, mixer1, 1);
AudioConnection          patchCord4(i2s2, 1, mixer2, 1);
AudioConnection          patchCord5(mixer1, 0, usb2, 0);
AudioConnection          patchCord6(mixer2, 0, usb2, 1);
AudioConnection          patchCord7(mixer1, 0, peak_L,0);
AudioConnection          patchCord8(mixer2, 0, peak_R,0);
const int ledPin = 13;

void setup(){
  AudioMemory(64);
  Serial.begin(57600);
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
}


elapsedMillis fps;
uint8_t cnt=0;

void loop(){  
   if(fps > 24) {
    if (peak_L.available() && peak_R.available()) {
      fps=0;
      uint8_t leftPeak=peak_L.read() * 50.0;
      uint8_t rightPeak=peak_R.read() * 50.0;
      cnt= leftPeak+rightPeak;
      if(cnt >= 45) {
        digitalWrite(ledPin, HIGH);   // set the LED on
      } else {
        digitalWrite(ledPin, LOW);    // set the LED off)
      }  
    }
  }
