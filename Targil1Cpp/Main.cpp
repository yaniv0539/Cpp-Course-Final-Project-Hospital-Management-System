// Alon Bletter ID 318650751
// Yaniv Zamir ID 206593444
#include "Menu.h"
#include <iostream>
using namespace std;

// This program runs a hospital database system which includes information about the hospital's departments, its stuff and patients. //
int main()
{
	Hospital mainHospital;
	int selection;

	try
	{
		mainHospital.loadHospital("data.txt");
	}
	catch (const std::invalid_argument& e)
	{
		cout << e.what() << endl;

		// Hard coded insertion 
		// Notice patients are created only when data.txt was not found - We weren't assigned to save patients info
		mainHospital.addDepartment("Lev");
		mainHospital.addDepartment("Reot");
		mainHospital.addDepartment("Yadaim");
	
		Article art1(Date(1, (Date::eMonths)1, 2000), "Mada", "Galey Moah");
		Article art2(Date(2, (Date::eMonths)2, 2001), "Mehkar", "Mahalot Or");
		Article art3(Date(3, (Date::eMonths)3, 2002), "Guf Adam", "Kosher");
		Article art4(Date(4, (Date::eMonths)4, 2003), "Micro Biologia", "O2");

		Doctor doc1("Yossi", "Lev");
		Doctor doc2("Dani", "Reot");
		Surgeon sur1("Moshe", "Lev", 19);
		Surgeon sur2("Dvir", "Yadaim", 20);

		DoctorResearcher docRes1("Alon", "Lev");
		docRes1.addArticle(art1);
		DoctorResearcher docRes2("Yaniv", "Moah");
		docRes2.addArticle(art2);

		SurgeonResearcher surRes1("Jacob", "Legs", 10);
		SurgeonResearcher surRes2("Yazek", "Berkaim", 99);

		Nurse nur1("Yahli", 5);
		Nurse nur2("Ofrat", 4);
		Nurse nur3("Zehava", 3);

		Researcher res1("Daniel Foo");
		res1.addArticle(art3);
		Researcher res2("Keren Kalif");
		res2.addArticle(art4);

		mainHospital.addEmployee(res1);
		mainHospital.addEmployee(res2);

		mainHospital.addEmployee(doc1, "Lev");
		mainHospital.addEmployee(doc2, "Reot");
		mainHospital.addEmployee(sur1, "Yadaim");
		mainHospital.addEmployee(sur2, "Lev");
		mainHospital.addEmployee(docRes1, "Lev");
		mainHospital.addEmployee(docRes2, "Lev");
		mainHospital.addEmployee(surRes1, "Reot");
		mainHospital.addEmployee(surRes2, "Yadaim");

		mainHospital.addEmployee(nur1, "Lev");
		mainHospital.addEmployee(nur2, "Reot");
		mainHospital.addEmployee(nur3, "Yadaim");

		VisitCard vis1(Date(1, (Date::eMonths)1, 2000), "Hani mamash hole!", doc1);
		VisitCard vis2(Date(2, (Date::eMonths)2, 2024), "Eize hom ya hoaradi!", doc2);

		SurgeonCard surCar1(Date(8, (Date::eMonths)8, 2020), "Mehizot", sur1, 1, true);
		SurgeonCard surCar2(Date(8, (Date::eMonths)8, 2020), "Gidul Shafir", sur2, 2, false);

		Patient pat1("Menny", 123, Date(5, (Date::eMonths)5, 1995), (Patient::eGender)1);
		Patient pat2("Levana", 124, Date(6, (Date::eMonths)6, 1996), (Patient::eGender)2);
		Patient pat3("Orna", 125, Date(7, (Date::eMonths)7, 1997), (Patient::eGender)2);
		Patient pat4("Motti", 126, Date(8, (Date::eMonths)8, 1998), (Patient::eGender)1);

		pat1.addVisit(&vis1);
		pat2.addVisit(&vis2);
		pat3.addVisit(&surCar1);
		pat4.addVisit(&surCar2);

		mainHospital.addPatient(pat1, "Lev");
		mainHospital.addPatient(pat2, "Reot");
		mainHospital.addPatient(pat3, "Yadaim");
		mainHospital.addPatient(pat4, "Lev");
	}
	catch (...)
	{
		cout << "Error! Please call the support...";
		exit(1);
	}

	// Interactive Menu:
	do
	{
		printMenu();
		cin >> selection;

		if (!checkSelection(selection))
			cout << "Invalid select! Please try again!!!" << endl;
		else if (selection != EXIT)
		{
			cout << endl;
			executeSelection(mainHospital, selection);
			system("pause");
			cout << endl;
		}
	} while (selection != EXIT);

	mainHospital.saveHospital("data.txt");
}