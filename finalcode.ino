const int m1_a = 5;
const int m1_b = 6;
const int m2_a = 9;
const int m2_b = 10;

const int mid_trig = 7;
const int mid_echo = 8;
const int right_trig = 11;
const int right_echo = 12;
const int left_trig = 2;
const int left_echo = 3;

// Base speeds for driving straight
const int m1_speed = 110;
const int m2_speed = 100; 

// --- DIFFERENTIAL TURN SPEEDS ---
// Adjust these to change the radius of the turn
const int turn_speed_fast = 160; // Outside wheel speeds up
const int turn_speed_slow = 100;  // Inside wheel slows down

// CALIBRATION REQUIRED: Because the robot is now drawing an arc instead of 
// spinning in place, it will take slightly longer to reach 90 degrees.
const int turnTime = 2000; 

// The memory states
enum Movement { FORWARD, BACKWARD, LEFT, STOPPED };
Movement currentMove = STOPPED;

void setup() {
  pinMode(m1_a, OUTPUT);
  pinMode(m1_b, OUTPUT);
  pinMode(m2_a, OUTPUT);
  pinMode(m2_b, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(mid_trig, OUTPUT);
  pinMode(mid_echo, INPUT);
  pinMode(right_trig, OUTPUT);
  pinMode(right_echo, INPUT);
  pinMode(left_trig, OUTPUT);
  pinMode(left_echo, INPUT);
  
  // Quick startup blink
  for(int i=0; i<5; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }

  stopAll();
  delay(2000);

  digitalWrite(13, HIGH);
  
  // Execute the square path
  executePath();
  
  digitalWrite(13, LOW);
}

void loop() {
  // Main code runs repeatedly
}

// --- THE SQUARE PATH LOGIC ---
void executePath(){
  for(int i = 0; i < 4; i++) {
    moveForward();
    smartDelay(3000); 
    
    stopAll();
    smartDelay(500);  
    

    moveBackward();
    smartDelay(3000);
    // moveLeft();
    // smartDelay(turnTime); 
    
    stopAll();
    smartDelay(500);  
  }
}

// --- THE PAUSE & RESUME LOGIC ---
void smartDelay(unsigned long timeToWait) {
  unsigned long startTime = millis();
  unsigned long elapsedTime = 0;

  while (elapsedTime < timeToWait) {
    
    if (isObstacleDetected()) {
      haltHardware(); 
      
      while (isObstacleDetected()) {
        delay(50); 
      }
      
      resumeMovement();
      startTime = millis() - elapsedTime; 
    }

    elapsedTime = millis() - startTime;
    delay(20); 
  }
}

// --- SENSOR FUNCTIONS ---
bool isObstacleDetected() {
  long dMid = getDistance(mid_trig, mid_echo);
  long dLeft = getDistance(left_trig, left_echo);
  long dRight = getDistance(right_trig, right_echo);

  if (dMid > 0 && dMid <= 10) return true;
  if (dLeft > 0 && dLeft <= 10) return true;
  if (dRight > 0 && dRight <= 10) return true;

  return false; 
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000); 
  
  if (duration == 0) return 999; 
  
  long distance = duration * 0.034 / 2; 
  return distance;
}

// --- MOVEMENT FUNCTIONS ---
void moveForward() {
  currentMove = FORWARD; 
  analogWrite(m1_a, m1_speed);
  digitalWrite(m1_b, LOW);  
  analogWrite(m2_a, m2_speed);
  digitalWrite(m2_b, LOW);
}

void moveBackward() {
  currentMove = BACKWARD; 
  digitalWrite(m1_a, LOW);  
  analogWrite(m1_b, m1_speed);
  digitalWrite(m2_a, LOW);
  analogWrite(m2_b, m2_speed);
}

// Arc turn: Both motors forward, but right wheel is faster
void moveLeft() {
  currentMove = LEFT; 
  // Motor 1 (Right wheel) speeds up
  analogWrite(m1_a, turn_speed_fast); 
  digitalWrite(m1_b, LOW);
  
  // Motor 2 (Left wheel) slows down
  analogWrite(m2_a, turn_speed_slow);     
  digitalWrite(m2_b, LOW);
}

void stopAll() {
  currentMove = STOPPED; 
  haltHardware();
}

void haltHardware() {
  digitalWrite(m1_a, LOW);
  digitalWrite(m1_b, LOW);
  digitalWrite(m2_a, LOW);
  digitalWrite(m2_b, LOW);
}

void resumeMovement() {
  if (currentMove == FORWARD) {
    moveForward();
  } else if (currentMove == BACKWARD) {
    moveBackward();
  } else if (currentMove == LEFT) {
    moveLeft();
  } else {
    haltHardware();
  }
}