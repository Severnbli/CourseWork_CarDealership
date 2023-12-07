﻿#pragma once
#include <string>
#include <vector>

class User
{
public:
	User() = default;

	User(int);

	User(const std::string&, const std::string&, const std::string& = "");

	User(const User&);

	void setUsername(const std::string&);

	void functionalSetUsername();

	std::string getUsername() const;

	void setUnmodifiedPassword(const std::string&);

	void setPassword(const std::string&);

	void functionalSetPassword();

	std::string getPassword() const;

	void setFio(const std::string&);

	void functionalSetFio();

	std::string getFio() const;

	virtual bool isAdmin() const = 0;

	virtual int getDimensionality() = 0;

	virtual void setInfoInVectorStringForm(const std::vector<std::string>&) = 0;

	virtual std::vector<std::string> getInfoInVectorStringForm() = 0;

private:
	std::string username_;

	std::string password_;

	std::string fio_;
};
