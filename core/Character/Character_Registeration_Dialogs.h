#if !defined _PROJECT_SAMPLE_GM_CHARACTER_REGISTERATION_DIALOGS_H_
#define _PROJECT_SAMPLE_GM_CHARACTER_REGISTERATION_DIALOGS_H_

#include "../../include/mini/ini.h"

#include "../../include/sampgdk/samp.h"
#include "../../include/sampgdk/players.h"

#include "Data.h"
#include "Character_Registeration_System.h"
#include "../Account/Data.h"


namespace Character::Registeration
{
	class Dialogs
	{
	public:
		static const int ID_MAIN_PANNEL = 20008;
		static const int ID_REGISTER_NAME = ID_MAIN_PANNEL+1;
		static const int ID_REGISTER_AGE = ID_REGISTER_NAME+1;
		static const int ID_REGISTER_GENDER = ID_REGISTER_AGE+1;

		static const int ID_LOGIN_PANNEL = ID_REGISTER_GENDER+1;
		static const int ID_REGISTER_PANNEL = ID_LOGIN_PANNEL+1;

		static inline char player_characters_string[1024] = {0};

		static inline bool register_name_check = false;
		static inline bool register_age_check = false;
		static inline bool register_gender_check = false;

		static void OpenMainPannel(int playerid);
		static void OpenRegisterPannel(int playerid);
		static void OpenRegisterName(int playerid);
		static void OpenRegisterAge(int playerid);
		static void OpenRegisterGender(int playerid);

		static void OpenLoginPannel(int playerid);



		// Response

		static void Response(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);

		static void MainPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterNameResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterAgeResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);
		static void RegisterGenderResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);

		static void LoginPannelResponse(int playerid, int dialogid, bool response, int listitem, const std::string &inputtext);


	};
}

#endif