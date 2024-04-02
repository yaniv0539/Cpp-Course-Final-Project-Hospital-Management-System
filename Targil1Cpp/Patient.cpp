#include "Patient.h"
using namespace std;

Patient::Patient(const string& name, int id, const Date& birthday, const eGender& gender) noexcept(false) :
	Person(name), m_birthday(birthday)
{
	setID(id);
	setGender(gender);
	m_visits.reserve(1);
}

Patient::~Patient() noexcept
{
	for (VisitCard* visit : m_visits)
		delete visit;
}

int Patient::getID() const noexcept
{ 
	return m_id; 
}

const Date& Patient::getBirthday() const noexcept
{ 
	return m_birthday; 
}

Date& Patient::getBirthday() noexcept
{ 
	return m_birthday; 
}

Patient::eGender Patient::getGender() const noexcept
{ 
	return m_gender; 
}

const vector<VisitCard*>& Patient::getVisitCard() const noexcept
{ 
	return m_visits; 
}

vector<VisitCard*>& Patient::getVisitCard() noexcept
{
	return m_visits;
}

void Patient::setID(int id) noexcept(false)
{
	if (id < 1 || id > 999999999) 
		throw invalid_argument("ID must be a 9 digit number.");
	m_id = id;
}

void Patient::setBirthday(const Date& birthday) noexcept
{ 
	m_birthday = birthday; 
}

void Patient::setGender(int gender) noexcept(false)
{
	if (gender != eGender::MALE && gender != eGender::FEMALE) 
		throw out_of_range("The gender must be male (1) or female (2)");
	m_gender = (eGender)gender;
}

void Patient::addVisit(VisitCard* visit) noexcept
{
	size_t size = m_visits.size();
	if (size == m_visits.capacity())
		m_visits.reserve(size * 2);
	m_visits.push_back(visit->clone());
}

void Patient::showVisits(ostream& os) const noexcept
{
	int index = 1;
	os << "-->Visit Cards: " << endl;
	if (m_visits.empty())
		os << "-->There are no visits to " << m_name << " patient!" << endl;
	else
	{
		for (VisitCard* visit : m_visits)
			os << "   #" << index++ << ":" << *visit << endl;
	}
}

void Patient::toOs(ostream& os) const noexcept
{
	os << ", ID: " << m_id
		<< ", Gender: " << genders[m_gender - 1]
		<< ", Birthday: " << m_birthday << endl;

	showVisits(os);
}

Patient* Patient::clone() const noexcept
{
	return new Patient(*this);
}

Patient::Patient(const Patient& other) noexcept : Person(other), m_birthday(other.m_birthday)
{
	setGender(other.m_gender);
	setVisits(other.m_visits);
	setID(other.m_id);
}

Patient::Patient(Patient&& other) noexcept : Person(std::move(other)), m_birthday(other.m_birthday)
{
	std::swap(m_gender, other.m_gender);
	std::swap(m_visits, other.m_visits);
	std::swap(m_id, other.m_id);
}

void Patient::setVisits(const vector<VisitCard*>&visits) noexcept
{
	for (VisitCard* visit : m_visits)
		delete visit;

	m_visits.reserve(visits.capacity());

	for (VisitCard* visit : visits)
		m_visits.push_back(visit->clone());
}