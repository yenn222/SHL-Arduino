#include <Adafruit_NeoPixel.h>

#define LIGHT 0
#define BUZZER 4
#define NUMPIXELS 4
#define LED 2
#define BUTTON 14

#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262


Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);

int scale[] = { NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4 };
int brightmelody[] = { 5, 5, 7, 5, 5, 7, 7, 5, 7, 5, 5, 7, 5, 5, 7, 7, 5, 7};
int brightdurations[] = { 8, 8, 4, 8, 8, 4, 4, 2, 4, 8, 8, 4, 8, 8, 4, 4, 2, 4};
int brightnoteLength = sizeof(brightmelody) / sizeof(int);

int darkmelody[] = { 5, 5, 7, 5, 5, 7, 7, 5, 7, 5, 5, 7, 5, 5, 7, 7, 5, 7};
int darkdurations[] = { 8, 8, 4, 8, 8, 4, 4, 2, 4, 8, 8, 4, 8, 8, 4, 4, 2, 4};
int darknoteLength = sizeof(brightmelody) / sizeof(int);

int buttonState = 0;  // variable for reading the pushbutton status


void setup() {
  pinMode(LIGHT, INPUT); 
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);

  pixels.begin(); 
  pixels.clear(); 
}

void loop() {
  buttonState = digitalRead(BUTTON);

  if(buttonState == LOW){
    if (digitalRead(0) == HIGH) {
      Serial.println("어두워요");

      pixels.setPixelColor(0, pixels.Color(190, 128, 232)); 
      pixels.setPixelColor(1, pixels.Color(248, 143, 160)); 
      pixels.setPixelColor(2, pixels.Color(100, 89, 36)); 
      pixels.setPixelColor(3, pixels.Color(167, 214, 244)); 
      pixels.show();

      for (int thisNote = 0; thisNote < darknoteLength; thisNote++) {
	      int duration = 1000 / darkdurations[thisNote];
	      tone(BUZZER, scale[darkmelody[thisNote]], duration);
	      int pause = duration * 1.30;
	      delay(pause);
	      noTone(BUZZER);
	      digitalWrite(BUZZER, HIGH);
      }
    }
    if (digitalRead(0) == LOW) {
      Serial.println("밝아요");

      pixels.setPixelColor(0, pixels.Color(190, 128, 232)); 
      pixels.setPixelColor(1, pixels.Color(248, 143, 160)); 
      pixels.setPixelColor(2, pixels.Color(100, 89, 36)); 
      pixels.setPixelColor(3, pixels.Color(167, 214, 244)); 
      pixels.show();
    
      for (int thisNote = 0; thisNote < brightnoteLength; thisNote++) {
	      int duration = 1000 / brightdurations[thisNote];
	      tone(BUZZER, scale[brightmelody[thisNote]], duration);
	      int pause = duration * 1.30;
	      delay(pause);
	      noTone(BUZZER);
	      digitalWrite(BUZZER, HIGH);
    }
    delay(5000);

  }

  else {
    pixels.clear(); 
  }
}
}