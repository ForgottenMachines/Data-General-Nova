constexpr int DelayAmount = 100; // time to wait between front panel commands

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

constexpr int MEM0 = A15;
constexpr int MEM1 = A14;
constexpr int MEM2 = A13;
constexpr int MEM3 = A12;
constexpr int MEM4 = A11;
constexpr int MEM5 = A10;
constexpr int MEM6 = A9;
constexpr int MEM7 = A8;

constexpr int StartPin = 15;
constexpr int EndPin = 51;

//Address Lights begin at 15 and end at 31 (32 is Carry)
//BUT we don't need to define them separately because the loops below set them all as output, and then re-assign the Data Light pins as inputs.

constexpr int Mem0StartPin = 33; //Data Light 0
int Mem15EndPin = 48; //Data Light 15  (should be 48 )

constexpr int blinky = 10;
constexpr int fastcycle = 0;

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
       pinMode(CON_RQ, OUTPUT); 
       pinMode(CON_INST, INPUT_PULLUP);
       pinMode(PL, INPUT_PULLUP);
       pinMode(ISTP, INPUT_PULLUP);
       pinMode(STOP, INPUT_PULLUP);
       pinMode(CON_DATA, INPUT_PULLUP);
       pinMode(CONT_ISTP_MSTP, INPUT_PULLUP);
       pinMode(MSTP, INPUT_PULLUP);

       pinMode(RESTART_ENAB, INPUT);
       pinMode(CON_INST, INPUT_PULLUP);
       pinMode(CON_DATA, INPUT_PULLUP);

       pinMode(CON_INST_LED, OUTPUT);  
       pinMode(CON_DATA_LED, OUTPUT); 

       pinMode(MEM0, OUTPUT); 
       pinMode(MEM1, OUTPUT); 
       pinMode(MEM2, OUTPUT); 
       pinMode(MEM3, OUTPUT); 
       pinMode(MEM4, OUTPUT); 
       pinMode(MEM5, OUTPUT); 
       pinMode(MEM6, OUTPUT); 
       pinMode(MEM7, OUTPUT); 
     


  for (int i = StartPin; i <= EndPin; i = i + 1) {   //For Testing all the pretty lights
        pinMode(i, INPUT_PULLUP);
  }
  
  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Switches 0-15
       pinMode(i, INPUT_PULLUP);  
  }
  
  
// set mode switches on tester board

  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);

  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, HIGH);
  digitalWrite(MEM7, HIGH);

}

void loop() {
//Make sure we put inputs back to inputs after testing the CPU tester board by itself:
pinMode(STOP, INPUT_PULLUP);
pinMode(CON_INST, INPUT_PULLUP);
pinMode(CON_DATA, INPUT_PULLUP);
pinMode(CONT_ISTP_MSTP, INPUT_PULLUP);
pinMode(MSTP, INPUT_PULLUP);
pinMode(ISTP, INPUT_PULLUP);
pinMode(PL, INPUT_PULLUP);
pinMode(RST, INPUT_PULLUP);
pinMode(RESTART_ENAB, INPUT);
  for (int i = StartPin; i <= EndPin; i = i + 1) {   //For Testing all the pretty lights
        pinMode(i, INPUT_PULLUP);
  }
  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Switches 0-15
       pinMode(i, INPUT_PULLUP);  
  }



//////////////////////TEST MODE SWITCHER///////////////////////////////////////
if (digitalRead(DIP1) == LOW){ ///// Test EXAMINE & EXAMINE NEXT fron front panel, all addresses 0


digitalWrite(MEM0, HIGH);///front panel code for EXAMINE (NOTE: these signals are inverted from how the NOVA sees them)
digitalWrite(MEM1, HIGH);
digitalWrite(MEM2, HIGH);
digitalWrite(MEM3, HIGH);
digitalWrite(MEM4, HIGH);
digitalWrite(MEM5,  LOW);
digitalWrite(MEM6,  LOW);
digitalWrite(MEM7, HIGH);

///temporary CON_INST test
pinMode(CON_INST, OUTPUT);
digitalWrite(CON_INST, LOW); 

digitalWrite(CON_RQ, LOW); 
delay(DelayAmount);  
digitalWrite(CON_RQ, HIGH);  
delay(DelayAmount);  

 for (int dg = 0; dg <= 25; dg++) {  

digitalWrite(MEM0, HIGH); ///front panel code for EXAMINE NEXT (NOTE: these signals are inverted from how the NOVA sees them)
digitalWrite(MEM1, HIGH);
digitalWrite(MEM2, HIGH);
digitalWrite(MEM3, HIGH);
digitalWrite(MEM4, HIGH);
digitalWrite(MEM5, HIGH);
digitalWrite(MEM6,  LOW);
digitalWrite(MEM7,  LOW); 

digitalWrite(CON_RQ, LOW); 
delay(DelayAmount);  
digitalWrite(CON_RQ, HIGH);  
delay(DelayAmount);  

  }

}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (digitalRead(DIP2) == LOW){ ///// NOT YET DEFINED



}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (digitalRead(DIP3) == LOW){ ///// NOT YET DEFINED



}

else if (digitalRead(DIP4) == LOW){ ///// ALL LIGHTS SEQUENTIALLY FOR CPU TESTER ONLY!  WARNING------DO NOT USE WHEN CPU BOARD IS CONNECTED!
pinMode(STOP, OUTPUT);
pinMode(CON_RQ, OUTPUT);
pinMode(CON_INST, OUTPUT);
pinMode(CON_DATA, OUTPUT);
pinMode(CONT_ISTP_MSTP, OUTPUT);
pinMode(MSTP, OUTPUT);
pinMode(ISTP, OUTPUT);
pinMode(PL, OUTPUT);
pinMode(RST, OUTPUT);
pinMode(RESTART_ENAB, OUTPUT);
digitalWrite(RESTART_ENAB, LOW); 

  for (int i = StartPin; i <= EndPin; i = i + 1) {   //For Testing all the pretty lights
      pinMode(i, OUTPUT);  
      digitalWrite(i, HIGH);  
  }
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
else{ /////  digitalWrite(CON_RQ, HIGH);  

digitalWrite(CON_RQ, HIGH); 

}

}