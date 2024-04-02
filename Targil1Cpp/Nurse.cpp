#include "Nurse.h"
using namespace std;

Nurse::Nurse(const string& name, int nofExperience) noexcept(false) : Employee(name)
{
	setNofExperience(nofExperience);
}

Nurse::Nurse(ifstream& in) noexcept : Employee(in)
{
	fromOs(in);
}

int Nurse::getNofExperience() const noexcept
{ 
	return m_nofExperience; 
}

void Nurse::setNofExperience(int nofExperience) noexcept(false)
{
	if (nofExperience < 0) 
		throw invalid_argument("Number of experience can not be negative.");
	m_nofExperience = nofExperience;
}

void Nurse::toOs(ostream& os) const noexcept
{
	Employee::toOs(os);
	if (typeid(os) == typeid(ofstream))
		os << m_nofExperience << " ";
	else
		os << ", Years of experience: " << m_nofExperience;
}

void Nurse::fromOs(std::istream& in) noexcept
{
	in >> m_nofExperience;
}

Employee* Nurse::clone() const noexcept
{
	return new Nurse(*this);
}
