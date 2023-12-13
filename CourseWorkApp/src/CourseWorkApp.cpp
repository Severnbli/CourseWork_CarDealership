#include "../header/menus.h"
#include "../header/Manager.h"
#include "Windows.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Manager manager;
	return mainMenu(manager);
}
