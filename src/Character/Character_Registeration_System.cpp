#include "../../core/Character/Character_Registeration_System.h"
#include <cstdio>

using namespace Character;

bool Registeration::System::Register(int playerid, Character::Data data)
{
	snprintf(data.filename, sizeof(data.filename), "Character-Database/Character-%s.ini", data.name);

	FILE* handle = fopen(data.filename, "r");
	if(handle != NULL)
	{
		fclose(handle);
		sampgdk::SendClientMessage(playerid, -1, "Register Character Error , Exists");
		return false;
	}

	mINI::INIFile account_file(Account::Player_Database[playerid].filename);
	mINI::INIStructure account_ini;
	account_file.read(account_ini);

	char p_character_accounts[128] = {0};
	//char available_character_slot[256] = {0};
	bool empty_check = false;

	for(int i = 0; i < MAX_CHARACTER_ACCOUNTS; i++)
	{
		snprintf(p_character_accounts, sizeof(p_character_accounts), "Character-%d", i);

		if(strcmp(account_ini["Character Accounts"][p_character_accounts].c_str(), "empty") == 0)
		{
			empty_check = true;
			break;
		}
	}

	if(empty_check == true)
	{
		account_ini["Character Accounts"][p_character_accounts] = std::string(data.name);
		account_file.write(account_ini);
	}
	else
	{
		sampgdk::SendClientMessage(playerid, -1, "Characters Accounts Passed Limits");
		return false;
	}

	mINI::INIFile file(data.filename);
	mINI::INIStructure ini;

	ini["General"]["ID"] = std::to_string(data.id);
	ini["General"]["Name"] = std::string(data.name);
	ini["General"]["Filename"] = std::string(data.filename);
	ini["General"]["Age"] = std::to_string(data.age);
	ini["General"]["Gender"] = std::to_string(data.gender);

	if(file.write(ini))
	{
		sampgdk::SendClientMessage(playerid, -1, "Register Character Success");
		return true;
	}
	else
	{
		sampgdk::SendClientMessage(playerid, -1, "Register Character Fails");
		return false;
	}
}

bool Registeration::System::Login(int playerid, Character::Data data)
{
	snprintf(data.filename, sizeof(data.filename), "Character-Database/Character-%s.ini", data.name);

	size_t idx = 0;

	FILE* handle = fopen(data.filename, "r");
	if(handle == NULL)
	{
		sampgdk::SendClientMessage(playerid, -1, "Login Character Error Exists");
		return false;
	}
	fclose(handle);

	mINI::INIFile file(data.filename);
	mINI::INIStructure ini;
	file.read(ini);

	if(file.write(ini))
	{
		data.id = std::stoi(ini["General"]["ID"], &idx, 10);
		strncpy(data.name, ini["General"]["Name"].c_str(), sizeof(data.name));
		strncpy(data.filename, ini["General"]["Filename"].c_str(), sizeof(data.filename));
		data.age = std::stoi(ini["General"]["Age"], &idx, 10);
		data.gender = std::stoi(ini["General"]["Gender"], &idx, 10);
		sampgdk::SendClientMessage(playerid, -1, "Login Character Success");
		return true;
	}
	else
	{
		sampgdk::SendClientMessage(playerid, -1, "Login Character Fails");
		return false;
	}
}