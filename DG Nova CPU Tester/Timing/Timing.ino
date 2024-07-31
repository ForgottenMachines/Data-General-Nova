constexpr int CON_RQ = A5; //used by multiple switches????

void setup() {
       pinMode(CON_RQ, OUTPUT); 
}

void loop() {

digitalWrite(CON_RQ, LOW);  
digitalWrite(CON_RQ, HIGH);  

}