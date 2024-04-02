#ifndef __VISITCARD_H
#define __VISITCARD_H

#pragma warning(disable: 4996)
#include <iostream>
#include <string>

#include "Date.h"
#include "Doctor.h"

class VisitCard
{
protected:
	Date m_visitDate;
	std::string m_visitReason;
	const Doctor* m_attendingDoctor;

public:
	// C'tors
	VisitCard(const Date& visitDate, const std::string& visitReason, const Doctor& doctor) noexcept(false);
	virtual ~VisitCard() = default;

	// Get Functions
	const Date& getVisitCardDate() const noexcept;
	Date& getVisitCardDate() noexcept;
	const std::string& getVisitReason() const noexcept;
	const Doctor* getAttendingDoctor() const noexcept;

	virtual VisitCard* clone() const noexcept;

	// Set Functions
	void setVisitCardDate(const Date& other) noexcept;
	void setVisitReason(const std::string& other) noexcept(false);
	void setAttendingDoctor(const Doctor& other) noexcept;
	
	// Show Functions
	virtual void show(std::ostream& os = std::cout) const noexcept;

	// Operator Functions
	friend std::ostream& operator<<(std::ostream& os, const VisitCard& visit_card) noexcept;

protected:
	// C'tors
	VisitCard(const VisitCard& other) noexcept;
	VisitCard(VisitCard&& other) noexcept;
	const VisitCard& operator=(const VisitCard& other) noexcept;
	const VisitCard& operator=(VisitCard&& other) noexcept;
};

#endif // __VISITCARD_H