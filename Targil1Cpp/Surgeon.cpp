#include "Surgeon.h"
using namespace std;
Surgeon::Surgeon(const Doctor& doctor, int nofSurgeries) noexcept(false) :
	Employee(doctor), Doctor(doctor)
{
	setNofSurgeries(nofSurgeries);
}

Surgeon::Surgeon(const string& name, const string& expertField, int nofSurgeries) noexcept(false) :
	Employee(name), Doctor(name,expertField)
{
	setNofSurgeries(nofSurgeries);
}

Surgeon::Surgeon(ifstream& in) noexcept : Employee(in), Doctor(in)
{
	fromOs(in);
}

int Surgeon::getNofSurgeries() const noexcept
{ 
	return m_nofSurgeries;
}

void Surgeon::setNofSurgeries(int nofSurgeries) noexcept(false)
{ 
	if (nofSurgeries < 0) 
		throw invalid_argument("Number of surgeries can not be negative.");
	m_nofSurgeries = nofSurgeries;
}

void Surgeon::toOs(ostream& os) const noexcept
{
	Doctor::toOs(os);
	if (typeid(os) == typeid(ofstream))
		os << m_nofSurgeries << " ";
	else
		os << ", Number of surgeons: " << m_nofSurgeries;
}

void Surgeon::fromOs(std::istream& in) noexcept
{
	in >> m_nofSurgeries;
}

Employee* Surgeon::clone() const noexcept
{
	return new Surgeon(*this);
}