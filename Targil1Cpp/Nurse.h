#ifndef __NURSE_H
#define __NURSE_H

#include <iostream>
#include <fstream>
#include <string>
#include "Employee.h"

class Nurse : public Employee
{
private:
	int m_nofExperience;

public:
	// C'tors
	Nurse(const std::string& name, int nofExperience) noexcept(false);
	Nurse(std::ifstream& in) noexcept;

	// Get Functions
	int getNofExperience() const noexcept;

	// Set Functions
	void setNofExperience(int nofExperience) noexcept(false);

	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override;
	virtual void fromOs(std::istream& in) noexcept override;
	
	// Other Functions
	virtual Employee* clone() const noexcept override;
	
	// Deleted Functions
	const Nurse& operator=(const Nurse&) = delete;

protected:
	// C'tors
	Nurse(const Nurse&) = default;
	Nurse(Nurse&&) = default;
};
#endif // __NURSE_H