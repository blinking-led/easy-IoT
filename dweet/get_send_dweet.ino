#include "ESP8266.h"
#include <SoftwareSerial.h>
#include "DHT.h"

#define SSID        "WanLi"                 //параметры подключения к сети
#define PASSWORD    "1111111111"
#define HOST_NAME   "dweet.io"
#define HOST_PORT   80

#define LIGHT_PIN A0                        //объявляем контакты к которым подключены датчики
#define DHTPIN 9
#define LAMP   7
#define HEAT   6
#define COOL   5
#define HUM    4


DHT dht(DHTPIN, DHT11);
SoftwareSerial mySerial(3, 2);              //подключение ESP-01
ESP8266 wifi(mySerial);
String name_val = "52M27PBHJ3LPSH4XEEES";   //иднтификатор показаний
String name_sw = "52M27PBHJ3LPSH4XEEED";    //иднтификатор выключателей

String rcvstr="";
float light, hum, temp;

void setup(void)
{
    Serial.begin(9600);
    dht.begin();
    for (int i = 5; i < 8; i++ ){           //инициализация поротов вывода
      pinMode( i, OUTPUT);}
    pinMode(A0, INPUT);
    if (wifi.joinAP(SSID, PASSWORD)) {      //подключаемся к WiFi
        Serial.print("Join AP success\r\n");
           } else {
        Serial.print("Join AP failure\r\n");
    }   
}

void loop(){    
    send();
    get();
}

void send(void) {
    Serial.println("_=Send=_");  

    light = analogRead(LIGHT_PIN);		//получаем данные c датчиков
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    wifi.createTCP(HOST_NAME, HOST_PORT);	//создаем TCP подключение
    String data = "GET /dweet/for/" + name_val + "?";
    data += "temp=" + String(temp) + "&";
    data += "light=" + String(light) + "&";    
    data += "hum=" + String(hum);
    data += " HTTP/1.1\r\n";
    data += "Host: dweet.io\r\n\r\n";		

    wifi.send(data.c_str(), data.length());	//формируем и оправляем строку
    //Serial.println(data);
    wifi.releaseTCP(); 				// освободаем TCP   
    Serial.println(temp);
    Serial.println(light);
    Serial.println(hum);  
    delay(1000);
}

void get(void){
    Serial.println("_=Get=_"); 

    uint8_t buffer[511] = {0};			//формируем переменные для приема данных
    rcvstr="";
    
    wifi.createTCP(HOST_NAME, HOST_PORT);	//создаем TCP подключение

    String data = "GET /get/latest/dweet/for/" + name_sw + "\r\nConnection: close\r\n\r\n";	//строка запроса
    wifi.send(data.c_str(), data.length());	//посылка запроса
    
    uint16_t len = wifi.recv(buffer, sizeof(buffer), 8000);	// получение длины запроса и посимвольный перебор ответа
    if (len > 0) {
        for(uint16_t i = 297; i < len - 3; i++) {
            Serial.print((char)buffer[i]);;
            rcvstr += String((char)buffer[i]);	//собираем данные в переменную
        }    
    }
    wifi.releaseTCP();				// освобождаем TCP 
    delay(1000);
    par();					// запуск парсинга данных    
}

void par(){

  String strint="";
  int data[20];
  int j = 0;
  int i = 0;
  int a, b;

  Serial.println();
  //Serial.println(rcvstr);
  for (int i=0; i < rcvstr.lastIndexOf(":"); i++){
      a = rcvstr.indexOf(':');
      b = rcvstr.indexOf(',');
      data[j] = rcvstr.substring(a + 1,b).toInt();	//все данные в виде цифр хранятся в массиве data
      Serial.println((data[j]));
      j++;
      
      rcvstr = rcvstr.substring(b + 1);  
  }
  bool mode = data[0];		// перенос данных в переменные (не обязательно)
  bool lamp_sw = data[1];
  bool heat_sw = data[2]; 
  bool cool_sw = data[3];
  bool hum_sw  = data[4];
  
  if (mode == 0){		// автоматическое управление
    if (temp < 18) {digitalWrite(HEAT, 1);}
    else {digitalWrite(HEAT, 0);}
    if (temp > 27) {digitalWrite(COOL, 1);}
    else {digitalWrite(COOL, 0);}
    if (light > 200) {digitalWrite(LAMP, 1);}
    else {digitalWrite(LAMP, 0);}
    if (hum < 40) {digitalWrite(HUM, 1);}
    else {digitalWrite(HUM, 0);}
  }
  if (mode == 1){		// ручное управление
  digitalWrite(LAMP, lamp_sw);
  digitalWrite(HEAT, heat_sw);
  digitalWrite(COOL, cool_sw);
  digitalWrite(HUM, hum_sw);
  }  
}
