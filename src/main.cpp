#include <Arduino.h>
#include <Led.h>
#include <LightSensorArray.h>
#include <RingBuffer.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define BUILTIN_LED_PIN GPIO_NUM_2
#define SENSOR_NUM 5
#define SENSOR_SAMPLES 10

uint32_t tick = 0;

Led_t builtinLed = {.pin = BUILTIN_LED_PIN, .state = LOW};
Led_t led1 = {.pin = 13, .state = LOW};

uint8_t lsapins[SENSOR_NUM] = {GPIO_NUM_35, GPIO_NUM_33, GPIO_NUM_34, GPIO_NUM_32, GPIO_NUM_39};

LSA_t lsa = {
    .pins = lsapins,
    .size = SENSOR_NUM,
};
uint16_t result[SENSOR_NUM] = {0};

// Ring Buffer
uint16_t buffer1[SENSOR_SAMPLES] = {0};
RingBuffer rb1 = {.size = SENSOR_SAMPLES, .buffer = buffer1, .index = 0, .ready = RING_BUFF_NOT_READY};

uint16_t buffer2[SENSOR_SAMPLES] = {0};
RingBuffer rb2 = {.size = SENSOR_SAMPLES, .buffer = buffer2, .index = 0, .ready = RING_BUFF_NOT_READY};

uint16_t buffer3[SENSOR_SAMPLES] = {0};
RingBuffer rb3 = {.size = SENSOR_SAMPLES, .buffer = buffer3, .index = 0, .ready = RING_BUFF_NOT_READY};

uint16_t buffer4[SENSOR_SAMPLES] = {0};
RingBuffer rb4 = {.size = SENSOR_SAMPLES, .buffer = buffer4, .index = 0, .ready = RING_BUFF_NOT_READY};

uint16_t buffer5[SENSOR_SAMPLES] = {0};
RingBuffer rb5 = {.size = SENSOR_SAMPLES, .buffer = buffer5, .index = 0, .ready = RING_BUFF_NOT_READY};

const char *ssid = "SPHINX-Mac";
const char *password = "onganhtot";

const char *mqttServer = "192.168.1.103";
const int mqttPort = 1883;
const char *mqttTopic = "esp32/sensor";

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);

  Led_Setup(&builtinLed);

  Led_Setup(&led1);
  LSA_Setup(&lsa);

  RingBuff_Setup(&rb1);
  RingBuff_Setup(&rb2);
  RingBuff_Setup(&rb3);
  RingBuff_Setup(&rb4);
  RingBuff_Setup(&rb5);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  client.setServer(mqttServer, mqttPort);
  Serial.println("Connecting to MQTT...");
  while (!client.connected())
  {
    Serial.print(".");
    client.connect("LightTracker");
    delay(1000);
  }

  Serial.println("\nConnected");
}

void SensorThread_Run(uint32_t tick)
{
  // TODO should I run or not?
  if (tick % 300 == 0) {
    LSA_Read(&lsa, result);
    RingBuff_Set(&rb1, result[0]);
    RingBuff_Set(&rb2, result[1]);
    RingBuff_Set(&rb3, result[2]);
    RingBuff_Set(&rb4, result[3]);
    RingBuff_Set(&rb5, result[4]);

    Serial.println("Sensor ticked");
  }
}

void MqttThread_Run(uint32_t tick)
{
  char message[50];
  if (tick % 999 == 0)
  {
    sprintf(message, "%d, %d, %d, %d, %d", 
      RingBuff_Median(&rb1), 
      RingBuff_Median(&rb2), 
      RingBuff_Median(&rb3), 
      RingBuff_Median(&rb4), 
      RingBuff_Median(&rb5)
    );
    client.publish("lightracker/sensors", message);
    Serial.println("Mqtt ticked");
  }
}

void loop()
{
  if (tick == 1000)
  {
    tick = 0;
  }
  tick++;
  delay(1);
  SensorThread_Run(tick);
  MqttThread_Run(tick);
}
