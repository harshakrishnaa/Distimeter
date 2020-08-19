#include<Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
long gyrox, gyroy, gyroz;
float rotx, roty, rotz;
int echo=9;
int trig=8;
int ps=12,ss=13,a=0,b=0;
float duration,cm;
float d1,d2,d3;
float z1,z2,z3;
float y1,y2,y3;
void setup()
{
 Serial.begin(9600);
//Wire.begin();
 lcd.begin(16,2);
 pinMode(echo,INPUT);
 pinMode(trig,OUTPUT);
 pinMode(12,INPUT);
 pinMode(ss,INPUT);
 Wire.beginTransmission(0b1101000); 
 Wire.write(0x6B); 
 Wire.write(0b00000000); 
 Wire.endTransmission();
 while(a==0)
 {
  df1();
 }
 lcd.clear();
 while(b==0)
 {
  df2();
 }
 z3=z2-z1;
 double cosine=cos(z3);
 double cos=(cosine*57.296);
 d3=sqrt((d1*d1)+(d2*d2)-(2*d1*d2*cos));
 lcd.print("final distance");
 lcd.setCursor(4,1);
 lcd.print("D3=");
 lcd.print(d3);
 
 float s=(d1+d2+d3)/2;
 float a=sqrt(s*(s-d1)*(s-d2)*(s-d3));
 float h=(2*a)/d3;
 lcd.print("straightdstns");
 lcd.print(h);
}
void distance1()
{
 Wire.beginTransmission(0b1101000);
 Wire.write(0x43);
 Wire.endTransmission();
 Wire.requestFrom(0b1101000,6); 
 while(Wire.available() < 6);
 gyrox = Wire.read()<<8|Wire.read(); 
 gyroy = Wire.read()<<8|Wire.read(); 
 gyroz = Wire.read()<<8|Wire.read(); 
 rotx = gyrox /131.0;
 roty=gyroy / 131.0; 
 rotz = gyroz / 131.0;
 // Serial.println(rotz);
}
void distance2()
{
 digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = (duration/2) / 29.1;   
  Serial.print(cm);
  Serial.println("cm");
}
void loop()
{ 
}
void df1()
{
//distance1();
 distance2();
 lcd.clear();
 //lcd.setCursor(1,0);
 lcd.print("1st distance");
 lcd.setCursor(7,1);
 lcd.print("D1=");
 lcd.print(cm);
 delay(1000);
 lcd.clear();
 //lcd.setCursor(7,1); 
 if(digitalRead(12)==1)
 {
  d1=cm;
  lcd.print("D1=");
  lcd.print(d1);
  z1=rotz;
  a=1;
 }
}
void df2()
{
 //distance1();
 distance2();
 //lcd.clear();
 lcd.print("2nd distance");
 lcd.setCursor(8,1);
 lcd.print("D2=");
 lcd.print(cm);
 if(digitalRead(13)==1)
 {
  d2=cm;
  lcd.setCursor(8,1);
  lcd.print("D2=");
  lcd.print(d2);
  z2=rotz;
  b=1;
  delay(2000);
 }
}
