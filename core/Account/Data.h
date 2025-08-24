#include <cstdint>
#include <cstring>
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

		char Characters[5][128] = {{0}};

		void reset()
		{
			id = 0;
			memset(filename, 0, sizeof(filename));
			memset(password, 0, sizeof(password));
			memset(backup_password, 0, sizeof(backup_password));
			age = 0;
			gender = 0;
			is_regesitired = false;
			is_logged = false;
		}
	};

	inline Data Player_Database[1000];
}

#endif