#include <cstdint>
#include <cstring>
#if !defined _PROJECT_SAMPLE_GM_CHARACTER_DATA_H_
#define _PROJECT_SAMPLE_GM_CHARACTER_DATA_H_

namespace Character
{
	const short MAX_CHARACTER_ACCOUNTS = 5;
	struct Data
	{
		uint32_t id = 0;
		char name[24+1] = {0};
		char filename[128] = {0};
		short age = 0;
		short gender = 0;
		bool is_logged = false;

		void reset()
		{
			id = 0;
			memset(name, 0, sizeof(name));
			memset(filename, 0, sizeof(filename));
			age = 0;
			gender = 0;
			is_logged = false;
		}
	};

	inline Data Player_Characters[1000];
}

#endif