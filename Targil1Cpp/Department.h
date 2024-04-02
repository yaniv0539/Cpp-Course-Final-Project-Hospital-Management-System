#ifndef __DEPARTMENT_H
#define __DEPARTMENT_H

#pragma warning(disable: 4996)
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

#include "Patient.h"
#include "Nurse.h"
#include "SurgeonResearcher.h"
#include "Print.h"

class Hospital;

class Department
{
private:
	std::string m_name;
	Hospital* m_hospital;
	
	std::set<Patient*, ltPatientID> m_patients;
	std::set<Nurse*, ltEmployeeID> m_nurses;
	std::set<Doctor*, ltEmployeeID> m_doctors;

public:
	// Get Functions
	const std::string& getDepartmentName() const noexcept;
	const std::set<Patient*, ltPatientID>& getPatients() const noexcept;
	const std::set<Nurse*, ltEmployeeID>& getNurses() const noexcept;
	const std::set<Doctor*, ltEmployeeID>& getDoctors() const noexcept;

	// Show Functions
	void showEmployees() const noexcept;
	void showDoctors() const noexcept;
	void showNurses() const noexcept;
	void showPatients() const noexcept;
	void showPatientByID(int id) const noexcept(false);
	
	// Search Functions
	Patient* searchPatient(int patient_id) const noexcept;
	Doctor* searchDoctor(int doctor_id) const noexcept;

	// Operators Functions
	void operator+=(Employee& employee) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const Department& department) noexcept;
	friend std::istream& operator>>(std::istream& in, Department& department) noexcept;

	// Deleted Funcions
	const Department& operator= (const Department&) = delete;

private:
	// C'tors
	Department(const std::string& departmentName) noexcept(false);
	Department(std::ifstream& in) noexcept;
	Department(const Department& other) noexcept;
	Department(Department&& other) noexcept;

	// Add Functions
	void addEmployee(Employee& employee) noexcept;
	void addPatient(Patient& patient) noexcept;

	// Set Functions
	void setDepartmentName(const std::string& name) noexcept(false);
	void setPatients(const std::set<Patient*, ltPatientID>& patients) noexcept;
	void setNurses(const std::set<Nurse*, ltEmployeeID>& nurses) noexcept;
	void setDoctors(const std::set<Doctor*, ltEmployeeID>& doctors) noexcept;
	void setHospital(Hospital* hospital) noexcept;

	void saveDepartment(const std::string& filename) const noexcept;
	void loadDepartment(std::ifstream& inFile) noexcept;

	friend class Hospital;
};

// Object Function
class ltDepartmentName
{
public:
	bool operator()(const Department* pDep1, const Department* pDep2) const noexcept 
	{ 
		return pDep1->getDepartmentName() < pDep2->getDepartmentName(); 
	}
};
//-----------------------------------------------------------------------------------

#endif // __DEPARTMENT_H