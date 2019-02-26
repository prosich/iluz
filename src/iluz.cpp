#include <Espini.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "config.h"
#include "ver.h"

const byte DREAD = D2;

const char* mqtt_server = "192.168.0.15";
const int   mqtt_port   = 1883;
const char* mqtt_user   = "";
const char* mqtt_pass   = "";

Espini *esp;
WiFiClient espClient;
PubSubClient *mqttc;
Ticker tic;

void conecta() {
  esp->log("Conectando");
  mqttc->connect(esp->getchipid(),mqtt_user, mqtt_pass);
  esp->log("Conectado!");
}

void pio() {
  char topic[100], payload[100], todo[200];

  snprintf(topic,sizeof(topic),"%s/%s","iluz",esp->getchipid());
  if (digitalRead(DREAD)) snprintf(payload,sizeof(payload),"ON");
                     else snprintf(payload,sizeof(payload),"OFF");
  snprintf(todo,sizeof(todo),"%s/%s",topic,payload);

  esp->log(todo);
 
  mqttc->publish(topic,payload);
}

void setup() {
  esp=new Espini(wifis(),"iluz",ver,otasrv,logsrv);
  esp->log("Iniciando");

  mqttc=new PubSubClient(espClient);
  mqttc->setServer(mqtt_server,mqtt_port);
 
  pinMode(DREAD, INPUT);
  attachInterrupt(digitalPinToInterrupt(DREAD), pio, CHANGE);

  // De vez en cuando, por si acaso, refrescar estado a mqtt.
  tic.attach(300,pio); 
}

void loop() {
  if (!mqttc->connected()) conecta();
  mqttc->loop();
}
