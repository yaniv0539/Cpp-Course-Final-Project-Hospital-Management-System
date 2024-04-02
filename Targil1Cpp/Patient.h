#ifndef __PATIENT_H
#define __PATIENT_H

#include "Date.h"
#include "SurgeonCard.h"
#include "Person.h"
#include <iostream>
#include <string>
#include <vector>

class Patient : public Person
{
public:
	const enum eGender { MALE = 1, FEMALE };
	const std::string genders[2] = { "Male", "Female" };

private:
	int	m_id;
	Date m_birthday;
	eGender	m_gender;
	std::vector<VisitCard*> m_visits;

public:
	// C'tors
	Patient(const std::string& name, int id, const Date& birthday, const eGender& gender) noexcept(false);
	virtual ~Patient() noexcept;

	// Get Functions
	int getID() const noexcept;
	const Date& getBirthday() const noexcept;
	Date& getBirthday() noexcept;
	eGender getGender() const noexcept;
	const std::vector<VisitCard*>& getVisitCard() const noexcept;
	std::vector<VisitCard*>& getVisitCard() noexcept;

	// Set Functions
	void setBirthday(const Date& birthday) noexcept;
	void setID(int id) noexcept(false);
	void setGender(int gender) noexcept(false);

	// Add Functions
	void addVisit(VisitCard* visit) noexcept;

	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override;
	void showVisits(std::ostream& os = std::cout) const noexcept;
	virtual void fromOs(std::istream& in) noexcept override {}

	// Other Functions
	virtual Patient* clone() const noexcept;

	// Deleted Functions
	const Patient& operator=(const Patient&) = delete;

private:
	// C'tors
	Patient(const Patient& other) noexcept;
	Patient(Patient&& other) noexcept;
	
	// Set Functions
	void setVisits(const std::vector<VisitCard*>& visits) noexcept;
};

// Object Function
class ltPatientID
{
public:
	bool operator()(const Patient* pPat1, const Patient* pPat2) const noexcept { return pPat1->getID() < pPat2->getID(); }
};
//----------------------------------------------------------------------------------------------------------------------------------------------

#endif // __PATIENT_H