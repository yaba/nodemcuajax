/*Arduino  code for ESP8266 AJAX Webserver

www.circuitdigest.com&nbsp;

*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#define LED D0

const char *ssid = "YaBaGuest";

const char *password = "XXXXXXXXXXXX";

ESP8266WebServer server(80);

void handleRoot()

{
	String s = webpage;

	server.send(200, "text/html", s);

}

void sensor_data()

{
	int a = analogRead(A0);

	int temp = a / 4.35;

	String sensor_value = String(temp);

	server.send(200, "text/plane", sensor_value);

}

void led_control()

{
	String state = "OFF";

	String act_state = server.arg("state");

	if (act_state == "1")

	{
		digitalWrite(LED, HIGH);	//LED ON

		state = "ON";
	}
	else

	{
		digitalWrite(LED, LOW);	//LED OFF

		state = "OFF";
	}

	server.send(200, "text/plane", state);

}

void setup(void)

{
	Serial.begin(115200);

	WiFi.begin(ssid, password);

	Serial.println("");

	pinMode(LED, OUTPUT);

	while (WiFi.status() != WL_CONNECTED)

	{
		Serial.print("Connecting...");
	}

	Serial.println("");

	Serial.print("Connected to ");

	Serial.println(ssid);

	Serial.print("IP address: ");

	Serial.println(WiFi.localIP());

	server.on("/", handleRoot);

	server.on("/led_set", led_control);

	server.on("/adcread", sensor_data);

	server.begin();

}

void loop(void)

{
	server.handleClient();

}