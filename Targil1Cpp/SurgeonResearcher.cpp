#include "SurgeonResearcher.h"
using namespace std;

SurgeonResearcher::SurgeonResearcher(const Surgeon& surgeon, const DoctorResearcher& doctor_researcher) noexcept :
	Employee(surgeon), Doctor(surgeon), Researcher(doctor_researcher),
	Surgeon(surgeon), DoctorResearcher(doctor_researcher) 
{
}

SurgeonResearcher::SurgeonResearcher(const string& name, const string& expertField, const Array<Article*>& articles, int nofSurgeons) noexcept(false) :
	Employee(name), Doctor(name, expertField), Researcher(name, articles),
	Surgeon(name, expertField, nofSurgeons), DoctorResearcher(name, expertField, articles)
{
}

SurgeonResearcher::SurgeonResearcher(const string& name, const std::string& expertField, int nofSurgeons) noexcept(false) :
	Employee(name), Doctor(name, expertField), Researcher(name),
	Surgeon(name, expertField, nofSurgeons), DoctorResearcher(name, expertField) 
{
}

SurgeonResearcher::SurgeonResearcher(ifstream& in) noexcept : Employee(in), Doctor(in), Researcher(in), Surgeon(in), DoctorResearcher(in)
{
}

void SurgeonResearcher::toOs(ostream& os) const noexcept
{
	Doctor::toOs(os);
	if (typeid(os) == typeid(ofstream))
	{
		Researcher::showArticles(os);
		os << m_nofSurgeries << " ";
	}
	else
	{
		os << ", Number of surgeons: " << m_nofSurgeries;
		Researcher::showArticles(os);
	}
}

Employee* SurgeonResearcher::clone() const noexcept
{
	return new SurgeonResearcher(*this);
}