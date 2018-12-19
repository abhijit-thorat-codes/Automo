#include <ESP8266WiFi.h>
#define SS_PIN 15  //D2
#define RST_PIN 5 //D1
#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
const char* ssid = "Ab's spot";
const char* password = "qwerty1996";
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}
void loop() {
   if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "70 6B 6E A3") 
  //change UID of the card that you want to give access
  {
    statuss = 1;
  }

  else   {
   // Serial.println(" Access Denied ");
    delay(3000);
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.print("AUTOMO RFID : ");
  String temp = req.substring(5, 12);
  for(int i=0;i<temp.length();i++)
  
  {
    if(temp[i]=="%")
        temp[i]=" ";
  }
  Serial.println(temp);
  
  
  

  
  delay(1000);
  client.flush();
}

//GET / 706B6EA3 HTTP / 1.1




