#include "Department.h"
#include "Hospital.h"
using namespace std;

Department::Department(const string& name) noexcept(false)
{
	setDepartmentName(name);
}

Department::Department(ifstream& in) noexcept : m_hospital(nullptr)
{
	in >> *this;
}

Department::Department(const Department& other) noexcept : m_hospital(other.m_hospital)
{
	setDepartmentName(other.m_name);
	setDoctors(other.m_doctors);
	setNurses(other.m_nurses);
	setPatients(other.m_patients);
}

Department::Department(Department&& other) noexcept
{
	std::swap(m_hospital, other.m_hospital);
	std::swap(m_patients, other.m_patients);
	std::swap(m_doctors, other.m_doctors);
	std::swap(m_nurses, other.m_nurses);
	std::swap(m_name, other.m_name);
}

const string& Department::getDepartmentName() const noexcept
{
	return m_name;
}

const set<Patient*, ltPatientID>& Department::getPatients() const noexcept
{
	return m_patients; 
}

const set<Nurse*, ltEmployeeID>& Department::getNurses() const noexcept
{
	return m_nurses;
}

const set<Doctor*, ltEmployeeID>& Department::getDoctors() const noexcept
{
	return m_doctors; 
}

void Department::setDepartmentName(const string& name) noexcept(false)
{
	if (name == "") 
		throw invalid_argument("Department name can not be empty");
	m_name = name;
}

void Department::setPatients(const set<Patient*, ltPatientID>& patients) noexcept
{
	for (Patient* patient : m_patients)
		delete patient;

	for (Patient* patient : patients)
		m_patients.insert(patient);
}

void Department::setNurses(const set<Nurse*, ltEmployeeID>& nurses) noexcept
{
	for (Nurse* nurse : m_nurses)
		delete nurse;

	for (Nurse* nurse : nurses)
		m_nurses.insert(nurse);
}

void Department::setDoctors(const set<Doctor*, ltEmployeeID>& doctors) noexcept
{
	for (Doctor* doctor : m_doctors)
		delete doctor;

	for (Doctor* doctor : doctors)
		m_doctors.insert(doctor);
}

void Department::setHospital(Hospital* hospital) noexcept
{
	m_hospital = hospital;
}

void Department::showDoctors() const noexcept
{
	if (m_doctors.empty())
	{
		cout << "There are no doctors in this department." << endl << endl;
		return;
	}

	cout << "Doctors:" << endl;
	for_each(m_doctors.begin(), m_doctors.end(), Print<Doctor*>());
	
	cout << endl;
}

void Department::showNurses() const noexcept
{
	if (m_nurses.empty())
	{
		cout << "There are no nurses in this department." << endl;
		return;
	}

	cout << "Nurses:" << endl;
	for_each(m_nurses.begin(), m_nurses.end(), Print<Nurse*>());
	
	cout << endl;
}
void Department::showEmployees() const noexcept
{
	cout << "The Employees In " << m_name << " Department Are:" << endl
		 << "------------------------------------------------------------" << endl;
	showNurses();
	showDoctors();
}

void Department::showPatients() const noexcept
{
	cout << "The Patients In " << m_name << " Department Are:" << endl;
	cout << "------------------------------------------------------------" << endl;

	if (m_patients.empty())
	{
		cout << "There are no patients in this department." << endl;
		return;
	}

	for_each(m_patients.begin(), m_patients.end(), Print<Patient*>());
}

void Department::showPatientByID(int id) const noexcept(false)
{
	Patient* pPatient = searchPatient(id);
	cout << *pPatient;
}

Patient* Department::searchPatient(int patient_id) const noexcept
{
	set<Patient*>::iterator found = find_if(m_patients.begin(), m_patients.end(),
		[patient_id](Patient* patient) { return patient->getID() == patient_id; });
	
	return found == m_patients.end() ? nullptr : *found;
}
 
Doctor* Department::searchDoctor(int doctor_id) const noexcept
{
	set<Doctor*>::iterator found = find_if(m_doctors.begin(), m_doctors.end(),
		[doctor_id](Doctor* doctor) { return doctor->getEmployeeId() == doctor_id; });
	
	return found == m_doctors.end() ? nullptr : *found;
}

void Department::operator+=(Employee& employee) noexcept
{
	m_hospital->addEmployee(employee, m_name);
}

ostream& operator<<(ostream& os, const Department& department) noexcept
{
	if (typeid(os) == typeid(ofstream))
	{
		os << department.m_name.length() << " " << department.m_name << "\n";
	}
	return os;
}

istream& operator>>(istream& in, Department& department) noexcept
{
	if (typeid(in) == typeid(ifstream))
	{
		int name_len;
		in >> name_len;
		in.ignore();
		getline(in, department.m_name);
	}
	return in;
}

void Department::addEmployee(Employee& employee) noexcept
{
	Doctor* tempDoc = dynamic_cast<Doctor*>(&employee);
	if (tempDoc)
		m_doctors.insert(tempDoc);

	Nurse* tempNur = dynamic_cast<Nurse*>(&employee);
	if (tempNur)
		m_nurses.insert(tempNur);
}

void Department::addPatient(Patient& patient) noexcept
{
	m_patients.insert(&patient);
}

void Department::saveDepartment(const string& filename) const noexcept
{
	ofstream outFile(filename, ios::app);

	outFile << *this << endl << m_doctors.size() << endl;
	for (Doctor* doctor : m_doctors)
		outFile << typeid(*doctor).name() + 6 << " " << *doctor << endl;

	outFile << endl;

	outFile << m_nurses.size() << endl;
	for (Nurse* nurse : m_nurses)
		outFile << typeid(*nurse).name() + 6 << " " << *nurse << endl;

	outFile.close();
}

void Department::loadDepartment(ifstream& inFile) noexcept
{
	int nofDoctors, nofNurses;

	inFile >> nofDoctors;
	for (int i = 0; i < nofDoctors; i++)
	{
		Doctor* doctor;
		char type[20];
		inFile >> type;

		if (strcmp((typeid(Doctor).name() + 6), type) == 0)
			doctor = new Doctor(inFile);
		else if (strcmp((typeid(Surgeon).name() + 6), type) == 0)
			doctor = new Surgeon(inFile);
		else if (strcmp((typeid(DoctorResearcher).name() + 6), type) == 0)
		{
			doctor = new DoctorResearcher(inFile);
			DoctorResearcher* temp = dynamic_cast<DoctorResearcher*>(doctor);
			m_hospital->addResearcher((Researcher&)(*temp));
		}
		else
		{
			doctor = new SurgeonResearcher(inFile);
			SurgeonResearcher* temp = dynamic_cast<SurgeonResearcher*>(doctor);
			m_hospital->addResearcher((Researcher&)(*temp));
		}
		m_doctors.insert(doctor);
		m_hospital->m_employees.insert(doctor);
	}

	inFile >> nofNurses;
	for (int i = 0; i < nofNurses; i++)
	{
		Nurse* nurse;
		char type[20];
		inFile >> type;
		
		nurse = new Nurse(inFile);
		m_nurses.insert(nurse);
		m_hospital->m_employees.insert(nurse);
	}
}