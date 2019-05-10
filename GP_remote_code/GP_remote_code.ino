
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RF24 radio(9, 10);                   // nRF24L01(+) radio attached using Getting Started board
RF24Network network(radio);          // Network uses that radio

long p_millis = 0;                    //variable to apply time delay using millis()
long interval = 200;                  //set the interval for time delay
 
int xAxis = A2, yAxis = A0, mAxis = A1, cAxis = A3, RecSw = 7; // define the pins to read the data

const uint16_t this_node = 01;        // Address of our node in Octal format
const uint16_t other_node = 00;       // Address of the other node in Octal format
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct payload_t {                  // Structure of our payload
  float joy0, joy1, joy2, joy3, joy4;
} joyvalue;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(void)
{
  Serial.begin(57600);
  Serial.println("\n RF24/Simple Transmit mode");
  pinMode(RecSw, INPUT);
  

  SPI.begin();
  radio.begin();
  network.begin(90, this_node);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  network.update();
  unsigned long c_millis = millis();
  if (c_millis - p_millis >= interval) {
    p_millis = c_millis;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  struct payload_t joyvalue;
    joyvalue.joy0 = analogRead(xAxis);
    joyvalue.joy1 = analogRead(yAxis);
    joyvalue.joy2 = analogRead(mAxis);
    joyvalue.joy3 = analogRead(cAxis);
    joyvalue.joy4 = digitalRead(RecSw);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    RF24NetworkHeader header(/*to node*/ 00);
    bool ok = network.write(header, &joyvalue, sizeof(joyvalue));
    Serial.print("XAxis==");
    Serial.println( joyvalue.joy0);
    Serial.print("yAxis==");
    Serial.println( joyvalue.joy1);
    Serial.print("mAxis==");
    Serial.println( joyvalue.joy2);
    Serial.print("cAxis==");
    Serial.println( joyvalue.joy3);
    Serial.print("RecSw==");
    Serial.println( joyvalue.joy4);
  }
}
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
