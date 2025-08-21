#include <cstdint>
#if !defined _PROJECT_SAMPLE_GM_ACCOUNT_DATA_H_
#define _PROJECT_SAMPLE_GM_ACCOUNT_DATA_H_

namespace Account
{
	struct Data
	{
		uint32_t id = 0;
		char filename[128] = {0};
		char password[128] = {0};
		char backup_password[128] = {0};
		short age = 0;
		short gender = 0;
		bool is_regesitired = false;
		bool is_logged = false;
	};

	inline Data Player_Database[1000];
}

#endif