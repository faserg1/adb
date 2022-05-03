#include <iostream>
#include <vector>
#include <libadb/api/api.hpp>
#include <libadb/api/gateway/gateway.hpp>

#include "cfg/secrets.hpp"

#include "tests/test1.hpp"
#include "tests/test-voice.hpp"
#include "tests/test-channel.hpp"
#include "tests/test-guild.hpp"
#include "tests/app-commands.hpp"
#include "tests/test-user.hpp"
#include "tests/test-rate.hpp"


int main()
{
	using namespace adb::api;

	auto api = DiscordApi(Secrets::getSecrets());
	auto gateway = api.GetGateway();
	
	TestVoice tvoice(api, gateway);

	// checkRoleMemberAdd(api);
	// checkGuildMembers(api);

	// testPins(api);

	// checkForErrors(api);

	// checkAppCommands(api, gateway);
	// checkAppCommands2(api, gateway);
	// checkAppCommands3(api, gateway);
	// checkAppCommands4(api, gateway);
	// checkAppCommands5(api, gateway);
	// checkGuildChannels(api, gateway);

	// checkRate(api, gateway);

	// checkGuild(api);

	checkCurrentApp(api);

	gateway->runUnlessStopped();
	
	return 0;
}