#include <Arduino.h>
#include <pitches.h>

#define speakerPin 3
#define ledPin 2
#define BUZZER_PIN 3

//Sensor pins
const int trigPin = 11;
const int echoPin = 12;
//Motor pins
const int MLS = 6;
const int ML1 = 7;
const int ML2 = 8;

const int MRS = 5;
const int MR2 = 9;
const int MR1 = 10;

int speed = 130;
int slow = speed/2;
float duration, distance;

bool bored = false;
int stack = 0;

void PlaySongPotter();
void PlaySongGOT();


void MeasureDistance(){

  //Pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Echo
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  delay(50);
  

}

void StartupPotter();

void phrase1() {
    
    int k = random(1000,2000);
    digitalWrite(ledPin, HIGH);
    for (int i = 0; i <=  random(100,2000); i++){
        
        tone(speakerPin, k+(-i*2));          
        delay(random(.9,2));             
    }  
    digitalWrite(ledPin, LOW);
    for (int i = 0; i <= random(100,1000); i++){
        
        tone(speakerPin, k + (i * 10));          
        delay(random(.9,2));             
    } 
}

void phrase2() {
    
    int k = random(1000,2000);
    digitalWrite(ledPin, HIGH);
    for (int i = 0; i <= random(100,2000); i++){
        
        tone(speakerPin, k+(i*2));          
        delay(random(.9,2));             
    } 
    digitalWrite(ledPin, LOW);
    for (int i = 0; i <= random(100,1000); i++){
        
        tone(speakerPin, k + (-i * 10));          
        delay(random(.9,2));             
    } 
}


void Sound() {
    
    int K = 2000;
    switch (random(1,7)) {
        
        case 1:phrase1(); break;
        case 2:phrase2(); break;
        case 3:phrase1(); phrase2(); break;
        case 4:phrase1(); phrase2(); phrase1();break;
        case 5:phrase1(); phrase2(); phrase1(); phrase2(); phrase1();break;
        case 6:phrase2(); phrase1(); phrase2(); break;
    }
    for (int i = 0; i <= random(3, 9); i++){
        
        digitalWrite(ledPin, HIGH);
        tone(speakerPin, K + random(-1700, 2000));          
        delay(random(70, 170));           
        digitalWrite(ledPin, LOW);
        noTone(speakerPin);         
        delay(random(0, 30));             
    } 
    noTone(speakerPin);         
    delay(20);             
}

bool SafetyCheck(){
  MeasureDistance();
  if (distance < 30)
  {
    return false;
  } else {
    return true;
  }
  
}

void Stop(){
  digitalWrite(MR1, LOW);
  digitalWrite(ML1, LOW);
  digitalWrite(MR2, LOW);
  digitalWrite(ML2, LOW);
}


void Forward(){

  analogWrite(MRS, speed);
  analogWrite(MLS, speed);

  digitalWrite(MR1, HIGH);
  digitalWrite(ML1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML2, LOW);

}


void Backward(float time){

  analogWrite(MRS, speed);
  analogWrite(MLS, speed);

  digitalWrite(MR1, LOW);
  digitalWrite(ML1, LOW);
  digitalWrite(MR2, HIGH);
  digitalWrite(ML2, HIGH);  
  delay(time*1000);

}

void SpotTurnLeft(float time){

  analogWrite(MRS, speed);

  digitalWrite(MR1, HIGH);
  digitalWrite(ML1, LOW);
  digitalWrite(MR2, LOW);
  digitalWrite(ML2, LOW);  
  delay(time*1000);

}

void SpotTurnRight(float time){

  analogWrite(MLS, speed);

  digitalWrite(MR1, LOW);
  digitalWrite(ML1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML2, LOW);  
  delay(time*1000);

}

void Right(float time){

  analogWrite(MRS, slow);
  analogWrite(MLS, speed);

  digitalWrite(MR1, HIGH);
  digitalWrite(ML1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML2, LOW); 
  delay(time*1000);

}

void Left(float time){

  analogWrite(MRS, speed);
  analogWrite(MLS, slow);

  digitalWrite(MR1, HIGH);
  digitalWrite(ML1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML2, LOW); 
  delay(time*1000);

}

void Swiggle(){
  for (size_t i = 0; i < random(2,8); i++)
  {
    Right(0.5);
    Left(0.5);
    if (SafetyCheck() == false)
    {
      break;
    }
    for (int i = 0; i <= random(2, 6); i++){
        
        tone(speakerPin, 2000 + random(-1700, 2000));          
        delay(random(70, 170));           
        noTone(speakerPin);         
        delay(random(0, 30));             
    } 
  }
  
}

void Spin(int dir){
  if (dir == 1)
  {
  analogWrite(MRS, speed);
  analogWrite(MLS, speed);
  digitalWrite(MR1, LOW);
  digitalWrite(ML1, HIGH);
  digitalWrite(MR2, HIGH);
  digitalWrite(ML2, LOW);  
  delay(1000);
  } else {
    analogWrite(MRS, speed);
    analogWrite(MLS, speed);
    digitalWrite(MR1, HIGH);
    digitalWrite(ML1, LOW);
    digitalWrite(MR2, LOW);
    digitalWrite(ML2, HIGH);  
    delay(1000);
  }
  
  
}

void Piruetti(){
  switch (random(1,2))
  {
    case 1: Sound(); Spin(1); break;
    case 2: Sound(); Spin(2); break;
  }
}


void setup() {

  pinMode(A0, INPUT);

  //Sensor pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Speaker and led
  randomSeed(analogRead(0));
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(speakerPin, LOW);

  //Motor pins modes
  pinMode(MLS, OUTPUT);
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  pinMode(MRS, OUTPUT);
  Stop();
  if (digitalRead(A0) == HIGH)
  {
    StartupPotter();
  }
  
}

void StartupPotter(){
  
  Forward();
  delay(3000);  
  Stop();
  Piruetti();
  Stop();
  PlaySongPotter();
  Piruetti();
}

void loop() {
  stack++;

  if (stack >= 300)
  {
    bored = true;
  }
  

  if (bored == true)
  {
    stack = 0;
    bored = false;
    switch (random(1,2))
    {
    case 1: SpotTurnLeft(0.1); PlaySongGOT(); break;
    case 2: Stop(); PlaySongPotter(); break;
    }
  }
  
  
  MeasureDistance();
  if (distance < 10)
  {
    Backward(1.5);
  }
  
  if (distance < 30)
  {
    Stop();
    Sound();
    float time = random(0.5,2);
    switch (random(1,2))
      {
      case 1: SpotTurnLeft(time); break;
      case 2: SpotTurnRight(time); break;

      }
  } else if (distance > 170 && stack > 80)
  {
    switch (random(1,4))
    {
      case 1: Piruetti(); break;
      case 2: Swiggle(); break;
      case 3: Stop(); Sound(); delay(random(1000,2000)); Sound(); break;
      case 4: Forward();

    }
  } else {
    Forward();
  }

}



void PlaySongPotter(){

  int melody[] = {
  REST, NOTE_D4,
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_D5,
  NOTE_C5, 
  NOTE_A4,
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_F4, NOTE_GS4,
  NOTE_D4, 
  NOTE_D4,
  
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_D5,
  NOTE_F5, NOTE_E5,
  NOTE_DS5, NOTE_B4,
  NOTE_DS5, NOTE_D5, NOTE_CS5,
  NOTE_CS4, NOTE_B4,
  NOTE_G4,
  NOTE_AS4,
   
  NOTE_D5, NOTE_AS4,
  NOTE_D5, NOTE_AS4,
  NOTE_DS5, NOTE_D5,
  NOTE_CS5, NOTE_A4,
  NOTE_AS4, NOTE_D5, NOTE_CS5,
  NOTE_CS4, NOTE_D4,
  NOTE_D5, 
  REST, NOTE_AS4,  
  
  NOTE_D5, NOTE_AS4,
  NOTE_D5, NOTE_AS4,
  NOTE_F5, NOTE_E5,
  NOTE_DS5, NOTE_B4,
  NOTE_DS5, NOTE_D5, NOTE_CS5,
  NOTE_CS4, NOTE_AS4,
  NOTE_G4
};

int durations[] = {
  2, 4,
  4, 8, 4,
  2, 4,
  2, 
  2,
  4, 8, 4,
  2, 4,
  1, 
  4,
  
  4, 8, 4,
  2, 4,
  2, 4,
  2, 4,
  4, 8, 4,
  2, 4,
  1,
  4,
   
  2, 4,
  2, 4,
  2, 4,
  2, 4,
  4, 8, 4,
  2, 4,
  1, 
  4, 4,  
  
  2, 4,
  2, 4,
  2, 4,
  2, 4,
  4, 8, 4,
  2, 4,
  1
};

  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(BUZZER_PIN);
  }
}

void PlaySongGOT(){

int melody[] = {
  NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_C4,
  
  NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_D4,
  NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_C4,
  
  NOTE_G4, NOTE_C4,
  
  NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
  NOTE_D4,
  NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_F4, NOTE_AS3,
  NOTE_DS4, NOTE_D4, NOTE_C4,
  NOTE_G4, NOTE_C4,
  NOTE_DS4, NOTE_F4, NOTE_G4,  NOTE_C4, NOTE_DS4, NOTE_F4,
  
  NOTE_D4,
  NOTE_F4, NOTE_AS3,
  NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_AS3,
  NOTE_C4,
  NOTE_C5,
  NOTE_AS4,
  NOTE_C4,
  NOTE_G4,
  NOTE_DS4,
  NOTE_DS4, NOTE_F4,
  NOTE_G4,
  
  NOTE_C5,
  NOTE_AS4,
  NOTE_C4,
  NOTE_G4,
  NOTE_DS4,
  NOTE_DS4, NOTE_D4,
  NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4,
  NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4,
  
  REST, NOTE_GS5, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_GS5, NOTE_AS5,
  NOTE_C6, NOTE_G5, NOTE_GS5, NOTE_AS5, NOTE_C6, NOTE_G5, NOTE_GS5, NOTE_AS5
};

int durations[] = {
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  4, 4,
  
  16, 16, 4, 4, 16, 16,
  1,
  4, 4,
  16, 16, 4, 4,
  16, 16, 1,
  
  4, 4,
  
  16, 16, 4, 4, 16, 16,
  1,
  4, 4,
  16, 16, 4, 4,
  16, 16, 1,
  4, 4,
  16, 16, 4, 4, 16, 16,
  
  2,
  4, 4,
  8, 8, 8, 8,
  1,
  2,
  2,
  2,
  2,
  2,
  4, 4,
  1,
  
  2,
  2,
  2,
  2,
  2,
  4, 4,
  8, 8, 16, 16, 8, 8, 16, 16,
  8, 8, 16, 16, 8, 8, 16, 16,
  
  4, 16, 16, 8, 8, 16, 16,
  8, 16, 16, 16, 8, 8, 16, 16
};

  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {

    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    noTone(BUZZER_PIN);
  }
}