#pragma once
#include "Database.h"

class Manager
{
public:
	Manager() = default;

	Manager(const Manager&);

	~Manager() = default;

	void beginRegistration();

	void beginAuthorization(bool&, std::shared_ptr<User>&) const;

	void workingWithEmployeeProfile(std::shared_ptr<User>&);

	void workingWithProfiles(std::shared_ptr<User>&);

	void customizeEmloyeeProfile(std::shared_ptr<User>&);

	int workingWithCatalog();

private:
	Database database_;
};