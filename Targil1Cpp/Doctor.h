#ifndef __DOCTOR_H
#define __DOCTOR_H

#include <iostream>
#include <fstream>
#include <string>
#include "Employee.h"

class Doctor : virtual public Employee
{
protected:
	std::string m_expertField;

public:
	// C'tors
	Doctor(const std::string& name, const std::string& expertField) noexcept(false);
	Doctor(std::ifstream& in) noexcept;
	virtual ~Doctor() = default;

	// Get Functions
	const std::string& getExpertField() const noexcept;
	
	// Set Functions
	void setExpertField(const std::string& expertField) noexcept(false);

	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override;
	virtual void fromOs(std::istream& in) noexcept override;
	
	// Other Functions
	virtual Employee* clone() const noexcept override;

	// Deleted Functions
	const Doctor& operator=(const Doctor& other) = delete;

protected:
	// C'tors
	Doctor(const Doctor& other) noexcept;
	Doctor(Doctor&& other) noexcept;
};

#endif // __DOCTOR_H