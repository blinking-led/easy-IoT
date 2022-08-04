#include "ESP8266.h"
#include <SoftwareSerial.h>
 
#define SSID        "WanLi"               //параметры подключения к сети
#define PASSWORD    "1111111111"
#define HOST_NAME   "dweet.io"
#define HOST_PORT   80
#define LIGHT_PIN   A0
 
SoftwareSerial mySerial(3, 2);  //RX, TX  //подключение ESP-01
ESP8266 wifi(mySerial);
String name_val = "52M27PBHJ3LPSH4XEEES"; //иднтификатор доступа
 
void setup(void){
  
    Serial.begin(9600);
   
    if (wifi.joinAP(SSID, PASSWORD)) {    //подключаемся к WiFi
        Serial.print("Join AP success\r\n");
           } else {
        Serial.print("Join AP failure\r\n");
    }
}

void loop(void) {  
  float light = analogRead(LIGHT_PIN);    //получаем данные  датчика света
  
  wifi.createTCP("www.dweet.io", 80);      //создаем TCP подключение
    String data = "GET /dweet/for/" + name_val + "?";
    data += "light=" + String(light) + " HTTP/1.1\r\n";
    data += "Host: dweet.io\r\n\r\n";
    wifi.send(data.c_str(), data.length()); //формируем и оправляем строку
        
    wifi.releaseTCP();                    // освободаем TCP 
    
    Serial.println("light\t"+String(light)); //выводим переданные данные
    
  delay(1000);
}