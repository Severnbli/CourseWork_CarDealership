#pragma once

class Date
{
public:
	Date() = default;
	Date(int, int, int);
	~Date() = default;
	Date(const Date&);
	void setDay(int);
	int getDay() const;
	void setMonth(int);
	int getMonth() const;
	void setYear(int);
	int getYear() const;
private:
	int day_ = 0;
	int month_ = 0;
	int year_ = 0;
};