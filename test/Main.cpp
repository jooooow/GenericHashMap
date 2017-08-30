#define DEBUG
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "HashMap.h"

#ifdef DEBUG
inline void enableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}
#endif

int main()
{
#ifdef DEBUG
	enableMemLeakCheck();
#endif
	HashMap *map = new HashMap();
	map->insert(1, "hello");
	map->insert(2, "fuck");
	map->insert(17, "you");
	std::cout << map->getValue(1) << '\n';
	std::cout << map->getValue(2) << '\n';
	std::cout << map->getValue(17) << '\n';
	delete map;
	map = nullptr;
	getchar();
	return 0;
}