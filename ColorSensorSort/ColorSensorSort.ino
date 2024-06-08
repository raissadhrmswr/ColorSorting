#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "Template" //add with your own personal blynk template id
#define BLYNK_TEMPLATE_NAME "Conveyor" //add with your own personal blynk template name
#define BLYNK_AUTH_TOKEN "Token" //add with your own personal blynk auth token

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "WiFi"; //wifi name
char pass[] = "PassWord"; // wifi password


#define S0 18
#define S1 5
#define S2 21
#define S3 19
#define sensorOut 34

Servo servo1;
Servo servo2;

int frequency = 0;
int color=0;
String colorname;
int count_r=0;
int count_g=0;
int count_b=0;

int detectColor() {
  // activating red photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);//printing RED color frequency
  Serial.print("   ");
  delay(50);
   // activating blue photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  // activating green photodiodes to read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.print("   ");
  delay(50);
  delay(50);
//Readings are different for different setup

//change the readings according your project and readings detected

  if(R<B & R<G ){
    color = 1; // Red
    Serial.print("Detected Color is = ");
    colorname = String("RED");
    Serial.println(colorname);
    count_r = count_r +1;
    Blynk.virtualWrite(V0, count_r); //change to integer
  }
  if(G<R & G<B){
    color = 2; // Green
    Serial.print("Detected Color is = ");
    colorname = String("GREEN");
    Serial.println(colorname);
    count_g = count_g +1;
    Blynk.virtualWrite(V1, count_g);
  }
  if (B<G & B<R){
    color = 3; // Blue
    Serial.print("Detected Color is = ");
    colorname = String("BLUE");
    Serial.println(colorname);
    count_b = count_b +1;
    Blynk.virtualWrite(V2, count_b);
  }
  return color; 
}

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("System Ready");

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  servo1.attach(33);
  servo2.attach(25);
  //frequency-scaling to 20% selected
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop(){

  //initial position of servo motor
  servo1.write(0);
  servo2.write(0);

  color = detectColor();
  switch (color) {
    case 1: //red
    servo1.write(100);
    delay(5000);
    servo1.write(0);
    break;

    case 2: //green
    servo2.write(100);
    delay(5000);
    servo2.write(0);
    break;

    case 3: //blue
    break;

    case 0:
    break;

  }


  delay(10000);
}
