#include "../../core/Character/Character_Registeration_Dialogs.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace Character;

void Registeration::Dialogs::OpenMainPannel(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, ID_MAIN_PANNEL, sampgdk::DIALOG_STYLE_LIST, "Character Management Pannel", "Register a character\nLogin to a character", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterPannel(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, ID_REGISTER_PANNEL, sampgdk::DIALOG_STYLE_LIST, "Create New Character", "Name\nAge\nGender\n{00FF00}Apply", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterName(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, ID_REGISTER_NAME, sampgdk::DIALOG_STYLE_INPUT, "CMP - Name (1/3)", "Character name", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterAge(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, ID_REGISTER_AGE, sampgdk::DIALOG_STYLE_INPUT, "CMP - Age (2/3)", "Character age", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterGender(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, ID_REGISTER_GENDER, sampgdk::DIALOG_STYLE_INPUT, "CMP - Gender (3/3)", "Character gender", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenLoginPannel(int playerid)
{
	mINI::INIFile file(Account::Player_Database[playerid].filename);
	mINI::INIStructure ini;
	file.read(ini);

	char character_keys[128] = {0};
	char character[128*3] = {0};

	for(int i = 0; i < MAX_CHARACTER_ACCOUNTS; i++)
	{
		snprintf(character_keys, sizeof(character_keys), "Character-%d", i);
		snprintf(character, sizeof(character), "Accounts : %s", ini["Character Accounts"][character_keys].c_str());
	}
	sampgdk::ShowPlayerDialog(playerid, ID_LOGIN_PANNEL, sampgdk::DIALOG_STYLE_INPUT, "CMP - Name (1/3)", "Available Characters Will Appear", "Confirm", "Cancel");
}

// Response

void Registeration::Dialogs::Response(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	MainPannelResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterPannelResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterNameResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterAgeResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterGenderResponse(playerid, dialogid, response, listitem, inputtext);

	LoginPannelResponse(playerid, dialogid, response, listitem, inputtext);
}

void Registeration::Dialogs::MainPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_MAIN_PANNEL)
	{
		if(response)
		{
			switch(listitem)
			{
			case 0:
				{
					OpenRegisterPannel(playerid);
					break;
				}
			case 1:
				{
					OpenLoginPannel(playerid);
					break;
				}
			}
		}
		else
		{
			OpenMainPannel(playerid);
		}
	}
}

void Registeration::Dialogs::RegisterPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_REGISTER_PANNEL)
	{
		if(response)
		{
			switch(listitem)
			{
			case 0:
				{
					OpenRegisterName(playerid);
					break;
				}
			case 1:
				{
					OpenRegisterAge(playerid);
					break;
				}
			case 2:
				{
					OpenRegisterGender(playerid);
					break;
				}
			case 3:
				{
					if(register_name_check == true && register_age_check == true && register_gender_check == true)
					{
						Registeration::System::Register(playerid, Character::Player_Characters[playerid]);
						OpenMainPannel(playerid);
					}
					else
					{
						sampgdk::SendClientMessage(playerid, -1, "Something goes wrong");
						OpenRegisterPannel(playerid);
					}
					break;
				}
			}
		}
		else
		{
			OpenMainPannel(playerid);
		}
	}
}

void Registeration::Dialogs::RegisterNameResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_REGISTER_NAME)
	{
		if(response)
		{
			if(inputtext.length() > 4 && inputtext.length() < 25)
			{
				strncpy(Character::Player_Characters[playerid].name, inputtext.c_str(), sizeof(Character::Player_Characters[playerid].name));
				register_name_check = true;
				OpenRegisterPannel(playerid);
			}
			else
			{
				sampgdk::SendClientMessage(playerid, -1, "Name Error");
				OpenRegisterPannel(playerid);
			}
		}
		else
		{
			OpenRegisterPannel(playerid);
		}
	}
}

void Registeration::Dialogs::RegisterAgeResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_REGISTER_AGE)
	{
		if(response)
		{
			size_t idx = 0;
			int temp_age = std::stoi(inputtext, &idx, 10);
			if(temp_age >= 20 && temp_age <= 100)
			{
				Character::Player_Characters[playerid].age = temp_age;
				register_age_check = true;
				OpenRegisterPannel(playerid);
			}
			else
			{
				OpenRegisterAge(playerid);
				sampgdk::SendClientMessage(playerid, -1, "Age Error");
			}
		}
		else
		{
			OpenRegisterPannel(playerid);
		}
	}
}

void Registeration::Dialogs::RegisterGenderResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_REGISTER_GENDER)
	{
		if(response)
		{
			size_t idx = 0;
			int temp_gender = std::stoi(inputtext, &idx, 10);
			if(temp_gender == 1 || temp_gender == 2)
			{
				Character::Player_Characters[playerid].gender = temp_gender;
				register_gender_check = true;
				OpenRegisterPannel(playerid);
			}
			else
			{
				OpenRegisterGender(playerid);
				sampgdk::SendClientMessage(playerid, -1, "Gender Error");
			}
		}
		else
		{
			OpenRegisterPannel(playerid);
		}
	}
}


void Registeration::Dialogs::LoginPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_LOGIN_PANNEL)
	{
		if(response)
		{
			if(inputtext.length() != 0)
			{
				char character_string[128] = {0};
				char character_account[128] = {0};

				bool character_account_found = true;

				mINI::INIFile file(Account::Player_Database[playerid].filename);
				mINI::INIStructure ini;
				file.read(ini);

				for(int i = 0; i < MAX_CHARACTER_ACCOUNTS; i++)
				{
					snprintf(character_string, sizeof(character_string), "Character-%d", i);
					strncpy(character_account, ini["Character Accounts"][character_string].c_str(), sizeof(character_account));
					if(strncmp(character_account, inputtext.c_str(), sizeof(character_account)) == 0)
					{
						character_account_found = true;
						break;
					}
				}

				if(character_account_found == true)
				{
					Registeration::System::Login(playerid, Character::Player_Characters[playerid]);
				}
				else
				{
					sampgdk::SendClientMessage(playerid, -1, "NOT FOUND");
					OpenLoginPannel(playerid);
				}
			}
		}
		else
		{
			OpenMainPannel(playerid);
		}
	}
}