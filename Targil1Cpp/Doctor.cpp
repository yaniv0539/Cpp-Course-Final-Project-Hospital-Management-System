#include "Doctor.h"
using namespace std;

Doctor::Doctor(const string& name, const string& expertField) noexcept(false) : Employee(name)
{
	setExpertField(expertField);
}

Doctor::Doctor(ifstream& in) noexcept : Employee(in)
{
	fromOs(in);
}

Doctor::Doctor(const Doctor& other) noexcept : Employee(other)
{
	setExpertField(other.m_expertField);
}

Doctor::Doctor(Doctor&& other) noexcept : Employee(std::move(other))
{
	std::swap(m_expertField, other.m_expertField);
}

const string& Doctor::getExpertField() const noexcept
{
	return m_expertField; 
}

void Doctor::setExpertField(const string& expertField) noexcept(false)
{
	if (expertField == "") 
		throw invalid_argument("Expert field name can not be empty");
	m_expertField = expertField;
}

void Doctor::toOs(ostream& os) const noexcept
{
	Employee::toOs(os);
	if (typeid(os) == typeid(ofstream))
		os << m_expertField.length() << " " << m_expertField << "\n";
	else
		os << ", Field of expertise: " << m_expertField;
}

void Doctor::fromOs(istream& in) noexcept
{
	int expertField_length;
	in >> expertField_length;
	in.ignore();
	getline(in, m_expertField);
}

Employee* Doctor::clone() const noexcept
{
	return new Doctor(*this);
}
