String Address = "07757";
String EnterData = "126440";

void setup() {
  Serial.begin(115200);

//for c = 1 to len(MyString)
//Hex = Mid(MyString,len(MyString),1)
//Next c

#include <string>

std::string MyString = "YourStringHere"; // Replace with your actual string
std::string Hex;

for (size_t c = 1; c <= MyString.length(); ++c) {
    Hex = MyString[MyString.length() - 1]; // Get the last character
};



}

void loop() {
  Serial.println("Hi");
  delay(200);

}
