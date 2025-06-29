constexpr int RESTART_ENAB = A7; // input from the CPU... connected to center/common of Reset & Stop switches, so must be low to test those
constexpr int RST = A6; // RESET
constexpr int CON_RQ = A5; //used by multiple switches????
constexpr int CON_INST = A4; // input from the CPU..."the twin of CON_DATA - nevets01"
constexpr int PL = A3;  // PROG LOAD - Has it's own wire to p1-23 
constexpr int ISTP = A2; // INST STEP - Has it's own wire to p1-24
constexpr int STOP = 14; // STOP
constexpr int CON_DATA = 0; // input from the CPU..."the twin of CON_INST - nevets01"
constexpr int CONT_ISTP_MSTP = 1; // used only by CONTINUE MEM STEP & INST STEP
constexpr int MSTP = 2;  // MEM STEP - Has it's own wire to p1-48

constexpr int CON_INST_LED = 11;  
constexpr int CON_DATA_LED = 12; 

constexpr int SwitchPattern1 = 10;
constexpr int SwitchDiag1 = 9;
constexpr int SwitchCON_INST = 8;
constexpr int SwitchCON_DATA = 7;

constexpr int StartPin = 15;
constexpr int EndPin = 51;

//Address Lights begin at 15 and end at 31 (32 is Carry)
//BUT we don't need to define them separately because the loops below set them all as output, and then re-assign the Data Light pins as inputs.

constexpr int Mem0StartPin = 33; //Data Light 0
int Mem15EndPin = 48; //Data Light 15  (should be 48 but I'm testing re-using the last 2 lamps)

constexpr int blinky = 10;
constexpr int fastcycle = 0;

//for the single legacy board DIP switch arrangement
//constexpr int DIP1 = 10;
//constexpr int DIP2 = 9;
//constexpr int DIP3 = 8;
//constexpr int DIP4 = 7;

//for upgraded boards only DIP switch arrangement
constexpr int DIP1 = 7;
constexpr int DIP2 = 8;
constexpr int DIP3 = 9;
constexpr int DIP4 = 10;

void setup() {
       pinMode(SwitchPattern1, INPUT_PULLUP);
       pinMode(SwitchDiag1, INPUT_PULLUP);
       pinMode(SwitchCON_DATA, INPUT_PULLUP);
       pinMode(SwitchCON_INST, INPUT_PULLUP);
       pinMode(RST, INPUT_PULLUP);
       pinMode(CON_RQ, INPUT_PULLUP);
       pinMode(CON_INST, INPUT_PULLUP);
       pinMode(PL, INPUT_PULLUP);
       pinMode(ISTP, INPUT_PULLUP);
       pinMode(STOP, INPUT_PULLUP);
       pinMode(CON_DATA, INPUT_PULLUP);
       pinMode(CONT_ISTP_MSTP, INPUT_PULLUP);
       pinMode(MSTP, INPUT_PULLUP);

       pinMode(RESTART_ENAB, OUTPUT);
       pinMode(CON_INST, OUTPUT);  
       pinMode(CON_DATA, OUTPUT);

       pinMode(CON_INST_LED, OUTPUT);  
       pinMode(CON_DATA_LED, OUTPUT); 
       


  for (int i = StartPin; i <= EndPin; i = i + 1) {   //For Testing all the pretty lights
      pinMode(i, OUTPUT);  
      digitalWrite(i, HIGH);  
  }

  digitalWrite(RESTART_ENAB, LOW);  // input from the CPU... connected to center/common of Reset & Stop switches, so must be low to test those

// set mode switches on tester board

  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);

//  Serial.begin(115200);  //Enabling Serial hijacks/breaks D0 and D1, and thus hijacks CON_DATA & CONT_ISTP_MSTP
  Serial.println("Arduino Live!");


}

void loop() {
//Make sure we put inputs back to inputs after testing the CPU tester board by itself:
pinMode(STOP, INPUT_PULLUP);
pinMode(CON_RQ, INPUT_PULLUP);
pinMode(CON_INST, INPUT_PULLUP);
pinMode(CON_DATA, INPUT_PULLUP);
pinMode(CONT_ISTP_MSTP, INPUT_PULLUP);
pinMode(MSTP, INPUT_PULLUP);
pinMode(ISTP, INPUT_PULLUP);
pinMode(PL, INPUT_PULLUP);
pinMode(RST, INPUT_PULLUP);

//////////////////////TEST MODE SWITCHER///////////////////////////////////////
if (digitalRead(DIP4) == LOW){ ///// Test all Lower Switches
  Serial.println("DIP4");

////////////////////////LOWER CONTROL SWITCH TEST SECTION//////////////////////////////

Mem15EndPin = 46; // was 48 but we're re-using the last 2 lamps for RESET and STOP indicators

  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Switches 0-15
       pinMode(i, INPUT_PULLUP);  
  }

  //DEFINES THE MODE OF ALL SWITCHES....SO PAY ATTENTION HERE  
  //ONLY ONE OF THESE SIGNALS SHOULD BE LOW AT ONE TIME. 
  digitalWrite(CON_INST, LOW);  
  digitalWrite(CON_DATA, HIGH);  


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//turn off all of the Address lights that might have been left on from the previous operation
for (int i = Mem0StartPin + 1; i <= Mem15EndPin; i = i + 1) {  //loop through all data switch signals except for 0 (becauze we use Carry for that)
digitalWrite(i-19, HIGH); //turn off all of the address lights
}
digitalWrite(32, HIGH); //turn off the Carry light


 if (digitalRead(PL) == LOW){  //prog load
    digitalWrite(51, LOW); //EXEC light
    }
 else {
    digitalWrite(51, HIGH); 
    }

 if (digitalRead(MSTP) == LOW){  // MEM STEP
    digitalWrite(49, LOW); //FETCH light

    }
 else {
    digitalWrite(49, HIGH); 
    }

 if (digitalRead(ISTP) == LOW){ // INST STEP
    digitalWrite(50, LOW); //DEFER light
    }
 else {
    digitalWrite(50, HIGH); 
    }


 if (digitalRead(CONT_ISTP_MSTP) == LOW){ // Other pole/side of the MEM STEP / INST STEP switch.  Also used by the CONTINUE switch.
    digitalWrite(31, LOW); //ION light
    }
 else {
    digitalWrite(31, HIGH); 
    }

//make con_RQ to RUN cuz most switches signal this pin?

 if (digitalRead(CON_RQ) == LOW){ // ????
    digitalWrite(30, LOW); //RUN light
    }
 else {
    digitalWrite(30, HIGH); 
    }

//What about RESET and STOP??  They have their own dedicated lines, but we've run out of lights to test with.

 if (digitalRead(RST) == LOW){ // RESET
    digitalWrite(28, LOW); //Address 14 light
    }
 else {
    digitalWrite(28, HIGH); 
    }

 if (digitalRead(STOP) == LOW){ // STOP
    digitalWrite(29, LOW); //Address 15 light
    }
 else {
    digitalWrite(29, HIGH); 
    }



}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (digitalRead(DIP3) == LOW){ ///// Test All Data Switches
  Serial.println("DIP3");

////////////////////////DATA SWITCH TEST SECTION//////////////////////////////

Mem15EndPin = 48; // back to 48 because we're not re-using the last 2 lamps for RESET and STOP indicators


  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Switches 0-15
       pinMode(i, INPUT_PULLUP);  
  }

  //DEFINES THE MODE OF ALL SWITCHES....SO PAY ATTENTION HERE  
  //ONLY ONE OF THESE SIGNALS SHOULD BE LOW AT ONE TIME
  digitalWrite(CON_INST, HIGH);  
  digitalWrite(CON_DATA, LOW);  
  

for (int i = Mem0StartPin + 1; i <= Mem15EndPin; i = i + 1) {  //loop through all data switch signals except for 0 (becauze )
  if (digitalRead(i) == LOW){
     digitalWrite(i-19, LOW);
  }
  else {
     digitalWrite(i-19, HIGH);
  }
}

 if (digitalRead(Mem0StartPin) == LOW){
    digitalWrite(32, LOW);  //(32 is Carry)
 }
 else {
    digitalWrite(32, HIGH); 
        }
/////////////////////////DATA SWITCH TEST SECTION END///////////////////////////

}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (1 == 0){ ///// Disable this option, as it could be fatal or dangerous to the front panel, because it creates conflicts with output signals.
//else if (digitalRead(DIP2) == LOW){ ///// ALL LIGHTS SEQUENTIALLY FOR CPU TESTER ONLY!
  Serial.println("DIP2");
pinMode(STOP, OUTPUT);
pinMode(CON_RQ, OUTPUT);
pinMode(CON_INST, OUTPUT);
pinMode(CON_DATA, OUTPUT);
pinMode(CONT_ISTP_MSTP, OUTPUT);
pinMode(MSTP, OUTPUT);
pinMode(ISTP, OUTPUT);
pinMode(PL, OUTPUT);
pinMode(RST, OUTPUT);

  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Lights 0-15
      pinMode(i, OUTPUT);  
      digitalWrite(i, HIGH);  
  }

  //DEFINES THE MODE OF ALL SWITCHES....SO PAY ATTENTION HERE  
  //ONLY ONE OF THESE SIGNALS SHOULD BE LOW AT ONE TIME. 
  //WHEN A REAL FRONT PANEL IS CONNECTED
  //HOWEVER, THIS IS THE CPU TESTER, WITH NO FRONT PANEL CONNECTED
  //WE HOPE....................................................
//  digitalWrite(CON_INST, HIGH);  
//  digitalWrite(CON_DATA, HIGH);  

  digitalWrite(30, LOW);
  delay(200);           
  digitalWrite(31, LOW);
  delay(200);           
  digitalWrite(49, LOW);
  delay(200);           
  digitalWrite(50, LOW);
  delay(200);           
  digitalWrite(51, LOW);
  delay(200);           
  digitalWrite(32, LOW);
  delay(200);           

  digitalWrite(STOP, LOW);
  delay(200);           
  digitalWrite(CON_RQ, LOW);
  delay(200);           
  digitalWrite(CON_INST, LOW);
  delay(200);           
  digitalWrite(CON_DATA, LOW);
  delay(200);           
  digitalWrite(CONT_ISTP_MSTP, LOW);
  delay(200);           
  digitalWrite(MSTP, LOW);
  delay(200);           
  digitalWrite(ISTP, LOW);
  delay(200);           
  digitalWrite(PL, LOW);
  delay(200);           
  digitalWrite(RESTART_ENAB, HIGH);  //Active HIGH
  delay(200);           
  digitalWrite(RST, LOW);
  delay(200);           

  for (int i = StartPin; i <= 29; i = i + 1) {   //sequence the lights 
  digitalWrite(i, LOW);
  delay(200);           
    }
  for (int i = 33; i <= 48; i = i + 1) {   //sequence the lights 
  digitalWrite(i, LOW);
  delay(200);           
  }

//turn all the lights off at once

  digitalWrite(STOP, HIGH);  
  digitalWrite(CON_RQ, HIGH);  
  digitalWrite(CON_INST, HIGH);  
  digitalWrite(CON_DATA, HIGH);  
  digitalWrite(CONT_ISTP_MSTP, HIGH);  
  digitalWrite(MSTP, HIGH);  
  digitalWrite(ISTP, HIGH);  
  digitalWrite(PL, HIGH);  
  digitalWrite(RESTART_ENAB, LOW);  
  digitalWrite(RST, HIGH);  

    for (int i = StartPin; i <= EndPin; i = i + 1) { //turn all the lights off at once
        digitalWrite(i, HIGH);
    }
  delay(200);  


  for (int c = 1; c <= blinky; c = c + 1) {          //blink the lights [blinky] times
    for (int i = StartPin; i <= EndPin; i = i + 1) { //turn all the lights on at once
        digitalWrite(i, LOW);
    }
  digitalWrite(STOP, LOW);  
  digitalWrite(CON_RQ, LOW);  
  digitalWrite(CON_INST, LOW);  
  digitalWrite(CON_DATA, LOW);  
  digitalWrite(CONT_ISTP_MSTP, LOW);  
  digitalWrite(MSTP, LOW);  
  digitalWrite(ISTP, LOW);  
  digitalWrite(PL, LOW);  
  digitalWrite(RESTART_ENAB, HIGH);  
  digitalWrite(RST, LOW);  
  delay(200);                                        //leave them on for 2/10ths of a second
    for (int i = StartPin; i <= EndPin; i = i + 1) { //turn all the lights off at once
        digitalWrite(i, HIGH);
    }
  digitalWrite(STOP, HIGH);  
  digitalWrite(CON_RQ, HIGH);  
  digitalWrite(CON_INST, HIGH);  
  digitalWrite(CON_DATA, HIGH);  
  digitalWrite(CONT_ISTP_MSTP, HIGH);  
  digitalWrite(MSTP, HIGH);  
  digitalWrite(ISTP, HIGH);  
  digitalWrite(PL, HIGH);  
  digitalWrite(RESTART_ENAB, LOW);  
  digitalWrite(RST, HIGH);  
  delay(200);  
  }

}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (digitalRead(DIP1) == LOW){ ///// All Lights Sequential
  Serial.println("DIP1");

  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Lights 0-15
      pinMode(i, OUTPUT);  
      digitalWrite(i, HIGH);  
  }

  //DEFINES THE MODE OF ALL SWITCHES....SO PAY ATTENTION HERE  
  //ONLY ONE OF THESE SIGNALS SHOULD BE LOW AT ONE TIME. 
  digitalWrite(CON_INST, HIGH);  
  digitalWrite(CON_DATA, HIGH);  

  for (int i = StartPin; i <= EndPin; i = i + 1) {   //sequence the lights 
  digitalWrite(i, LOW);
  delay(200);           
  digitalWrite(i, HIGH);  
    }
  for (int c = 1; c <= blinky; c = c + 1) {          //blink the lights [blinky] times
    for (int i = StartPin; i <= EndPin; i = i + 1) { //turn all the lights on at once
        digitalWrite(i, LOW);
    }
  delay(200);                                        //leave them on for 2/10ths of a second
    for (int i = StartPin; i <= EndPin; i = i + 1) { //turn all the lights off at once
        digitalWrite(i, HIGH);
    }
  delay(200);  
  }

}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else{ /////  All Lights Blink in Unison
  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Lights 0-15
      pinMode(i, OUTPUT);  
      digitalWrite(i, HIGH);  
  }

  //DEFINES THE MODE OF ALL SWITCHES....SO PAY ATTENTION HERE  
  //ONLY ONE OF THESE SIGNALS SHOULD BE LOW AT ONE TIME. 
  digitalWrite(CON_INST, HIGH);  
  digitalWrite(CON_DATA, HIGH);  

for (int i = StartPin; i <= EndPin; i = i + 1) { //turn all the lights on at once
        digitalWrite(i, LOW);
    }
  delay(2000);                                        //leave them on for 4 seconds
    for (int i = StartPin; i <= EndPin; i = i + 1) { //turn all the lights off at once
        digitalWrite(i, HIGH);
    }
  delay(2000);  

}

}