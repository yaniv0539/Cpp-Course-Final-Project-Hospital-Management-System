#ifndef __HOSPITAL_H
#define __HOSPITAL_H

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

#include "Department.h"
#include "Patient.h"
#include "ResearchInstitute.h"

class Hospital
{
private:
	ResearchInstitute m_researchInstitute;
	
	std::set<Department*, ltDepartmentName> m_departments;
	std::set<Patient*, ltPatientID> m_patients;
	std::set<Employee*, ltEmployeeID> m_employees;

public:
	// C'tors
	Hospital() noexcept;
	~Hospital() noexcept;
		
	// Get Functions
	const ResearchInstitute& getResearchInstitute() const noexcept;
	ResearchInstitute& getResearchInstitute() noexcept;
	const std::set<Department*, ltDepartmentName>& getDepartments() const noexcept;
	const std::set<Patient*, ltPatientID>& getPatients() const noexcept;
	const std::set<Employee*, ltEmployeeID>& getEmployees() const noexcept;

	// Add Functions
	void addDepartment(const std::string& department_name) noexcept(false);
	void addEmployee(Employee& employee, const std::string& department_name) noexcept(false);
	void addEmployee(Researcher& researcher) noexcept(false);
	void addPatient(Patient& patient, const std::string& department_name) noexcept(false);

	// Search Functions
	Department* searchDepartment(const std::string& name) const noexcept;
	Patient* searchPatient(int patient_id) const noexcept;
	Employee* searchEmployee(int employee_id) const noexcept;

	// Show Functions
	void showEmployees() const noexcept;
	void showResearchers() const noexcept;
	void showPatientByID(int id) const noexcept;
	void showDoctorResearchers() const noexcept;

	// File Functions
	void saveHospital(const std::string& filename) const noexcept;
	void loadHospital(const std::string& filename) noexcept(false);

	// Deleted Functions
	Hospital(const Hospital&) = delete;
	const Hospital& operator=(const Hospital&) = delete;

private:
	// Friending load functions to optimize the efficiency of the loading (withoud cloning twice)
	friend void Department::loadDepartment(std::ifstream& inFile) noexcept;
	friend void ResearchInstitute::loadResearchInstitute(std::ifstream& inFile) noexcept;
	
	void addResearcher(Researcher& researcher) noexcept;
};

#endif // __HOSPITAL_H

