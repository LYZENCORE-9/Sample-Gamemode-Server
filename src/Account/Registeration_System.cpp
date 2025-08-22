#include "../../core/Account/Registeration_System.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

using namespace Account;
using namespace FileEngine;

bool Registeration::System::Register(int playerid, Data &data)
{
	char user_name[25] = {0};
	sampgdk::GetPlayerName(playerid, user_name, sizeof(user_name));
	sprintf(data.filename, "[%d]-(%s).ini", data.id, user_name);

	 sampgdk::SendClientMessage(playerid, -1, "Register Declared !");

	FILE *handle = fopen(data.filename, "r");
	
	//if(data.is_regesitired == false && handle == NULL)
	if(handle == NULL)
	{
		mINI::INIFile file(data.filename);
        mINI::INIStructure ini;
        
        data.is_regesitired = true;

        ini["Main Account"]["Filename"] = std::string(data.filename);
        ini["Main Account"]["Password"] = std::string(data.password);
        ini["Main Account"]["Backup Password"] = std::string(data.backup_password);
        ini["Main Account"]["Age"] = std::to_string(data.age);        // Convert to string
        ini["Main Account"]["Gender"] = std::to_string(data.gender);  // Convert to string
        ini["Main Account"]["Registired"] = data.is_regesitired ? "1" : "0";  // Convert to string
        
         sampgdk::SendClientMessage(playerid, -1, "IF Registration Declared");
        if(file.write(ini))
        {
            sampgdk::SendClientMessage(playerid, -1, "Registration successful!");
            return true;
        }
        else
        {
            sampgdk::SendClientMessage(playerid, -1, "Registration failed - file write error!");
            return false;
        }
			
		///writter.WriteCString("Filename", data.filename);
		//writter.WriteCString("Password", data.password);
		//writter.WriteCString("Backup_Password", data.backup_password);
		//writter.WriteShort("Age", &data.age);
		//writter.WriteShort("Gender", &data.gender);
		//writter.WriteBool("Registired", &data.is_regesitired);/
		return true;
	}
	else
	{
		 sampgdk::SendClientMessage(playerid, -1, "Else Declared");
		//assert("Condition goes false");
		fclose(handle);
		return false;
	}
}


bool Registeration::System::Login(int playerid, Data &data)
{
	char user_name[sampgdk::MAX_PLAYER_NAME] = {0};
	char password_check[128] = {0};
	sampgdk::GetPlayerName(playerid, user_name, sizeof(user_name));

	sprintf(data.filename, "[%d]-(%s).ini", data.id, user_name);
	
	FILE *handle = fopen(data.filename, "r");
	size_t idx = 0;


	if(handle != NULL)
	{
		fclose(handle);
		mINI::INIFile file(data.filename);
		mINI::INIStructure ini;
		file.read(ini);
		sampgdk::SendClientMessage(playerid, -1, "Login Declared");	
		strncpy(password_check, ini["Main Account"]["Password"].c_str(), sizeof(password_check));
		
		if(strcmp(password_check, data.password) == 0)
		{
			memset(password_check, 0, sizeof(password_check));
			strcpy(data.backup_password, ini["Main Account"]["Backup Password"].c_str());	
			data.age = std::stoi(ini["Main Account"]["Age"], &idx, 10);
			data.gender = std::stoi(ini["Main Account"]["Gender"], &idx, 10);
			data.is_regesitired = std::stoi(ini["Main Account"]["Registired"], &idx, 10);
			sampgdk::SendClientMessage(playerid, -1, "{00FF00} Logged In !");
			return true;
		}
		else
		{
			memset(password_check, 0, sizeof(password_check));
			sampgdk::SendClientMessage(playerid, -1, "Wrong Password");
			sampgdk::Kick(playerid);
			return false;
		}

	}
	else
	{
		sampgdk::SendClientMessage(playerid, -1, "Else Declared");
		//fclose(handle);
		return false;
	}

}

/*
bool Registeration::System::Register(int playerid, Data &data)
{
    char user_name[sampgdk::MAX_PLAYER_NAME] = {0};
    sampgdk::GetPlayerName(playerid, user_name, sizeof(user_name));
    
    // Debug: Check player name
    char debug1[128];
    snprintf(debug1, sizeof(debug1), "Player name: '%s', ID: %d", user_name, data.id);
    sampgdk::SendClientMessage(playerid, -1, debug1);
    
    snprintf(data.filename, sizeof(data.filename), "[%d]-(%s).ini", data.id, user_name);
    
    // Debug: Check filename
    char debug2[256];
    snprintf(debug2, sizeof(debug2), "Filename: '%s'", data.filename);
    sampgdk::SendClientMessage(playerid, -1, debug2);

    // Check if file already exists
    FILE *handle = fopen(data.filename, "r");
    if(handle != NULL)
    {
        fclose(handle);
        sampgdk::SendClientMessage(playerid, -1, "Player already registered!");
        return false;
    }
    
    // Try to create INI
    try 
    {
        mINI::INIFile file(data.filename);
        mINI::INIStructure ini;
        
        data.is_regesitired = true;
        
        ini["Main Account"]["Filename"] = std::string(data.filename);
        ini["Main Account"]["Password"] = std::string(data.password);
        ini["Main Account"]["Backup Password"] = std::string(data.backup_password);
        ini["Main Account"]["Age"] = std::to_string(data.age);
        ini["Main Account"]["Gender"] = std::to_string(data.gender);
        ini["Main Account"]["Registired"] = "1";
        
        sampgdk::SendClientMessage(playerid, -1, "About to write file...");
        
        bool result = file.write(ini);
        if(result)
        {
            sampgdk::SendClientMessage(playerid, -1, "File write SUCCESS!");
            return true;
        }
        else
        {
            sampgdk::SendClientMessage(playerid, -1, "File write FAILED!");
            return false;
        }
    }
    catch(const std::exception& e)
    {
        sampgdk::SendClientMessage(playerid, -1, "Exception during file write!");
        return false;
    }
}*/