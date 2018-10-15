#include <IRremote.h>
 
// Define sensor pin
const int RECV_PIN = 4, LED1 = 10, LED2 = 9;
int i = 0, cli = 0;
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
 
 
void setup(){
  // Serial Monitor @ 9600 baud
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  // Enable the IR Receiver
  irrecv.enableIRIn();
}
 
void loop(){
  if(cli == 1){
    if(i < 1000){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
    }
    else if(i > 2000){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    }
    i++;
  }
  if(cli > 1) cli = 0;
  if (irrecv.decode(&results)){
    // Print Code in HEX
      //Serial.println(results.value);
      irrecv.resume();
      if(results.value == 16582903) cli++;//Serial.println("1");
      if(results.value == 16615543) Serial.println("2");
      if(results.value == 16599223) Serial.println("3");
      if(results.value == 16591063) Serial.println("4");
      if(results.value == 16623703) Serial.println("5");
      if(results.value == 16607383) Serial.println("6");
      if(results.value == 16586983) Serial.println("7");
      if(results.value == 16619623) Serial.println("8");
      if(results.value == 16603303) Serial.println("9");
  }
}
