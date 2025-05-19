uint16_t load_addr = 0102;
uint16_t load_code[] = {
  0174420, 020411, 0105420,
  0111020, 0133020, 0121020,
  0145020, 0175424, 0773,
  063077, 0
};

int prog_delays[] = { //use 4 switches to assign one of the values in this array
  5,
  30,
  300,
  800
};
int DelayAmount = 100; // time to wait between INDIVIDUAL front panel commands
int RepeatAt = 800; // Repeat all commands after this delay
int Loops = 10; // Examine Next Count Limit

String TestStr = "";
String Upper = "";
String Lower = "";

constexpr int DataPin1 = 3;
constexpr int ClockPin1 = 4;
constexpr int LatchPin1 = 5;
constexpr int DataPin2 = 6;
constexpr int ClockPin2 = 11;
constexpr int LatchPin2 = 12;

constexpr int RESTART_ENAB = A7; // input from the CPU... connected to center/common of Reset & Stop switches, so must be low to test those
constexpr int RST = A6; // RESET
constexpr int CON_RQ = A5; //used by multiple switches????
constexpr int CON_INST = A4; // input from the CPU..."the twin of CON_DATA - nevets01"
constexpr int PL = A3; // PROG LOAD - Has it's own wire to p1-23 
constexpr int ISTP = A2; // INST STEP - Has it's own wire to p1-24
constexpr int STOP = 14; // STOP
constexpr int CON_DATA = 0; // input from the CPU..."the twin of CON_INST - nevets01"
constexpr int CONT_ISTP_MSTP = 1; // used only by CONTINUE MEM STEP & INST STEP
constexpr int MSTP = 2; // MEM STEP - Has it's own wire to p1-48

constexpr int SwitchPattern1 = 10;
constexpr int SwitchDiag1 = 9;
constexpr int SwitchCON_INST = 8;
constexpr int SwitchCON_DATA = 7;
constexpr int PauseSwitch = 13;

constexpr int MEM0  = A15;
constexpr int MEM1  = A14;
constexpr int MEM2  = A13;
constexpr int MEM3  = A12;
constexpr int MEM4  = A11;
constexpr int MEM5  = A10;
constexpr int MEM6  = A9;
constexpr int MEM7  = A8;

constexpr int StartPin = 15;
constexpr int EndPin = 51;

#define NO_INC 0
#define INC    1

//Switches Lights begin at 15 and end at 31 (32 is Carry)
//BUT we don't need to define them separately because the loops below set them all as output, and then re-assign the Data Light pins as inputs.

constexpr int Mem0StartPin = 33; //Data Light 0
int Mem15EndPin = 48; //Data Light 15  (should be 48 )

constexpr int blinky = 10;
constexpr int fastcycle = 0;

constexpr int DIP1 = 7;
constexpr int DIP2 = 8;
constexpr int DIP3 = 9;
constexpr int DIP4 = 10;

uint8_t sw_bits;

void setup() {
  sw_bits = (digitalRead(DIP1) ? 0 : 1) |
    (digitalRead(DIP2) ? 0 : 2) |
    (digitalRead(DIP3) ? 0 : 4) |
    (digitalRead(DIP4) ? 0 : 8);
    
  for (int i = 0; i < (sizeof(prog_delays) / sizeof(prog_delays[0])); i++) {
    if (sw_bits & (1 << i)) DelayAmount = prog_delays[i];
    else break;
  }

  //       Serial.begin(115200);  //Using this MAY hijack pins D0-D1, which is hard-wired to /CON DATA & /CONT+ISTP+MSTP.
  //       Serial.println("====================");
  pinMode(PauseSwitch, INPUT_PULLUP);
  pinMode(SwitchPattern1, INPUT_PULLUP);
  pinMode(SwitchDiag1, INPUT_PULLUP);
  pinMode(SwitchCON_DATA, INPUT_PULLUP);
  pinMode(SwitchCON_INST, INPUT_PULLUP);
  pinMode(RST, OUTPUT);
  digitalWrite(RST, HIGH);
  pinMode(CON_RQ, OUTPUT);
  digitalWrite(CON_RQ, HIGH);
  pinMode(CON_INST, INPUT_PULLUP); //should be input NO Pullup?
  pinMode(PL, INPUT);
  pinMode(STOP, OUTPUT);
  digitalWrite(STOP, HIGH);
  pinMode(CON_DATA, INPUT);
  
  digitalWrite(CONT_ISTP_MSTP, HIGH);
  pinMode(CONT_ISTP_MSTP, OUTPUT);
  digitalWrite(MSTP, HIGH);
  pinMode(MSTP, OUTPUT);
  digitalWrite(ISTP, HIGH);
  pinMode(ISTP, OUTPUT);

  pinMode(RESTART_ENAB, INPUT);
  pinMode(CON_INST, INPUT_PULLUP);
  pinMode(CON_DATA, INPUT_PULLUP);

  pinMode(MEM0, OUTPUT);
  pinMode(MEM1, OUTPUT);
  pinMode(MEM2, OUTPUT);
  pinMode(MEM3, OUTPUT);
  pinMode(MEM4, OUTPUT);
  pinMode(MEM5, OUTPUT);
  pinMode(MEM6, OUTPUT);
  pinMode(MEM7, OUTPUT);

  for (int i = StartPin; i <= EndPin; i = i + 1) { //For Testing all the pretty lights
    pinMode(i, INPUT);
  }

  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) { //For testing Data Switches 0-15
    pinMode(i, INPUT);
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

  //2025-05-18 Usagi says don't do digital write high, instead do pinmode inputd [NO Pullup]

  fp_set(017777);

  pinMode(DataPin1, OUTPUT);
  pinMode(ClockPin1, OUTPUT);
  pinMode(LatchPin1, OUTPUT);
  pinMode(DataPin2, OUTPUT);
  pinMode(ClockPin2, OUTPUT);
  pinMode(LatchPin2, OUTPUT);

  delay(500);
}

void loop() {
  //Make sure we put inputs back to inputs after testing the CPU tester board by itself:
  digitalWrite(CON_RQ, HIGH);
  digitalWrite(RST, HIGH);
  digitalWrite(STOP, HIGH);
  pinMode(CON_INST, INPUT_PULLUP);
  pinMode(CON_DATA, INPUT_PULLUP);

  /*
  pinMode(CONT_ISTP_MSTP, INPUT_PULLUP);
  pinMode(MSTP, INPUT_PULLUP);
  pinMode(ISTP, INPUT_PULLUP);
  */
  
  pinMode(PL, INPUT);
  pinMode(RESTART_ENAB, INPUT);
  for (int i = StartPin; i <= EndPin; i = i + 1) { //For Testing all the pretty lights
    pinMode(i, INPUT);
  }
  for (int i = Mem0StartPin; i <= Mem15EndPin; i = i + 1) { //For testing Data Switches 0-15
    pinMode(i, INPUT);
  }

  InitializeSignals();

  //////////////////////TEST MODE SWITCHER///////////////////////////////////////
  switch (sw_bits) {
    case (0x1): {     // DIP1 program loader
      if (load_code[0] != 0) {
        Stop2Reset2();
        
        // set start address
        fp_set(load_addr);
        Examine();
        delay(DelayAmount);
    
        // send first data
        fp_set(load_code[0]);
        Deposit();
        delay(DelayAmount);
        
        for (int i = 1; i < (sizeof(load_code) / sizeof(load_code[0])); i++) {
          fp_set(load_code[i]);
          DepositNext();
          delay(DelayAmount);
        }
    
        // PUT CODE-SPECIFIC INSTRUCTIONS HERE
        // set value to compute in address 3
        fp_set(5);
        Deposit_AC(3);
        delay(DelayAmount);
        
        fp_set(0102);
        Examine();
        delay(DelayAmount * 2);
    
        // Start();
        while (true) {
          Memory_Step();
          delay(DelayAmount * 2);
        }
    
        // read computed value from address 0
        Examine_AC(0);
        delay(DelayAmount);
      }
      break;
    }
    case (0x2): {     // DIP2
      uint16_t s;
      uint16_t start_addr = 0;
      
      Stop2Reset2();

      while(true) {
        start_addr ^= 01000;  //Exclusive OR 

        // start at address 0
        fp_set(start_addr);
        Examine();
          
        for (uint16_t i = start_addr; i < start_addr + 0100; i++) {
          s = i & 017;
          s = 1 << s;
          
          fp_set(s);
          DepositNext();
          delay(30);
          Pause();
        }
        for (uint16_t i = start_addr; i < start_addr + 0100; i++) {
          fp_set(i);
          Examine();
          delay(60);
          Pause();
        }
        delay(1000);
        fp_set(start_addr);
        Examine();
        delay(1000);
        for (uint16_t i = start_addr; i < start_addr + 0100; i++) {
          s = 0177777;
          fp_set(s);
          DepositNext();
          delay(30);
          Pause();
        }
        for (uint16_t i = start_addr; i < start_addr + 0100; i++) {
          fp_set(i);
          Examine();
          delay(60);
          Pause();
        }
        delay(1000);
      }
      
      break;
    }
    case (0x4): {     // DIP3
      Stop2Reset2();

      uint16_t r = 0;
      uint16_t lit;
      uint8_t dir = 0;
      
      while(true) {
        r++;
        
        if (r > 15) {
          r = 0;
          dir ^= 1;
        }

        if (dir) {
          lit = 1 << r;           // light the segment
          if (r)
            lit |= 1 << (r - 1);  // trail
        } else {
          lit = 1 << (15 - r);    // light the segment
          if (r)
            lit |= 1 << (16 - r);  // trail
        }

        fp_set(lit);
        Examine();
        
        delay(15);
      }
      
      break;
    }
    case (0x8): {     // DIP4
      uint16_t s;
      uint16_t start_addr = 0;
      
      Stop2Reset2();

      while(true) {
        start_addr = 010000;  //Exclusive OR 

        // clear low addresses
        fp_set(0);
        Examine();

        for (uint16_t i = start_addr; i < start_addr + 0100; i++) {
          
          fp_set(0);
          DepositNext();
          delay(20);
          Pause();
        }

        // set pattern to high addresses
        fp_set(start_addr);
        Examine();

        for (uint16_t i = start_addr; i < start_addr + 0100; i++) {
          s = i & 017;
          s = 1 << s;
          
          fp_set(s);
          DepositNext();
          delay(20);
          Pause();
        }

        // read from high addresses
        for (uint16_t i = start_addr; i < start_addr + 0100; i++) {
          fp_set(i);
          Examine();
          delay(60);
          Pause();
        }

        // read from low addresses
        for (uint16_t i = 0; i < 0100; i++) {
          fp_set(i);
          Examine();
          delay(60);
          Pause();
        }
        delay(1000);
    }

      break;
    }
  }

  /*
  for (int i = StartPin; i <= 29; i = i + 1) { //sequence the lights 
    digitalWrite(i, LOW);
    delay(200);
  }
  for (int i = 33; i <= 48; i = i + 1) { //sequence the lights 
    digitalWrite(i, LOW);
    delay(200);
  }
  */
}

void fp_set(uint16_t switches) 
{
  uint16_t s;
    
  digitalWrite(LatchPin1, LOW); // Send bits 0 - 7 into the 595
  digitalWrite(LatchPin2, LOW); // Send bits 8 -15 into the 595

  for (uint8_t i = 0; i < 8; i++) {
    s = switches >> 8;    // fixes stupid 8-bit compiler bug
    digitalWrite(DataPin1, (s        & 1));
    digitalWrite(DataPin2, (switches & 1));
    switches >>= 1;

    digitalWrite(ClockPin1, HIGH);
    digitalWrite(ClockPin2, HIGH);
    digitalWrite(ClockPin1, LOW);
    digitalWrite(ClockPin2, LOW);
  }

  digitalWrite(LatchPin1, HIGH);
  digitalWrite(LatchPin2, HIGH);
}

void InitializeSignals()
{
  digitalWrite(CON_RQ, HIGH); // INITIALIZE SIGNALS?
  digitalWrite(RST, HIGH);
  digitalWrite(STOP, HIGH);
  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, HIGH);
  digitalWrite(MEM7, HIGH);
}

void Stop2Reset2()
{
  digitalWrite(STOP, LOW); //STOP TWICE
  delay(50);
  digitalWrite(STOP, HIGH);
  delay(50);
  digitalWrite(STOP, LOW);
  delay(50);
  digitalWrite(STOP, HIGH);
  delay(50);

  digitalWrite(RST, LOW); //RESET TWICE
  delay(50);
  digitalWrite(RST, HIGH);
  delay(50);
  digitalWrite(RST, LOW);
  delay(50);
  digitalWrite(RST, HIGH);
  delay(50);
}

void Deposit()
{
  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, LOW);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, LOW);
  digitalWrite(MEM7, HIGH);

  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void DepositNext()
{
  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, LOW);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, LOW);
  digitalWrite(MEM7, LOW);

  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void Examine()
{
  digitalWrite(MEM0, HIGH); ///front panel code for EXAMINE (NOTE: these signals are inverted from how the NOVA sees them)
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, LOW);
  digitalWrite(MEM6, LOW);
  digitalWrite(MEM7, HIGH);

  digitalWrite(CON_RQ, LOW);
  delay(DelayAmount);
  digitalWrite(CON_RQ, HIGH);
  delay(DelayAmount);
}

void ExamineNext()
{
  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, LOW);
  digitalWrite(MEM7, LOW);

  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void Start()
{
  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, LOW);
  digitalWrite(MEM6, HIGH);
  digitalWrite(MEM7, HIGH);

  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void Deposit_AC(uint8_t ac)
{
  if (ac > 3) return;

  digitalWrite(MEM0, LOW);
  digitalWrite(MEM1, LOW);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, ac & 2);
  digitalWrite(MEM4, ac & 1);
  digitalWrite(MEM5, LOW);
  digitalWrite(MEM6, HIGH);
  digitalWrite(MEM7, HIGH); 

  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void Examine_AC(uint8_t ac)
{
  if (ac > 3) return;

  digitalWrite(MEM0, LOW);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, ac & 2);
  digitalWrite(MEM4, ac & 1);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, HIGH);
  digitalWrite(MEM7, HIGH); 

  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void Instruction_Step()
{
  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, HIGH);
  digitalWrite(MEM7, HIGH);

  digitalWrite(ISTP, LOW);
  digitalWrite(CONT_ISTP_MSTP, LOW);
  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(ISTP, HIGH);
  digitalWrite(CONT_ISTP_MSTP, HIGH);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void Memory_Step()
{
  digitalWrite(MEM0, HIGH);
  digitalWrite(MEM1, HIGH);
  digitalWrite(MEM2, HIGH);
  digitalWrite(MEM3, HIGH);
  digitalWrite(MEM4, HIGH);
  digitalWrite(MEM5, HIGH);
  digitalWrite(MEM6, HIGH);
  digitalWrite(MEM7, HIGH);

  digitalWrite(MSTP, LOW);
  digitalWrite(CONT_ISTP_MSTP, LOW);
  digitalWrite(CON_RQ, LOW);
  delay(50);
  digitalWrite(MSTP, HIGH);
  digitalWrite(CONT_ISTP_MSTP, HIGH);
  digitalWrite(CON_RQ, HIGH);
  delay(50);
}

void Pause() 
{
  while(digitalRead(PauseSwitch) == LOW){
//just loop endlessly until the switch goes high again
  }
}

