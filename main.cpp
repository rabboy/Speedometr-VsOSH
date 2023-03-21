#include<LiquidCrystal.h>
#include<Thread.h>
LiquidCrystal lcd(4,6, 10, 11, 12, 13);
#define SENSOR A0
#define LED 8
#define LASER A1
int f = 0;
int l = 0;
int v = 0;
int leas = 0;
int sec = 0;
int aks;
long seco = 0;
int c;
int tim = 0;
int d;
int a;

#define BTN 2
#define THRESHOLD 50
Thread prthr = Thread();
Thread simthr = Thread();

void setup(){
    prthr.onRun(prog);
    prthr.setInterval(1);
    simthr.onRun(conout);
    simthr.setInterval(1);
    Serial begin(9600);
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
    pinMode(Sensor, input);
    pinMode(LED, OUTPUT);
    pinMode(BTN, INPUT);
    digitalWrite(LED,HIGH);

    lcd.begin(16,2)
}
int ne;
float k = 0;
long white = 0;
int s = 0;
bool done = false;
void loop(){
    if(prthr.shouldRun()) prthr.run();
    if(simthr.shouldRun()) simthr.run();
}

void prog(){
    a = digitalRead(BTN);
    if(a == LOW){
        sec = 0;
        white = 0;
    }
    c = analogRead(SENSOR);
    d = analogRead(LASER);
    if(c < THRESHOLD) {
        if (!done){
            white++;
            k++;
            delay(5);
        }
        done = true;
    }
    else done = false;
}

void conout(){
    s++;
    if (aks != 0){
        sec++;
    }
    seco = sec/1000;
    if(s>999){
        lcd.clear();
        v = k;
        lcd.print(v);
        lcd.print(" rpm");
        lcd.setCursor(0,1);
        lcd.print(white);
        lcd.print(" r ");
        lcd.print(seco);
        lcd.print(" sec");
        
        if(v==0) aks - 0;
        else aks = 1;
        Serial.println(d);
        k = 0;
        v = 0;
        s = 0;
    }
}
