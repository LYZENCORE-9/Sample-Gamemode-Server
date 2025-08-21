#include "../../core/Account/Registeration_Dialogs.h"
#include <string>

using namespace Account;

void Registeration::Dialogs::OpenRegisterPannel(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_PANNEL, sampgdk::DIALOG_STYLE_LIST, "Registeration Pannel (Register)", "[*] Password\n[*] Backup Password\n[*] Age\n[*] Gender\n{00FF00}[!] Apply", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_PANNEL, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Password (1/4)", "Password", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterBackupPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_PANNEL, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Backup Password (2/4)", "Backup Password", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterAge(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_PANNEL, sampgdk::DIALOG_STYLE_INPUT, "Registeration Age (3/4)", "Age", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterGender(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_PANNEL, sampgdk::DIALOG_STYLE_INPUT, "Registeration Gender (4/4)", "Gender", "Confirm", "Cancel");
}


void Registeration::Dialogs::OpenLoginPannel(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_LOGIN_PANNEL, sampgdk::DIALOG_STYLE_LIST, "Registeration Pannel (Login)", "[*] Password\n[*] Backup Password\n{00FF00}[!] Apply", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenLoginPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_LOGIN_PANNEL, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Password (Login)", "Password 2", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenLoginBackupPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_LOGIN_PANNEL, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Backup Password (Login)", "Backup Password 2", "Confirm", "Cancel");
}

// Response

// // Register
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
					OpenRegisterPannel(playerid);
				}
			case 1:
				{
					OpenRegisterPassword(playerid);
				}
			case 2:
				{
					OpenRegisterAge(playerid);
				}
			case 3:
				{
					OpenRegisterGender(playerid);
				}
			case 5:
				{
					Registeration::System::Register(playerid, Account::Player_Database[playerid]);
				}
			}
		}
	}
}

void Registeration::Dialogs::RegisterPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_REGISTER_PASSWORD)
	{
		if(response)
		{
			if(inputtext.length() >= 8 && inputtext.length() <= 16)
			{
				strcpy(Account::Player_Database[playerid].password, inputtext.c_str());
				OpenRegisterPannel(playerid);
			}
			else
			{
				memset(Account::Player_Database[playerid].password, 0, sizeof(Account::Player_Database[playerid].password));
				sampgdk::SendClientMessage(playerid, -1, "Password is > 8 or < 16");
				OpenRegisterPassword(playerid);
			}
		}
		else
		{
			OpenRegisterPannel(playerid);
		}
	}
}

void Registeration::Dialogs::RegisterBackupPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_REGISTER_BACKUPPASSWORD)
	{
		if(response)
		{
			if(inputtext.length() >= 8 && inputtext.length() <= 16)
			{
				strcpy(Account::Player_Database[playerid].backup_password, inputtext.c_str());
				OpenRegisterPannel(playerid);
			}
			else
			{
				memset(Account::Player_Database[playerid].backup_password, 0, sizeof(Account::Player_Database[playerid].backup_password));
				sampgdk::SendClientMessage(playerid, -1, "Password is < 8 or > 16");
				OpenRegisterBackupPassword(playerid);
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
			int16_t age = std::stol(inputtext, &idx, 10);
			if(age >= 13 && age <= 100)
			{
				Account::Player_Database[playerid].age = age;
				OpenRegisterPannel(playerid);
			}
			else
			{
				Account::Player_Database[playerid].age = 0;
				sampgdk::SendClientMessage(playerid, -1, "Age is < 13 or > 100");
				OpenRegisterAge(playerid);
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
			int16_t gender = std::stol(inputtext, &idx, 10);
			if(gender == 1 || gender == 2)
			{
				Account::Player_Database[playerid].gender = gender;
				OpenRegisterPannel(playerid);
			}
			else
			{
				Account::Player_Database[playerid].gender = 0;
				sampgdk::SendClientMessage(playerid, -1, "Gender is 0 or 1");
				OpenRegisterGender(playerid);
			}
		}
		else
		{
			OpenRegisterPannel(playerid);
		}
	}
}


void Registeration::Dialogs::LoginPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_LOGIN_PASSWORD)
	{
		if(response)
		{
			if(inputtext.length() >= 8 && inputtext.length() <= 16)
			{
				strcpy(Account::Player_Database[playerid].password, inputtext.c_str());
				OpenLoginPannel(playerid);
			}
			else
			{
				memset(Account::Player_Database[playerid].password, 0, sizeof(Account::Player_Database[playerid].password));
				sampgdk::SendClientMessage(playerid, -1, "Password is > 8 or < 16");
				OpenLoginPassword(playerid);
			}
		}
		else
		{
			OpenLoginPannel(playerid);
		}
	}
}

void Registeration::Dialogs::LoginBackupPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_LOGIN_PASSWORD)
	{
		if(response)
		{
			if(inputtext.length() >= 8 && inputtext.length() <= 16)
			{
				strcpy(Account::Player_Database[playerid].password, inputtext.c_str());
				OpenLoginPannel(playerid);
			}
			else
			{
				memset(Account::Player_Database[playerid].password, 0, sizeof(Account::Player_Database[playerid].password));
				sampgdk::SendClientMessage(playerid, -1, "Password is > 8 or < 16");
				OpenLoginPassword(playerid);
			}
		}
		else
		{
			OpenLoginPannel(playerid);
		}
	}
}