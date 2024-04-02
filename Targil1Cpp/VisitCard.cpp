#include "VisitCard.h"
using namespace std;

VisitCard::VisitCard(const Date& visitDate, const string& visitReason, const Doctor& doctor) noexcept(false) :
	m_visitDate(visitDate), m_attendingDoctor(&doctor)
{ 
	setVisitReason(visitReason);
}

VisitCard::VisitCard(const VisitCard& other) noexcept :
	m_visitDate(other.m_visitDate), m_attendingDoctor(nullptr)
{
	*this = other;
}

VisitCard::VisitCard(VisitCard&& other) noexcept : m_visitDate(std::move(other.m_visitDate)), m_attendingDoctor(nullptr)
{
	*this = std::move(other);
}

const Date& VisitCard::getVisitCardDate() const noexcept
{
	return m_visitDate;
}

Date& VisitCard::getVisitCardDate() noexcept
{ 
	return m_visitDate; 
}

const string& VisitCard::getVisitReason() const noexcept
{ 
	return m_visitReason; 
}

const Doctor* VisitCard::getAttendingDoctor() const noexcept
{ 
	return m_attendingDoctor; 
}

void VisitCard::setVisitCardDate(const Date& other) noexcept
{ 
	m_visitDate = other;
}

void VisitCard::setVisitReason(const string& visitReason) noexcept(false)
{
	if (visitReason == "") 
		throw invalid_argument("Visit reason can not be empty");
	m_visitReason = visitReason;
}

void VisitCard::setAttendingDoctor(const Doctor& other) noexcept
{
	m_attendingDoctor = &other;
}

const VisitCard& VisitCard::operator=(const VisitCard& other) noexcept
{
	if (this != &other)
	{
		setVisitCardDate(other.m_visitDate);
		setVisitReason(other.m_visitReason);
		setAttendingDoctor(*other.m_attendingDoctor);
	}
	return *this;
}

const VisitCard& VisitCard::operator=(VisitCard&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_visitDate, other.m_visitDate);
		std::swap(m_visitReason, other.m_visitReason);
		std::swap(m_attendingDoctor, other.m_attendingDoctor);
	}
	return *this;
}

void VisitCard::show(ostream& os) const noexcept
{
	os << "Visit Date " << m_visitDate
		<< ", Visit Reason: " << m_visitReason
		<< ", Attending doctor: Dr. " << m_attendingDoctor->getName();
}

ostream& operator<<(ostream& os, const VisitCard& visit_card) noexcept
{
	visit_card.show(os);
	return os;
}

VisitCard* VisitCard::clone() const noexcept
{
	return new VisitCard(*this);
}