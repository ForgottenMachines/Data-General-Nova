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

constexpr int DIP1 = 10;
constexpr int DIP2 = 9;
constexpr int DIP3 = 8;
constexpr int DIP4 = 7;

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

       pinMode(RESTART_ENAB, INPUT_PULLUP);
       pinMode(CON_INST, INPUT_PULLUP);
       pinMode(CON_DATA, INPUT_PULLUP);

       pinMode(CON_INST_LED, OUTPUT);  
       pinMode(CON_DATA_LED, OUTPUT); 
       


  for (int i = StartPin; i <= EndPin; i = i + 1) {   //For Testing all the pretty lights
        pinMode(i, INPUT_PULLUP);
//      pinMode(i, OUTPUT);  don't do any of that with the CPU installed in the tester
//      digitalWrite(i, HIGH);  
  }

  digitalWrite(RESTART_ENAB, LOW);  // input from the CPU... connected to center/common of Reset & Stop switches, so must be low to test those

// set mode switches on tester board

  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);

}

void loop() {
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
if (digitalRead(DIP4) == LOW){ ///// Test all Lower Switches

////////////////////////LOWER CONTROL SWITCH TEST SECTION//////////////////////////////

Mem15EndPin = 46; // was 48 but we're re-using the last 2 lamps for RESET and STOP indicators

  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) {   //For testing Data Switches 0-15
       pinMode(i, INPUT_PULLUP);  
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






 digitalWrite(CON_RQ, LOW);  
 delay(2000);  
 digitalWrite(CON_RQ, HIGH);  
 delay(2000);  


}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (digitalRead(DIP3) == LOW){ ///// Test All Data Switches

////////////////////////DATA SWITCH TEST SECTION//////////////////////////////


/////////////////////////DATA SWITCH TEST SECTION END///////////////////////////

}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (digitalRead(DIP2) == LOW){ ///// NOT YET DEFINED

}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else if (digitalRead(DIP1) == LOW){ ///// All Lights Sequential

}
//////////////////////TEST MODE SWITCHER///////////////////////////////////////
else{ /////  All Lights Blink in Unison


}

}