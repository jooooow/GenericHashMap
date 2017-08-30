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
	auto *map = new HashMap<char,char>();
	map->insert('1', 'h');
	map->insert('2', 'f');
	map->insert('7', 'y');
	std::cout << map->getValue('1') << '\n';
	std::cout << map->getValue('2') << '\n';
	std::cout << map->getValue('7') << '\n';
	delete map;
	map = nullptr;
	getchar();
	return 0;
}