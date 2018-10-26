#include <Stepper.h>
#include <IRremote.h>

#define STEPS 200

const int RECV_PIN = 4, LED1 = 2, LED2 = 7;
int i = 0, cli = 0, previous = 0, motor_speed = 60, depm = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;
Stepper stepper(STEPS, 8, 9, 10, 11);

void setup()
{
  Serial.begin(9600);
  stepper.setSpeed(50);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  irrecv.enableIRIn();
}

void loop()
{
  int val = analogRead(0);

  stepper.step(motor_speed);

  if(cli == 1){
    if(i < 3){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      if(motor_speed == 0) delay(50);
    }
    else if(i > 2){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      if(motor_speed == 0) delay(50);
    }
    i++;
  }
  else{
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  if(cli > 1) cli = 0;
  if(i > 5) i = 0;
  
  if (irrecv.decode(&results)){
      Serial.print("Key pressed : ");
      Serial.println(results.value);
      irrecv.resume();

      //if(results.value == 4294967295) motor_speed += depm;

      if(results.value == 16582903){
          motor_speed += 20, depm = 20;
          Serial.println("Acceleration"); /// 1
      }
      if(results.value == 16615543) cli++;//Serial.println("2"); /// 2
      if(results.value == 16599223){
          motor_speed -= 20, depm = -20;
          Serial.println("Deceleration"); /// 3
      }
      if(results.value == 16591063) Serial.println(motor_speed); /// 4
      if(results.value == 16623703) Serial.println("5");
      if(results.value == 16607383) Serial.println("6");
      if(results.value == 16586983) Serial.println("7");
      if(results.value == 16619623) Serial.println("8");
      if(results.value == 16603303) Serial.println("9");
  }
}

