# SmartEspClock
**Ev İçin Akıllı Saat Uygulaması**

## Nedir Bu ?
**Esp8266 kullanarak akıllı bir ev saati projesidir, LCD ekranı ile**
```
saat, 
hava durumu, 
ev sıcaklığı, 
ev nem oranı,
2 adet alarm,           | eklenmedi!
uzaktan röle kontrolü   | eklenmedi!
```
**gibi özellikleri olan bir esp projesidir**

## Nasıl Çalışıyor ?
**Esp8266, internete bağlanarak hava durumu, saat gibi verileri alır ve saati RTC ye kaydederek sürekli olarak interneti kullanma ihtiyacı duymaz, internete erişim olmadığında RTC üzerinden saati gösterebilir, Alarmları buzzer üzerinden çalıştırabilir. Hava Durumu her 30 dk da yenilenir**

## Daha doğrusu neden çalışmıyor ?
**yapmaya üşendim açıkçası**

## Gerekli Malzemeler
**Tüm parçalar internet üzerinden kolayca alınabilir, Lehime gerek yoktur**
```
Nodemcu Esp8266
2x16 LCD ekran
2x16 LCd ekran IC2 Arayüzü Modülü
DS3231 
ds18b20
Jumper Kablolar
BreadBoard
USB Kablo
Bilgisayar
```

## Gerekli Yazılımlar ve Kütüphaneler
```
LiquidCrystal_I2C (Built in By Arduino)
DS3231 by Andrew Wickert
Dallas Temperature by Miles Burton
```

## Bağlantı Şeması
Nodemcu esp8266 için
```
 D1 -> SCL
 D2 -> SDA
 3v3 voltu DS3231 için
 VU pini (5V) LCD için
 kullanabilirsiniz
```


