#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const char* mqtt_server = "YOUR_HIVEMQ_SERVER";
const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_pass = "YOUR_MQTT_PASSWORD";

// -------- Ultrasonic Pins --------
#define TRIG_PIN 14
#define ECHO_PIN 25

const float THRESHOLD_CM = 20.0;
const char* topic = "parking/slot/1";

WiFiClientSecure espClient;
PubSubClient client(espClient);

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1.0;

  return duration * 0.0343 / 2.0;
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.print("Connecting to HiveMQ...");
    String clientId = "ESP32Parking-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  setup_wifi();

  espClient.setInsecure();   // for testing
  client.setServer(mqtt_server, mqtt_port);

  Serial.println("Smart Parking MQTT Publisher Started");
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  float distance = readDistanceCM();

  if (distance > 0) {
    String status = (distance < THRESHOLD_CM) ? "occupied" : "free";

    StaticJsonDocument<200> doc;
    doc["slot_id"] = "S1";
    doc["distance_cm"] = distance;
    doc["status"] = status;
    doc["ts"] = millis() / 1000;

    char buffer[200];
    serializeJson(doc, buffer);

    Serial.print("Publishing: ");
    Serial.println(buffer);

    client.publish(topic, buffer);
  } else {
    Serial.println("No echo received");
  }

  delay(6000);
}