#include <esp_now.h>
#include <WiFi.h>
char ssid[] = "esp";
char pass[] = "12345678";
int led;
typedef struct struct_message {
 int led_b;
}struct_message;
struct_message ledstate;
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&ledstate, incomingData, sizeof(ledstate));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(ledstate.led_b);}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init()!= ESP_OK){
    Serial.println("Error in initialsiing esp now");
    return;
  }
 esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  pinMode(2,OUTPUT);
}
  // put your setup code here, to run once:
 


void loop() {
  // put your main code here, to run repeatedly:
  led = ledstate.led_b;
  if (led == 1) {
    digitalWrite(2,LOW);
}
else {
  digitalWrite(2,HIGH);
}
}
