#include <Servo.h> // servo library 
Servo myservo1, myservo2, myservo3, myservo4; // servo name

char t; //received from the application
int pos1 = 90;
int pos2 = 90;
//int pos = 0;
int trig1 = 5;
int trig2 = 12;
int trig3 = 13;
int echo1 = A0;
int echo2 = A2;
int echo3 = A3;
float totaltime1, totaldistance1, distance1;
float totaltime2, totaldistance2, distance2;
float totaltime3, totaldistance3, distance3;

//--- Motors---
int rf = 8;  //IN1
int rb = 7;  //IN2
int lf = 2;  //IN3
int lb = 4;  //IN4

//-------------------
void ultrasonic() {
  digitalWrite(trig1, LOW);
  delayMicroseconds(10);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  
  totaltime1 = pulseIn(echo1, HIGH);
  totaldistance1 = 343*totaltime1*0.000001;
  distance1 = (totaldistance1/2)*100;
  //-------------------

  digitalWrite(trig2, LOW);
  delayMicroseconds(10);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  
  totaltime2 = pulseIn(echo2, HIGH);
  totaldistance2 = 343*totaltime2*0.000001;
  distance2 = (totaldistance2/2)*100;
  //-------------------

  digitalWrite(trig3, LOW);
  delayMicroseconds(10);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  
  totaltime3 = pulseIn(echo3, HIGH);
  totaldistance3 = 343*totaltime3*0.000001;
  distance3 = (totaldistance3/2)*100;
  Serial.print("L: ");
  Serial.print(distance1);
  Serial.print("| F: ");
  Serial.print(distance2);
  Serial.print("| R: ");
  Serial.println(distance3);
}


void setup()
{
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);

  myservo1.attach(6); // attach servo signal wire to pin 9
  myservo2.attach(9);
  myservo3.attach(10); //gripper
  //myservo4.attach(11); //base

  myservo1.write(pos1);   
  myservo2.write(pos2);   
  myservo3.write(0);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    t = Serial.read();
    //---SERVO1----
    while (t == 'j') {
      pos1 += 10;
      t = Serial.read();
      if (pos1 <= 180) {
        myservo1.write(pos1);
      } else {
        pos1-=10;
        break;
      }
    }
    while (t == 'h') {
      pos1 -= 10;
      t = Serial.read();
      if (pos1 >= 0) {
        myservo1.write(pos1);
      } else {
        pos1+=10;
        break;
      }
    }

    //----SERVO2-----
    while (t == 'J') {
      pos2 += 10;
      t = Serial.read();
      if (pos2 <= 180) {
        myservo2.write(pos2);
      } else {
        pos2-=10;
        break;
      }
    }
    while (t == 'H') {
      pos2 -= 10;
      t = Serial.read();
      if (pos2 >= 0) {
        myservo2.write(pos2);
      } else {
        pos2+=10;
        break;
      }
    }

    //------------------
    if(t == 'O') {
        myservo3.write(130);  
      }
      if(t == 'C') {
        myservo3.write(0);
      }
      if (t == 'a') {       
      myservo4.attach(11);
      myservo4.write(120);
      delay(20);            
      Serial.println(t);
    }
    if (t == 'c') {         
      myservo4.attach(11);
      myservo4.write(50);
      delay(20);            
      Serial.println(t);
    }
    if (t == 'p') {
      myservo4.detach();
      Serial.println(t);
    }
  }
  
  //------MOTORS WITH ULTRASONIC------------------------
  //turn ultrasonic ON
  if(t == 'U') {
    ultrasonic();
  }
  //turn ultrasonic OFF
  if(t == 'u') {
    
  }
 
  //---While ultrasonic sensors are running-----
  //FORWARD BUTTON
  if(t == 'F') {
    digitalWrite(rf, HIGH);
    digitalWrite(rb, LOW);
    digitalWrite(lf, HIGH);
    digitalWrite(lb, LOW);
    ultrasonic();
  }
  //STOP BUTTON
  if(t == 'S'){
    digitalWrite(rf, LOW);
    digitalWrite(rb, LOW);
    digitalWrite(lf, LOW);
    digitalWrite(lb, LOW);
    ultrasonic();
  }
  //BACKWARD BUTTON
  if(t == 'B'){
    digitalWrite(rf, LOW);
    digitalWrite(rb, HIGH);
    digitalWrite(lf, LOW);
    digitalWrite(lb, HIGH);
    ultrasonic();
  }
  //RIGHT BUTTON
  if(t == 'R'){
    digitalWrite(rf, LOW);
    digitalWrite(rb, HIGH);
    digitalWrite(lf, HIGH);
    digitalWrite(lb, LOW);
    ultrasonic();
  }
  //LEFT BUTTON
  if(t == 'L'){
    digitalWrite(rf, HIGH);
    digitalWrite(rb, LOW);
    digitalWrite(lf, LOW);
    digitalWrite(lb, HIGH);
    ultrasonic();
  }

  //---No ultrasonic sensors running---------
  //FORWARD BUTTON
  if(t == 'f') {
    digitalWrite(rf, HIGH);
    digitalWrite(rb, LOW);
    digitalWrite(lf, HIGH);
    digitalWrite(lb, LOW);
  }
  //STOP BUTTON
  if(t == 's'){
    digitalWrite(rf, LOW);
    digitalWrite(rb, LOW);
    digitalWrite(lf, LOW);
    digitalWrite(lb, LOW);
  }
  //BACKWARD BUTTON
  if(t == 'b'){
    digitalWrite(rf, LOW);
    digitalWrite(rb, HIGH);
    digitalWrite(lf, LOW);
    digitalWrite(lb, HIGH);
  }
  //RIGHT BUTTON
  if(t == 'r'){
    digitalWrite(rf, LOW);
    digitalWrite(rb, HIGH);
    digitalWrite(lf, HIGH);
    digitalWrite(lb, LOW);
  }
  //LEFT BUTTON
  if(t == 'l'){
    digitalWrite(rf, HIGH);
    digitalWrite(rb, LOW);
    digitalWrite(lf, LOW);
    digitalWrite(lb, HIGH);
  }
  //----------------------------
  
}
