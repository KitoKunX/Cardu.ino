// Pin declarations

const int sonarPin1 = 8;
const int sonarPin2 = 9;
const int motorLeft1 = 2;
const int motorLeft2 = 4;
const int motorRight1 = 3;
const int motorRight2 = 5;

// Constant declarations

const int carMove = 100;
const int carForwards = 1000;
const int carTurn = 1500;
const int checkBluetoothTime = millis() + 10000;

// Variable declarations

unsigned long rawSonar;
int prevSonar = 0;
int testSonar = 0;
int currSonar = 0;
int i = 0;
int x = 0;
String moveInstruct[];
bool isBluetoothOn = false;
bool commandRunning = false;

// Function declarations


// This function performs the sonar reading
int sonarCar() {

  pinMode(sonarPin1, OUTPUT);
  digitalWrite(sonarPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonarPin1, LOW);

  pinMode(sonarPin2, INPUT);
  rawSonar = pulseIn(sonarPin2, HIGH);

  Serial.print("rawSonar: " + rawSonar);

  return rawSonar / 29 / 2;

}


// This function check if the sonar readings are accurate
bool dataCheck(int checking, int index) {

  if (prevSonar + carMove < checking || prevSonar - carMove > checking) {

     // If the current sonar reading is within the expected range

  } else if (moveInstruct[x] == "Left" || moveInstruct[x] == "Right") {

      // If the last instructions given to the motors were good

    }

}

void moveCar(String direction, int duration = 1000);


// This function tells the motors to move in a particualr direction for a specified time
void moveCar(String direction, int duration) {

  if (direction == "up") {

    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorRight2, LOW);

    delay(duration);

  } else if (direction == "down") {

    digitalWrite(motorLeft1, LOW);
    digitalWrite(motorLeft2, HIGH);
    digitalWrite(motorRight1, LOW);
    digitalWrite(motorRight2, HIGH);

    delay(duration);

  } else if (direction == "rotate left"){
    // Rotate left
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, HIGH);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorRight2, LOW);
    
    delay(duration);
    
  }
  else if (direction == "rotate right"){
    // Rotate right
    digitalWrite(motorLeft1, HIGH);
    digitalWrite(motorLeft2, LOW);
    digitalWrite(motorRight1, HIGH);
    digitalWrite(motorRight2, HIGH);
    
    delay(duration);
    
  }

}


// This function tells the motors to stop running
void breakCar() {

  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, HIGH);

}


// This function uses the sonar readings to decide what to do next
void thinkCar(int sonar, int index) {

  //  thinkCarResult -> temporary value to represent the output of this function

  String thinkCarResult = moveInstruct[index];
  

  moveCar(thinkCarResult);

}

// Function to process bluetooth input (Less messy)
void procInput(String input){
// Conditions upon input
      if (input == "48"){
        // Call stop function
        breakCar(); 
      }
      if (input == "56"){
        // Call move up
        if (!commandRunning){
          commandRunning = true; 
          moveCar("up", carForwards);
          breakCar();
          commandRunning = false;
        }
        else{
          return;
        }
      }
      if (input == "50"){
        // Call move down function
        if (!commandRunning){
          commandRunning = true;
          moveCar("down", carForwards);
          breakCar();
          commandRunning = false;
        }
        else{
          return;
        }
      }
      if (input == "69"){
        // Call rotate left function
        if (!commandRunning){
          commandRunning = true;
          moveCar("rotate left", carTurn);
          breakCar();
          commandRunning = false;
        }
        else{
          return;
        }
      }
      if (input == "70"){
        // Call rotate right function
        if (!commandRunning){
          commandRunning = true;
          moveCar("rotate right", carTurn);
          breakCar();
          commandRunning = false;
        }
        else{
          return;
        }
      }
      else{
        // Do nothing
        breakCar();
      }
    return;	
}



// Core Arduino Functions

void setup() {
  
  // Need to initialise certain values and variables here
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);
  
  // Setup for Bluetooth Component
  Serial.begin(9600);
}

//Make code easier to access
void mainSonar(){
	testSonar = sonarCar();
  
    if (dataCheck(testSonar, x) == true) {
  
      prevSonar = currSonar;
      currSonar = testSonar;
  
      x++;
  
      // This is where thinkCar function is called and chooses what to do based off the currSonar variable
  
      thinkCar(currSonar, x);
    }
	}

void loop() {
  
  // Check in start if bluetooth is connected 
  while (millis() < checkBluetoothTime){
    
    if ((Serial.available()) && (isBluetoothOn == false)){
      isBluetoothOn = true;
      String input = String(Serial.read());
      Serial.print("Character entered: ");
      Serial.println(input);
    
      procInput(input);
	  return; // Don't go any further and restart main loop
    }
	
    
  }
  
  if (isBluetoothOn){
    if (Serial.available()) {
		String input = String(Serial.read());
		Serial.print("Character entered: ");
		Serial.println(input);
  
    procInput(input);
  }
  }
  else{
    
	//call mainSonar function
	mainSonar();
  
    }
  }


