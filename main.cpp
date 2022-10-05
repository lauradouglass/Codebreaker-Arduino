#include <Arduino.h>
#include "DigitalPin.h"

//states for changing isr
int stateR = 0;
int stateG = 0;
int stateB = 0;
int stateY = 0;

//assign pin numbers
DigitalPin red(5);
DigitalPin green(6);
DigitalPin blue(44);
DigitalPin yellow(11);

void setup() 
{
  //initialize connection to serial monitor 
  Serial.begin(9600);

 //timer 3 (RED)
  noInterrupts(); // Disable all interrupts
  red.set_TCCRA();
  red.set_TCCRB();
  red.set_TIMSK();
  red.set_TCNT();
  red.set_OCR_slow();
  interrupts();

  //timer 4 (GREEN)
  noInterrupts(); 
  green.set_TCCRA();
  green.set_TCCRB();
  green.set_TIMSK();
  green.set_TCNT();
  green.set_OCR_slow();
  interrupts();

  //timer 5 (BLUE)
  noInterrupts(); 
  blue.set_TCCRA();
  blue.set_TCCRB();
  blue.set_TIMSK();
  blue.set_TCNT();
  blue.set_OCR_slow();
  interrupts();

  //timer 1 (YELLOW)
  noInterrupts(); 
  yellow.set_TCCRA();
  yellow.set_TCCRB();
  yellow.set_TIMSK();
  yellow.set_TCNT();
  yellow.set_OCR_slow();
  interrupts();
}

void loop() 
{
  //generate random passcode 
  int passcode = random(0,9999);
  
  //counter for a maximum of 5 attempts 
  int cnt;
  for (cnt = 0; cnt < 5; cnt++)
  {
    //while nothing is in terminal, do nothing 
    while (Serial.available() == 0)
    {
      
    }
    
    //convert int to string
    char buff[30];
    memset(buff, 0, sizeof(buff));
    snprintf(buff, sizeof(buff)-1, "%d", passcode);
    
    //print code to terinal for testing purposes
    Serial.println(buff); 
    
    Serial.println("Enter 4-digit passcode:");
    delay(10000);
    int buff2 = Serial.parseInt();
    //convert int to string
    char userCode[30];
    memset(userCode, 0, sizeof(userCode));
    snprintf(userCode, sizeof(userCode)-1, "%d", buff2);

    //if code is correct, break;
    if((stateY == 1)&&(stateB == 1)&&(stateG == 1)&&(stateR == 1))
    {
      break;
    }

    if(userCode[0] == buff[0])
    {
      //yellow off
      stateY = 1;
    }
    else
    {
      stateY = 0;
      yellow.set_OCR_fast();
    }

    if(userCode[1] == buff[1])
    {
      //blue off
      stateB = 1;
    }
    else{
      stateB = 0;
      blue.set_OCR_fast();
    }

    if(userCode[2] == buff[2])
    {
      //green off
      stateG = 1;
    }
    else
    {
      stateG = 0;
      green.set_OCR_fast();
    }
    
    if(userCode[3] == buff[3])
    {
      //red off
      stateR = 1;
    }
    else
    {
      stateR = 0;
      red.set_OCR_fast();
    }
  }
  delay(5000);
  if((stateY == 1)&&(stateB == 1)&&(stateG == 1)&&(stateR == 1))
  {
    Serial.println("Passcode correct!");
  }
  else
  {
    Serial.println("Unfortunately, you have reached the maximum attempts available. Please restart program.");
    
    //set all states to 0, just incase
    if(stateY == 1)
    {
      stateY = 0;
      yellow.set_OCR_on();
    }
    else if (stateY == 0)
    {
      yellow.set_OCR_on();
    }
    
    if(stateB == 1)
    {
      stateB = 0;
      blue.set_OCR_on();
    }
    else if (stateB == 0)
    {
      blue.set_OCR_on();
    }

    if(stateG == 1)
    {
      stateG = 0;
      green.set_OCR_on();
    }
    else if (stateG == 0)
    {
      green.set_OCR_on();
    }

    if(stateR == 1)
    {
      stateR = 0;
      red.set_OCR_on();
    }
    else if (stateR == 0)
    {
      red.set_OCR_on();
    }
  }
}

//on-off toggle (0 = on, else off)
//red
ISR(TIMER3_COMPA_vect){
  if (stateR == 0)
  {
    digitalWrite(5,!digitalRead(5));
  }
  else 
  {
    digitalWrite(5,LOW);
  }
}
//green
ISR(TIMER4_COMPA_vect){
  if (stateG == 0)
  {
    digitalWrite(6,!digitalRead(6)); 
  }
  else
  {
    digitalWrite(6,LOW);
  }
}
//blue
ISR(TIMER5_COMPA_vect){
  if (stateB == 0)
  {
    digitalWrite(44,!digitalRead(44)); 
  }
  else
  {
    digitalWrite(44,LOW);
  }
}
//yellow
ISR(TIMER1_COMPA_vect){
  if (stateY == 0)
  {
    digitalWrite(11,!digitalRead(11)); 
  }
  else
  {
    digitalWrite(11,LOW);
  }
}

