#include "menus.h"
#include "Manager.h"
#include "Windows.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Manager manager;
	return mainMenu(manager);
}
