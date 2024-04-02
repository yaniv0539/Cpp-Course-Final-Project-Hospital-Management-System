#ifndef __DATE_H
#define __DATE_H

#include <fstream>
#include <iostream>

class Date
{
public:
	const enum eMonths {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

private:
	int	m_day;
	eMonths	m_month;
	int	m_year;
	static constexpr int MIN_YEAR = 0;
	static constexpr int MAX_YEAR = 9999;

public:
	// C'tors
	Date(int day = 1, int month = JAN, int year = 2000) noexcept(false);
	Date(const Date& other) = default;
	Date(std::ifstream& in) noexcept;

	// Get Functions
	int getDay() const noexcept;
	int getMonth() const noexcept;
	int getYear() const noexcept;

	// Set Functions
	void setDate(int day, int month, int year) noexcept(false);

	// Show Functions
	void show(std::ostream& os = std::cout) const noexcept;
	
	// Operator Functions
	friend std::ostream& operator<<(std::ostream& os, const Date& date) noexcept;
	friend std::istream& operator>>(std::istream& in, Date& date) noexcept;

private:
	void checkValidDate(int day, eMonths month, int year) noexcept(false);
};

#endif // __DATE_H