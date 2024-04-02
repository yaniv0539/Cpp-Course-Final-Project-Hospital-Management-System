#include "SurgeonCard.h"
using namespace std;

SurgeonCard::SurgeonCard(const Date& visitDate, const string& visitReason, const Doctor& doctor, int room_num, bool isFasted) noexcept(false) :
	VisitCard(visitDate, visitReason, doctor)
{
	setRoomNum(room_num);
	setIsFasted(isFasted);
}

SurgeonCard::SurgeonCard(const VisitCard& visit_card, int room_num, bool isFasted) noexcept(false) :
	VisitCard(visit_card), m_isFasted(isFasted) 
{
	setRoomNum(room_num);
}

int SurgeonCard::getRoomNum() const noexcept
{ 
	return m_room_num; 
}

bool SurgeonCard::getIsFasted() const noexcept
{ 
	return m_isFasted; 
}

void SurgeonCard::setRoomNum(int room_num) noexcept(false)
{ 
	if (room_num < 0) 
		throw invalid_argument("Room number can not be negative.");
	m_room_num = room_num; 
}

void SurgeonCard::setIsFasted(bool isFasted) noexcept
{ 
	m_isFasted = isFasted; 
}

void SurgeonCard::show(ostream& os) const noexcept
{
	VisitCard::show(os);
	os << ", Room number: " << m_room_num << ", Is fasted: " << (m_isFasted ? "Yes" : "No");
}

ostream& operator<<(ostream& os, const SurgeonCard& surgeon_card) noexcept
{
	surgeon_card.show(os);
	return os;
}

VisitCard* SurgeonCard::clone() const noexcept
{
	return new SurgeonCard(*this);
}