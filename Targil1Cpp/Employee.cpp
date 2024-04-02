#include "Employee.h"
using namespace std;
int Employee::s_cnt = 100;

Employee::Employee(const string& name) noexcept(false) : Person(name), m_employee_id(s_cnt++)
{
}

Employee::Employee(ifstream& in) noexcept : Person(in)
{
	fromOs(in);
}

int Employee::getEmployeeId() const noexcept
{
	return m_employee_id; 
}

void Employee::toOs(ostream& os) const noexcept
{
	if (typeid(os) == typeid(ofstream))
		os << m_employee_id << " ";
	else
		os << ", Employee ID: " << m_employee_id;
}

void Employee::fromOs(istream& in) noexcept
{
	in >> m_employee_id;
}