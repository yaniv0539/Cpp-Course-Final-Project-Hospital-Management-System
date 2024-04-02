#ifndef __RESEARCH_INSTITUTE_H
#define __RESEARCH_INSTITUTE_H

#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "SurgeonResearcher.h"
class Hospital;

class ResearchInstitute
{
private:
	std::set<Researcher*> m_researchers;
	Hospital* m_hospital;
	int m_pureResearchers;

public:
	// Get Functions
	const std::set<Researcher*>& getAllResearchers() const noexcept;
	std::set<Researcher*>& getAllResearchers() noexcept;

	// Search Functions
	Researcher* searchResearcher(int researcher_id) const noexcept;
	
	// Show Functions
	void showResearchers() const noexcept;
	void showDoctorResearchers() const noexcept;

	// Deleted Functions
	ResearchInstitute(const ResearchInstitute&) = delete;
	const ResearchInstitute& operator=(const ResearchInstitute&) = delete;

private:
	// C'tors
	ResearchInstitute();

	// File Functions
	void saveResearchInstitute(const std::string& filename) const noexcept;
	void loadResearchInstitute(std::ifstream& inFile) noexcept;

	// Add Functions
	void addResearcher(Researcher& researcher) noexcept;

	friend class Hospital;
};

#endif // __RESEARCH_INSTITUTE_H