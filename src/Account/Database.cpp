#include "../../core/Account/Database.h"

using namespace Account;
using namespace FileEngine;

int Database::Load(Data &data)
{
	INI::File file(data.filename, ".ini");
	file.SetCurrentSection("Main Account");
	if(file.Exists())
	{
		INI::Reader::Section_Structure reader(&file);
		reader.ReadCString("Filename", data.filename);
		reader.ReadCString("Password", data.password);
		reader.ReadCString("Backup_Password", data.backup_password);
		reader.ReadShort("Age", &data.age);
		reader.ReadShort("Gender", &data.gender);
		reader.ReadBool("Is_Regestired", &data.is_regesitired);
		return 0;
	}
	else
	{
		return -1;
	}
	return -2;
}

int Database::Save(Data &data)
{
	INI::File file(data.filename, ".ini");
	file.SetCurrentSection("Main Account");
	if(file.Exists())
	{
		INI::Writter::Section_Structure writter(&file);
		writter.WriteCString("Filename", data.filename);
		writter.WriteCString("Password", data.password);
		writter.WriteCString("Backup_Password", data.backup_password);
		writter.WriteShort("Age", &data.age);
		writter.WriteShort("Gender", &data.gender);
		writter.WriteBool("Is_Regestired", &data.is_regesitired);
		return 0;
	}
	else
	{
		return -1;
	}
	return -2;
}