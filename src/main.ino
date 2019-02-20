#include <Espini.h>
#include <PubSubClient.h>
#include "config.h"
#include "ver.h"

const char* mqtt_server = "broker.hivemq.com";

Espini *cosa;
PubSubClient *mqttc;

void setup() {
  Serial.println("hola0");
  cosa=new Espini(wifis(),"luz1",ver,otasrv,logsrv);
  Serial.println("hola1");
  cosa->log("Iniciando");
  mqttc=new PubSubClient();
  mqttc->setServer(mqtt_server,1883);
  while (!mqttc->connected()) {
    if (mqttc->connect(cosa->getchipid())) {
      cosa->log("conectado");
      }else{
      cosa->log("reintentando, rc="); Serial.print(mqttc->state());
      delay(5000);
    }
  }
}

void loop() {
  cosa->log("LOOP!!"); delay(5000);
  mqttc->publish("luz1", "hello world");
}
