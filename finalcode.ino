#include<LiquidCrystal.h> 	//included liquid crystal library
const int BUTTON_PIN =7;	 //button to check temperature
const int BUTTON_RESET =8;	//button to reset timer
LiquidCrystal lcd(12,11,5,4,3,2);	 //lcd variable
int buttonState =0; 	//button state
int contrast =20;	 //contrast of display
int s=0; 	//seconds variable
int session_count = 1;	//counts the number of sessions
float time_studied =0;	//counts the total number of seconds
float temp;		//variable to store the valu of temperature
int tempPin = A0;	//taking analog input via A0 pin
int hour_second=0; //temporary variable to hold seconds when reset
 


void setup(){
  //setting up the reset button
  pinMode(BUTTON_RESET,INPUT_PULLUP);
  //setting up the slide switch
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  //setting the contrast of the display
  analogWrite(6,contrast);
  //starting the display
  lcd.begin(16,2);
}


void loop(){
  buttonState = digitalRead(BUTTON_PIN);
  //when button is pressed temperature is displayed
  //with the message stay hydrated
  if(buttonState == LOW){
    lcd.clear();
    
    while(buttonState==LOW){
      lcd.clear();
      
      //reading temperature
     temp = analogRead(tempPin);
      //temprature conversion
  	temp = temp /1024;
  	temp = temp*5;
  	temp = temp - 0.5;
  	temp = temp*100;
    lcd.print("Stay Hydrated");
     
      //printing temperature
  	lcd.setCursor(1,1);
      lcd.print("TEMP: ");
      lcd.print(temp);
      lcd.print("'C");
    
      //reads buttonState
      buttonState=digitalRead(BUTTON_PIN);
      //delay for proper printing
      delay(150);
    }
  }
  
  //when switch is high the timer code runs
  else{
    //extra variables for reading button state and reset state
     int bs = 0;
     int rs =0;
    
    lcd.setCursor(0,1);
    
    
    while(s<43200){ //12hrs =43200
      
    //reading swtich and button inputs
    bs = digitalRead(BUTTON_PIN);
    rs = digitalRead(BUTTON_RESET);
    
    
    
      //when bs is LOW(right side) it goes to the temperature code
      if(bs==LOW){break;}
      //when reset is LOW(pressed) Timer resets to zero and session is incremented
      if(rs == LOW){hour_second=0; session_count++;}
      
      //constantly refreshing display and printing
  	  lcd.clear();
      //hour conversion
      int hour =hour_second/3600;
      //minute conversion
      int min = (hour_second/60)%60;
      
      //printing the time
      lcd.print(hour);
      lcd.print(":");
      lcd.print(min);
      lcd.print(":");
      lcd.print(hour_second%60);
      lcd.setCursor(7,1);
      
      //printing session count
      lcd.print("S:");
      lcd.print(session_count);
      
      //printing time studied
      lcd.print(" TS:");
      lcd.print(time_studied/3600);
      
      delay(1000);//DELAY SHOULD BE 1000 for proper measure of time as 1000ms = 1s
      
      //incrementation and updation of loop variables
      s++;
      time_studied=s;
      hour_second++;
    }
  }
}


 
