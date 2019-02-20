#include <Espini.h>
#include <PubSubClient.h>
#include "config.h"
#include "ver.h"

//const char* mqtt_server = "broker.hivemq.com";
//const int mqtt_port = 1883;
const char* mqtt_server = "m21.cloudmqtt.com";
const int mqtt_port = 19645;
const char* mqtt_user = "lzxaksqt";
const char* mqtt_pass = "MEsnDE8fOjpl";
Espini *cosa;

WiFiClient espClient;
PubSubClient *mqttc;

void callback(char* topic, byte* payload, unsigned int length) {
    cosa->log("Callback!");
}

void setup() {
  cosa=new Espini(wifis(),"iluz",ver,otasrv,logsrv);
  Serial.println("Conectado");
  cosa->log("Iniciando");
  mqttc=new PubSubClient(espClient);
  mqttc->setServer(mqtt_server,mqtt_port);
  mqttc->setCallback(callback);
  cosa->log("entrando en bucle de conexion");
  while (!mqttc->connected()) {
    cosa->log("conectaNdo");
    if (mqttc->connect(cosa->getchipid(),mqtt_user, mqtt_pass)) {
      cosa->log("conectado!");
      }else{
      cosa->log("reintentando, rc="); //cosa->log(mqttc->state());
    }
  }
}

void loop() {
  cosa->log("LOOP!!"); delay(10000);
  mqttc->publish("luz", "hello world");
}
