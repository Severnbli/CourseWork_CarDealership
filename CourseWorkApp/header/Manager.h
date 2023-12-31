﻿#pragma once
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

	void workingEmployeeWithProfiles(std::shared_ptr<User>&);

	void customizeClientProfile(std::shared_ptr<User>&);

	void customizeEmloyeeProfile(std::shared_ptr<User>&);

	void workingEmployeeWithCatalog(const std::shared_ptr<User>&);

	void workingClientWithCatalog(const std::shared_ptr<User>&);

	void workingEmployeeWithReceipts();

	void workingClientWithFavorites(const std::shared_ptr<User>&);

	void generateReports() const;

private:
	Database database_;
};