// Code written by Mahomed Mouneer
// Date: May 2020
// Arduino Security system
// Code for master arduino
// Communication: I2C
// The system can be scaled for additional slaves arduino(one for each room)
// Refer the readme for more information


#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
//// Variables relaled to password
String password = String("1234");
String new_password;
String confirm_password;
//// Variables relaled to keypad
String userEntered;
char invalidVal = 'I';
String dots = String();  // Insert "*" when typing password
const byte ROWS = 4;
const byte COLS = 4;
char key;
char keys[ROWS][COLS] = {{'1', '2', '3', 'A'},
                         {'4', '5', '6', 'B'},
                         {'7', '8', '9', 'C'},
                         {'*', '0', '#', 'D'}};

// Variables related to alarms
int alarm_set = 1;  // If 1, security is on
int attempts = 3;
int alarm = 0;
const int alarm_led = 13;
const int led_buzzer = 9;

// functions
unsigned int getKeyPad();
void passwordCheck();

// number of rooms or slaves arduinos
int num_rooms = 1;
void setup() {
    Serial.begin(9600);
    Wire.begin();

    lcd.begin(16, 2);  // Initializes the interface to the LCD screen, and
                       // specifies the dimensions
                       //(width and height) of the display
                       /// initLCD();
    userEntered = String();
    pinMode(alarm_led, OUTPUT);
}

void loop() {
    lcd.setCursor(0, 0);
    digitalWrite(alarm_led, alarm_set);
    lcd.print("Enter Password");
    key = getKeyPad();

    while (key == 'I' && alarm == 0) {
        for (int i = 1; i <= num_rooms; i++) {
            Wire.requestFrom(i, 1);

            switch (Wire.read()) {
                case 1:
                    lcd.clear();
                    alarm = 1;
                    lcd.setCursor(0, 0);
                    lcd.print("Door 1 room");
                    lcd.print(i);
                    lcd.setCursor(0, 1);
                    lcd.print("opened");
                    delay(1000);
                    // lcd.clear();
                    break;
                case 2:
                    lcd.clear();
                    alarm = 1;
                    lcd.setCursor(0, 0);
                    lcd.print("Win 1 room");
                    lcd.print(i);
                    lcd.setCursor(0, 1);
                    lcd.print("opened");
                    delay(1000);
                    // lcd.clear();
                    break;
                case 3:
                    lcd.clear();
                    alarm = 1;

                    lcd.setCursor(0, 0);
                    lcd.print("Win 2 room");
                    lcd.print(i);
                    lcd.setCursor(0, 1);
                    lcd.print("opened");
                    break;
                    delay(1000);
                    // lcd.clear();

                case 4:
                    alarm = 1;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Intruder at");
                    lcd.setCursor(0, 1);
                    lcd.print("room ");
                    lcd.print(i);
                    delay(1000);
                    // lcd.clear();
                    break;
                default:
                    alarm = 0;
                    lcd.setCursor(0, 0);
                    lcd.print("Enter Password: ");
                    key = getKeyPad();
                    delay(20);
            }
        }
    }

    while (alarm == 1 && key == 'I') {
        key = getKeyPad();
        delay(20);
    }
    if (key == 35) {  // 35 is the ascii code for "#"
        lcd.clear();
        userEntered = "";
        dots = "";
        delay(100);
    } else if (key == '*') {
        passwordCheck();
        userEntered = "";
        dots = "";
    } else if (key == 'C') {
        if (userEntered == password) {
            dots = "";
            lcd.clear();
            lcd.print("Access Allowed");
            delay(250);
            lcd.setCursor(1, 0);
            attempts = 3;
            /////new passwrd
            lcd.print("New Password:");

            int i = 0;
            dots = "";
            while (i < 4) {
                key = getKeyPad();
                if (key == 'I') {
                    delay(20);
                } else if (key == 35) {
                    dots = "";
                    new_password = "";
                } else if (key == 'A' || key == 'B' || key == 'C' ||
                           key == 'D' || key == '*') {
                    lcd.setCursor(1, 0);
                    lcd.print("Invalid Password");
                    new_password = "";
                    delay(500);
                    dots = "";
                    lcd.clear();
                    break;
                } else {
                    new_password.concat(key);
                    delay(20);
                    i = i + 1;
                    dots += '*';
                    lcd.setCursor(0, 1);
                    lcd.print(dots);
                }
            }
            delay(100);
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("Confirm Password:");

            ////////////confrim passwrd
            int j = 0;
            dots = "";
            while (j < 4 && i == 4) {
                key = getKeyPad();
                if (key == 'I') {
                    delay(20);
                } else if (key == 35 && i == 4) {
                    dots = "";
                    confirm_password = "";
                } else if (key == 'A' || key == 'B' || key == 'C' ||
                           key == 'D' || key == '*' && i == 3) {
                    lcd.setCursor(0, 1);
                    lcd.print("Invalid Password");
                    delay(500);
                    dots = "";
                    lcd.clear();
                    break;
                } else if (i == 4) {
                    confirm_password.concat(key);
                    delay(20);
                    j = j + 1;
                    dots += '*';
                    lcd.setCursor(0, 1);
                    lcd.print(dots);
                }
            }
            if (new_password == confirm_password && i == 4 && j == 4) {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("password changed");
                dots = "";
                password = new_password;
            } else {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Try again");
                new_password = "";
                confirm_password = "";
            }
            delay(500);
            lcd.clear();
        } else {
            lcd.clear();
            lcd.print("Access Denied");
            lcd.setCursor(0, 1);
            lcd.print("Attempts left ");
            attempts = attempts - 1;
            lcd.print(attempts);
            userEntered = "";
            dots = "";
            if (attempts == 0) {
                alarm_set = 1;
                // sound alarm
                tone(led_buzzer, 1000);  // Send 1KHz sound signal
                delay(1 * 60 * 1000);    // sounds alarm for 1min
                noTone(led_buzzer);
                attempts = 1;

                delay(500);
                lcd.clear();
                // password bad
                delay(20);
            }
        }
    } else {
        userEntered.concat(key);
        dots += '*';
        lcd.setCursor(0, 1);
        lcd.print(dots);

        delay(100);
    }
}
void initLCD() {
    lcd.clear();
    lcd.print("No intruder");
}
unsigned int getKeyPad() {
    int keyVal1 = analogRead(A1);
    char Button = PossibleButt(keyVal1);
    return Button;
}
char PossibleButt(int val) {
    switch (val) {
        case 930:
            return keys[0][0];
        case 908:
            return keys[0][1];
        case 886:
            return keys[0][2];
        case 866:
            return keys[0][3];
        case 852:
            return keys[1][0];
        case 834:
            return keys[1][1];
        case 816:
            return keys[1][2];
        case 799:
            return keys[1][3];
        case 787:
            return keys[2][0];
        case 771:
            return keys[2][1];
        case 756:
            return keys[2][2];
        case 741:
            return keys[2][3];
        case 731:
            return keys[3][0];
        case 717:
            return keys[3][1];
        case 704:
            return keys[3][2];
        case 691:
            return keys[3][3];
        default:
            return (invalidVal);
    }
}
void passwordCheck() {
    if (userEntered == password) {
        dots = "";
        lcd.clear();
        lcd.print("Access Allowed");
        // delay(500);
        lcd.setCursor(0, 1);
        attempts = 3;

        if (alarm_set == 1) {
            alarm_set = 0;
            alarm = 0;
            lcd.print("Alarm Off");

            /////////////////////////////////////
            for (int i = 1; i <= num_rooms; i++) {
                Wire.beginTransmission(1);  // transmit to device #1
                Wire.write(alarm_set);

                Wire.endTransmission();
                // Serial.println(alarm);
                delay(500);
            }
        } else if (alarm_set == 0) {
            alarm_set = 1;
            alarm = 0;
            lcd.print("Alarm On");

            for (int i = 1; i <= num_rooms; i++) {
                Wire.beginTransmission(i);  // for i=1 transmit to device #1
                Wire.write(alarm_set);
                Wire.endTransmission();
                // Serial.println(alarm);
                delay(500);
            }
        }
        lcd.clear();
    } else {
        lcd.clear();
        lcd.print("Access Denied");
        lcd.setCursor(0, 1);
        lcd.print("Attempts left ");
        attempts = attempts - 1;
        lcd.print(attempts);
        userEntered = "";

        dots = "";
        if (attempts == 0) {
            alarm_set = 1;
            // sound alarm
            tone(led_buzzer, 1000);  // Send 1KHz sound signal
            delay(1 * 60 * 1000);    // sounds alarm for 1min
            noTone(led_buzzer);
            attempts = 1;
        }
        delay(500);
        lcd.clear();
        // password bad
    }
}