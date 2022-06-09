#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define URL "https://caos-api.startw.cf/v1/automate/state"
#define TLS_SHA1 "E1 BB 4A 71 2D C5 B7 E7 97 66 0D F5 BB B8 9A BD 8A BD 2C B6"
#define USER_AGENT "startw-caos device v1.0"
#define CAOS_TOKEN ""
#define PW_PIN1 0
#define PW_PIN2 2

const char* ssid = "";
const char* password = "";

HTTPClient httpClient;
WiFiClientSecure networkClient;
StaticJsonDocument<256> cacheData;

void setup()
{
    Serial.begin(115200);
    Serial.printf("\nConnecting to %s ", ssid);
    pinMode(PW_PIN1, OUTPUT);
    pinMode(PW_PIN2, OUTPUT);
    digitalWrite(PW_PIN1, LOW);
    digitalWrite(PW_PIN2, LOW);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.printf("connected.\n");
    networkClient.setFingerprint(TLS_SHA1);
    httpClient.setUserAgent(USER_AGENT);
    httpClient.setTimeout(30000);
}

void loop()
{
    if ((WiFi.status() == WL_CONNECTED)) {
        polling();
    }
    delay(5000);
}

void polling()
{
    httpClient.begin(networkClient, URL);
    httpClient.addHeader("CAOS", CAOS_TOKEN);
    Serial.print("URL: ");
    Serial.println(URL);

    int httpCode = httpClient.GET();
    Serial.print("Send GET request to URL: ");
    Serial.println(URL);

    if (httpCode == HTTP_CODE_OK) {
        String responsePayload = httpClient.getString();
        Serial.println("Server Response Payload: ");
        Serial.println(responsePayload);
        deserializeJson(cacheData, responsePayload);
        String message = cacheData["message"];
        if (message == "ON") {
            digitalWrite(PW_PIN1, HIGH);
        } else if (message == "OFF") {
            digitalWrite(PW_PIN1, LOW);
        }
    } else {
        String responsePayload = httpClient.getString();
        Serial.println("Server Respose Code：");
        Serial.println(httpCode);
    }

    httpClient.end();
}
