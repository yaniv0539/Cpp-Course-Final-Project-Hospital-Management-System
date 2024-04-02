#include "Date.h"
using namespace std;

Date::Date(int day, int month, int year) noexcept(false)
{
    setDate(day, month, year);
}

Date::Date(ifstream& in) noexcept
{
    in >> *this;
}

int Date::getDay() const noexcept
{
    return m_day; 
}

int Date::getMonth() const noexcept
{
    return m_month; 
}

int Date::getYear() const noexcept
{
    return m_year;
}

void Date::setDate(int day, int month, int year) noexcept(false)
{
    checkValidDate(day, (eMonths)month, year);
    m_day = day;
    m_month = (eMonths)month;
    m_year = year;
}

void Date::show(ostream& os) const noexcept
{
    os << m_day << "/" << m_month << "/" << m_year;
}

ostream& operator<<(ostream& os, const Date& date) noexcept
{
    if (typeid(os) == typeid(ofstream))
    {
        os << date.m_day << " " << date.m_month << " " << date.m_year; 
    }
    else
    {
        date.show();
    }
    return os;
}

istream& operator>>(istream& in, Date& date) noexcept
{
    if (typeid(in) == typeid(ifstream))
    {
        int temp_month;
        in >> date.m_day >> temp_month >> date.m_year;
        date.m_month = (Date::eMonths)temp_month;
    }
    return in;
}

void Date::checkValidDate(int day, eMonths month, int year) noexcept(false)
{
    bool valid = false;
    if ((year >= MIN_YEAR) && (year <= MAX_YEAR))
    {
        // checking if the month has 31 days.
        if ((month == JAN) || (month == MAR) || (month == MAY) || (month == JUL)
            || (month == AUG) || (month == OCT) || (month == DEC))
        {
            if ((day <= 31) && (day >= 0))
            {
                valid = true;
            }
        }
        // checking if the month has 30 days.
        if ((month == APR) || (month == JUN) || (month == SEP) || (month == NOV))
        {
            if ((day <= 30) && (day >= 0))
            {
                valid = true;
            }
        }
        // checking if the month has 28 days or 29 days in a leap year.
        if (month == FEB)
        {
            if ((day >= 0) && (day <= 28))
            {
                valid = true;
            }
            else if ((day == 29) &&
                (((year % 4 == 0) && (year % 100 != 0)) || (year % 100 == 0 && year % 400 == 0)))
            {
                valid = true;
            }
        }
    }
    if (!valid) 
        throw invalid_argument("Invalid date...");
}