#pragma once
#include <string>

class User
{
public:
	User() = default;
	User(const std::string&, const std::string&, const std::string&);
	User(const User&);
	~User() = default;
	void setUsername(const std::string&);
	std::string getUsername() const;
	void setPassword(const std::string&);
	std::string getPassword() const;
	void setFio(const std::string&);
	std::string getFio() const;
	virtual bool isAdmin() const = 0;
private:
	std::string username_ = "";
	std::string password_ = "";
	std::string fio_ = "";
};