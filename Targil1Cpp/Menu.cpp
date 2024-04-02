#include "Menu.h"
using namespace std;

// Main Functions
void printMenu()
{
	cout << endl << "Please enter your selection: " << endl
		<< "------------------------------------------------------------" << endl
		<< "0.  Exit." << endl
		<< "1.  Add a department to the hospital." << endl
		<< "2.  Add a nurse to hospital, and assign her to a department." << endl
		<< "3.  Add a doctor to hospital, and assign her to a department." << endl
		<< "4.  Add a patient visit." << endl
		<< "5.  Add a researcher to the research institute." << endl
		<< "6.  Add an article to a researcher's resume." << endl
		<< "7.  Show all patients in a specific department." << endl
		<< "8.  Show all the employees in the system." << endl
		<< "9.  Show all researchers/doctor-researchers in the system." << endl
		<< "10. Search patient visit information by id." << endl
		<< "11. Add employee to department (Checks operator +=)." << endl
		<< "12. Compare between two researchers by their articles (Checks operator +=)." << endl
		<< "13. Print some random details (Checks operator <<)." << endl
		<< "------------------------------------------------------------" << endl;
}

bool checkSelection(int selection)
{
	if (selection < EXIT || selection > CHECK_OP_LT_LT)
		return false;
	return true;
}

void executeSelection(Hospital& mainHospital, int selection)
{
	try
	{
		switch (selection)
		{
		case ADD_DEP:
			addDepartment(mainHospital);
			break;
		case ADD_NUR:
			addNurse(mainHospital);
			break;
		case ADD_DOC:
			addDoctor(mainHospital);
			break;
		case ADD_VIS:
			addVisit(mainHospital);
			break;
		case ADD_RES:
			addResearcher(mainHospital);
			break;
		case ADD_ART:
			addArticle(mainHospital);
			break;
		case SHOW_PAT:
			showDepartmentPatients(mainHospital);
			break;
		case SHOW_EMP:
			showAllHospitalEmployees(mainHospital);
			break;
		case SHOW_RES:
			showResearchInstituteResearchers(mainHospital);
			break;
		case SEARCH_VIS:
			showPatientVisitsByID(mainHospital);
			break;
		case CHECK_OP_PLUS_EQUAL:
			checkOpPlusEqual(mainHospital);
			break;
		case CHECK_OP_GT:
			checkOpGt(mainHospital);
			break;
		case CHECK_OP_LT_LT:
			checkOpLtLt(mainHospital);
			break;
		}
	}
	catch (const std::invalid_argument& e)
	{
		cout << "Invalid argument: " << e.what() << endl;
	}
	catch (const std::out_of_range& e)
	{
		cout << "Out of range: " << e.what() << endl;
	}
	catch (const std::exception& e)
	{
		cout << "General error: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "Error! Please call the support...";
		exit(1);
	}
}

//	Selections

// Selection 1
void addDepartment(Hospital& mainHospital)
{
	string department_name;

	cin.ignore();
	cout << "Please enter the department name: ";
	getline(cin, department_name);

	mainHospital.addDepartment(department_name);
	cout << department_name << " department added successfully to the hospital!" << endl;
}

// Selection 2
void addNurse(Hospital& mainHospital) 
{
	Department* pDepartment = nullptr;
	Nurse* pNurse = nullptr;
	string department_name;

	cin.ignore();
	cout << "Please enter the nurse's assigned department: ";
	getline(cin, department_name);

	pDepartment = mainHospital.searchDepartment(department_name);

	if (!pDepartment)
	{
		cout << "The department was not found!" << endl;
		return;
	}

	pNurse = readNurse();

	mainHospital.addEmployee(*pNurse, department_name);

	cout << pNurse->getName() << " added successfully as an employee to " << department_name << " department." << endl 
		<< "The employee ID is: " << pNurse->getEmployeeId() << endl;

	delete pNurse;
}

// Selection 3
void addDoctor(Hospital& mainHospital)
{
	Doctor* pDoctor = nullptr;
	Department* pDepartment = nullptr;
	string department_name;

	cin.ignore();
	cout << "Please enter the doctor's assigned department: ";
	getline(cin, department_name);

	pDepartment = mainHospital.searchDepartment(department_name);

	if (!pDepartment)
	{
		cout << "The department was not found!" << endl;
		return;
	}

	pDoctor = readDoctor(mainHospital.getResearchInstitute());

	mainHospital.addEmployee(*pDoctor, department_name);

	cout << pDoctor->getName() << " added successfully as an employee to " << department_name << " department." << endl
		<< "The employee ID is: " << pDoctor->getEmployeeId() << endl;
	delete pDoctor;
}

// Selection 4
void addVisit(Hospital& mainHospital) noexcept(false)
{
	Patient* pPatient = nullptr;
	VisitCard* pVisit = nullptr;
	Department* pDepartment = nullptr;
	Doctor* pDoctor = nullptr;
	string department_name;
	int patient_id, doctor_id, surgery_flag;
	bool newPatient = false;

	cin.ignore();
	cout << "Please enter the patient caregiver department: ";
	getline(cin, department_name);

	pDepartment = mainHospital.searchDepartment(department_name);

	if (!pDepartment)
	{
		cout << "There is no " << department_name << " department in this hospital! Please try again." << endl;
		return;
	}

	cout << "Are you going through surgery? (Yes - Enter any number / No - Enter 0): ";
	cin >> surgery_flag;

	cout << "Please enter the attending doctor's employee ID (must be a surgeon if needed): ";
	cin >> doctor_id;

	pDoctor = pDepartment->searchDoctor(doctor_id);

	if (!pDoctor)
	{
		cout << "The doctor is not assigned to " << department_name << " department." << endl;
		return;
	}

	if (surgery_flag)
	{
		Surgeon* temp = dynamic_cast<Surgeon*>(pDoctor);
		if (!temp)
		{
			cout << "The doctor " << pDoctor->getName() << " is not a surgeon." << endl;
			return;
		}
		pDoctor = temp;
	}

	cout << "Please enter the patient ID: ";
	cin >> patient_id;

	pPatient = mainHospital.searchPatient(patient_id);

	if (!pPatient)
	{
		// Creating new patient in the hospital and the department points to it...
		cout << endl << "There is no patient in this ID, receiving patient data..." << endl;

		pPatient = readPatient(patient_id);

		cout << "The patient data received successfully!" << endl << endl;
		cout << "Resuming reading visit information:" << endl;
		newPatient = true;
	}

	try
	{
		pVisit = readVisit(*pDoctor, surgery_flag);
	}
	catch (const std::invalid_argument& e)
	{
		if(newPatient)
			delete pPatient;
		throw invalid_argument(e);
	}
	catch (...)
	{
		cout << "Error! Please call the support...";
		exit(1);
	}

	pPatient->addVisit(pVisit);
	cout << "The visit added successfully to the patient's visit card array!" << endl;
	mainHospital.addPatient(*pPatient, department_name);
	cout << "The patient was added successfully to the hospital." << endl << endl;

	if (newPatient)
		delete pPatient;
	delete pVisit;
}

// Selection 5
void addResearcher(Hospital& mainHospital) noexcept(false)
{
	Researcher* pResearcher = nullptr;

	pResearcher = readResearcher();

	try
	{
		readArticles(*pResearcher);
	}
	catch (const std::invalid_argument& e)
	{
		delete pResearcher;
		throw invalid_argument(e);
	}
	catch (...)
	{
		cout << "Error! Please call the support...";
		exit(1);
	}

	mainHospital.addEmployee(*pResearcher);

	cout << pResearcher->getName() << " added successfully as a researcher to hospital's research institute." << endl <<
		"The employee ID is: " << pResearcher->getEmployeeId() << endl;

	delete pResearcher;
}

// Selection 6
void addArticle(Hospital& mainHospital)
{
	int researcher_id;
	Researcher* pResearcher = nullptr;
	const Article* pArticle = nullptr;

	cout << "Please enter researcher's ID: ";
	cin >> researcher_id;

	pResearcher = mainHospital.getResearchInstitute().searchResearcher(researcher_id);

	if (!pResearcher)
	{
		cout << "The Researcher was not found." << endl;
		return;
	}

	pArticle = readArticle();
	pResearcher->addArticle(*pArticle);
	cout << "The artical added successfully!" << endl << endl;
	delete pArticle;
}

// Selection 7
void showDepartmentPatients(Hospital& mainHospital)
{
	Department* pDepartment = nullptr;
	string department_name;

	cin.ignore();
	cout << "Please enter the department in which you want to see the patients in it: ";
	getline(cin, department_name);

	pDepartment = mainHospital.searchDepartment(department_name);
	
	if (!pDepartment)
	{
		cout << "The Department was not found." << endl;
		return;
	}

	pDepartment->showPatients();
}

// Selection 8
void showAllHospitalEmployees(Hospital& mainHospital) 
{
	mainHospital.showEmployees(); 
}

// Selection 9
void showResearchInstituteResearchers(Hospital& mainHospital) 
{ 
	int selection;
	
	cout << "Select 1 to print all the researchers and 2 to print doctor-researchers specifically: ";
	cin >> selection;

	switch (selection)
	{
	case ALL:
	{
		mainHospital.showResearchers(); 
		break;
	}

	case DOC_RESEARCHER_ONLY:
	{
		mainHospital.showDoctorResearchers();
		break;
	}
	default:
		throw out_of_range("Selection is out of range!");
	}
}

// Selection 10
void showPatientVisitsByID(Hospital& mainHospital)
{
	int idToFind;
	
	cout << "Please enter the ID of the patient: ";
	cin >> idToFind;

	mainHospital.showPatientByID(idToFind);
}

// Selection 11
void checkOpPlusEqual(Hospital& mainHospital) noexcept(false)
{
	Employee* pEmployee = nullptr;
	Department* pDepartment = nullptr;
	string department_name;
	int selection;
	
	cin.ignore();
	cout << "Please choose a department to add an employee: ";
	getline(cin, department_name);

	pDepartment = mainHospital.searchDepartment(department_name);

	if (!pDepartment)
	{
		cout << "The Department was not found." << endl;
		return;
	}

	cout << "Enter 1 to add doctor or 2 to add nurse: ";
	cin >> selection;
	cin.ignore();

	switch (selection)
	{
		case DOCTOR:
			pEmployee = readDoctor(mainHospital.getResearchInstitute());
			break;
		case NURSE:
			pEmployee = readNurse();
			break;
		default:
			throw out_of_range("Selection is out of range!");
	}

	// Here the magic happens!
	*pDepartment += *pEmployee;
	cout << "The employee was added successfully!" << endl;
}

// Selection 12
void checkOpGt(Hospital& mainHospital)
{
	int id1, id2, selection;

	cout << "If you don't remember the researcher employee ID, return to the menu and print the researchers to get their IDs" << endl
		<< "To continue - Enter any number / To exit - Enter 0" << endl;
	cin >> selection;

	if (selection == 0)
		return;

	cout << "Enter the first Researcher employee ID: ";
	cin >> id1;
	Researcher* pResearcher1 = mainHospital.getResearchInstitute().searchResearcher(id1);

	if (!pResearcher1)
	{
		cout << "The Researcher was not found." << endl;
		return;
	}

	cout << "Enter the second Researcher employee ID: ";
	cin >> id2;

	Researcher* pResearcher2 = mainHospital.getResearchInstitute().searchResearcher(id2);

	if (!pResearcher2)
	{
		cout << "The Researcher was not found." << endl;
		return;
	}

	// Here the magic happens!
	if (*pResearcher1 > *pResearcher2)
		cout << pResearcher1->getName() << " has more articles than " << pResearcher2->getName();
	else
		cout << pResearcher2->getName() << " has more articles than " << pResearcher1->getName();
	cout << endl;
}

// Selection 13
void checkOpLtLt(Hospital& mainHospital)
{
	// Actually we use the operatoer<< through all the program but still we will show some of them
	cout << Researcher("Daniel Foo") << endl
		<< DoctorResearcher("Alon", "Lev") << endl
		<< Nurse("Yahli", 5) << endl;
}

// Read Functions
Nurse* readNurse()
{
	string nurse_name;
	int nofExperience;

	cout << "Please enter the nurse's name: ";
	getline(cin, nurse_name);

	cout << "Please enter the nurse's years of experience: ";
	cin >> nofExperience;

	return (new Nurse(nurse_name, nofExperience));
}

Doctor* readDoctor(ResearchInstitute& research_institute) noexcept(false)
{
	Doctor* pDoctor = nullptr;
	string name, expertField;
	int selection, nofSurgeons;
	
	cout << "Please enter the doctor's name: ";
	getline(cin, name);

	cout << "Please enter the doctor's expertise field: ";
	getline(cin, expertField);

	cout << "Please select the doctor specialization:" << endl
		<< "0. None." << endl << "1. Surgeon." << endl << "2. Researcher." << endl << "3. Suregon Researcher" << endl;
	cin >> selection;

	switch (selection)
	{
		case NONE:
		{
			pDoctor = new Doctor(name, expertField);
			break;
		}
		case SURGEON:
		{
			cout << "Please enter the number of surgeries: ";
			cin >> nofSurgeons;
			pDoctor = new Surgeon(name, expertField, nofSurgeons);
			break;
		}
		case DOC_RESEARCHER:
		{
			pDoctor = new DoctorResearcher(name, expertField);
			DoctorResearcher* temp = dynamic_cast<DoctorResearcher*>(pDoctor);
			readArticles(*temp);
			break;
		}
		case SUR_RESEARCHER:
		{
			cout << "Please enter the number of surgeries: ";
			cin >> nofSurgeons;
			pDoctor = new SurgeonResearcher(name, expertField, nofSurgeons);
			SurgeonResearcher* temp = dynamic_cast<SurgeonResearcher*>(pDoctor);
			readArticles(*temp);
			break;
		}
		default:
			throw out_of_range("Selection is out of range!");
	}
	return pDoctor;
}

Patient* readPatient(int patient_id)
{
	string patient_name;
	int day, month, year, gender;
	bool exit = false;

	cin.ignore();
	cout << "Please enter the patient name: ";
	getline(cin, patient_name);

	cout << "Please enter the patient birthday (dd mm yyyy): ";
	cin >> day >> month >> year;
	Date birthday(day, month, year);

	cout << "Please enter the patient gender (1 for male and 2 for female): ";
	cin >> gender;

	return (new Patient(patient_name, patient_id, birthday, (Patient::eGender)gender));
}

VisitCard* readVisit(Doctor& pDoctor, bool surgery_flag)
{
	VisitCard* pVisitCard = nullptr;
	string visit_reason;
	int day, month, year, room_num, isFasted;
	bool exit = false;

	cout << "Please enter the date of the treatment (dd mm yyyy): ";
	cin >> day >> month >> year;
	Date visit_date(day, month, year);

	cin.ignore();
	cout << "Please enter the visit reason: ";
	cin >> visit_reason;

	if (!surgery_flag)
		pVisitCard = new VisitCard(visit_date, visit_reason, pDoctor);
	else
	{
		cout << "Please enter the surgery room: ";
		cin >> room_num;
		
		cout << "Did you fast? (Yes - Enter any number / No - Enter 0) ";
		cin >> isFasted;

		pVisitCard = new SurgeonCard(visit_date, visit_reason, pDoctor, room_num, isFasted);
	}

	return pVisitCard;
}

Researcher* readResearcher()
{
	string researcher_name;

	cin.ignore();
	cout << "Please enter the researcher's name: ";
	getline(cin, researcher_name);

	return (new Researcher(researcher_name));
}

void readArticles(Researcher& pResearcher)
{
	Article* pArticle = nullptr;
	int indicator = true;

	while (indicator)
	{
		cout << "To add an article - Enter any number / To exit - Enter 0: ";
		cin >> indicator;

		if (!indicator)
			break;

		pArticle = readArticle();
		pResearcher.addArticle(*pArticle);
	}
}

Article* readArticle()
{
	string article_name, published_magazine;
	int day, month, year;

	cin.ignore();
	cout << "Articale name: ";
	getline(cin, article_name);

	cout << "Date of publication (dd mm yyyy): ";
	cin >> day >> month >> year;
	Date publish_date(day, month, year);

	cin.ignore();
	cout << "The name of the magazine that the articale was published in it: ";
	getline(cin, published_magazine);

	return new Article(publish_date, published_magazine, article_name);
}