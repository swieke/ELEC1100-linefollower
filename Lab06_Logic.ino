/*
  ELEC1100
  Group 86
  FPN & TA
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
int rightSensor =1;
int middleSensor = 1;
int frontSensor =1;
int counter= 0;

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

void L_drive_motor(int LQ3,int LQ2,int LQ1,int LQ0,int Ldir)
{
  digitalWrite(pinLQ3, LQ3);
  digitalWrite(pinLQ2, LQ2);
  digitalWrite(pinLQ1, LQ1);
  digitalWrite(pinLQ0, LQ0);
  digitalWrite(pinLdir,Ldir);
}

void R_drive_motor(int RQ3,int RQ2,int RQ1,int RQ0,int Rdir)
{
  digitalWrite(pinRQ3, RQ3);
  digitalWrite(pinRQ2, RQ2);
  digitalWrite(pinRQ1, RQ1);
  digitalWrite(pinRQ0, RQ0);
  digitalWrite(pinRdir,Rdir);
}

void start_run(int frontSensor){//, int leftSensor, int rightSensor, int middleSensor, int counter){
    if(!frontSensor && counter == 1){// && !leftSensor && !rightSensor && !middleSensor && counter==1){
       L_drive_motor(1,1,1,1,HIGH);
       R_drive_motor(1,1,1,1,HIGH);  
       
       delay(500);
       counter++;
    }
}

void stop(){ 
  if (counter==0) {
  L_drive_motor(0,0,0,0,LOW);
  R_drive_motor(0,0,0,0,LOW);
  counter++;
  }
}

void adjust(int middleSensor, int rightSensor, int leftSensor, int counter){
  //buat jalan sebelum belokan ketiga
  if(!middleSensor && counter >=2 && counter <=4){
    if(leftSensor && rightSensor){
      L_drive_motor(1,1,1,1,HIGH);
      R_drive_motor(1,1,1,1,HIGH);                //gas pollllllllll
    }
    else if(!leftSensor && rightSensor){
      L_drive_motor(0,1,0,1,HIGH);
      R_drive_motor(1,1,1,1,HIGH);                //kirii
    }
    
    else if(leftSensor && !rightSensor){
      L_drive_motor(0,1,0,1,HIGH);
      R_drive_motor(1,1,1,1,HIGH);                //kanann
    }
  }
  //buat jalan setelah belokan ketiga
  //if
}


void splitPath(int leftSensor, int rightSensor, int middleSensor){
  if(!leftSensor && !rightSensor){          //lagi galau
     if(counter==2 || counter==3){                          //2 pertama ke kiri
       L_drive_motor(0,1,0,1,HIGH);
       R_drive_motor(1,1,1,1,HIGH);
     }
     if(counter==4){                                        //ketiga ke kanan
       L_drive_motor(1,1,1,1,HIGH);
       R_drive_motor(0,1,0,1,HIGH); 
     }
  }
}

void firstTwoLeft(int leftSensor , int rightSensor, int counter){//to left
    if (!leftSensor && !rightSensor && (counter==2||counter==3)) {
    digitalWrite(pinLdir, LOW);
    digitalWrite(pinRdir, HIGH);
    delay(220);//tadqi200
    counter++;
    }
}

void thirdRight(int leftSensor , int rightSensor, int counter){     //to right
    if (!leftSensor && !rightSensor && counter==4) {
    digitalWrite(pinLdir, HIGH);
    digitalWrite(pinRdir, LOW);
    delay(220);
    counter++;
    }
}

void justDrive(int middleSensor, int leftSensor, int rightSensor, int counter){
    if (!middleSensor && (counter>=2)) {
      if(leftSensor && rightSensor){
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, HIGH);
        delay(20); //35
      }
      else if(!leftSensor && rightSensor){
        digitalWrite(pinLdir, LOW);
        digitalWrite(pinRdir, HIGH);
        delay(20);  
      }
       else if(leftSensor && !rightSensor){
        digitalWrite(pinLdir, HIGH);
        digitalWrite(pinRdir, LOW);
        delay(20);  
      }
  }
}

void loop() {

  leftSensor = digitalRead(pinLeftSensor);
  rightSensor = digitalRead(pinRightSensor);
  middleSensor = digitalRead(pinMiddleSensor);
  frontSensor = digitalRead(pinFrontSensor);

  stop();                                                                                 //counter jadi 1                                                              
  start_run(frontSensor);//, leftSensor, rightSensor, middleSensor, counter);             //counter udah 2
  //justDrive(middleSensor, leftSensor, rightSensor, counter);
  firstTwoLeft(leftSensor, rightSensor, counter);
  justDrive(middleSensor, leftSensor, rightSensor, counter);
  thirdRight(leftSensor, rightSensor, counter);
  
    
  
}
