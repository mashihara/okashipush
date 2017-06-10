#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int SERVO_PIN = 10;
const int BUTTON_PIN = 5;
const int SENSOR_TRIG_PIN = 6;
const int SENSOR_ECHO_PIN = 7;
boolean first = true;
boolean fuseru = false;
boolean agaru = false;

//======servo=====
int pos = 90;    // variable to store the servo position
int count = 0;

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
  boolean button = true;
  //======button=====
  if(digitalRead(BUTTON_PIN)==HIGH){
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
      if(Distance < 10){
        fuseru = true;
      }else{
        agaru = true;
      }
      Serial.print("Distance:");
      Serial.print(Distance);
      Serial.println(" cm");
    }
    //======servo=====
    if(fuseru && agaru){
      count += 1;
      pos += count*5;
      fuseru =false;
      agaru =false;
    }
    Serial.println("fuseru:");
    Serial.println(fuseru);
    Serial.println("agaru:");
    Serial.println(agaru);
    Serial.println("pos:");
    Serial.println(pos);
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  }
  delay(500);
}

