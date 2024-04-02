#ifndef __SURGEON_H
#define __SURGEON_H

#include <iostream>
#include <fstream>
#include <string>
#include "Doctor.h"

class Surgeon : virtual public Doctor
{
protected:
	int m_nofSurgeries;

public:
	// C'tors
	Surgeon(const Doctor& doctor, int m_nofSurgeries) noexcept(false);
	Surgeon(const std::string& name, const std::string& expertField, int m_nofSurgeries) noexcept(false);
	Surgeon(std::ifstream& in) noexcept;

	// Get Functions
	int getNofSurgeries() const noexcept;

	// Set Functions
	void setNofSurgeries(int m_nofSurgeries) noexcept(false);
	
	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override;
	virtual void fromOs(std::istream& in) noexcept override;

	// Other Functions
	virtual Employee* clone() const noexcept override;

	// Deleted Functions
	const Surgeon& operator=(const Surgeon& other) = delete;

protected:
	// C'tors
	Surgeon(const Surgeon& surgeon) = default;
	Surgeon(Surgeon&& surgeon) = default;
};

#endif // __SURGEON_H
