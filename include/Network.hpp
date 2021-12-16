#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

class Network
{
	public:
	Network();
	void StartServer(unsigned int port = 80);
	void ConnectNetwork(const char *ssid, const char *password);
	void CreateNetwork(const char*ssid, const char *password);

	protected:
		
	private:


};





#endif//NETWORK_HPP