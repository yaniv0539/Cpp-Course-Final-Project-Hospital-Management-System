#include "Person.h"
#include <string.h>
using namespace std;

Person::Person(const string& name) noexcept(false)
{ 
	setName(name);
}

Person::Person(ifstream& in) noexcept
{
	in >> *this;
}

Person::Person(const Person& other) noexcept
{
	setName(other.m_name);
}

Person::Person(Person&& other) noexcept
{
	std::swap(m_name, other.m_name);
}

const string& Person::getName() const noexcept
{ 
	return m_name;
}

void Person::setName(const string& name) noexcept(false)
{
	if (name == "") 
		throw invalid_argument("Person's name can not be empty");
	m_name = name;
}

ostream& operator<<(ostream& os, const Person& person) noexcept
{
	if (typeid(os) == typeid(ofstream))
		os << person.m_name.length() << " " << person.m_name << "\n";
	else
		os << "Name: " << person.m_name;
	person.toOs(os);
	return os;
}

istream& operator>>(istream& in, Person& person) noexcept
{
	int name_len;
	in >> name_len;
	in.ignore();
	getline(in, person.m_name);
	person.fromOs(in);
	return in;
}
