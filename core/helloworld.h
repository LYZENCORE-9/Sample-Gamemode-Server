#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <string>

#include "../include/sampgdk/eventhandler.h"

class HelloWorld : public sampgdk::EventHandler {
public:
	HelloWorld();
	virtual ~HelloWorld();
	virtual bool OnGameModeInit();
	virtual bool OnGameModeExit();
	virtual bool OnPlayerConnect(int playerid);
	virtual bool OnPlayerDisconnect(int playerid, int reason);
	virtual bool OnPlayerRequestClass(int playerid, int classid);
	virtual bool OnPlayerCommandText(int playerid, const std::string &cmdtext);

	virtual bool OnDialogResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
};

#endif
