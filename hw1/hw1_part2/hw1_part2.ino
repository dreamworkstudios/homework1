#include <Servo.h>

//servo variables
int servo_pin = 3;
int servo_pos = 0;
bool going_up = true;
long millisecond_count = 0;
int servo_wait = 30;
Servo servo_motor;

//song variables
int buzzer_pin = 2;
int imperialMarch[] = {2551, 2551, 2551, 3214, 2144, 2551, 3214, 2144, 2551, 1703, 1703, 1703, 1607, 2144, 2702, 3214, 2144, 2551};
long imperialMarchNoteLength[] = {500, 500, 500, 375, 125, 500, 375, 125, 1000, 500, 500, 500, 375, 125, 500, 375, 125, 1000};
int imperialMarchLength = 18;
int delayBetweenNotes = 100;
int delayBetweenMelodies = 5000;

void setup() {
  servo_motor.attach(servo_pin);
  pinMode(buzzer_pin, OUTPUT);
  servo_motor.write(servo_pos);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  for (int i = 0; i < imperialMarchLength; i++) {
    playNote(imperialMarch[i], imperialMarchNoteLength[i]);
    delay_while_spinning_milliseconds(delayBetweenNotes);
  }
  delay_while_spinning_milliseconds(delayBetweenMelodies);
}

//Delay function that keeps the servo spinning, in milliseconds
void delay_while_spinning_milliseconds(int num_milliseconds) {
  int curr_milliseconds = 0;
  while (curr_milliseconds < num_milliseconds) {
    delay(1);
    millisecond_count += 1;
    if (millisecond_count % servo_wait == 0) {
      if (going_up) {
      servo_pos += 1;
      } else {
        servo_pos -= 1;
      }
      if (servo_pos <= 0) {
        servo_pos = 0;
        going_up = true;
      } else if (servo_pos >= 180) {
        servo_pos = 180;
        going_up = false;
      }
      servo_motor.write(servo_pos);
    }
    //resets the millisecond counter
    if (millisecond_count == 1000) {
      millisecond_count = 1;
    }
    curr_milliseconds += 1;
  }
}

void update_servo() {
  if (going_up) {
        servo_pos += 1;
      } else {
        servo_pos -= 1;
      }
      if (servo_pos <= 0) {
        servo_pos = 0;
        going_up = true;
      } else if (servo_pos >= 180) {
        servo_pos = 179;
        going_up = false;
      }
      servo_motor.write(servo_pos);
      delay(servo_wait);
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
  for (int i = 0; i < timeElapsed / (15 * 1000); i++) {
    update_servo();
  }
}
