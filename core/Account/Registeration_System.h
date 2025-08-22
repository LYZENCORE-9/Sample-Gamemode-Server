#if !defined _PROJECT_SAMPLE_GM_ACCOUNT_REGISTERATION_SYSTEM_H_
#define _PROJECT_SAMPLE_GM_ACCOUNT_REGISTERATION_SYSTEM_H_

#include "Data.h"
#include "../../include/lfile-ini/iem-ini.h"
#include "../../include/mini/ini.h"
#include "../../include/sampgdk/samp.h"
#include "../../include/sampgdk/players.h"

namespace Account::Registeration
{
	class System
	{
	public:
		static bool Register(int playerid, Data &data);
		static bool Login(int playerid, Data &data);
	};
}
#endif