
#include <CheapStepper.h>
CheapStepper stepper (9, 10, 11, 12);

int encoder = 1;
int encoderp = 1;
int runner = 1;

byte a, b, x, y;
byte i = 0;
byte j = 0;

byte m = 0;
byte hold = 0;

int SmallStep = 2;
int BigStep = 2;

//_________________________________________________________________________________________

void setup( ){

    stepper.setRpm(10);

    pinMode(13, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A3, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(2), InterruptPinA, CHANGE );
    attachInterrupt(digitalPinToInterrupt(3), InterruptPinB, CHANGE);
    pinMode (4,INPUT); // Encoder
    pinMode (5,INPUT); // Encoder
    pinMode (7, INPUT_PULLUP);; // Links
    pinMode (8, INPUT_PULLUP); // Rechts

    digitalWrite(13, HIGH);
    digitalWrite(A0, HIGH);
    digitalWrite(A3, HIGH);
    delay(1000);
    digitalWrite(13, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(A3, LOW);

}

//_________________________________________________________________________________________

void loop( ){

    Feinlauf( );
    Schnelllauf( );
    Laeuferstrich( );
    Schrittmotor( );
    
}

//_________________________________________________________________________________________

void Feinlauf( ){
  
    if ( i == 4 ) { 
      encoder = encoder + SmallStep;
      runner  = runner  + 1;
      i = 0; 
    }

    if ( j == 4 ) {
      encoder = encoder - SmallStep;
      runner  = runner  - 1;
      j = 0; 
    }
}

//_________________________________________________________________________________________

void Schnelllauf( ){

  x = digitalRead(8);
  y = digitalRead(7);

    if ( x == LOW ) {
      encoder = encoder + BigStep;
      digitalWrite(13, LOW);
      digitalWrite(A0, HIGH);
      digitalWrite(A3, HIGH); 
    }
      
    if ( y == LOW ) {
      encoder = encoder - BigStep;
      digitalWrite(13, HIGH);
      digitalWrite(A0, HIGH);
      digitalWrite(A3, LOW); 
    }
    delay(10);
}

//_________________________________________________________________________________________

void Laeuferstrich( ){

    if ( runner > 3 ) runner = 1;
    if ( runner < 1 ) runner = 3;
}

//_________________________________________________________________________________________

void Schrittmotor( ){

    if ( encoder > encoderp ) { 
      
      stepper.moveTo(true, encoder);
      encoderp = encoder;

      digitalWrite(13, LOW);
      digitalWrite(A0, LOW);
      digitalWrite(A3, LOW);
      if ( runner == 1 ) digitalWrite(13, HIGH);
      if ( runner == 2 ) digitalWrite(A0, HIGH);
      if ( runner == 3 ) digitalWrite(A3, HIGH);
    }

    if ( encoder < encoderp ) {
      
      stepper.moveTo(false, encoder);
      encoderp = encoder;
      
      digitalWrite(13, LOW);
      digitalWrite(A0, LOW);
      digitalWrite(A3, LOW);
      if ( runner == 1 ) digitalWrite(13, HIGH);
      if ( runner == 2 ) digitalWrite(A0, HIGH);
      if ( runner == 3 ) digitalWrite(A3, HIGH);
    }
}

//_________________________________________________________________________________________

void InterruptPinA( ){

    a = digitalRead(5);
    b = digitalRead(4);
  
    if ( a == 0 && b == 1) i = 2;
    if ( a == 1 && b == 0 && i == 2) i = 4;
    
    a = 0; b = 0;
}

void InterruptPinB( ){

    a = digitalRead(5);
    b = digitalRead(4);
  
    if ( b == 0 && a == 1) j = 2;
    if ( b == 1 && a == 0 && j == 2) j = 4;
    
    a = 0; b = 0;
}

//_________________________________________________________________________________________
