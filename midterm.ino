#include <Stepper.h> //引入步進馬達函示庫
#include <Wire.h>
#include "SSD1306Wire.h"

const int stepsPerRevolution = 2048;  //此馬達轉一圈為2048步
const int RPM = 10; //馬達旋轉速度
const int btn1_pin = 34, btn2_pin = 35 ,btn3_pin = 36;
const int LED[3] = {4,12,14};
bool btn1_Pressed = false, btn2_Pressed = false, btn3_Pressed = false;  
bool floor1_Btn_Status = false, floor2_Btn_Status = false, floor3_Btn_Status = false;
int cc=0;

//宣告Stepper物件，的步數和引腳
//引角依序對應驅動版的1N1、1N3、1N2、1N4
Stepper myStepper(stepsPerRevolution, 27, 25, 26, 33);  
SSD1306Wire display(0x3c,21,22);

void setup() {  
  Serial.begin(115200);
  
  myStepper.setSpeed(RPM);  //設定馬達轉速
  pinMode(btn1_pin,INPUT);
  pinMode(btn2_pin,INPUT);
  pinMode(btn3_pin,INPUT);
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  digitalWrite(LED[0],LOW);
  digitalWrite(LED[1],LOW);
  digitalWrite(LED[2],LOW);

  display.init();
}

//OLED 
//display.setFont(ArialMT_Plain_24);
//display.drawString(0,16,String(precent_floor));

int precent_floor=1;
//what floor?
int i=0;
int j = 0;
int floors[3] = {0};
int n=0; //n為經過幾層樓
//void move()
//{
//  //上升中
//  for(i=(precent_floor)-1;i<3;i++)
//  {
//    if(floors[i]!=0)
//    {
//      cc = ((i+1)- precent_floor)*n;  //n為一層樓所需步數
//      myStepper.step(cc);
//      display.clear();
//      display.setFont(ArialMT_Plain_24);
//      precent_floor=floors[i];
//      display.drawString(0,16,String(precent_floor));
//    }
//  }
//  
//  //下降中
//    for(i=(precent_floor)-2;i>-1;i--)
//  {
//    if(floors[i]!=0)
//    {
//      cc = (precent_floor-(i+1))*n;
//      myStepper.step(-cc);
//      display.clear();
//      display.setFont(ArialMT_Plain_24);
//      precent_floor=floors[i];
//      display.drawString(0,16,String(precent_floor));
//      display.display();
//    }
//  }
//}
//移動
//switch(floor)
//{
//  case:.  
//  
//}

void down(int n){
  for(j=n;j>0;j--){
    myStepper.step(-50);
    if(floors[j-2] != 0)
    {
      digitalWrite(LED[j-2],LOW);
      precent_floor--;
    }
  }
}

void up(int n)
{
  for(j=0; j<n; j++)
  {
    myStepper.step(50);
    if(floor[j] != 0)
    {
      digitalWrite(floors[j],LOW);
      precent_floor++;
    }
  }
}


void loop() {

  //Floor 1
  if(digitalRead(btn1_pin) == 1 && btn1_Pressed == false)
  {
    btn1_Pressed = true;

    floor1_Btn_Status = !floor1_Btn_Status;
    digitalWrite(LED[0],floor1_Btn_Status? HIGH: LOW);

    if(floor1_Btn_Status == true) floors[0] = 1;
    else floors[0] = 0;
  }
  else if(digitalRead(btn1_pin) == 0 && btn1_Pressed == true){
    btn1_Pressed = false;
  }
  
  //Floor 2
  if(digitalRead(btn2_pin) == 1 && btn2_Pressed == false)
  {
    btn2_Pressed = true;

    floor2_Btn_Status = !floor2_Btn_Status;
    digitalWrite(LED[1],floor2_Btn_Status? HIGH: LOW);

    if(floor2_Btn_Status == true) floors[1] = 2;
    else floors[1] = 0;
  }
  else if(digitalRead(btn2_pin) == 0 && btn2_Pressed == true){
    btn2_Pressed = false;
  }

  //Floor 3
  if(digitalRead(btn3_pin) == 1 && btn3_Pressed == false)
  {
    btn3_Pressed = true;

    floor3_Btn_Status = !floor3_Btn_Status;
    digitalWrite(LED[2],floor3_Btn_Status? HIGH: LOW);

    if(floor3_Btn_Status == true) floors[2] = 3;
    else floors[2] = 0;
  }
  else if(digitalRead(btn3_pin) == 0 && btn3_Pressed == true){
    btn3_Pressed = false;
  }

//  if(digitalRead(btn1_pin)==LOW && btn1_Pressed==false )
//  {
//    btn1_Pressed==true;
//    if(digitalRead(LED_1)==LOW)
//    {
//      digitalWrite(LED_1,HIGH);
//      floors[0]=1;
//      Serial.println("digitalWrite Low");
//    }
//    else if(digitalRead(LED_1)==HIGH)
//    {
//       digitalWrite(LED_1,LOW);
//       floors[0]=0;
//       Serial.println("digitalWrite High");
//    }
//  }
//
//  else if(digitalRead(btn1_pin) == LOW && btn1_Pressed == true){
//    btn1_Pressed = false;
//  }
  
//btn2
//  if(digitalRead(btn2_pin)==1 && btn2_Pressed==false )
//  {
//    btn1_Pressed==true;
//    if(digitalRead(LED_2)==LOW)
//    {
//      digitalWrite(LED_2,HIGH);
//      floors[1]=2;
//    }
//    else if(digitalRead(LED_2)==HIGH)
//    {
//       digitalWrite(LED_2,LOW);
//       floors[1]=0;
//    }
//  }
//
//  else if(digitalRead(btn2_pin) == LOW && btn2_Pressed == true){
//    btn2_Pressed = false;
//  }
//  
////btn3
//  if(digitalRead(btn3_pin)==1 && btn3_Pressed==false )
//  {
//    btn1_Pressed==true;
//    if(digitalRead(LED_3)==LOW)
//    {
//      digitalWrite(LED_3,HIGH);
//      floors[2]=3;
//    }
//    else if(digitalRead(LED_3)==HIGH)
//    {
//       digitalWrite(LED_3,LOW);
//       floors[2]=0;
//    }
//  }
//
//  else if(digitalRead(btn3_pin) == LOW && btn3_Pressed == true){
//    btn3_Pressed = false;
//  }

//Serial.print(floors[0]);
//Serial.print(floors[1]);
//Serial.println(floors[2]);
  for(i = 0; i<3; i++)
  {
    if(floors[i]!=0)
    {
      
     if( precent_floor > floors[i])
     {
        int floor_gap = precent_floor - floors[i];
        for(j=floor_gap;j>0;j--)
        {
          for(int k = 0;k<850;k++)
          {
            myStepper.step(-1);
            delay(10);
          }
          precent_floor--;
          if(floors[j-1] != 0)
          {
            digitalWrite(LED[j-1],LOW);
            floors[j-1 ]=0;
          }
        }
        digitalWrite(LED[i],LOW); 
        floors[i] = 0;
     }
    
     else if( precent_floor < floors[i])
     {
       int floor_gap = floors[i] - precent_floor;
       for(int j=0; j<floor_gap; j++)
       {
          Serial.println(precent_floor);
        
          for(int k = 0;k<850;k++)
          {
            myStepper.step(1);
            delay(10);
          }
          
          precent_floor++;
          
          if(floor[i+j] != 0)
          {
            digitalWrite(LED[j],LOW);
            floors[i+j]=0;
          }
       } 
       digitalWrite(LED[i],LOW); 
       floors[i] = 0;
     }
   }
  }
//  
//  //下降中
//  for(i=(precent_floor)-2;i>-1;i--)
//  {
//    if(floors[i]!=0)
//    {
//      cc = (precent_floor-(i+1))*n;
//      myStepper.step(-cc);
//      display.clear();
//      display.setFont(ArialMT_Plain_24);
//      precent_floor=floors[i];
//      display.drawString(0,16,String(precent_floor));
//    }
//  }

//  cc=digitalRead(btn1_pin)-digitalRead(btn2_pin);
//  myStepper.step(cc);
//  delay(50);
//  Serial.println(cc);
}
