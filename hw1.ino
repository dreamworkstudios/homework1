int buzzer_pin = 2;

int imperialMarch[] = {2551, 2551, 2551, 3214, 2144, 2551, 3214, 2144, 2551, 1703, 1703, 1703, 1607, 2144, 2702, 3214, 2144, 2551};
long imperialMarchNoteLength[] = {500, 500, 500, 375, 125, 500, 375, 125, 1000, 500, 500, 500, 375, 125, 500, 375, 125, 1000};
int imperialMarchLength = 18;
int zelda_first[] = {3033, 2863, 2272, 1911};
int zelda_second[] = {4049, 3822, 3033, 2551};
int delayBetweenNotes = 50;
int delayBetweenMelodies = 5000;



void setup() {
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  for (int i = 0; i < imperialMarchLength; i++) {
    playNote(imperialMarch[i], imperialMarchNoteLength[i]);
    delay(delayBetweenNotes);
  }
  delay(delayBetweenMelodies);
  /*
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      playNote(zelda_first[i]);
      //delay(pauseBetweenConst);
    }
  }
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      playNote(zelda_second[i]);
      //delay(pauseBetweenConst);
    }
  }*/
}

void playNote(int notePause, long timePlaying) {
  long timeElapsed = 0;
  while (timeElapsed < timePlaying * 1000) {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(notePause);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(notePause);
    timeElapsed += 2 * notePause;
  }
}
