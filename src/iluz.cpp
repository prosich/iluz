#include <Espini.h>
#include <PubSubClient.h>
#include "config.h"
#include "ver.h"

const byte DREAD = D2;

const char* mqtt_server = "m21.cloudmqtt.com";
const int   mqtt_port   = 19645;
const char* mqtt_user   = "lzxaksqt";
const char* mqtt_pass   = "MEsnDE8fOjpl";

Espini *cosa;
WiFiClient espClient;
PubSubClient *mqttc;

void callback(char* topic, byte* payload, unsigned int length) {
    cosa->log("Callback!");
}

void flip() {
    cosa->log(String(digitalRead(DREAD)).c_str());
    mqttc->publish("iluz", String(digitalRead(DREAD)).c_str());
}

void setup() {
  cosa=new Espini(wifis(),"iluz",ver,otasrv,logsrv);
  cosa->log("Iniciando");

  mqttc=new PubSubClient(espClient);
  mqttc->setServer(mqtt_server,mqtt_port);
  mqttc->setCallback(callback);
  cosa->log("Conectando");
  while (!mqttc->connect(cosa->getchipid(),mqtt_user, mqtt_pass)) delay(5000);
  cosa->log("Conectado!");

  pinMode(DREAD, INPUT);
  attachInterrupt(digitalPinToInterrupt(DREAD), flip, CHANGE);
}

void loop() {
  while (true) { cosa->log("ALIVE!!"); delay(300e3); }
}

