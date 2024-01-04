#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define SIM800_TX_PIN 2
#define SIM800_RX_PIN 3
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);


const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
int in1 = A0;
int in2 = A1;
int out1 = A2;
int out2 = A3;
int out3 = A4;
int button = 6;
int a,b,c,d,e,f,g,h,i,j;
String gate = "";
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {

serialSIM800.begin(9600);

serialSIM800.write("AT+CMGF=1\r\n");
delay(1000);
serialSIM800.write("AT+CMGS=\"01575088499\"\r\n");
delay(1000);
      
Serial.begin(9600);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(button, INPUT);
pinMode(out1, INPUT);
pinMode(out2, INPUT);
pinMode(out3, INPUT);
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("IC Tester");
lcd.setCursor(0, 1);
lcd.print("IUT Avijatrik");
Serial.println("IC Tester");
delay(1500);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Place IC and");
lcd.setCursor(0, 1);
lcd.print("press the button");
Serial.println("Place IC and press the button");
}
void loop() {
   if (digitalRead(button) == HIGH) {
  lcd.clear();
    delay(1000);
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
    a=digitalRead(out1);
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    b=digitalRead(out1);
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    c=digitalRead(out1);
    digitalWrite(in1, 1);
    digitalWrite(in2, 1);
    d=digitalRead(out1);
    if (a==0 && b==0 && c==0 && d==1)
    { gate="AND gate 7408" ;}
    if (a==0 && b==1 && c==1 && d==1)
    { gate="OR gate 7432" ;}
    if (a==1 && b==1 && c==1 && d==0)
    { gate="NAND gate 7400" ;}
    if (a==1 && b==0 && c==0 && d==0)
    { gate="XNOR gate 747266"; }
    if (a==0 && b==1 && c==1 && d==0)
    { gate="XOR gate 7486" ;}
    
    digitalWrite(in1, HIGH);
    e=digitalRead(out3);
    Serial.println(e);
    delay(1000);
    digitalWrite(in1, LOW);
    f=digitalRead(out3);
    Serial.println(f);
    delay(200);
    if (e==0 && f==1)
    { gate="NOT gate 7404"; }
     
     
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
    g=digitalRead(out2);
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    h=digitalRead(out2);
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    i=digitalRead(out2);
    digitalWrite(in1, 1);
    digitalWrite(in2, 1);
    j=digitalRead(out2);
    if (g==1 && h==0 && i==0 && j==0) 
    { gate="NOR gate 7402" ;} 
     
     
    if (a==0 && b==0 && c==0 && d==0 && e==0 && f==0 && g==0 && h==0 && i==0 && j==0)
    { gate="ic not present";}
    lcd.print(gate);
    Serial.print(gate);
    if (gate==""){
    lcd.print("Bad ic");}
    lcd.setCursor(0, 0);
    lcd.print(gate);
    delay(2000);
    lcd.clear();

    
    
    
    char buff[gate.length() + 1];
    gate.toCharArray(buff, gate.length() + 1);
    serialSIM800.write(buff);
    delay(1000);
    //Serial.println(buff);
    serialSIM800.write((char)26);
    delay(1000);
    Serial.println("SMS Sent!");
}}
     
    
