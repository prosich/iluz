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

PubSubClient *mqttc;

void callback(char* topic, byte* payload, unsigned int length) {
    cosa->log("Callback!");
}

void setup() {
  Serial.println("hola0");
  cosa=new Espini(wifis(),"iluz",ver,otasrv,logsrv);
  Serial.println("hola1");
  cosa->log("Iniciando");
  WiFiClient espClient;
  PubSubClient client(espClient);
  mqttc=new PubSubClient();
  mqttc->setServer(mqtt_server,mqtt_port);
  client.setCallback(callback);
  cosa->log("entrando en bucle de conexion");
  while (!mqttc->connected()) {
    cosa->log("conectaNdo");
    delay(5000);
    //if (mqttc->connect(cosa->getchipid())) {
    if (mqttc->connect("prueba",mqtt_user, mqtt_pass)) {
      cosa->log("conectado!");
      delay(5000);
      cosa->log("conectadooooooooooooo!");
      }else{
      cosa->log("reintentando, rc="); //cosa->log(mqttc->state());
      delay(5000);
    }
  }
}

void loop() {
  cosa->log("LOOP!!"); delay(5000);
  //mqttc->publish("luz1", "hello world");
}
