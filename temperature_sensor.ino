#include <LiquidCrystal.h>      //includes the library for the LCD
const int temp_sensor = A0;     //initialize the temp sensor through pin A0
const int button = 7;           //initialize the button through pin 7
const int led_hot = 8;          //initialize the red LED through pin 8
const int led_cold = 9;         //initialize the blue LED through pin 9
const int led_refresh = 6;      //initialize the white LED through pin 6
const int led_roomtemp = 10;    //initialize the green LED through pin 10

float temp = 0;       //create the temperature variable
float avg_temp = 0;   //create the variable for average temperature
int count = 0;        //create the count variable
bool toggle = 0;      //create the button toggle variable
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    //initialize the LCD through multiple pins

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);   //start the LCD to display 16x2
  Serial.begin(9600);   //put serial out through 9600
  pinMode(button, INPUT);   //initialize the button pin to be an input
  pinMode(led_hot, OUTPUT);   //initialize the red LED pin to be an output
  pinMode(led_cold, OUTPUT);    //initialize the blue LED pin to be an output
  pinMode(led_roomtemp, OUTPUT);    //initialized the white LED pin to be an output
  pinMode(led_refresh, OUTPUT);   //initialized the green LED pin to be an output
}

void loop() {
  float input_v = analogRead(temp_sensor);   //read the temperature sensor and assign the reading to variable "input v"
  float volts = input_v / 1023 * 5 - 0.5;    //take that input, and convert it into an actual voltage reading by reversing the arduino input and offset of the sensor
  float C = volts *100;    //multiply by 1000 and divide by 10 (multiply by 100) because the sensor reads 10mV per degree Celsius
  
  bool button_state = digitalRead(button);   //read the button state and assign it to the "button state" variable
  delay(10);    //delay the arduino by 10ms
  temp += C;    //add to the temp variable, the current reading temp in Celsius
  count += 1;   //add one to the count

  if (count == 100){
    float avg_temp = (temp / 100);   //averages the last 100 temperature readings (essentially readings over 1 second)
    Serial.println((String) avg_temp + "°C");   //Serial prints the Celsius temperature
    Serial.println((String)(avg_temp * 1.8 + 32) + "°F");   //Serial prints the Fahrenheit temperature
    Serial.println("~~~~~~~~~~~~~");    //Serial prints a spacer line
    lcd.clear();    //clears the LCD
    lcd.setCursor(0,1);   //Sets the LCD to start writing at the beginning

    if (button_state == 1){
    toggle = !toggle;   //If button is clicked, toggle the "toggle" variable to the opposite state
    }

    if (toggle == 1){
      lcd.print(avg_temp * 1.8 + 32, 1);  //If button toggle is True, outputs to the LCD the Fahrenheit temperature
      lcd.print(char(223));   //Outputs the degrees symbol
      lcd.print("F");   //Outputs "F" for Fahrenheit
    }
    else{
      lcd.print(avg_temp);    //If button toggle is False, outputs to the LCD the Celsius temperature
      lcd.print(char(223));   //Outputs the degrees symbol
      lcd.print("C");   //Outputs "C" for Celsius
    }
    
    if (avg_temp > 37){     //If the average temperature reading is above 37, turns on the red LED
      digitalWrite(led_hot, HIGH);
    }
    else{     //Otherwise, turns off the "hot" LED
      digitalWrite(led_hot, LOW);
    }
    if (avg_temp < -17){    //If the average temperature reading is below -17, turns on the blue LED
      digitalWrite(led_cold, HIGH);
    }
    else{     //Otherwise, turns off the "cold" LED
      digitalWrite(led_cold, LOW);
    }
    if (count == 100){    //If count = 100, always true due to previous if, turns on the white LED for .1 seconds
      digitalWrite(led_refresh, HIGH);
      delay(count);
      digitalWrite(led_refresh, LOW);
    }
    if (20 < avg_temp && avg_temp < 30){    //If the average temperature reading is between 20 and 30, turns on the green LED
      digitalWrite(led_roomtemp, HIGH);
    }
    if(avg_temp > 30){    //If average temperature more than 30, turns off green LED
      digitalWrite(led_roomtemp, LOW);
    }
    if(avg_temp < 20){    //If average temperature less than 20, turns off green LED
      digitalWrite(led_roomtemp, LOW);
    }
    avg_temp = 0;   //Resets "avg_temp" variable to  0
    temp = 0;   //Resets "temp" variable to 0
    count = 0;    //Resets "count" variable to 0
  }
}

