#include "../../core/Account/Registeration_Dialogs.h"
#include <cstdio>
#include <string>

using namespace Account;
using namespace FileEngine;


void Registeration::Dialogs::Check(int playerid)
{
	char user_name[sampgdk::MAX_PLAYER_NAME] = {0};
	char filename[128] = {0};
	bool is_regesitired_temp = false;

	sampgdk::GetPlayerName(playerid, user_name, sizeof(user_name));
	sprintf(filename, "Player-Database/[0]-(%s).ini", user_name);

	FILE* file_handle = fopen(filename, "r");
	size_t idx = 0;
	
	if(file_handle != NULL)
	{
		fclose(file_handle);
		mINI::INIFile file(filename);
		mINI::INIStructure ini;
		file.read(ini);
		std::string ret_value = ini["Main Account"]["Registired"];
		
		is_regesitired_temp = std::stoi(ret_value, &idx, 10);
		sampgdk::SendClientMessage(playerid, -1, ret_value.c_str());

		if(is_regesitired_temp == true)
		{
			OpenLoginPannel(playerid);
		}
		else
		{
			remove(filename);
			OpenRegisterPannel(playerid);
		}
	}
	else
	{
		OpenRegisterPannel(playerid);
	}
}


void Registeration::Dialogs::OpenRegisterPannel(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_PANNEL, sampgdk::DIALOG_STYLE_LIST, "Registeration Pannel (Register)", "[*] Password\n[*] Backup Password\n[*] Age\n[*] Gender\n{00FF00}[!] Apply", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_PASSWORD, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Password (1/4)", "Password", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterBackupPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_BACKUPPASSWORD, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Backup Password (2/4)", "Backup Password", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterAge(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_AGE, sampgdk::DIALOG_STYLE_INPUT, "Registeration Age (3/4)", "Age", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenRegisterGender(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_REGISTER_GENDER, sampgdk::DIALOG_STYLE_INPUT, "Registeration Gender (4/4)", "Gender", "Confirm", "Cancel");
}


void Registeration::Dialogs::OpenLoginPannel(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_LOGIN_PANNEL, sampgdk::DIALOG_STYLE_LIST, "Registeration Pannel (Login)", "[*] Password\n[*] Backup Password\n{00FF00}[!] Apply", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenLoginPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_LOGIN_PASSWORD, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Password (Login)", "Password 2", "Confirm", "Cancel");
}

void Registeration::Dialogs::OpenLoginBackupPassword(int playerid)
{
	sampgdk::ShowPlayerDialog(playerid, Dialogs::ID_LOGIN_BACKUPPASSWORD, sampgdk::DIALOG_STYLE_PASSWORD, "Registeration Backup Password (Login)", "Backup Password 2", "Confirm", "Cancel");
}

// Response

void Registeration::Dialogs::Response(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	RegisterPannelResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterPasswordResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterBackupPasswordResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterAgeResponse(playerid, dialogid, response, listitem, inputtext);
	RegisterGenderResponse(playerid, dialogid, response, listitem, inputtext);

	LoginPannelResponse(playerid, dialogid, response, listitem, inputtext);
	LoginPasswordResponse(playerid, dialogid, response, listitem, inputtext);
	LoginBackupPasswordResponse(playerid, dialogid, response, listitem, inputtext);
}

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
					OpenRegisterPassword(playerid);
					break;
				}
			case 1:
				{
					OpenRegisterBackupPassword(playerid);
					break;
				}
			case 2:
				{
					OpenRegisterAge(playerid);
					break;
				}
			case 3:
				{
					OpenRegisterGender(playerid);
					break;
				}
			case 4:
				{
					if(register_password_check == true && register_backup_password_check == true && register_age_check == true && register_gender_check == true)
					{
						register_password_check = false;
						register_backup_password_check = false;
						register_age_check = false;
						register_gender_check = false;

						sampgdk::SendClientMessage(playerid, -1, "Registired !");
						Registeration::System::Register(playerid, Account::Player_Database[playerid]);
					}
					else
					{
						sampgdk::SendClientMessage(playerid, -1, "Something Goes Wrong");
						OpenRegisterPannel(playerid);
					}
					break;
				}
			}
		}
	}
}

void Registeration::Dialogs::LoginPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext)
{
	if(dialogid == ID_LOGIN_PANNEL)
	{
		if(response)
		{
			switch(listitem)
			{
			case 0:
				{
					OpenLoginPassword(playerid);
					break;
				}
			case 1:
				{
					OpenLoginBackupPassword(playerid);
					break;
				}
			case 2:
				{
					if(login_password_check == true || login_backup_password_check == true)
					{
						login_password_check = false;
						login_backup_password_check = false;
						Registeration::System::Login(playerid, Account::Player_Database[playerid]);
					}
					else
					{
						sampgdk::SendClientMessage(playerid, -1, "Something Goes Wrong");
						OpenLoginPannel(playerid);
					}
					break;
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
				register_password_check = true;
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
				register_backup_password_check = true;
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
				register_age_check = true;
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
				register_gender_check = true;
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
			if(login_backup_password_check == true)
			{
				OpenLoginPannel(playerid);
				sampgdk::SendClientMessage(playerid, -1, "Backup Password Already defined !");
			}

			if(inputtext.length() >= 8 && inputtext.length() <= 16)
			{
				strcpy(Account::Player_Database[playerid].password, inputtext.c_str());
				login_password_check = true;
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
	if(dialogid == ID_LOGIN_BACKUPPASSWORD)
	{
		if(response)
		{
			if(login_password_check == true)
			{
				OpenLoginPannel(playerid);
				sampgdk::SendClientMessage(playerid, -1, "Password Already defined !");
			}

			if(inputtext.length() >= 8 && inputtext.length() <= 16)
			{
				strcpy(Account::Player_Database[playerid].password, inputtext.c_str());
				login_backup_password_check = true;
				OpenLoginBackupPassword(playerid);
			}
			else
			{
				memset(Account::Player_Database[playerid].password, 0, sizeof(Account::Player_Database[playerid].password));
				sampgdk::SendClientMessage(playerid, -1, "Password is > 8 or < 16");
				OpenLoginBackupPassword(playerid);
			}
		}
		else
		{
			OpenLoginPannel(playerid);
		}
	}
}