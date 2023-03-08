#include <WiFi.h>
#include <WiFiClient.h>
#include "ESP32FtpServer.h"
#define LED_BUILTIN 2

const char* ssid = "SSID"; //WiFi SSID
const char* password = "SSID_PASSWORD"; //WiFi Password

FtpServer ftpSrv;   //set #define FTP_DEBUG in ESP32FtpServer.h to see ftp verbose on serial

void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  pinMode (LED_BUILTIN, OUTPUT);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /////FTP Setup, ensure SD is started before ftp;  /////////
  
  if (SD.begin()) {
      Serial.println("SD opened!");
      ftpSrv.begin("ESP32","ESP32");    //username, password for ftp.  set ports in ESP32FtpServer.h  (default 21, 50009 for PASV)
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(2000);
  }
  Serial.print(":)");  
}

void loop(void){
  ftpSrv.handleFTP();        //make sure in loop you call handleFTP()!!   
}
