#define trigPin 9
#define echoPin 10
#define relayPin 11
#define buzzerPin 12

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  Serial.begin(9600);
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  if (distance <10) {
     Serial.println("Distance is");
    Serial.println(distance);   
    digitalWrite(relayPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    
    }
    else{
    digitalWrite(relayPin, LOW);
    digitalWrite(buzzerPin, LOW);
    Serial.println("Distance is");
    Serial.println(distance);   
    delay(1000);
  }

  
}