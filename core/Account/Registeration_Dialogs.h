#include <string>
#if !defined _PROJECT_SAMPLE_GM_ACCOUNT_REGISTERATION_DIALOGS_H_
#define _PROJECT_SAMPLE_GM_ACCOUNT_REGISTERATION_DIALOGS_H_

#include "../../include/sampgdk/samp.h"
#include "../../include/sampgdk/players.h"
#include "Registeration_System.h"

namespace Account::Registeration 
{
	class Dialogs
	{
	public:

		static const int ID_REGISTER_PANNEL = 20000;
		static const int ID_REGISTER_PASSWORD = ID_REGISTER_PANNEL+1;
		static const int ID_REGISTER_BACKUPPASSWORD = ID_REGISTER_PASSWORD+1;
		static const int ID_REGISTER_AGE = ID_REGISTER_BACKUPPASSWORD+1;
		static const int ID_REGISTER_GENDER = ID_REGISTER_AGE+1;


		static const int ID_LOGIN_PANNEL = ID_REGISTER_GENDER+1;
		static const int ID_LOGIN_PASSWORD = ID_LOGIN_PANNEL+1;
		static const int ID_LOGIN_BACKUPPASSWORD = ID_REGISTER_PASSWORD+1;

		static void OpenRegisterPannel(int playerid);
		static void OpenRegisterPassword(int playerid);
		static void OpenRegisterBackupPassword(int playerid);
		static void OpenRegisterAge(int playerid);
		static void OpenRegisterGender(int playerid);

		static void OpenLoginPannel(int playerid);
		static void OpenLoginPassword(int playerid);
		static void OpenLoginBackupPassword(int playerid);

		static void Response(int dialog_id);

		static void RegisterPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterBackupPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterAgeResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterGenderResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);

		static void LoginPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void LoginPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void LoginBackupPasswordResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);

	};
}

#endif