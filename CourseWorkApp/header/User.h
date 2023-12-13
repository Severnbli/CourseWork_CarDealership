#pragma once
#include <future>
#include <string>
#include <vector>

class User
{
public:
	User();

	User(int);

	User(const std::string&, const std::string&, const std::string& = "");

	User(const User&);

	virtual ~User() = default;

	bool operator<(const User&) const;

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

	virtual void printInfoTableForm() const = 0;

	virtual bool isAdmin() const = 0;

	virtual int getDimensionality() = 0;

	virtual void setInfoInVectorStringForm(const std::vector<std::string>&) = 0;

	virtual std::vector<std::string> getInfoInVectorStringForm() = 0;

	void setUniqueId_(const std::string&);

	std::string getUniqueId() const;

private:
	std::string username_;

	std::string password_;

	std::string fio_;

	std::string uniqueId_;
};

bool compareUsersByUsername(const User&, const User&);

bool compareUsersByUsername(const std::shared_ptr<User>&, const std::shared_ptr<User>&);

bool compareUsersByFio(const User&, const User&);

bool compareUsersByFio(const std::shared_ptr<User>&, const std::shared_ptr<User>&);

bool compareUsersByAdmin(const User&, const User&);

bool compareUsersByAdmin(const std::shared_ptr<User>&, const std::shared_ptr<User>&);
