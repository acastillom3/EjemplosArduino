
const char* MQTT_BROKER_ADRESS = "XXX.XXX.XXX.XXX";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_USERNAME = "ubicua";
const char* MQTT_USERPASS = "ubicua";
const char* MQTT_CLIENT_NAME = "ESP32Client_2";

const char* MQTT_TOPIC_TEMP = "est2/temperature";
const char* MQTT_TOPIC_HUMI = "est2/humidity";
const char* MQTT_TOPIC_UV = "est2/uv";
const char* MQTT_TOPIC_LUX = "est2/lux";
const char* MQTT_TOPIC_LOAD = "est1/load";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void SuscribeMqtt()
{
	mqttClient.subscribe(MQTT_TOPIC_TEMP);
	mqttClient.subscribe(MQTT_TOPIC_HUMI);
	mqttClient.subscribe(MQTT_TOPIC_UV);
}

String payload;
void PublisMqtt(unsigned long data, const char* topic)
{
	payload = "";
	payload = String(data);
	mqttClient.publish(topic, (char*)payload.c_str());
}

String content = "";
void OnMqttReceived(char* topic, byte* payload, unsigned int length) 
{
	Serial.print("Received on ");
	Serial.print(topic);
	Serial.print(": ");

	content = "";	
	for (size_t i = 0; i < length; i++) {
		content.concat((char)payload[i]);
	}
	Serial.print(content);
	Serial.println();
}
