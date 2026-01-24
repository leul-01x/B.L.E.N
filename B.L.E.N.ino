const int trigFront = 7;
const int echoFront = 8;
const int trigDown = 9;
const int echoDown = 10;
const int buzzerPin = 3;
const int vibrationMotorPin = 5;

long durationFront, durationDown;
int distanceFront, distanceDown;

void setup() {
  Serial.begin(9600);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigDown, OUTPUT);
  pinMode(echoDown, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(vibrationMotorPin, OUTPUT);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

void loop() {
  distanceFront = getDistance(trigFront, echoFront);
  delay(50);
  distanceDown = getDistance(trigDown, echoDown);

  Serial.print("Front: ");
  Serial.print(distanceFront);
  Serial.print(" cm | Down: ");
  Serial.print(distanceDown);
  Serial.println(" cm");

  if (distanceFront > 0 && distanceFront <= 50) {
    int flickerDelay = map(distanceFront, 50, 0, 400, 50);
    tone(buzzerPin, 1000);
    delay(flickerDelay);
    noTone(buzzerPin);
    delay(flickerDelay);
  } 
  else {
    noTone(buzzerPin);
  }

  if (distanceDown > 0 && distanceDown <= 30) {
    digitalWrite(vibrationMotorPin, HIGH);
  } else {
    digitalWrite(vibrationMotorPin, LOW);
  }
  delay(50);
}