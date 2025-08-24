#include <cstdio> // for sprintf
#include <cstring>
#include <string>

#include "../include/sampgdk/plugin.h"

#include "../include/sampgdk/samp.h"
#include "../include/sampgdk/players.h"
#include "../include/sampgdk/timers.h"
#include "../include/sampgdk/wrapper.h"

#include "../core/helloworld.h"

#include "../core/Account/Registeration_System.h"
#include "../core/Account/Registeration_Dialogs.h"

#include "../core/Character/Character_Registeration_System.h"
#include "../core/Character/Character_Registeration_Dialogs.h"


typedef void (*logprintf_t)(const char *format, ...);
static logprintf_t logprintf;

using namespace sampgdk;

static HelloWorld theGameMode;

HelloWorld::HelloWorld() {
	// Register our gamemode in order to catch events - if we don't do this
	// somewhere none of the HelloWorld callbacks will be ever called.
	this->Register();
}

HelloWorld::~HelloWorld() {}

//static Timer *oneSecondTimer = 0;

static void OneSecondTimer(Timer *timer, void *param) {
	//logprintf("one second timer");
};

bool HelloWorld::OnGameModeInit() {
	SetGameModeText("Sample-GameMode");

	AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

	logprintf("------------------------------------------\n");
	logprintf(" LYZENCORE-9 Server got loaded. \n");
	logprintf("------------------------------------------\n");

	// Set two timers using two different methods
	//oneSecondTimer = SetTimer(1000, true, OneSecondTimer, 0);

	return true;
}

bool HelloWorld::OnPlayerConnect(int playerid) {
	SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
	Account::Registeration::Dialogs::Check(playerid);
	return true;
}

bool HelloWorld::OnPlayerDisconnect(int playerid, int reason)
{
	Account::Player_Database[playerid].reset();
	Character::Player_Characters[playerid].reset();
	return true;
}

bool HelloWorld::OnPlayerRequestClass(int playerid, int classid) {
	SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
	SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
	SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f);
	return true;
}

bool HelloWorld::OnPlayerCommandText(int playerid, const std::string &cmdtext) {
	if (cmdtext == "/hello") {
		char name[MAX_PLAYER_NAME];
		GetPlayerName(playerid, name);
		char message[128];
		std::sprintf(message, "{00FF00}Hello, %s!", name);
		SendClientMessage(playerid, 0x00FF00FF, message);
		return true;
	}
	if (cmdtext == "/pos") {
		float x, y, z;
		GetPlayerPos(playerid, x, y, z);
		char message[128];
		std::sprintf(message, "Your position is (%f, %f, %f)", x, y, z);
		SendClientMessage(playerid, 0xFFFFFFFF, message);
		return true;
	}
	return false;
}

bool HelloWorld::OnGameModeExit() {
	//KillTimer(oneSecondTimer);
	return true;
}

bool HelloWorld::OnDialogResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	Account::Registeration::Dialogs::Response(playerid, dialogid, response, listitem, inputtext);
	Character::Registeration::Dialogs::Response(playerid, dialogid, response, listitem, inputtext);
	return true;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return SUPPORTS_VERSION | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData) {
	logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];
	logprintf("Sample-GameMode Internal Core Has Been Launched !");
	// Initialize the wrapper - this always should be done here.
	Wrapper::Initialize(ppPluginData);
	// Do not call any natives here - they are not yet prepared for use at this stage.
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
	logprintf("Sample-GameMode Internal Core Has Been Stopped !");
	return;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
	Timer::ProcessTimers();
}
