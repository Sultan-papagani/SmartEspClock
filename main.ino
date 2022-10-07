#include <LiquidCrystal_I2C.h>

#include <ESP8266WiFi.h>
#include <coredecls.h>                  
#include <time.h>         
#include <TZ.h>              
#include <sys/time.h>  

#include <DS3231.h>

#define MYTZ TZ_Europe_Istanbul

static time_t now;

const char* ssid = "internetinin adını yaz";
const char* password = "şifreni yaz";

// ip belirlememin sebepi benim modem bazen ip vermiyor
IPAddress local_IP(192, 168, 1, 52);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   
IPAddress secondaryDNS(8, 8, 4, 4); 

const char daysOfTheWeek[7][9] = {"Pzrts", "Sali", "Carsamba", "Persembe", "Cuma", "Cmrts", "Pazar"};
const char months[12][10]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

LiquidCrystal_I2C lcd(0x27, 16, 2); 

DS3231 myRTC;
bool h12;
bool hPM;
bool CenturyBit;

int wifiTryConnectCount = 0;
const int maxTryCountWifi = 6;

// now = time(nullptr); fonksiyonundan
// asıl zamanı almak için loop fonksiyonunda
// birkaç defa çağrılması gerekiyor
// o yüzden böyle garip bir yöntem kullanıyoruz
bool time_done = false;
int time_Try_Value = 0;
const int time_Max_Value = 10;

void setup() 
{
  InitLCD();
  ConnectToWifi();
  configTime(MYTZ, "pool.ntp.org");
}

void loop() {
  TemizleDon();
  TimeUpdate();

  lcd.print(myRTC.getHour(h12, hPM));
  lcd.print(":");
  lcd.print(myRTC.getMinute());
  lcd.print(":");
  lcd.print(myRTC.getSecond());

  if (h12 == true) 
  { 
    if (hPM == true) {
      lcd.print(" PM");
    } else {
      lcd.print(" AM");
    }
  }
  
  lcd.setCursor(0,1);
  lcd.print(months[myRTC.getMonth(CenturyBit) - 1]);
  
  delay(2000);
}

// evinizdeki cihazlar gizemli biçimde wifiye bağlanmayı reddederse esp den kaynaklı olduğunu bilin
// modemi aç kapa yapın düzelir
void ConnectToWifi()
{
  TemizleDon();
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    lcd.print("STA Config Fail");
  }
  else
  {
    lcd.print("STA Configured!");
  }
  delay(500);
  
  WiFi.begin(ssid, password);
  TemizleDon();
  lcd.print("Connecting...");
  
  while(WiFi.status() != WL_CONNECTED) 
  {  
    if (WiFi.status() == WL_CONNECT_FAILED || WiFi.status() == WL_NO_SSID_AVAIL)
    {
      TemizleDon();
      lcd.print("Connect Failed");
      lcd.setCursor(0,1);
      lcd.print("Trying Again...");
      delay(300);
      
      
      if (wifiTryConnectCount > maxTryCountWifi)
      {
        TemizleDon();
        lcd.print("Wifi FAILED");
        delay(1000);
        return;
      }
      
      wifiTryConnectCount++;
      ConnectToWifi();
    }
    
    delay(250);
  }
  TemizleDon();
  lcd.print("Connected!");
  delay(500);
}

void TimeUpdate()
{
  if (time_done) {return;}
  
  if (WiFi.status() == WL_CONNECTED)
  {
    if (time_Try_Value < time_Max_Value)
    {
      now = time(nullptr);
      time_Try_Value++;
    }
    else
    {
      myRTC.setEpoch((uint32_t)now);
      time_done = true;
    }
  }
  else
  {
    TemizleDon();
    lcd.print("Ag Yok!");
    lcd.setCursor(0,1);
    lcd.print("RTC kullaniliyor");
    time_done = true;
    delay(1000);
  }
  
}

// lcd için yardımcı komutlar

void InitLCD()
{
  lcd.init();
  lcd.backlight();
  TemizleDon();
}

void TemizleDon()
{
  lcd.clear();
  lcd.setCursor(0,0);
}
