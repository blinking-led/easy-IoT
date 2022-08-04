#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID        "WanLi"               //параметры подключения к сети
#define PASSWORD    "1111111111"
#define HOST_NAME   "dweet.io"
#define HOST_PORT   80

SoftwareSerial mySerial(3, 2);            //подключение ESP-01
ESP8266 wifi(mySerial);
String name_sw = "52M27PBHJ3LPSH4XEEED";  //иднтификатор доступа
String rcvstr="";

void setup(void){

    Serial.begin(9600);
   
    if (wifi.joinAP(SSID, PASSWORD)) {     //подключаемся к WiFi
        Serial.print("Join AP success\r\n");
           } else {
        Serial.print("Join AP failure\r\n");
    }
}

void loop(void)
{
    uint8_t buffer[511] = {0};            //формируем переменные для приема данных
    rcvstr="";

    wifi.createTCP(HOST_NAME, HOST_PORT); //создаем TCP подключение

      String data = "GET /get/latest/dweet/for/" + name_sw + "\r\nConnection: close\r\n\r\n";   //строка запроса
      wifi.send(data.c_str(), data.length());                                                   //посылка запроса

      uint16_t len = wifi.recv(buffer, sizeof(buffer), 10000);      // получение длины запроса и посимвольный перебор ответа
      if (len > 0) {
          for(uint16_t i = 297; i < len - 3; i++) {
              Serial.print((char)buffer[i]);;
              rcvstr += String((char)buffer[i]);                    //собираем данные в переменную
          }
          Serial.println();
          
      }
      wifi.releaseTCP();      // освобождаем TCP 

    delay(1000);
    
    par();                    // запуск парсинга данных
}

void par(){

  String strint="";
  int data[20];
  int j = 0;
  int a, b;

  for (int i = 0; i < rcvstr.lastIndexOf(":"); i++){
    a = rcvstr.indexOf(':');
    b = rcvstr.indexOf(',');
    data[j] = rcvstr.substring(a + 1, b).toInt();   //все данные в виде цифр хранятся в массиве data
    Serial.println(data[j]);
    j++;
    
    rcvstr = rcvstr.substring(b + 1);  
  }
}