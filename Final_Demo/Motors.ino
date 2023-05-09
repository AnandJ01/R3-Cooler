// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;


int motor2Pin3 = 25;
int motor2Pin4 = 33;
int enable2Pin = 32;

// Setting PWM properties
const int freq = 1000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 60;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);
  // digitalWrite(enable1Pin, HIGH);
  // digitalWrite(enable2Pin, HIGH);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  ledcWrite(pwmChannel, dutyCycle); 
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);
  delay(5000);


  // // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  delay(3000);

  // // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW); 
  delay(5000);

  // // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  delay(3000);

  // //Right Turn
  Serial.println("Right Turn");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);   
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH); 
  delay(5000);
  
  // //Left Turn
  Serial.println("Left Turn");
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW); 
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(5000);


}