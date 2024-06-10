#include <Adafruit_NeoPixel.h>

// #define LIGHT 0
#define BUZZER 4
#define NUMPIXELS 4
#define LED 5

#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_D2  73
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_G2  98
#define NOTE_A2  110
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_D3  133
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_D5  311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);

int brightscale[] = {NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_D5, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
int brightmelody[] = { 7, 9, 9, 9, 7, 9, 7, 9, 9, 9, 11, 9, 14, 12, 12, 12, 12, 12, 12, 12, 11, 11, 11, 9, 11, 8, 8, 9, 9, 11, 11, 12, 13, 10, 9, 15, 15, 15, 15, 13, 15, 14};
int brightdurations[] = { 6, 6, 6, 3, 6, 3, 6, 6, 6, 3, 6, 3, 6, 6, 3, 6, 6, 3, 6, 6, 3, 4, 6, 3, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 6, 6, 6, 4, 5, 4, 2, 6, 6};
int brightnoteLength = sizeof(brightmelody) / sizeof(int);

int darkscale[] = {NOTE_B1, NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_B2, NOTE_C3, NOTE_D3, NOTE_D4, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4};
int darkmelody[] = {1, 1, 3, 2, 1, 5, 5, 6, 7, 8, 5, 4, 4, 6, 5, 4, 5, 4, 3, 2, 5, 1, 8, 8, 8, 8, 7, 6, 5, 4, 5, 6, 7, 5, 8, 8, 8, 8, 8, 7, 6, 5, 5, 9, 9, 8, 9, 8, 9, 9, 9, 9, 9, 8, 8, 7, 8, 9, 9, 5, 8, 9, 9, 9, 9, 9, 8, 8, 7, 8, 9, 9, 5};
int darkdurations[] = {3, 3, 3, 4, 3, 1, 4, 3, 1, 3, 1, 3, 3, 3, 4, 3, 2, 2, 3, 1, 3, 1, 3, 3, 2, 3, 5, 4, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 5, 4, 2, 3, 3, 3, 3, 1, 4, 3, 1, 3, 3, 3, 1, 3, 2, 3, 3, 3, 2, 3, 1, 3, 3, 3, 1, 3, 2, 3, 3, 3, 1};
int darknoteLength = sizeof(darkmelody) / sizeof(int);

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pinMode(BUZZER, OUTPUT);
  
}

void loop() {
    int inputValue = analogRead(A0);
      Serial.println(inputValue);
    if (inputValue > 400 ) {
      Serial.println("어두워요");

      pixels.setPixelColor(0, pixels.Color(16, 21, 30)); 
      pixels.setPixelColor(1, pixels.Color(22, 16, 31)); 
      pixels.setPixelColor(2, pixels.Color(26, 39, 49)); 
      pixels.setPixelColor(3, pixels.Color(15, 31, 24)); 
      pixels.show();

      for (int thisNote = 0; thisNote < darknoteLength; thisNote++) {
        int duration = 1000 / darkdurations[thisNote];
        tone(BUZZER, darkscale[darkmelody[thisNote]], duration);
        int pause = duration * 1.30;
        delay(pause);
        noTone(BUZZER);
      }
    }
    else if (inputValue > 200) {
      Serial.println("밝아요");

      pixels.setPixelColor(0, pixels.Color(190, 128, 232)); 
      pixels.setPixelColor(1, pixels.Color(248, 143, 160)); 
      pixels.setPixelColor(2, pixels.Color(100, 89, 36)); 
      pixels.setPixelColor(3, pixels.Color(167, 214, 244)); 
      pixels.show();
    
      for (int thisNote = 0; thisNote < brightnoteLength; thisNote++) {
        int duration = 1000 / brightdurations[thisNote];
        tone(BUZZER, brightscale[brightmelody[thisNote]], duration);
        int pause = duration * 1.30;
        delay(pause);
        noTone(BUZZER);
      }
    }
    delay(5000); // 추가 대기 시간
    pixels.clear();
    Serial.println("off");
}
