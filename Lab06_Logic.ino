/*
  ELEC1100 Spring 2019 HKUST
  Group 086
  Theo Azriel and Ferris Prima Nugraha 
  20541062  and 20543826
  
  NEED FULL BATTERY, TEST FEW TIMES AFTER FULLY CHARGED
  ALIGN THE CONNECTOR TO BATTERY INDICATOR WELL
  CHECK SENSOR ORIENTATION
*/

// assign meaningful names to those pins that will be used
#define pinLeftSensor A5      //pin A5
#define pinRightSensor A3     //pin A3
#define pinMiddleSensor A1    //pin A1
#define pinFrontSensor A0     //pin A0

#define pinLQ3 3              //pin D3
#define pinLQ2 4              //pin D4
#define pinLQ1 5              //pin D5
#define pinLQ0 6              //pin D6

#define pinRQ3 7              //pin D7
#define pinRQ2 8              //pin D8
#define pinRQ1 9              //pin D9
#define pinRQ0 10             //pin D10

#define pinLdir 11            //pin D11
#define pinRdir 12            //pin D12

//define variables to be used in script
int leftSensor = 1;
int rightSensor = 1;
int middleSensor = 1;
int frontSensor = 1;
int counter = 0;
long time_now = 0;
long time_then = 0;
long elapsed = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // define pins as input and output.
  pinMode(pinLeftSensor, INPUT);
  pinMode(pinRightSensor, INPUT);
  pinMode(pinMiddleSensor, INPUT);
  pinMode(pinFrontSensor, INPUT);

  pinMode(pinLQ3, OUTPUT);
  pinMode(pinLQ2, OUTPUT);
  pinMode(pinLQ1, OUTPUT);
  pinMode(pinLQ0, OUTPUT);

  pinMode(pinRQ3, OUTPUT);
  pinMode(pinRQ2, OUTPUT);
  pinMode(pinRQ1, OUTPUT);
  pinMode(pinRQ0, OUTPUT);

  pinMode(pinLdir, OUTPUT);
  pinMode(pinRdir, OUTPUT);

  // initialize output pins.
  digitalWrite(pinLQ3, LOW);
  digitalWrite(pinLQ2, LOW);
  digitalWrite(pinLQ1, LOW);
  digitalWrite(pinLQ0, LOW);
  digitalWrite(pinRQ3, LOW);
  digitalWrite(pinRQ2, LOW);
  digitalWrite(pinRQ1, LOW);
  digitalWrite(pinRQ0, LOW);
  digitalWrite(pinLdir, HIGH);        // HIGH: move forward
  digitalWrite(pinRdir, HIGH);        // LOW:  move backward
}

void L_drive_motor(int LQ3,int LQ2,int LQ1,int LQ0,int Ldir){
  digitalWrite(pinLQ3, LQ3);
  digitalWrite(pinLQ2, LQ2);
  digitalWrite(pinLQ1, LQ1);
  digitalWrite(pinLQ0, LQ0);
  digitalWrite(pinLdir,Ldir);
}

void R_drive_motor(int RQ3,int RQ2,int RQ1,int RQ0,int Rdir){
  digitalWrite(pinRQ3, RQ3);
  digitalWrite(pinRQ2, RQ2);
  digitalWrite(pinRQ1, RQ1);
  digitalWrite(pinRQ0, RQ0);
  digitalWrite(pinRdir,Rdir);
}

void start_run(int frontSensor){
    if(!frontSensor && counter == 1){
       time_now = millis(); 
       L_drive_motor(1,1,1,1,HIGH);
       R_drive_motor(1,1,1,1,HIGH);  
       delay(600);
       counter++;
    }
}

void stop(){ 
  if(counter==0){
    L_drive_motor(0,0,0,0,LOW);
    R_drive_motor(0,0,0,0,LOW);
    counter++;
  }
}

void sharpTurn(int leftSensor , int rightSensor){
    if(!leftSensor && !rightSensor){
      time_then = millis();
      elapsed = (time_then - time_now);
      
      if(elapsed<5500){
        digitalWrite(pinLdir, LOW);
        digitalWrite(pinRdir, HIGH);
        delay(200);     
      }
      else{
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, LOW);
        delay(200);
      }
    }  
}

void justDrive(int middleSensor, int leftSensor, int rightSensor, int counter){
    if (!middleSensor && (counter>=2)) {
      if(leftSensor && rightSensor){
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
      }
      else if(!leftSensor && rightSensor){
        digitalWrite(pinLdir, LOW);
        digitalWrite(pinRdir, HIGH);
      }
       else if(leftSensor && !rightSensor){
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, LOW);
      }
  }
}

void turnBackWall(int frontSensor){
  time_then = millis();
  elapsed = (time_then - time_now);
  
  if(elapsed>10000 && !frontSensor){
      L_drive_motor(0,0,0,0,LOW);
      R_drive_motor(0,0,0,0,LOW);
      delay(500);
    
      R_drive_motor(1,1,1,1,HIGH);
      L_drive_motor(1,1,1,1,LOW);
      delay(650);
    
      R_drive_motor(1,1,1,1,HIGH);
      L_drive_motor(1,1,1,1,HIGH);
      delay(600);
    
      L_drive_motor(0,0,0,0,LOW);
      R_drive_motor(0,0,0,0,LOW);
      delay(1000000);
  }  
}

void loop() {
  leftSensor = digitalRead(pinLeftSensor);
  rightSensor = digitalRead(pinRightSensor);
  middleSensor = digitalRead(pinMiddleSensor);
  frontSensor = digitalRead(pinFrontSensor);

  stop();                                                                                                                                             
  start_run(frontSensor);             
  justDrive(middleSensor, leftSensor, rightSensor, counter);
  sharpTurn(leftSensor, rightSensor);
  turnBackWall(frontSensor);
}
