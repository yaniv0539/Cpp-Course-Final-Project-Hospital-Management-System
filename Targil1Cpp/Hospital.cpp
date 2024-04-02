#include "Hospital.h"
#include "Employee.h"
using namespace std;

Hospital::Hospital() noexcept
{
	m_researchInstitute.m_hospital = this;
}

Hospital::~Hospital() noexcept
{
	for (Department* dep : m_departments)
		delete dep;

	for (Employee* emp : m_employees)
		delete emp;

	for (Patient* pat : m_patients)
		delete pat;
}

const set<Department*, ltDepartmentName>& Hospital::getDepartments() const noexcept
{
	return m_departments;
}

const set<Employee*, ltEmployeeID>& Hospital::getEmployees() const noexcept
{
	return m_employees;
}

const set<Patient*, ltPatientID>& Hospital::getPatients() const noexcept
{
	return m_patients;
}

const ResearchInstitute& Hospital::getResearchInstitute() const noexcept
{ 
	return m_researchInstitute;
}

ResearchInstitute& Hospital::getResearchInstitute() noexcept
{
	return m_researchInstitute; 
}

void Hospital::addDepartment(const string& department_name) noexcept(false)
{
	Department* pDepartment = searchDepartment(department_name);
	if (pDepartment != nullptr)
		throw invalid_argument("Department already exists!");

	Department* new_department = new Department(department_name);

	new_department->setHospital(this);
	m_departments.insert(new_department);
}

void Hospital::addEmployee(Employee& employee, const string& department_name) noexcept(false)
{
	Department* pDepartment = searchDepartment(department_name);
	if (pDepartment == nullptr)
		throw invalid_argument("Department doesn't exist!");

	Employee* pEmployee = searchEmployee(employee.getEmployeeId());
	if (pEmployee != nullptr)
		throw invalid_argument("Employee is already in the system!");
	
	Employee* pClone = employee.clone();
	m_employees.insert(pClone);
	pDepartment->addEmployee(*pClone);

	Researcher* tempRes = dynamic_cast<Researcher*>(pClone);
	if (tempRes)
		m_researchInstitute.addResearcher(*tempRes);
}

void Hospital::addEmployee(Researcher& researcher) noexcept(false)
{
	Researcher* pResearcher = m_researchInstitute.searchResearcher(researcher.getEmployeeId());
	if (pResearcher != nullptr)
		throw invalid_argument("Researcher is already in the system!");

	Employee* pClone = researcher.clone();
	m_employees.insert(pClone);

	Researcher* tempRes = dynamic_cast<Researcher*>(pClone);
	m_researchInstitute.addResearcher(*tempRes);
}

void Hospital::addPatient(Patient& patient, const string& department_name) noexcept(false)
{
	Department* pDepartment = searchDepartment(department_name);
	if (pDepartment == nullptr)
		throw invalid_argument("Department doesn't exist!");

	Patient* pPatient = searchPatient(patient.getID());
	if (pPatient == nullptr)
	{
		pPatient = patient.clone();
		m_patients.insert(pPatient);
	}

	pDepartment->addPatient(*pPatient);
}

void Hospital::showEmployees() const noexcept
{
	if (m_departments.empty())
	{
		cout << "There are no departments in this hospital." << endl;
		return;
	}

	cout << "Printing this hospital entire employees in every department:" << endl << endl;
	
	for (Department* dep : m_departments)
		dep->showEmployees();
}

void Hospital::showResearchers() const noexcept
{
	m_researchInstitute.showResearchers();
}

void Hospital::showPatientByID(int id) const noexcept
{
	set<Department*>::iterator itr = m_departments.begin();
	set<Department*>::iterator itrEnd = m_departments.end();
	
	for (; itr != itrEnd; ++itr)
		if ((*itr)->searchPatient(id))
			break;

	if (itr == itrEnd)
	{
		cout << "Sorry! There is no such patient in this hospital." << endl;
		return;
	}
	
	(*itr)->showPatientByID(id);
}

void Hospital::showDoctorResearchers() const noexcept
{
	m_researchInstitute.showDoctorResearchers();
}

Department* Hospital::searchDepartment(const string& name) const noexcept
{
	set<Department*>::iterator found = find_if(m_departments.begin(), m_departments.end(),
		[name](const Department* pDep) { return name == pDep->getDepartmentName(); });

	return found == m_departments.end() ? nullptr : *found;
}

Patient* Hospital::searchPatient(int id) const noexcept
{
	set<Patient*>::iterator found = find_if(m_patients.begin(), m_patients.end(),
		[id](const Patient* pPat) { return id == pPat->getID(); });

	return found == m_patients.end() ? nullptr : *found;
}

Employee* Hospital::searchEmployee(int employee_id) const noexcept
{
	set<Employee*>::iterator found = find_if(m_employees.begin(), m_employees.end(),
		[employee_id](const Employee* pEmp) { return employee_id == pEmp->getEmployeeId(); });

	return found == m_employees.end() ? nullptr : *found;
}

void Hospital::saveHospital(const string& filename) const noexcept
{
	cout << "Saving this hospital's data..." << endl;
	ofstream outFile1(filename, ios::trunc);
	outFile1 << Employee::s_cnt << endl;
	m_researchInstitute.saveResearchInstitute(filename);
	outFile1.close();

	ofstream outFile2(filename, ios::app);
	outFile2 << m_departments.size() << endl;
	for (Department* department : m_departments)
	{
		department->saveDepartment(filename);
		outFile2 << endl;
	}
	outFile2.close();
	cout << "Data was saved successfully into " << filename << " file." << endl;
}

void Hospital::loadHospital(const string& filename) noexcept(false)
{
	ifstream inFile(filename);
	if (!(inFile.is_open()))
		throw invalid_argument("File does not exist or could not be opened.\n\n");
	else 
	{
		cout << "Loading data from the previous run..." << endl;
		inFile >> Employee::s_cnt;

		m_researchInstitute.loadResearchInstitute(inFile);

		int nofDepartments;
		inFile >> nofDepartments;

		for (int i = 0; i < nofDepartments; i++)
		{
			Department* department = new Department(inFile);
			department->setHospital(this);
			department->loadDepartment(inFile);
			m_departments.insert(department);
		}
		inFile.close();
		cout << "Data uploaded successfully from " << filename << " file." << endl;
	}
}

void Hospital::addResearcher(Researcher& researcher) noexcept 
{ 
	m_researchInstitute.addResearcher(researcher);
}