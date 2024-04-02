#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H

#include <iostream>
#include <fstream>
#include "Person.h"

// Abstract class
class Employee : public Person
{
protected:
	static int s_cnt;
	int m_employee_id;

public:
	// C'tors
	Employee(const std::string& name) noexcept(false);
	Employee(std::ifstream& in) noexcept;

	// Get Functions
	int getEmployeeId() const noexcept;

	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override = 0;
	virtual void fromOs(std::istream& os) noexcept override;

	// Other functions
	virtual Employee* clone() const noexcept = 0;
	static int getLastEmployeeID() noexcept { return s_cnt; }

	friend class Hospital;
};

// Object Function
class ltEmployeeID
{
public:
	bool operator()(const Employee* pEmp1, const Employee* pEmp2) const noexcept 
	{ 
		return pEmp1->getEmployeeId() < pEmp2->getEmployeeId();
	}
};
//----------------------------------------------------------------------------------------------------------------------------------------------

#endif // __EMPLOYEE_H


