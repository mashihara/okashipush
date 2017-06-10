#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int SERVO_PIN = 10;
const int BUTTON_PIN = 5;
const int SENSOR_TRIG_PIN = 6;
const int SENSOR_ECHO_PIN = 7;

//======servo=====
int pos = 0;    // variable to store the servo position

//===========sensor==========
double Duration = 0; //受信した間隔
double Distance = 0; //距離

void setup() {
  Serial.begin( 9600 );
  //======button=====
  pinMode(BUTTON_PIN, INPUT);
  //======servo=====
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  //===========sensor==========
  pinMode(SENSOR_ECHO_PIN,INPUT);
  pinMode(SENSOR_TRIG_PIN,OUTPUT);
}

void loop() {
  //本当はここをfalseではじめたい、けどうまくいかないので後回し
  boolean button = false;
  //======button=====
  if(digitalRead(BUTTON_PIN)==LOW){
    button = true;
  }
  if(button){
    //===========sensor==========
    digitalWrite( SENSOR_TRIG_PIN, LOW); 
    delayMicroseconds(2); 
    digitalWrite( SENSOR_TRIG_PIN, HIGH ); //超音波を出力
    delayMicroseconds( 10 ); //
    digitalWrite( SENSOR_TRIG_PIN, LOW );
    Duration = pulseIn( SENSOR_ECHO_PIN, HIGH ); //センサからの入力
    if (Duration > 0) {
      Duration = Duration/2; //往復距離を半分にする
      Distance = Duration*340*100/1000000; // 音速を340m/sに設定
      Serial.print("Distance:");
      Serial.print(Distance);
      Serial.println(" cm");
    }
    //======servo=====
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}

