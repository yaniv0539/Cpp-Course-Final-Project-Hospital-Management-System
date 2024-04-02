#ifndef __PERSON_H
#define __PERSON_H

#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <string>

// Abstract class
class Person
{
protected:
	std::string m_name;

public:
	// C'tor
	Person(const std::string& name) noexcept(false);
	Person(std::ifstream& in) noexcept;
	virtual ~Person() = default;

	// Get functions
	const std::string& getName() const noexcept;

	// Set functions
	void setName(const std::string& name) noexcept(false);

	// Stream functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept = 0 {}
	virtual void fromOs(std::istream& in) noexcept {}
	friend std::ostream& operator<<(std::ostream& os, const Person& person) noexcept;
	friend std::istream& operator>>(std::istream& in, Person& person) noexcept;

protected:
	Person(const Person& other) noexcept;
	Person(Person&& other) noexcept;
};

#endif // __PERSON_H