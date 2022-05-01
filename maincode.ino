#include<LiquidCrystal.h>
const int BUTTON_PIN =7; //button to check temperature
const int BUTTON_RESET =8;//button to reset timer
const int BUTTON_PAUSE = 13;//button to pause timer
LiquidCrystal lcd(12,11,5,4,3,2); //lcd variable
int buttonState =0; //button state
int contrast =20; //contrast of display
int s=0; //seconds variable
int session_count = 1;
float total_seconds =0;
float temp;
int pause_state=0;
int pause_counter=0;
int tempPin = A0;
int hour_second=0;
int time_studied =0;


void setup(){
  pinMode(BUTTON_RESET,INPUT_PULLUP);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(BUTTON_PAUSE,INPUT_PULLUP);
  analogWrite(6,contrast);
  lcd.begin(16,2);
}


void loop(){
  //lcd.clear();
  buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == LOW){
    lcd.clear();
    
    while(buttonState==LOW){
      lcd.clear();
      
     temp = analogRead(tempPin);
  	temp = temp /1024;
  	temp = temp*5;
  	temp = temp - 0.5;
  	temp = temp*100;
      lcd.print("Stay Hydrated");
      
  	lcd.setCursor(1,1);
      lcd.print("TEMP: ");
      lcd.print(temp);
      lcd.print("'C");
  	
  	//lcd.print("Strech a bit");
    
      buttonState=digitalRead(BUTTON_PIN);
      delay(150);
    }
  }
  else{
     int bs = 0;
     int rs =0;
     int ps = 0;
    
    lcd.setCursor(0,1);
    
    
    while(s<43200){
      
    
    bs = digitalRead(BUTTON_PIN);
    rs = digitalRead(BUTTON_RESET);
    
    
    
        
      if(bs==LOW){break;}
      if(rs == LOW){total_seconds =hour_second; hour_second=0; session_count++;}
  	  lcd.clear();
      int hour =hour_second/3600;
      int min = (hour_second/60)%60;
      
      lcd.print(hour);
      lcd.print(":");
      lcd.print(min);
      lcd.print(":");
      lcd.print(hour_second%60);
      lcd.setCursor(7,1);
      lcd.print("S:");
      lcd.print(session_count);
      
      lcd.print(" TS:");
      lcd.print(time_studied/3600);
      
      delay(1000);//DELAY SHOULD BE 1000!!!
      s++;
      time_studied=s;
      hour_second++;
    }
  }
}


 
