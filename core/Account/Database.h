#if !defined _PROJECT_SAMPLE_GM_ACCOUNT_DATABASE_H_
#define _PROJECT_SAMPLE_GM_ACCOUNT_DATABASE_H_

#include "../../include/lfile-ini/iem-ini.h"
#include "Data.h"

namespace Account
{
	class Database
	{
	public:
		int Load(Data &data);
		int Save(Data &data);
	};
}
#endif