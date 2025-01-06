#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);



#define ir_enter 6
#define ir_back  7

#define ir_car1 5
#define ir_car2 3
#define ir_car3 2
#define ir_car4 4


#define card1 "41 42 04 47"
#define card2 "23 F5 90 56"
#define card3 "63 7C 2E 10"
#define card4 "53 E3 68 A0"
#define card5 "B3 D1 5A A0"

#define card1_user "FAISAL"
#define card2_user "RIFAT"
#define card3_user "TAHMID"
#define card4_user "TOWHID"
#define card5_user "MAHIN"


 
#define SS_PIN 10
#define RST_PIN 9

Servo myservo;
MFRC522 mfrc522(SS_PIN, RST_PIN);

int S1=0, S2=0, S3=0, S4=0;
int flag1=0, flag2=0; 
int slot = 4;  int count=0;




void setup(){
Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();

pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);

pinMode(A0,OUTPUT);
pinMode(A1,OUTPUT);
pinMode(A2,OUTPUT);
pinMode(A3,OUTPUT);
digitalWrite(A3,HIGH);

pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);


  
myservo.attach(8);
myservo.write(90);

lcd.begin(20, 4);  
lcd.setCursor (0,0);
lcd.print("CAR PARKING SYSTEM");
delay (500);
lcd.setCursor (0,1);
lcd.print("    DEVELOPED BY");
delay (500);
lcd.setCursor (0,2);
lcd.print("FAISAL RIFAT TOWHID");
delay (500);
lcd.setCursor (0,3);
lcd.print("    TAHMID MAHIN");
delay (3000);
lcd.clear();   

Read_Sensor();

int total = S1+S2+S3+S4;
slot = slot-total; 
}

void loop(){

       
Read_Sensor();
if(!digitalRead (ir_enter) == 0){
  if(count==1)
       {
         lcd.clear();
       }
       count=0;
lcd.setCursor (0,0);
lcd.print("   Have Slot: "); 
lcd.print(slot);
lcd.print("    ");  

lcd.setCursor (0,1);
if(S1==1){lcd.print("S1:Fill ");}
     else{lcd.print("S1:Empty");}

lcd.setCursor (10,1);
if(S2==1){lcd.print("S2:Fill ");}
     else{lcd.print("S2:Empty");}

lcd.setCursor (0,2);
if(S3==1){lcd.print("S3:Fill ");}
     else{lcd.print("S3:Empty");}

lcd.setCursor (10,2);
if(S4==1){lcd.print("S4:Fill ");}
     else{lcd.print("S4:Empty");}
     
}

if(digitalRead (ir_enter) == 0 && flag1==0){
    if(flag2==1)
          {
            delay (500);
            myservo.write(90);
            flag2=0;
            lcd.clear(); 
            lcd.setCursor (4,0);
            lcd.print("GOODBYE");
            lcd.setCursor (0,1);
            lcd.print("HAVE A NICE DAY");
            lcd.setCursor (4,2);
            lcd.print("VISIT AGAIN");
            lcd.setCursor (4,3);
            lcd.print("GOOD LUCK");
            delay(3000);
            lcd.clear(); 
          }
    else if(slot>0){
     
         if(count==0)
       {
         lcd.clear();
       }
       count=1;
        lcd.setCursor (0,0);
        lcd.print("    PLEASE ENTER   ");
        lcd.setCursor (0,1);
        lcd.print("                   ");
        lcd.setCursor (0,2);
        lcd.print("    YOUR CARD      ");
        lcd.setCursor (0,3);
        lcd.print("                   ");
         
        
        

        if(flag2==0){
          
          authy();
        
          }
          
    }
    else{
    lcd.setCursor (0,0);
    lcd.print(" Sorry Parking Full ");  
    delay(1500);
    }   
}

if(digitalRead (ir_back) == 0 && flag2==0){
  flag2=1;
if(flag1==0){
  myservo.write(180);
   slot = slot+1;
  }
}



if(flag1==1 && flag2==1 && digitalRead (ir_back)==1){
delay(500);
myservo.write(90);
flag1=0, flag2=0;
digitalWrite(A1,LOW);
digitalWrite(A2,LOW);
}


delay(500);

}

void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0;

if(digitalRead(ir_car1) == 0){S1=1;}
if(digitalRead(ir_car2) == 0){S2=1;}
if(digitalRead(ir_car3) == 0){S3=1;}
if(digitalRead(ir_car4) == 0){S4=1;}
}

void authy()
{
  
      String content= "";
      byte letter;
      if ( ! mfrc522.PICC_IsNewCardPresent()) 
      {
        return;
      }
      if ( ! mfrc522.PICC_ReadCardSerial()) 
      {
        return;
      }
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
       //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       // Serial.print(mfrc522.uid.uidByte[i], HEX);
       tone(A0,2500,1000);
       
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      Serial.println(content.substring(1));
      content.toUpperCase();
      if (content.substring(1) == card1) //change here the UID of the card/cards that you want to give access
      {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("WELCOME");
        lcd.setCursor (0,1);
        lcd.print(card1_user);
        flag1=1;
        myservo.write(180); 
        slot = slot-1;
        digitalWrite(A1,HIGH);
        delay(2000);
        lcd.clear();
       
        
      }
      else if (content.substring(1) == card2) //change here the UID of the card/cards that you want to give access
      {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("WELCOME");
        lcd.setCursor (0,1);
        lcd.print(card2_user);
        flag1=1;
        myservo.write(180); 
        slot = slot-1;
        digitalWrite(A1,HIGH);
        delay(2000);
        lcd.clear();
        
        
      }
      else if (content.substring(1) == card3) //change here the UID of the card/cards that you want to give access
      {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("WELCOME");
        lcd.setCursor (0,1);
        lcd.print(card3_user);
        flag1=1;
        myservo.write(180); 
        slot = slot-1;
        digitalWrite(A1,HIGH);
        delay(2000);
        lcd.clear();
        
      
      }
      else if (content.substring(1) == card4) //change here the UID of the card/cards that you want to give access
      {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("WELCOME");
        lcd.setCursor (0,1);
        lcd.print(card4_user);
        flag1=1;
        myservo.write(180); 
        slot = slot-1;
        digitalWrite(A1,HIGH);
        delay(2000);
        lcd.clear();
       
        
      }
      else if (content.substring(1) == card5) //change here the UID of the card/cards that you want to give access
      {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("WELCOME");
        lcd.setCursor (0,1);
        lcd.print(card5_user);
        flag1=1;
        myservo.write(180); 
        slot = slot-1;
        digitalWrite(A1,HIGH);
        delay(2000);
        lcd.clear();
       
        
      }
    else if(content.substring(1) !="" ) 
    {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("Access denied");
        tone(A0,500,1200);
        digitalWrite(A2,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(A2,LOW);
        
      }

}

