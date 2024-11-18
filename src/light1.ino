#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* root_ca = R"(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)";
// Configurações de WiFi e MQTT
const char* ssid = "yanoma";
const char* password = "yanomalindao";
const char* mqtt_username = "yanoma";
const char* mqtt_password = "Safyfk090391!";
const char* mqtt_server = "c6c0a7b3489745eebf6facb43d10e815.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* clientID = "11";


String initTopic = "traffic-light/" + String(clientID) + "/new"; // Tópico de inicialização
String stateTopic = "traffic-light/state/" + String(clientID); // Tópico para receber o estado do semáforo
String stateLdrTopic = "traffic-light/"+String(clientID)+"/ldr-state";

int lastLdrReadStateMillis = millis();

// Tópicos MQTT
const char* topicStatus = "traffic/light1/status";
const char* topicControl = "traffic/light1/control";
const char* topicLightSensor = "traffic/light1/light"; // Novo tópico para dados do sensor

enum TrafficLightState { RED, YELLOW, GREEN };

// Pinos do semáforo
const int PIN_RED = 12;
const int PIN_YELLOW = 14;
const int PIN_GREEN = 13;
const int ldrPin = 34; // Pino analógico para o sensor LDR

// Constantes do sistema
const int NIGHT_MODE_THRESHOLD = 350;
const int VEHICLE_DETECTION_THRESHOLD = 1500;
const unsigned long SENSOR_PUBLISH_INTERVAL = 1000; // Intervalo de publicação dos dados do sensor

// Variáveis globais
bool nightMode = false;
int currentState = 10000;
unsigned long lastStateChange = 10000;

// Variáveis para média móvel do LDR
const int NUM_READINGS = 10;
int ldrReadings[NUM_READINGS];
int ldrIndex = 0;
int ldrTotal = 0;
int ldrAverage = 0;

// Tempos padrão (em millisegundos)
int greenTime = 5000;
int yellowTime = 2000;
int redTime = 5000;

// Objetos para WiFi e MQTT
WiFiClientSecure espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(115200);
  
  // Configuração dos pinos
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(ldrPin, INPUT);
  
  // Inicializa array de leituras do LDR
  for (int i = 0; i < NUM_READINGS; i++) {
    ldrReadings[i] = 0;
  }
  
  // Inicializa conexão WiFi
  setupWiFi();
  
  // Configura certificado para conexão segura
  espClient.setCACert(root_ca);
  
  // Configura MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  connectMQTT();
  sendInitializationMessage();
}

// Função para ler e calcular média do sensor LDR
int readLDR() {
  ldrTotal = ldrTotal - ldrReadings[ldrIndex];
  ldrReadings[ldrIndex] = analogRead(ldrPin);
  ldrTotal = ldrTotal + ldrReadings[ldrIndex];
  ldrIndex = (ldrIndex + 1) % NUM_READINGS;
  
  ldrAverage = ldrTotal / NUM_READINGS;
  return ldrAverage;
}



void setupWiFi() {
  delay(10);
  Serial.println("Conectando ao WiFi...");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi conectado!");
}

// Função para conectar ao HiveMQ
void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao HiveMQ...");
    if (client.connect(clientID, mqtt_username, mqtt_password)) {
      Serial.println(" Conectado ao HiveMQ!");
      client.subscribe(stateTopic.c_str()); // Inscreve-se no tópico de estado
    } else {
      Serial.print(" Falha de conexão: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
// Função para enviar a mensagem de inicialização ao HiveMQ
void sendInitializationMessage() {
  if (client.connected()) {
    const char* initMessage = "{ \"status\": \"initialized\", \"device\": \"ESP32\" }";
    client.publish(initTopic.c_str(), initMessage);
    Serial.println("Mensagem de inicialização enviada!");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Processa mensagens recebidas via MQTT
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload, length);
  
  if (doc.containsKey("nightMode")) {
    nightMode = doc["nightMode"];
  }
  
  if (String(topic) == stateTopic) {
    String message;
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }

    if (message == "green"){
      updateLights(GREEN);
    }
    else if (message == "red"){
      updateLights(RED);
    }
    else if (message == "yellow"){
      updateLights(YELLOW);
    }
  }
}

void publishStatus() {
  StaticJsonDocument<200> doc;
  doc["lightState"] = currentState;
  doc["nightMode"] = nightMode;
  doc["ldrValue"] = readLDR();
  doc["light_percentage"] = map(readLDR(), 0, 4095, 0, 100);
  
  char buffer[200];
  serializeJson(doc, buffer);
  client.publish(topicStatus, buffer);
}

int getStateTime() {
  switch (currentState) {
    case 0: return greenTime;
    case 1: return yellowTime;
    case 2: return redTime;
    default: return 1000;
  }
}

void updateLights(TrafficLightState state) {
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_YELLOW, LOW);
  switch (state) {
    case RED:
      digitalWrite(PIN_RED, HIGH);
      break;
    case YELLOW:
      digitalWrite(PIN_YELLOW, HIGH);
      break;
    case GREEN:
      digitalWrite(PIN_GREEN, HIGH);
      break;
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  publishStatus();
  checkLdrState();
  
  delay(100);
}

// Função para verificar o estado do LDR e publicar se é HIGH ou LOW
String lastLdrState = "";
void checkLdrState() {
  if (millis() - lastLdrReadStateMillis > 500) {
    int ldrValue = analogRead(ldrPin); // Lê o valor do LDR
    String ldrState = (ldrValue < 600) ? "HIGH" : "LOW"; // Determina o estado baseado no limite
    if (lastLdrState != ldrState ){
      String ldrMessage = "{ \"ldrState\": \"" + ldrState + "\" }";
      // Publica o estado do LDR no tópico MQTT
      client.publish(stateLdrTopic.c_str(), ldrMessage.c_str());
      Serial.print("Estado do LDR publicado: ");
      Serial.println(ldrMessage);
      lastLdrState = ldrState;
    }
    lastLdrReadStateMillis = millis();  
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("TrafficLight1", mqtt_username, mqtt_password)) {
      client.subscribe(topicControl);
      Serial.println("Conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}