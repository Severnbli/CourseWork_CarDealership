#pragma once

#include <array>
#include <string>

class Date {
public:
    Date() = default;

	Date(int, int, int);

	Date(const Date&);

	~Date() = default;

	Date& operator=(const Date&);

	bool operator==(const Date&) const;

	bool operator!=(const Date&) const;

	bool operator<(const Date&) const;

	bool operator>(const Date&) const;

	void functionalSetInfo();

	void setInfo(int, int, int);

	void setInfoInVectorStringForm(const std::vector<std::string>&);

	void getInfo() const noexcept;

	std::vector<std::string> getInfoInVectorStringForm();

	std::array<int, 3> getFunctionalInfo() const noexcept;

	void getAdditionalInfo() noexcept;

	void functionalSetDay();

	void setDay(int);

	int getDay() const noexcept;

	void functionalSetMonth();

	void setMonth(int);

	int getMonth() const noexcept;

	static std::string defineMonth(int);

	void functionalSetYear(int = 2023);

	void setYear(int);

	int getYear() const noexcept;

	static std::string defineYear(int);

	static size_t getDimensionality();

private:
	static size_t dimensionality_;

    int day_ = 1;

	int month_ = 1;

	int year_ = 1983;
};