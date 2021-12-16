#include "Network.hpp"

Network::Network()
{
StartServer(80);
}


void Network::ConnectNetwork(const char *ssid, const char *password)
{
	WiFi.begin(ssid,password);
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}
	Serial.println("Connected to Network");
}

void Network::CreateNetwork(const char*ssid, const char *password)
{
	
	IPAddress DeviceIP(192,168,1,31);//Create IP addresses to pass to the softAPConfig
	IPAddress Gateway(192,168,1,1);
	IPAddress SubnetMask(255,255,255,0);

	WiFi.softAPConfig(DeviceIP,Gateway,SubnetMask);
	WiFi.softAP(ssid, password);
	Serial.println("Started Local AP");
}

void Network::StartServer(unsigned int port)
{
	ESP8266WebServer LightsWebServer(port);
}