#if !defined _PROJECT_SAMPLE_GM_CHARACTER_REGISTERATION_SYSTEM_H_
#define _PROJECT_SAMPLE_GM_CHARACTER_REGISTERATION_SYSTEM_H_

#include "../../include/mini/ini.h"
#include "Data.h"
#include "../Account/Data.h"
#include "../../include/sampgdk/samp.h"
#include "../../include/sampgdk/players.h"

namespace Character::Registeration
{
	class System
	{
	public:
		static bool Register(int playerid, Character::Data data);
		static bool Login(int playerid, Character::Data data);
	};
}

#endif