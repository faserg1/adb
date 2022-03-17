#include <iostream>
#include <vector>
#include <libadb/api/api.hpp>
#include <libadb/api/gateway/gateway.hpp>

#include "tests/test-voice.hpp"
#include "tests/app-commands.hpp"

int main()
{
	using namespace adb::api;

	auto api = DiscordApi();
	auto gateway = api.GetGateway();
	
	/*TestVoice tvoice(api, gateway);*/

	checkAppCommands(api, gateway);

	gateway->connect();
	gateway->run();
	
	return 0;
}