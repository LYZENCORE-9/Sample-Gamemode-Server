#include "../../core/Account/Registeration_System.h"
#include <cassert>
#include <cstdio>

using namespace Account;
using namespace FileEngine;

bool Registeration::System::Register(int playerid, Data &data)
{
	char user_name[25] = {0};
	sampgdk::GetPlayerName(playerid, user_name, sizeof(user_name));
	sprintf(data.filename, "[%d]-(%s)", data.id, user_name);

	INI::File file(data.filename, ".ini");
	if(data.is_regesitired == false && !file.Exists())
	{
		data.is_regesitired = true;
		file.Create();
		INI::Writter::Section_Structure writter(&file);
		writter.WriteCString("Filename", data.filename);
		writter.WriteCString("Password", data.password);
		writter.WriteCString("Backup_Password", data.backup_password);
		writter.WriteShort("Age", &data.age);
		writter.WriteShort("Gender", &data.gender);
		writter.WriteBool("Is_Regestired", &data.is_regesitired);
		return true;
	}
	else
	{
		assert("Condition goes false");
		return false;
	}
}

bool Registeration::System::Login(int playerid, Data &data)
{
	char user_name[25] = {0};
	sampgdk::GetPlayerName(playerid, user_name, sizeof(user_name));

	sprintf(data.filename, "[%d]-(%s)", data.id, user_name);
	INI::File file(data.filename, ".ini");
	if(file.Exists())
	{
		INI::Reader::Section_Structure reader(&file);
		reader.ReadCString("Filename", data.filename);
		reader.ReadCString("Password", data.password);
		reader.ReadCString("Backup_Password", data.backup_password);
		reader.ReadShort("Age", &data.age);
		reader.ReadShort("Gender", &data.gender);
		reader.ReadBool("Is_Regestired", &data.is_regesitired);
		return true;
	}
	else
	{
		assert("Condition goes false");
		return false;
	}

}