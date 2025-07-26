
#define BLYNK_TEMPLATE_ID "TMPL3r4UCW-si"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "5uxjIPyGvNiHcaP4UUVJ_7DCn3SV_U1q"
#include <esp_now.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "5uxjIPyGvNiHcaP4UUVJ_7DCn3SV_U1q";
char ssid[] = "esp";
char pass[] = "12345678";
int led;
unsigned long previousMillis = 0;
const long interval = 200;
uint8_t broadcastAddress[] = {0x78, 0x42, 0x1C, 0x6D, 0x3D, 0x1C};
typedef struct struct_message {
 int led_b;
}struct_message;

struct_message ledstate;

esp_now_peer_info_t peer;
BLYNK_WRITE(V0){
  led = param.asInt();
}
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Blynk.begin(auth, ssid, pass);
  if (WiFi.status() == WL_CONNECTED && Blynk.connected()) {
    Serial.println("Connected to Wi-Fi and Blynk");
  } else {
    Serial.println("Connection failed (Wi-Fi or Blynk)");
  }
  pinMode(2,OUTPUT);

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  if (esp_now_init()!= ESP_OK){
    Serial.println("Error in initialsiing esp now");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peer.peer_addr, broadcastAddress, 6);
  peer.channel = 0;  
  peer.encrypt = false;
  // put your setup code here, to run once:
  if (esp_now_add_peer(&peer) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  Blynk.run();
  if (led == 1){
    digitalWrite(2,HIGH);
  // put your main code here, to run repeatedly:

}

else{
  digitalWrite(2,LOW);
  
}
 unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  ledstate.led_b = led ;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &ledstate, sizeof(ledstate));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}
}
