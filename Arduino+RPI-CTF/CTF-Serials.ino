#include <TM1637Display.h>

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int buzzerPin = 12;

//7 Segment Display
const byte DISPLAY_CLK_PIN = 6;
const byte DISPLAY_DIO_PIN = 5;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Create TM1637Display object
TM1637Display display = TM1637Display(DISPLAY_CLK_PIN, DISPLAY_DIO_PIN);

const byte wordGOOD[] = {
  SEG_A | SEG_C | SEG_D | SEG_E | SEG_F,              
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,      
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,      
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G               
};

const byte nope[] = {
  SEG_C | SEG_E | SEG_G,                          
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,          
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           
};

const byte wordYAY[] = {
  0x00,                                               
  SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,              
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,      
  SEG_B | SEG_C | SEG_D | SEG_F | SEG_G               
};

const byte flagFourPin[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,               
  SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,               
  SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,                       
  SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G                
};



void setup() {
  Serial.begin(9600);
  display.setBrightness(7);  // Set brightness (0-7)
  Serial.println("Ready!");
}

void loop() {
    display.clear();

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    Serial.println("Input: " + input);

    if (input == "pass") {
      pass();
    }
    else if (input == "fail"){
      fail();
    }
    else if (input == "four"){
      flagFour();
    }
    else if (input == "celebrate"){
      celebrate();
    }
    
  }
}


void pass() {
  Serial.println("pass() function called!");

  display.clear();
  rgbColor(0, 255, 0);  // Green
  display.setSegments(wordGOOD);

  
  int melody[] = { NOTE_C4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_C5, 8 };
  int noteCount = 4;  
  int tempo = 120;
  int wholeNote = (60000 * 4) / tempo;

  unsigned long startTime = millis();
  unsigned long currentTime = millis();

  while (currentTime - startTime < 5000) {
    for (int i = 0; i < noteCount * 2; i += 2) {
      int note = melody[i];
      int divider = melody[i + 1];
      int noteDuration;

      if (divider > 0) {
        noteDuration = wholeNote / divider;
      } else {
        noteDuration = (wholeNote / abs(divider)) * 3 / 2; // dotted note
      }

      tone(buzzerPin, note, noteDuration * 0.9);
      delay(noteDuration);
      noTone(buzzerPin);

      currentTime = millis();
      if (currentTime - startTime >= 10000) {
        break; // Exit if time is up
      }
    }
  }

  noTone(buzzerPin);
  rgbColor(0, 0, 0);  // Turn off LED
  display.clear();    // Turn off 7-segment display
}



void fail() {
  Serial.println("fail() function called!");

  display.clear();
  rgbColor(255, 0, 0);  // Red
  display.setSegments(nope);

  int melody[] = { NOTE_A3, 8, NOTE_B3, 8, NOTE_C4, 8, NOTE_D4, 8 };  // A fail tone melody
  int noteCount = 4;  
  int tempo = 100;
  int wholeNote = (60000 * 4) / tempo;

  unsigned long startTime = millis();
  unsigned long currentTime = millis();

  while (currentTime - startTime < 5000) {
    for (int i = 0; i < noteCount * 2; i += 2) {
      int note = melody[i];
      int divider = melody[i + 1];
      int noteDuration;

      if (divider > 0) {
        noteDuration = wholeNote / divider;
      } else {
        noteDuration = (wholeNote / abs(divider)) * 3 / 2; // dotted note
      }

      tone(buzzerPin, note, noteDuration * 0.9);
      delay(noteDuration);
      noTone(buzzerPin);

      currentTime = millis();
      if (currentTime - startTime >= 10000) {
        break; 
      }
    }
  }

  noTone(buzzerPin);
  rgbColor(0, 0, 0);  // Turn off LED
  display.clear();    // Turn off 7-segment display
}


void rgbColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void celebrate() {
  display.clear();
  rgbColor(255, 0, 0);  
  display.setSegments(wordYAY);

  int colors[][3] = {
    {255, 0, 0},   // Red
    {0, 255, 0},   // Green
    {0, 0, 255},   // Blue
    {255, 255, 0}, // Yellow
    {0, 255, 255}, // Cyan
    {255, 0, 255}, // Magenta
    {255, 255, 255} // White
  };
  int colorCount = sizeof(colors) / sizeof(colors[0]);
  int colorIndex = 0;

  int tempo = 160;
  int melody[] = {

    REST,1,
    REST,1,
    NOTE_C4,4, NOTE_E4,4, NOTE_G4,4, NOTE_E4,4, 
    NOTE_C4,4, NOTE_E4,8, NOTE_G4,-4, NOTE_E4,4,
    NOTE_A3,4, NOTE_C4,4, NOTE_E4,4, NOTE_C4,4,
    NOTE_A3,4, NOTE_C4,8, NOTE_E4,-4, NOTE_C4,4,
    NOTE_G3,4, NOTE_B3,4, NOTE_D4,4, NOTE_B3,4,
    NOTE_G3,4, NOTE_B3,8, NOTE_D4,-4, NOTE_B3,4,

    NOTE_G3,4, NOTE_G3,8, NOTE_G3,-4, NOTE_G3,8, NOTE_G3,4, 
    NOTE_G3,4, NOTE_G3,4, NOTE_G3,8, NOTE_G3,4,
    NOTE_C4,4, NOTE_E4,4, NOTE_G4,4, NOTE_E4,4, 
    NOTE_C4,4, NOTE_E4,8, NOTE_G4,-4, NOTE_E4,4,
    NOTE_A3,4, NOTE_C4,4, NOTE_E4,4, NOTE_C4,4,
    NOTE_A3,4, NOTE_C4,8, NOTE_E4,-4, NOTE_C4,4,
    NOTE_G3,4, NOTE_B3,4, NOTE_D4,4, NOTE_B3,4,
    NOTE_G3,4, NOTE_B3,8, NOTE_D4,-4, NOTE_B3,4,

    NOTE_G3,-1, 
  
};

  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote += 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    // Sync RGB with current note
    rgbColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    colorIndex = (colorIndex + 1) % colorCount; // Cycle through colors

    tone(buzzerPin, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);

    noTone(buzzerPin);
  }

  // Turn off the RGB at the end
  rgbColor(0, 0, 0);

}

void flagFour() {
  int tempo = 114;
  
  int melody[] = {  
 
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4,
 
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
   
  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
 
  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8,
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
 
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  NOTE_E5,4, NOTE_D5,2, REST,4,
  
};

  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  
  int divider = 0, noteDuration = 0;
  int colors[][3] = {
    {255, 0, 0},   // Red
    {0, 255, 0},   // Green
    {0, 0, 255},   // Blue
    {255, 255, 0}, // Yellow
    {0, 255, 255}, // Cyan
    {255, 0, 255}, // Magenta
    {255, 255, 255} // White
  };
  int colorCount = sizeof(colors) / sizeof(colors[0]);
  int colorIndex = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration for dotted notes
    }

    // Sync RGB with current note
    rgbColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    colorIndex = (colorIndex + 1) % colorCount; // Cycle through colors

    // Play the note
    tone(buzzerPin, melody[thisNote], noteDuration * 0.9);

    delay(noteDuration);

    noTone(buzzerPin);
  }
unsigned long startTime = millis();
unsigned long currentTime = millis();

while (currentTime - startTime < 10000) {
    display.setSegments(flagFourPin);
    rgbColor(0,0,255);

    if (millis() - currentTime >= 1000) {
        currentTime = millis(); 
    }
}
    display.clear();

    rgbColor(0, 0, 0);
}

