#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h> //for keypad
#include <EEPROM.h>
#define IRQ   (2)
#define RESET (3)  
const int relay = 38;

DS3231  rtc(SDA, SCL); //real time clock connect
#define DS3231_I2C_ADDRESS 104
byte seconds, minutes, hours, day, date, month, year;

LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; 
byte colPins[COLS] = {30, 32, 34, 36}; 

Keypad  buttonKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int   add;
int    AA[20];
int    BB[20];
int sum;
int bell1H;
int bell1M;
//int BB;
//int AA;
int q = 0;
int p = 0;
int A = 0;
char  data[16];
char weekDay[4];
byte tMSB, tLSB;
float my_temp;
char my_array[100]; 
char customKey;
int hourupg;
int minupg;
int yearupg;
int monthupg;
int dayupg;
int menu = 0;
int list = 0;
int secupg;
bool blinking = true;

Time  t;

void setup()
{
  Wire.begin();  //begin I2C
  lcd.begin();  // initialize the lcd 
  lcd.backlight();
  rtc.begin();  //begin real time clock
  Serial.begin(9600);
  t = rtc.getTime();
  pinMode(relay, OUTPUT);
  digitalWrite(relay,HIGH);

  
}
void loop()
{
  int  Credit,Num;
  //menu = 0;
  customKey =  buttonKeypad.getKey();  //read form keypad
 
 if (customKey == 'B'){
    digitalWrite(relay,LOW);
      delay(10000);
      digitalWrite(relay,HIGH);
    }
 if (customKey == 'D'){
    
    menu=menu+1;
    if(menu==2){p=1;}
    if(menu==1){p=0;}
    }
  if (customKey == 'A'){
    list=list+1;
    if(list==2){p=1;}
    if(list==1){p=0;}
    }
    
  if (menu==0)
  {
      lcd.setCursor(3,0);
      lcd.print(rtc.getDateStr());   // Print date to LCD
      lcd.setCursor(0,1);
      lcd.print(rtc.getTimeStr());   // Print time to LCD
      lcd.setCursor(11,1);
      lcd.print(rtc.getTemp());     // Print temp to LCD
      lcd.setCursor(13,1);
      lcd.print(" C ");
  }
  
 if (menu==1)
    {
    DisplaySetHour();    // set hour
    }
  if (menu==2)
    {
    DisplaySetMinute();  // set minute
    }
  if (menu==3)
    {
    DisplaySetDay();      // set day
    }
  if (menu==4)
    {
    DisplaySetMonth();   // set Month
    }
  if (menu==5)
    { 
    DisplaySetYear();    // set year   

    if(minupg <= 0 && hourupg <= 0 && dayupg <= 0 && monthupg <= 0 && yearupg <= 0)
    { 
      menu = 0;         
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   ERROR   ");
    }    
  }
  if (menu==6)
  {
    StoreAgg();      //setup time date to DS3231
    delay(500);
    menu=0;    // return to main menu
  }
  delay(100);
  
  if (list==1)
  {add=0;
   AA[1]= DisplaySetAlarm1Hour();
   EEPROM.update(add,AA[1]);
  add=add+1;
  }

  if(list==2)
  {
   BB[1]= DisplaySetAlarm1Minute();
   EEPROM.update(add,BB[1]);
    add=add+1;
  }
      
  if (list==3)
  {
  AA[2]= DisplaySetAlarm2Hour();
   EEPROM.update(add,AA[2]);
  add=add+1;
  }

  if(list==4)
  {
   BB[2]= DisplaySetAlarm2Minute();
  EEPROM.update(add,BB[2]);
    add=add+1;
  }
  
  if (list==5)
 {
 AA[3]= DisplaySetAlarm3Hour();
   EEPROM.update(add,AA[3]);
  add=add+1;
  }

  if(list==6)
  {
    BB[3]= DisplaySetAlarm3Minute();
  EEPROM.update(add,BB[3]);
    add=add+1;
  }
  
   if (list==7)
  {
  AA[4]= DisplaySetAlarm4Hour();
  EEPROM.update(add,AA[4]);
  add=add+1;
  }

  if(list==8)
  {
   BB[4]= DisplaySetAlarm4Minute();
  EEPROM.update(add,BB[4]);
    add=add+1;
  }
   
   if (list==9)
  {
  AA[5]= DisplaySetAlarm5Hour();
   EEPROM.update(add,AA[5]);
  add=add+1;
  }

  if(list==10)
  {
    BB[5]= DisplaySetAlarm5Minute();
 EEPROM.update(add,BB[5]);
    add=add+1;
  }

 if (list==11)
  {
   AA[6]= DisplaySetAlarm6Hour();
   EEPROM.update(add,AA[6]);
  add=add+1;
  }

  if(list==12)
  {
   BB[6]= DisplaySetAlarm6Minute();
    EEPROM.update(add,BB[6]);
    add=add+1;
  }
  
   if (list==13)
  {
 AA[7]= DisplaySetAlarm7Hour();
  EEPROM.update(add,AA[7]);
  add=add+1;
  }

  if(list==14)
  {
    BB[7]= DisplaySetAlarm7Minute();
  EEPROM.update(add,BB[7]);
    add=add+1;
  }
  
 if (list==15)
  {
  AA[8]= DisplaySetAlarm8Hour();
   EEPROM.update(add,AA[8]);
  add=add+1;
  }

  if(list==16)
  {
    BB[8]= DisplaySetAlarm8Minute();
   EEPROM.update(add,BB[8]);
    add=add+1;
  }
  
   if (list==17)
  {
  AA[9]= DisplaySetAlarm9Hour();
   EEPROM.update(add,AA[9]);
  add=add+1;
  }

  if(list==18)
  {
    BB[9]= DisplaySetAlarm9Minute();
  EEPROM.update(add,BB[9]);
    add=add+1;
  }
  
   if (list==19)
  { 
  AA[10]= DisplaySetAlarm10Hour();
   EEPROM.update(add,AA[10]);
  add=add+1;
  }

  if(list==20)
  {
    BB[10]= DisplaySetAlarm10Minute();
    EEPROM.update(add,BB[10]);
    add=add+1;
  }

   if (list==21)
  { 
  AA[11]= DisplaySetAlarm11Hour();
   EEPROM.update(add,AA[11]);
  add=add+1;
  }

  if(list==22)
  {
    BB[11]= DisplaySetAlarm11Minute();
    EEPROM.update(add,BB[11]);
    add=add+1;
  }

   if (list==23)
  { 
  AA[12]= DisplaySetAlarm12Hour();
   EEPROM.update(add,AA[12]);
  add=add+1;
  }

  if(list==24)
  {
    BB[12]= DisplaySetAlarm12Minute();
    EEPROM.update(add,BB[12]);
    add=add+1;
  }

   if (list==25)
  { 
  AA[13]= DisplaySetAlarm13Hour();
   EEPROM.update(add,AA[13]);
  add=add+1;
  }

  if(list==26)
  {
    BB[13]= DisplaySetAlarm13Minute();
    EEPROM.update(add,BB[13]);
    add=add+1;
  }

   if (list==27)
  { 
  AA[14]= DisplaySetAlarm14Hour();
   EEPROM.update(add,AA[14]);
  add=add+1;
  }

  if(list==28)
  {
    BB[14]= DisplaySetAlarm14Minute();
    EEPROM.update(add,BB[14]);
    add=add+1;
  }

  if (list==29)
  { 
  AA[15]= DisplaySetAlarm15Hour();
   EEPROM.update(add,AA[15]);
  add=add+1;
  }

  if(list==30)
  {
    BB[15]= DisplaySetAlarm15Minute();
    EEPROM.update(add,BB[15]);
    add=add+1;
  }

  if (list==31)
  { 
  AA[16]= DisplaySetAlarm16Hour();
   EEPROM.update(add,AA[16]);
  add=add+1;
  }

  if(list==32)
  {
    BB[16]= DisplaySetAlarm16Minute();
    EEPROM.update(add,BB[16]);
    add=add+1;
  }

  if (list==33)
  { 
  AA[17]= DisplaySetAlarm17Hour();
   EEPROM.update(add,AA[17]);
  add=add+1;
  }

  if(list==34)
  {
    BB[17]= DisplaySetAlarm17Minute();
    EEPROM.update(add,BB[17]);
    add=add+1;
  }

  if (list==35)
  { 
  AA[18]= DisplaySetAlarm18Hour();
   EEPROM.update(add,AA[18]);
  add=add+1;
  }

  if(list==36)
  {
    BB[18]= DisplaySetAlarm18Minute();
    EEPROM.update(add,BB[18]);
    add=add+1;
  }

  if (list==37)
  { 
  AA[19]= DisplaySetAlarm19Hour();
   EEPROM.update(add,AA[19]);
  add=add+1;
  }

  if(list==38)
  {
    BB[19]= DisplaySetAlarm19Minute();
    EEPROM.update(add,BB[19]);
    add=add+1;
  }

  if (list==39)
  { 
  AA[20]= DisplaySetAlarm20Hour();
   EEPROM.update(add,AA[20]);
  add=add+1;
  }

  if(list==40)
  {
    BB[20]= DisplaySetAlarm20Minute();
    EEPROM.update(add,BB[20]);
    add=add+1;
  }
  if(list==41){
    list=0;
    }
  
     delay(100); 
  
   t = rtc.getTime();

   for(int k=0;k<40;k++){
    if(EEPROM.read(k)==t.hour && EEPROM.read(k+1)==t.min && t.sec==1){
      digitalWrite(relay,LOW);
      delay(10000);
      digitalWrite(relay,HIGH);
     }
    k = k+1;
    }
}

int DisplaySetAlarm1Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 1 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm1Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 1 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm2Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 2 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm2Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 2 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm3Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 3 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm3Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 3 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm4Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 4 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm4Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 4 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm5Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 5 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm5Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 5 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}
int DisplaySetAlarm6Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 6 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm6Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 6 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm7Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 7 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm7Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 7 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm8Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 8 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm8Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 8 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm9Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 9 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm9Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 9 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm10Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 10 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm10Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 10 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm11Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 11 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm11Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 11 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm12Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 12 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm12Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 12 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm13Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 13 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm13Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 13 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm14Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 14 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm14Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 14 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm15Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 15 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm15Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 15 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}
int DisplaySetAlarm16Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 16 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm16Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 16 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm17Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 17 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm17Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 17 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm18Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 18 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm18Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 18 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm19Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 19 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm19Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 9 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

int DisplaySetAlarm20Hour()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 20 Hour:",0,1);
  int bell1H= GetNumB(2,12,2);
 return ( bell1H);
  
  delay(100);
}

int DisplaySetAlarm20Minute()
{
  int Credit,Num;
  p = 0;
  lcd_show(0,0,"Alarm 20 Minute:",0,1);
  bell1M = GetNumB(2,12,2);
   return (bell1M);                                 
  delay(100);
}

void DisplaySetHour()
{
  int  Credit,Num;
// time setting
  p = 0;
  lcd_show(0,0,"Set Hour:",0,1);  
  hourupg = GetNum(2,12,2);   
  if(hourupg < 0 or hourupg > 23){menu = 1;}
  Serial.println(hourupg);
  delay(100);
}

void DisplaySetMinute()
{
// Setting the minutes
  p = 0;
  lcd_show(0,0,"Set Minute:",0,1);
  minupg = GetNum(2,12,2);
  if(minupg < 0 or minupg > 59) {menu = 2;}
  Serial.println(minupg);
  delay(100);
}
  
void DisplaySetYear()
{
  // setting the year
  p = 0;
  lcd_show(0,0,"Set Year:",0,1);
  yearupg = GetNum(4,12,2);
  if(yearupg < 0 or yearupg > 99){menu = 5;}
  Serial.println(yearupg);
  delay(100);
}

void DisplaySetMonth()
{
  // Setting the month
  p = 0;
  lcd_show(0,0,"Set Month:",0,1);
  monthupg = GetNum(2,12,2);
  if(monthupg < 0 or monthupg > 12) {menu = 4 ;}
  Serial.println(monthupg);
  delay(100);
}

void DisplaySetDay()
{
  // Setting the day
  p = 0;
  lcd_show(0,0,"Set Day:",0,1);
  dayupg = GetNum(2,12,2);
  if(dayupg < 0 or dayupg > 31) {
    menu = 3 ; 
  };
  Serial.println(dayupg);
  delay(100);
}

// set time to DS3231 
void StoreAgg()
{
  // Variable saving
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SAVING IN");
  lcd.setCursor(8,1);
  lcd.print("PROGRESS");
  seconds = 0 ; 
  day     = 0 ;
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minupg));
  Wire.write(decToBcd(hourupg));
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(dayupg));
  Wire.write(decToBcd(monthupg));
  Wire.write(decToBcd(yearupg));
  Wire.endTransmission();
  delay(1000);
  lcd.clear();
  delay(200);

}
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}

void NumToChar(unsigned long Num, char  *Buffer,unsigned char Digit)
{char i;
   for(i=(Digit-1);i>= 0;i--)
    { Buffer[i] =  (Num % 10) + '0';
      Num = Num / 10;
    }  
   for(i=0;i<Digit;i++)
    { if(Buffer[i] == '0'){Buffer[i] =  ' ';}else{i =100;}
                         
    }   
}

char BufNum[8];
void  SlideNum(void)
{
  BufNum[6]  = BufNum[5];
  BufNum[5]  = BufNum[4];
  BufNum[4]  = BufNum[3];
  BufNum[3]  = BufNum[2];
  BufNum[2]  = BufNum[1];
  BufNum[1]  = BufNum[0];
}

unsigned long GetNum(int Count,int X,int Y)
{ char Key,i,N;
  int Sum; 
  lcd.blink();
  lcd.setCursor(X+(Count-2),Y-1); 
  N = 0;
  for(i=0;i<Count;i++){BufNum[i] = ' ';}
  i = 0;
  Key =  buttonKeypad.getKey();
  while(p != 1)
  { 
         
    Key = NO_KEY;
    while(Key == NO_KEY){Key =  buttonKeypad.getKey();}
   if(Key == 'D'){menu = menu+1; p = 1; }   
            
   if((N < Count)&&(Key >= '0')&&(Key <= '9'))
   { SlideNum();
     BufNum[0] = Key;
     N++;
   }
   lcd.setCursor(X-1,Y-1);
   for(i=0;i<Count;i++){lcd.print(BufNum[Count-(i+1)]);}
   lcd.setCursor(X+(Count-2),Y-1);  
  }
Sum = 0;
if (Count != 4)
{
for(i=0;i<Count;i++)
 {
   if(BufNum[Count-(i+1)]==0x20){BufNum[Count-(i+1)] = '0';}
   Sum = (Sum*10) + (BufNum[Count-(i+1)]-'0');
 }
}
 if (Count == 4)
 {
  Count = 2;
 
 for(i=0;i<Count;i++)
 {
   if(BufNum[Count-(i+1)]==0x20){BufNum[Count-(i+1)] = '0';}
   Sum = (Sum*10) + (BufNum[Count-(i+1)]-'0');
 }
 }
 //Serial.println(hours);
lcd.noCursor();
lcd.noBlink();

return(Sum); 
 
}



unsigned long GetNumB(int Count,int X,int Y)
{ char Key,i,N;
  int Sum; 
  lcd.blink();
  lcd.setCursor(X+(Count-2),Y-1); 
  N = 0;
  for(i=0;i<Count;i++){BufNum[i] = ' ';}
  i = 0;
  Key =  buttonKeypad.getKey();
  while(p != 1)
  { 
         
    Key = NO_KEY;
    while(Key == NO_KEY){Key =  buttonKeypad.getKey();}
    
   if(Key == 'A'){list = list+1; p = 1; }  
     if(Key == 'C'){list =0; p = 1; }       
   if((N < Count)&&(Key >= '0')&&(Key <= '9'))
   { SlideNum();
     BufNum[0] = Key;
     N++;
   }
   lcd.setCursor(X-1,Y-1);
   for(i=0;i<Count;i++){lcd.print(BufNum[Count-(i+1)]);}
   lcd.setCursor(X+(Count-2),Y-1);  
  }
Sum = 0;
if (Count != 4)
{
for(i=0;i<Count;i++)
 {
   if(BufNum[Count-(i+1)]==0x20){BufNum[Count-(i+1)] = '0';}
   Sum = (Sum*10) + (BufNum[Count-(i+1)]-'0');
 }
}
 if (Count == 4)
 {
  Count = 2;
 
 for(i=0;i<Count;i++)
 {
   if(BufNum[Count-(i+1)]==0x20){BufNum[Count-(i+1)] = '0';}
   Sum = (Sum*10) + (BufNum[Count-(i+1)]-'0');
 }
 }
 //Serial.println(hours);
lcd.noCursor();
lcd.noBlink();

return(Sum); 
 
}

void lcd_show(int b,int c,char* txt0,int d,int e)
{
  lcd.clear();
  lcd.setCursor(b,c);
  lcd.print(txt0);
  lcd.setCursor(d,e);
  
}
