#include <Wire.h>


const byte SENSOR_ADDRESS = B1001000;

int analogPin = 15;

int pin_led = 13;
volatile int led_status = LOW;
volatile int change = LOW;

// TIA register vars
byte tia=0;

byte tia_gain2 = 0;
byte tia_gain1 = 0;
byte tia_gain0 = 0;
byte rload1 = 0;
byte rload0 = 0;

byte pin_tia_gain2 = 26;
byte pin_tia_gain1 = 25;
byte pin_tia_gain0 = 24;
byte pin_rload1 = 23;
byte pin_rload0 = 22;

// MODECN register vars
byte modecn=0;

byte fet_short = 0;
byte op_mode2 = 0;
byte op_mode1 = 0;
byte op_mode0 = 0;

byte pin_fet_short = 30;
byte pin_op_mode2 = 29;
byte pin_op_mode1 = 28;
byte pin_op_mode0 = 27;

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    pinMode(2, INPUT);

    // TIA
    pinMode(pin_tia_gain2, INPUT);
    pinMode(pin_tia_gain1, INPUT);
    pinMode(pin_tia_gain0, INPUT);
    pinMode(pin_rload1, INPUT);
    pinMode(pin_rload0, INPUT);

    // MODECN
    pinMode(pin_fet_short, INPUT);
    pinMode(pin_op_mode2, INPUT);
    pinMode(pin_op_mode1, INPUT);
    pinMode(pin_op_mode0, INPUT);

    // LED
    pinMode(pin_led, OUTPUT);

    // Interrupt
    attachInterrupt(0, int_change, RISING);
}

void loop()
{
    digitalWrite(pin_led, led_status); 

    if(change == 1){
        get_registers();
    }
    else {
        // TIA
        set_registers(0x10, tia);
        // MODECN
        set_registers(0x12, modecn);
    }

    Serial.print("Vout: \t");
    Serial.print(analogRead(analogPin));
    Serial.print("\n");

    delay(250);
}

void set_registers(byte address, byte value){
    Wire.beginTransmission(SENSOR_ADDRESS);
    Wire.write(address);
    Wire.write(value);
    Wire.endTransmission();
}


void int_change(){
    led_status = !led_status;
    change = 1;
}

void get_registers(){
    tia = get_tia_register();
    modecn = get_modecn_register();
    change = 0;
}

byte get_modecn_register(){
    // MODECN Mode Control Register (0x12)
    fet_short = digitalRead(pin_fet_short) << 7;
    op_mode2 = digitalRead(pin_op_mode2) << 2;
    op_mode1 = digitalRead(pin_op_mode1) << 1;
    op_mode0 = digitalRead(pin_op_mode0);
    modecn = op_mode0 + op_mode1 + op_mode2 + fet_short; 
    Serial.print("MODECN: \t");
    Serial.print(modecn, BIN);
    Serial.print("\n");
    return modecn;
}

byte get_tia_register(){
    // TIA Control Register (0x10)
    tia_gain2 = digitalRead(pin_tia_gain2) << 4;
    tia_gain1 = digitalRead(pin_tia_gain1) << 3;
    tia_gain0 = digitalRead(pin_tia_gain0) << 2;
    rload1 = digitalRead(pin_rload1) << 1;
    rload0 = digitalRead(pin_rload0);
    tia = rload0 + rload1 + tia_gain0 + tia_gain1 + tia_gain2; 
    Serial.print("TIA: \t");
    Serial.print(tia, BIN);
    Serial.print("\n");
    return tia;
}