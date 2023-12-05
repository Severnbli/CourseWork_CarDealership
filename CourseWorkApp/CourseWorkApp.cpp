#include "menus.h"
#include "Manager.h"
#include "Windows.h"

//#include "Client.h"
//#include <iostream>
//#include "Employee.h"
//#include "Car.h"
//#include "User.h"
//#include <vector>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*std::vector<User> users;
	users.emplace_back(Client());
	users.emplace_back(Employee());
	std::cout << Car::getDimensionality() << std::endl;*/
	Manager manager;
	return mainMenu(manager);
}
