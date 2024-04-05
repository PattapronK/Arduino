#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define LED1 16
#define relay 4
int sensorPin = A0;

const char* ssid = "KaewKanya_5G";
const char* password ="05051214";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "84518a69-16b8-4e1f-b342-c8dca1650137";
const char* mqtt_username = "FPb92mBBsTc4xeZ2N4SHp8DNgqBVoftW";
const char* mqtt_password = "uatF2DkKQXgSFBpey_g(!epz7lWeA2_N";

WiFiClient espClient;
PubSubClient client(espClient);

char msg[100];

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection…");
        if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
            Serial.println("connected");
            client.subscribe("@msg/led");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            delay(5000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    String message;
    for (int i = 0; i < length; i++) {
        message = message + (char)payload[i];
    }
    Serial.println(message);
    if(String(topic) == "@msg/led") {
        if(message == "on"){
            digitalWrite(LED1,1);
            client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"on\"}}");
            Serial.println("LED on");
            //delay(2000);
        }
        else if (message == "off"){//off
            digitalWrite(LED1,0);
            client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"off\"}}");
            Serial.println("LED off");
       }
    }
}

void setup() {
    pinMode(LED1,OUTPUT);
    Serial.begin(115200);
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
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
  //  dht.begin();
}

void loop() {
   // int humidity; //= readHumidity();//int sensorPin = A0;//
     //int temperature;// = readTemperature();
  int Moisture;
  Moisture = analogRead(sensorPin);
  Moisture = map(Moisture, 0, 1023, 0, 100);
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    String data = "{\"data\": {\"Moisture\":" + String(Moisture) + "}}";
    Serial.println(data);
    data.toCharArray(msg, (data.length() + 1));
    client.publish("@shadow/data/update", msg);
    delay(2000);
}
