String Address = "07757";
String EnterData = "126440";
String Octal = "0";
String Binary = "0";
String TestStr = "";
String Upper = "";
String Lower = "";

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

}

void loop() {
 Serial.println(Binary);
 Serial.println(Upper);
 Serial.println(Lower);
     delay(20000);

}
