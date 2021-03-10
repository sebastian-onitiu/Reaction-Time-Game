#include <stdlib.h>
#include <Arduino.h>

#define LEFT_LED    11 
#define RIGHT_LED   10
#define LEFT_BUTTON_PIN     2
#define RIGHT_BUTTON_PIN    3
#define CENTER_BUTTON_PIN   4

#define LEFT_BUTTON     digitalRead(LEFT_BUTTON_PIN)
#define RIGHT_BUTTON    digitalRead(RIGHT_BUTTON_PIN)
//#define CENTER_BUTTON   digitalRead(CENTER_BUTTON_PIN)
#define CENTER_BUTTON   (digitalRead(RIGHT_BUTTON_PIN) & digitalRead(LEFT_BUTTON_PIN))
#define RANDOM_NUMBER   analogRead(A1)

#define LOG true 

void setup() {
    pinMode(LEFT_LED,   OUTPUT);
    pinMode(RIGHT_LED,  OUTPUT);
    pinMode(LEFT_BUTTON_PIN,    INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN,   INPUT_PULLUP);
    pinMode(CENTER_BUTTON_PIN,  INPUT_PULLUP);
    if (LOG) Serial.begin(9600);
    srand(RANDOM_NUMBER);
}

void loop() {
    bool left_player = true;
    bool right_player = true;
    
    if (LOG) Serial.println("Waiting for center button to be pressed");
    while (CENTER_BUTTON);
    delay(1000);
    int wait = rand()%4000;
    if (LOG) { Serial.print("Waiting "); Serial.println(wait); }
    unsigned long time = millis();
    while(millis() - time < wait){
        if(!LEFT_BUTTON) left_player = false;
        if(!RIGHT_BUTTON) right_player = false;
    }
    digitalWrite(LEFT_LED, HIGH);
    digitalWrite(RIGHT_LED, HIGH);
    while (LEFT_BUTTON && RIGHT_BUTTON);
    if(LEFT_BUTTON && right_player) left_player = false;
    if(RIGHT_BUTTON && left_player)    right_player = false;
    
    if (LOG && left_player)  Serial.println("Left player wins!");
    if (LOG && right_player) Serial.println("Right player wins!");
    digitalWrite(LEFT_LED, left_player);
    digitalWrite(RIGHT_LED, right_player);

    delay(1000);
    digitalWrite(RIGHT_LED, LOW);
    digitalWrite(LEFT_LED, LOW);
    // if (LOG) print_buttons_state();
    // delay(200);
}

void print_buttons_state(){
    Serial.print(" Left button: "); Serial.print(LEFT_BUTTON);
    Serial.print(" Center button: "); Serial.print(CENTER_BUTTON);
    Serial.print(" Right button: "); Serial.println(RIGHT_BUTTON);
}
