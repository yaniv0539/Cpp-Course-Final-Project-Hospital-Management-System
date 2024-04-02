#include "DoctorResearcher.h"
using namespace std;

DoctorResearcher::DoctorResearcher(const Doctor& doctor, const Researcher& researcher) noexcept : 
	Employee(doctor), Doctor(doctor), Researcher(researcher) 
{
}

DoctorResearcher::DoctorResearcher(const string& name, const string& expertField, const Array<Article*>& articles) noexcept(false) :
	Employee(name), Doctor(name, expertField), Researcher(name, articles)
{
}

DoctorResearcher::DoctorResearcher(const string& name, const string& expertField) noexcept(false) :
	Employee(name), Doctor(name, expertField), Researcher(name) 
{
}

DoctorResearcher::DoctorResearcher(ifstream& in) noexcept : Employee(in), Doctor(in), Researcher(in)
{
}

void DoctorResearcher::toOs(ostream& os) const noexcept
{
	Doctor::toOs(os);
	Researcher::showArticles(os);
}

Employee* DoctorResearcher::clone() const noexcept
{
	return new DoctorResearcher(*this);
}