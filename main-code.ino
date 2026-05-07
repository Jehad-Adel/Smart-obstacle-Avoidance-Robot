
const int ENA = 10; const int IN1 = 12; const int IN2 = 13; 
const int ENB = 11; const int IN3 = 8;  const int IN4 = 9;  

const int trigF = 2, echoF = 3;
const int trigL = 4, echoL = 5;
const int trigR = 6, echoR = 7;

bool autonomousMode = false; 
bool manualMode = false;     
int robotSpeed = 0;      
int autoSpeed = 120;     
int manualSpeed = 255;   
const int safeDist = 15;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(trigF, OUTPUT); pinMode(echoF, INPUT);
  pinMode(trigR, OUTPUT); pinMode(echoR, INPUT);
  pinMode(trigL, OUTPUT); pinMode(echoL, INPUT);
  stopRobot();
  Serial.println("System Ready: 'A' for Smart Auto | 'W' for Manual");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    if (command == 'W') { 
      autonomousMode = false;
      manualMode = true;
      robotSpeed = manualSpeed;
      stopRobot(); 
      Serial.println(">> MODE: MANUAL");
    } 
    else if (command == 'A') { 
      autonomousMode = true;
      manualMode = false;
      robotSpeed = autoSpeed;
      Serial.println(">> MODE: SMART AUTO");
    }

    if (manualMode) {
      handleManualControl(command);
    }
  }

  if (autonomousMode) {
    handleAutonomous();
  }
}

void handleManualControl(char cmd) {
  switch (cmd) {
    case 'F': moveForward();  break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft();     break;
    case 'R': turnRight();    break;
    case 'S': stopRobot();    break; 
  }
}

void handleAutonomous() {
  int distFront = readSensor(trigF, echoF);
  int distRight = readSensor(trigR, echoR);
  int distLeft  = readSensor(trigL, echoL);

  if (distFront > safeDist) {
    moveForward(); 
  } 
  else {
    stopRobot();
    delay(200);
    
    if (distRight > distLeft && distRight > safeDist) {
      Serial.println("Auto: Turning Right");
      turnRight();
      delay(400); 
    } 
    else if (distLeft > distRight && distLeft > safeDist) {
      Serial.println("Auto: Turning Left");
      turnLeft();
      delay(400);
    } 
    else {
      Serial.println("Auto: Full Block! Reversing");
      moveBackward();
      delay(50);
      
    }
    stopRobot();
    delay(200);
  }
}

int readSensor(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 25000); 
  int distance = duration * 0.034 / 2;
  return (distance <= 0) ? 400 : distance;
}
void moveForward() {
  analogWrite(ENA, robotSpeed); digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  analogWrite(ENB, robotSpeed); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void moveBackward() {
  analogWrite(ENA, robotSpeed); digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  analogWrite(ENB, robotSpeed); digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}
void turnLeft() {
  analogWrite(ENA, robotSpeed); digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  analogWrite(ENB, robotSpeed); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}
void turnRight() {
  analogWrite(ENA, robotSpeed); digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  analogWrite(ENB, robotSpeed); digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
}
void stopRobot() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}
