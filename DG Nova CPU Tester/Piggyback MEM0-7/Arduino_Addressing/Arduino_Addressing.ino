String Address = "07757";
String EnterData = "126440";
String Octal = "0";
String Binary = "0";
String TestStr = "";
String Upper = "";

void setup() {
  Serial.begin(115200);
  Serial.println("====================");

for (size_t c = 1; c <= Address.length(); ++c) {
  Octal = Address[c - 1]; // Get the last character
  Serial.println(Octal);
if(Octal == "0") {Binary = Binary + "000";};
if(Octal == "5") {Binary = Binary + "101";};
if(Octal == "7") {Binary = Binary + "111";};
};

Binary = "1234567890123456";

Upper = Binary.SubStr(7, 8);
  Serial.println(Upper);

}

void loop() {
 Serial.println(Binary);
 Serial.println(Upper);
    delay(20000);

}
