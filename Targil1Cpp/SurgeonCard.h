#ifndef __SURGEON_CARD_H
#define __SURGEON_CARD_H

#include <iostream>
#include <string>
#include "VisitCard.h"

class SurgeonCard : public VisitCard 
{
private:
	int m_room_num;
	bool m_isFasted;

public:
	// C'tors
	SurgeonCard(const Date& visitDate, const std::string& visitReason, const Doctor& doctor, int room_num, bool isFasted) noexcept(false);
	SurgeonCard(const VisitCard& visit_card, int room_num, bool isFasted) noexcept(false);

	// Get Functions
	int getRoomNum() const noexcept;
	bool getIsFasted() const noexcept;

	// Set Functions
	void setRoomNum(int room_num) noexcept(false);
	void setIsFasted(bool isFasted) noexcept;
	
	// Show Functions
	virtual void show(std::ostream& os = std::cout) const noexcept;
	
	// Operator Functions
	friend std::ostream& operator<<(std::ostream& os, const SurgeonCard& surgeon_card) noexcept;

	virtual VisitCard* clone() const noexcept override;
	
	// Deleted Functions
	const SurgeonCard& operator=(const SurgeonCard&) = delete;

protected:
	// C'tors
	SurgeonCard(const SurgeonCard& other) = default;
	SurgeonCard(SurgeonCard&& other) = default;
};

#endif // __SURGEON_CARD_H
