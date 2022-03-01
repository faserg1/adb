#include <iostream>
#include <vector>
#include <api/api.hpp>
#include <api/gateway/gateway.hpp>

#include "tests/test-voice.hpp"

int main()
{
	using namespace adb::api;

	auto api = DiscordApi();
	auto gateway = api.GetGateway();
	
	TestVoice tvoice(api, gateway);

	gateway->connect();
	gateway->run();
	return 0;
}