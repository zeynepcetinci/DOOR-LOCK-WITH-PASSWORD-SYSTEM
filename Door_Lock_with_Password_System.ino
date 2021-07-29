#include <Servo.h>
#include <LiquidCrystal_I2C_AvrI2C.h>
#include <Keypad.h>
Servo myservo; 
LiquidCrystal_I2C_AvrI2C lcd(0x27, 16, 2);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 8}; //connect to the column pinouts of the keypad
String password = "1234"; // the password of the door
String mypassword; //your entry password
int deg=0;
int counter = 0; 
int buzzer=11; // buzzer pin
 
void setup(){
  Serial.begin(9600);
  lcd.begin();
  myservo.attach(10); //SERVO ATTACHED
  pinMode(buzzer, OUTPUT);
  Serial.println("enter password");
  lcd.print("Enter Password:");
}
  
void loop(){
 keypadfunction();
}

void buzzerFunc(){ //Makes the buzzer work when the button is pressed
  digitalWrite(buzzer, HIGH);
  delay(50);
  digitalWrite(buzzer, LOW);
}
 
void keypadfunction(){
 char key = keypad.getKey();
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print("*");
  }
  if (key == '1'){
    mypassword = mypassword + 1;   
    buzzerFunc();
  }
  if (key == '2'){
    mypassword = mypassword + 2;  
    buzzerFunc();
  }
  if (key == '3'){
    mypassword = mypassword + 3; 
    buzzerFunc();
  }
   if (key == '4'){
    mypassword = mypassword + 4;  
    buzzerFunc();
  }
  if (key == '5'){
    mypassword = mypassword + 5;
    buzzerFunc();
  }
   if (key == '6'){ 
    mypassword = mypassword + 6; 
    buzzerFunc();
  }
   if (key == '7'){
    mypassword = mypassword + 7; 
    buzzerFunc();
  }
   if (key == '8'){
    mypassword = mypassword + 8; 
    buzzerFunc();
  }
  if (key == '9'){
    mypassword = mypassword + 9;
    buzzerFunc();
  }            
  if (key == '0'){
    mypassword = mypassword + 0; 
    buzzerFunc();
  }
  if (key == '*'){ //After entering the password, * key is pressed.
    Serial.println(mypassword); 
    if ( password == mypassword ){ //If the password entered is correct
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("Welcome ");
      lcd.setCursor(0,1);
      lcd.print("Door Open");
      lcd.clear();
      
      for(deg = 90; deg>=0; deg-=5){ //goes from 180 degrees to 0 degrees
        myservo.write(deg); 
        delay(5); //waits 5ms for the servo to reach the position
      }
      counterbeep();
      for(deg = 0; deg <= 90; deg +=5){ // goes from 0 degrees to 180 degrees
        myservo.write(deg); // tell servo to go to position in variable deg
        delay(15);
        counter = 0; //Password entry is reset
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Enter Password");
      }
    }
    else{   //If the password entered is wrong
      lcd.clear(); 
      lcd.setCursor(0,0); 
      lcd.print("Wrong Password");
      delay(1000);
      lcd.clear(); 
      lcd.println("Enter password: ");
      lcd.setCursor(0,1); 
    }
  }  
}

void counterbeep(){
    lcd.clear();
    digitalWrite(buzzer, HIGH);    
    delay(200);
//It counts down to close the door.
    for(int i = 5; i>=0; i--){
      digitalWrite(buzzer, HIGH);
      lcd.setCursor(0,0);
      lcd.print("Door to close");
      lcd.setCursor(0,1); 
      lcd.print("for");
      lcd.setCursor(4,1); 
      lcd.print(i); //Countdown
      lcd.setCursor(6,1); 
      lcd.print("seconds");
      delay(100);
      digitalWrite(buzzer,LOW); //When the door will close, the buzzer sounds
      delay(1000);
    }
    digitalWrite(buzzer, HIGH);
    delay(40);
    digitalWrite(buzzer,LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Close Door!");
    delay(440);
    lcd.clear();
}
