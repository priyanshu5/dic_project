#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <SD.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RF24 radio(9, 10);               // nRF24L01(+) radio attached using Getting Started board
RF24Network network(radio);      // Network uses that radio

int left_motor1 = 6, left_motor2 = 8,  right_motor1 = 39, right_motor2 = 43; //pins for motors
int up = 2, dw = 4, cutter = 12, ReadSw = 7;    // pins for additions function
int xAxis, yAxis, mAxis, cAxis, RecSw;     //variables for storing joystick reading

const uint16_t this_node = 00;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t other_node = 01;   // Address of the other node in Octal format
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
File myFile;              //created object for SD library
const int chipSelect = 5;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fwd()
{
  digitalWrite(left_motor1, LOW);
  //digitalWrite(left_motor2, HIGH);
  digitalWrite(right_motor1, LOW);
  //digitalWrite(right_motor2, HIGH);
  Serial.println(" forward ");
}
void back()
{
  //digitalWrite(left_motor1, HIGH);
  digitalWrite(left_motor2, LOW);
 // digitalWrite(right_motor1, HIGH);
  digitalWrite(right_motor2, LOW);
  Serial.println(" back ");
}
//to move the robot in left direction
void left()
{
  //digitalWrite(left_motor1, HIGH);
  //digitalWrite(left_motor2, HIGH);
  digitalWrite(right_motor1, LOW);
 // digitalWrite(right_motor2, HIGH);
  Serial.println(" left ");
}
//to move the robot in right direction
void right()
{
  digitalWrite(left_motor1, LOW);
  //digitalWrite(left_motor2, HIGH);
  //digitalWrite(right_motor1, HIGH);
  //digitalWrite(right_motor2, HIGH);
  Serial.println(" right ");
}
//to stop the robot
void stp()
{
  digitalWrite(left_motor1, HIGH);
  digitalWrite(left_motor2, HIGH);
  digitalWrite(right_motor1,HIGH);
  digitalWrite(right_motor2, HIGH);
  digitalWrite(up,HIGH);
  digitalWrite(dw,HIGH);
  digitalWrite(cutter,HIGH);
  Serial.println(" stop ");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct payload_t {                 // Structure of our payload
  float joy0, joy1, joy2, joy3, joy4;
} payload;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(57600);
  Serial.println("\n RF24/Simple Receive mode");
  //pin declaration
  pinMode(left_motor1, OUTPUT); //left motor pin connection
  digitalWrite(left_motor1,HIGH);
  pinMode(left_motor2, OUTPUT); //left motor pin connection
  digitalWrite(left_motor2,HIGH);
  pinMode(right_motor1, OUTPUT); //right motor pin connection
  digitalWrite(right_motor1,HIGH);
  pinMode(right_motor2, OUTPUT); //right motor pin connection
  digitalWrite(right_motor2,HIGH);
  pinMode(up, OUTPUT);
  digitalWrite(up,HIGH);
  pinMode(dw, OUTPUT);
  digitalWrite(dw,HIGH);
  pinMode(cutter, OUTPUT);
  pinMode(ReadSw, INPUT);
  digitalWrite(cutter, HIGH);
  
 

  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ 00);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("first_test.txt", FILE_WRITE);

  // if the file opened okay, write to it://////////////////////////////////////////////////////////////////////////////////////////////////
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("path writing starts here:- ");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening first_test.txt");
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  network.update();// Check the network regularly
 
  while ( network.available() )// Is there anything ready for us?
  {
    RF24NetworkHeader header;
    network.read(header, &payload, sizeof(payload));
    xAxis = payload.joy0;
    yAxis = payload.joy1;
    mAxis = payload.joy2;
    cAxis = payload.joy3;
    RecSw = payload.joy4;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(RecSw == 1)
    {
      myFile = SD.open("first_test.txt",FILE_WRITE);
      delay(50);
    }
    else
    myFile.close();
  
    Serial.print("xAxis = ");
    Serial.println(xAxis);
    Serial.print("yAxis = ");
    Serial.println(yAxis);
    Serial.print("mAxis = ");
    Serial.println(mAxis);
    Serial.print("cAxis = ");
    Serial.println(cAxis);
    Serial.print("RecSw = ");
    Serial.println(RecSw);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (xAxis > 700) {
      myFile.write("2");
      back();
    }
    else if (xAxis < 300) {
      myFile.write("1");
      fwd();
    }
    else if (yAxis < 350) {
      myFile.write("3");
      right();
    }
    else if (yAxis > 750) {
      myFile.write("4");
      left();
    }
    else 
    {
      myFile.write("0");
      stp();
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (mAxis > 600)
    {
      myFile.write("5");
      digitalWrite(dw, HIGH);
      digitalWrite(up, LOW);
      Serial.println(" linear actuator up ");
    }
    else if (mAxis < 300) {
      myFile.write("6");
      digitalWrite(dw, LOW);
      digitalWrite(up, HIGH);
      Serial.println(" linear actuator down ");

    }
    else {
      
      digitalWrite(dw, LOW);
      digitalWrite(up, LOW);
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (cAxis > 800) {
      myFile.write("7");
      digitalWrite(cutter, HIGH);
      Serial.println(" blade on ");
    }
    else if (cAxis < 200) {
      myFile.write("8");
      digitalWrite(cutter, LOW);
      Serial.println(" blade off ");
    }
    delay(20);
  }
}
/*
 * digits has been used to store the information of all the movement of robot in form of charecter. 
 * stop     --> 0
 * forward  --> 1
 * backward --> 2
 * right  -->   3
 * left   -->   4
 * blade up --> 5
 * blade dowm-->6
 * blade on --> 7
 * blade off -->8
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


              ////////////////////   ///          ///         /////////////////
                     ///             ///          ///         ///
                     ///             ///          ///         ///
                     ///             ////////////////         /////////////////
                     ///             ////////////////         ///
                     ///             ///          ///         ///
                     ///             ///          ///         ///
                     ///             ///          ///         /////////////////


                 ///////////////////        /////        ///            ////////////////
                 ///                        /// //       ///              //          ///
                 ///                        ///  //      ///              //          ///
                 ///                        ///   //     ///              //          ///
                 ///////////////////        ///    //    ///              //          ///
                 ///                        ///     //   ///              //          ///
                 ///                        ///      //  ///              //          ///
                 ///                        ///       // ///              //          ///
                 ///////////////////        ///        /////           ////////////////
                     


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
