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
	auto *map = new HashMap<const char*,char>();
	map->insert("123", 'h');
	map->insert("456", 'f');
	map->insert("789", 'y');
	std::cout << map->getValue("123") << '\n';
	std::cout << map->getValue("456") << '\n';
	std::cout << map->getValue("789") << '\n';
	delete map;
	map = nullptr;
	getchar();
	return 0;
}