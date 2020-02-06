#include <ESP8266WiFi.h>
int led = 16;
const char* ssid = "SSID2"; // Enter SSID here
const char* password = "00110011"; //Enter Password here
WiFiServer server(80);                //ทำหน้าที่เป็น Server โดยใช้ Port 80 
//IPAddress local_ip(192, 168, 1, 1);
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 255, 0);

void setup() 
{
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  //WiFi.softAP(ssid, password);
  //WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(100);
  server.begin();                     //เริ่มต้นทำงาน TCP Server
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println("Server started");   //แสดงข้อความ server เริ่มทำงาน
  Serial.println(WiFi.localIP());
  
}
void loop()
{
 
          WiFiClient client = server.available();  //รอรับ การเชื่อมต่อจาก Client
          
          String  web ="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
          web +="<!DOCTYPE HTML>";
          web +="<html>";
          web +="<head></head>";
          web +="<body><center>";
          web +="<h1>LED</h1>";
          web +="<a href=\"ON\"><button>ON</button></a>&nbsp;&nbsp;";
          web +="<a href=\"OFF\"><button>OFF</button></a>";
          web +="</center></body>";
          web +="</html>";  
          
          client.println(web);

          String req = client.readStringUntil('\r');    //อ่านค่าที่ได้รับจาก client จากข้อมูลแรกจนถึงอักขระ ‘\r’ แล้วหยุด
          Serial.println(req);                          //แสดงค่าที่ได้รับทาง Serial
          if (req.indexOf("OFF") != -1)                 //ตรวจสอบว่า data ที่เข้ามาและเจอข้อความ ”OFF” ถ้าไม่เจอ"OFF" จะมีเท่ากับ -1
          {
          digitalWrite(led,HIGH);                       //ให้ LED ดับ
          Serial.println("LED OFF");
          }
          else if(req.indexOf("ON") != -1)              //ตรวจสอบว่า data ที่เข้ามาและเจอข้อความ ”ON”
          {
            digitalWrite(led,LOW);                      //ให้ LED ติด
            Serial.println("LED ON");
          }
}
