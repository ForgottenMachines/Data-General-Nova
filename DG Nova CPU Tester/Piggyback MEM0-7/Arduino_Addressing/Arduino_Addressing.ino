String Address = "07757";
String EnterData = "126440";
///http://www.bitsavers.org/pdf/dg/software/utility/093-000002-01_Bootstrap_Loader70.pdf#page=8
///https://forum.arduino.cc/t/msbfirst-and-lsbfirst-on-shift-register/1100980/2
///https://www.codeconvert.ai/vb.net-to-c++-converter

String Octal = "0";
String Binary = "0";
String TestStr = "";
String Upper = "";
String Lower = "";

int DataPin1 = 3;  
int ClockPin1 = 4; 
int LatchPin1 = 5; 
int DataPin2 = 6;  
int ClockPin2 = 11; 
int LatchPin2 = 12; 


void setup() {
  Serial.begin(115200);
  Serial.println("====================");

for (size_t c = 1; c <= Address.length(); ++c) {
  Octal = Address[c - 1]; // Get the last character
  Serial.println(Octal);
if(Octal == "0") {Binary = Binary + "000";};
if(Octal == "1") {Binary = Binary + "001";};
if(Octal == "2") {Binary = Binary + "010";};
if(Octal == "3") {Binary = Binary + "011";};
if(Octal == "4") {Binary = Binary + "100";};
if(Octal == "5") {Binary = Binary + "101";};
if(Octal == "6") {Binary = Binary + "110";};
if(Octal == "7") {Binary = Binary + "111";};
};

//Binary = "1234567890123456";

Upper = Binary.substring(0, 8);
Lower = Binary.substring(8, 16);

  pinMode(DataPin1, OUTPUT); 
  pinMode(ClockPin1, OUTPUT);  
  pinMode(LatchPin1, OUTPUT);
  pinMode(DataPin2, OUTPUT);  
  pinMode(ClockPin2, OUTPUT);  
  pinMode(LatchPin2, OUTPUT);


}

void loop() {
 Serial.println(Binary);
 Serial.println(Upper);
 Serial.println(Lower);


///https://forum.arduino.cc/t/converting-string-to-binary-code/115562
///https://docs.arduino.cc/built-in-examples/strings/StringToInt/

digitalWrite(LatchPin1,LOW);
shiftOut(DataPin1,ClockPin1,MSBFIRST,Upper);
digitalWrite(LatchPin1,HIGH);
digitalWrite(LatchPin2,LOW);
shiftOut(DataPin2,ClockPin2,MSBFIRST,Upper);
digitalWrite(LatchPin2,HIGH);

     delay(20000);


}
