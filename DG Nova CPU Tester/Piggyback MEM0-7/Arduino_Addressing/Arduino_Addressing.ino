String Address = "07757";
String EnterData = "126440";
String Octal = "0";
String Binary = "";

void setup() {
  Serial.begin(115200);
  Serial.println("====================");

//for c = 1 to len(MyString)
//Hex = Mid(MyString,len(MyString),1)
//Hex = Mid(Address,c,1)
//Next c

for (size_t c = 1; c <= Address.length(); ++c) {
  Octal = Address[c - 1]; // Get the last character
  Serial.println(Octal);
if(Octal == "0") {Binary = Binary + "000";};
if(Octal == "5") {Binary = Binary + "101";};
if(Octal == "7") {Binary = Binary + "111";};
};

}

void loop() {
 Serial.println(Binary);
   delay(20000);

}
