#include <Servo.h>

Servo dustbinServo;

int trigPin = 9;
int echoPin = 10;
int ledPin = 7;

long duration;
int distance;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  dustbinServo.attach(6);

  dustbinServo.write(0); // lid closed
  Serial.begin(9600);
}

void loop()
{
  // Send ultrasonic signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Receive signal
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance < 20)   // Hand detected
  {
    digitalWrite(ledPin, HIGH);
    dustbinServo.write(90);   // open lid
    delay(3000);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    dustbinServo.write(0);    // close lid
  }

  delay(200);
}
