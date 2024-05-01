# Arduino_I2C_Home_Security
Date: June 2020

### Circuit and design

In this project, we’ve designed smart home security system based on Arduino microcontrollers interconnected via I2C to create a robust and scalable solution. 
Please find the key components listed below:

##### Master and Slave Arduinos:
Our system comprises two Arduinos: a master and multiple slave nodes.
The master Arduino acts as the central control unit, orchestrating communication and managing the entire network.
Each room has its dedicated slave Arduino, allowing for seamless expansion as you add more rooms.
##### Communication via I2C:
The master and slave Arduinos communicate using the I2C (Inter-Integrated Circuit) protocol.
I2C ensures efficient data exchange, enabling real-time monitoring and control across all connected nodes.
Sensors for Comprehensive Security:
##### Magnetic Contact Switches:
These switches are strategically placed on doors and windows.
When a door or window is opened (or breached), the magnetic contact switch detects the change and triggers an alert.
In the circuit, the Magnetic Contact switches are replaced with normal switch for simulation purposes.
##### Passive Infrared (PIR) Sensor:
The PIR sensor detects human presence by sensing body heat and motion.
If an intruder enters the room, the PIR sensor activates the alarm system.
##### Buzzer Alarm:
The buzzer emits a loud sound to alert occupants and deter intruders.
It can be customized with different tones or patterns based on the severity of the threat.
##### User-Friendly Interface:
Keypad and LCD Screen:
Users interact with the system through a keypad and an LCD screen.
The keypad allows users to input commands, set or change the alarm password, switch off the buzzer and toggle the system on/off.
The LCD screen provides visual feedback, displaying system status, alerts, and password prompts.
##### Scalability and Flexibility:
As your smart home expands, simply add more slave Arduinos—one for each room.
The modular design ensures that each room’s security is independently managed while remaining part of the larger network.
##### Password Protection:
The password system adds an extra layer of security.
Users can set a unique password to control system access.
Use the keypad and LCD screen to manage passwords and enable/disable the alarm.


![image](https://github.com/Mouneerm/Arduino_I2C_Home_Security/assets/45911394/1a00ec90-4ae6-4c89-81cd-99cf02077ee6)

### User Manual:

● The alarm can be switched on and off by entering the 4-digits user password using the
keypad.

● Every time a digit is entered successfully, a “*” will appear as shown in figure 1:

● When the four digits have been entered, press “*”. Depending on the initial state of the
alarm, the latter will be turned on or off.

● To change the password, “C” must be pressed after entering the 4 digits.

● If the alarm is on, the red led will light up and will light off if alarm is off.

● In case the password is wronged, 2 more attempts will be given to you as shown in fig 2.

● To clear the screen, press “#” from the keypad.

● If no more attempt is left, the alarm will be activated and so the buzzer for 30 minutes.
An additional attempt will then be given.

● In the case of an intruder detected, the password is required to deactivate the alarm. The
LCD screen will display some information as shown in fig3:

● Again, press “#” to clear the display.

● When the user switches on the alarm, the LCD screen will show some information in case
the user has forgotten to close windows or doors as shown in fig4.


![image](https://github.com/Mouneerm/Arduino_I2C_Home_Security/assets/45911394/c212882a-e8d8-49bf-ab5e-8adae75d54b8)


