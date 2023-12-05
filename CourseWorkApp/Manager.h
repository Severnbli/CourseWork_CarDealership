#pragma once
#include "Database.h"

class Manager
{
public:
	Manager() = default;

	Manager(const Manager&);

	~Manager() = default;

	void beginRegistration();

	void beginAuthorization(bool&, std::shared_ptr<User>&);

	int workingWithProfiles(std::shared_ptr<User>&);

	int customizeAuthorizedUserProfile(std::shared_ptr<User>&);

	int workingWithCatalog();

private:
	Database database_;
};