#ifndef __DOCTOR_RESEARCHER_H
#define __DOCTOR_RESEARCHER_H

#include "Doctor.h"
#include "Researcher.h"
#include "Array.h"
#include <iostream>
#include <fstream>

class DoctorResearcher : virtual public Doctor, virtual public Researcher
{
public:
	// C'tors
	DoctorResearcher(const Doctor& doctor, const Researcher& researcher) noexcept;
	DoctorResearcher(const std::string& name, const std::string& expertField, const Array<Article*>& articles) noexcept(false);
	DoctorResearcher(const std::string& name, const std::string& expertField) noexcept(false);
	DoctorResearcher(std::ifstream& in) noexcept;
	virtual ~DoctorResearcher() = default;

	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override;

	// Other Functions
	virtual Employee* clone() const noexcept override;

	// Deleted Functions
	const DoctorResearcher& operator=(const DoctorResearcher& other) = delete;

protected:
	// C'tors
	DoctorResearcher(const DoctorResearcher& doctor_researcher) = default;
	DoctorResearcher(DoctorResearcher&& doctor_researcher) = default;
	virtual void fromOs(std::istream& in) noexcept override {}
};

#endif // __DOCTOR_RESEARCHER_H
