// Code written by Mahomed Mouneer
// Date: May 2020
// Arduino Security system
// Code for slave arduino
// Communication: I2C
// Refer the read me for more information

#include <Wire.h>
const int led_buzzer = 11;
const int pir1 = 5;
const int pir2 = 6;
const int s[3] = {2, 3, 4};
int init_s[3];
int alarm = 1;  // stays 1 in case powercut
int message;
void setup() {
    Serial.begin(9600);
    Wire.begin(1);

    Wire.onReceive(i2c_signal);
    Wire.onRequest(sendmessage);
    int message;
    pinMode(led_buzzer, OUTPUT);
    pinMode(s[0], INPUT);
    pinMode(s[1], INPUT);
    pinMode(s[2], INPUT);
    pinMode(pir1, INPUT);
    pinMode(pir2, INPUT);
}
void loop() {
    while (alarm == 0) {
        message = 0;
        for (int i = 0; i < 3; i++) {
            init_s[i] = s[i];
        }
        delay(10);
    }
    message = 0;
    // Serial.println(alarm);
    while (alarm == 1) {
        if (digitalRead(pir1) == HIGH || digitalRead(pir2) == HIGH) {
            message = 4;
            for (int i = 0; i < 10; i++) {  // 10seconds
                tone(led_buzzer, 1000);     // Send 1KHz sound signal
                delay(1000);
                if (alarm == 0) {
                    noTone(led_buzzer);
                    break;
                }
            }
        } else if (digitalRead(s[0]) == 0) {
            message = 1;
            delay(500);
        } else if (digitalRead(s[1]) == 0) {
            message = 2;
            delay(500);
        } else if (digitalRead(s[2]) == 0) {
            message = 3;  // sends 3
            delay(500);
        } else if (init_s[0] != s[0] || init_s[1] != s[1] ||
                   init_s[2] != s[2]) {
            message = 4;
            for (int i = 0; i < 10; i++) {  // seconds
                tone(led_buzzer, 1000);     // Send 1KHz sound signal
                delay(1000);
                if (alarm == 0) {
                    noTone(led_buzzer);
                    break;
                }
            }
        } else {
            noTone(led_buzzer);
            // digitalWrite(13,LOW);
        }
    }
}
void i2c_signal(int numberofbytes) {
    // while(Wire.available()){
    // Serial.println(numberofbytes);
    alarm = Wire.read();
    //}
}
void sendmessage() {
    Wire.write(message);  // sends x
}
