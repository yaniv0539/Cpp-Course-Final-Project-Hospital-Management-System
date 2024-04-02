#ifndef __SURGEON_RESEARCHER_H
#define __SURGEON_RESEARCHER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Array.h"
#include "Surgeon.h"
#include "DoctorResearcher.h"

class SurgeonResearcher : public Surgeon, public DoctorResearcher 
{
public:
	// C'tors
	SurgeonResearcher(const Surgeon& surgeon, const DoctorResearcher& doctor_researcher) noexcept;
	SurgeonResearcher(const std::string& name, const std::string& expertField, const Array<Article*>& articles, int nofSurgeons) noexcept(false);
	SurgeonResearcher(const std::string& name, const std::string& expertField, int nofSurgeons) noexcept(false);
	SurgeonResearcher(std::ifstream& in) noexcept;
	virtual Employee* clone() const noexcept override;

	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override;

	// Deleted Functions
	const SurgeonResearcher& operator=(const SurgeonResearcher&) = delete;
	
protected:
	// C'tors
	SurgeonResearcher(const SurgeonResearcher& surgeon_researcher) = default;
	SurgeonResearcher(SurgeonResearcher&& surgeon_researcher) = default;
	virtual void fromOs(std::istream& in) noexcept override {}
};

#endif // __SURGEON_RESEARCHER_H
