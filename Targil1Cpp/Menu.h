#ifndef __MENU_H
#define __MENU_H

#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include "Hospital.h"

const enum eSelections {EXIT = 0, ADD_DEP, ADD_NUR, ADD_DOC, ADD_VIS, ADD_RES, ADD_ART, SHOW_PAT, SHOW_EMP, SHOW_RES, SEARCH_VIS, CHECK_OP_PLUS_EQUAL, CHECK_OP_GT, CHECK_OP_LT_LT};
const enum eOpPlusEqualSelection {DOCTOR = 1, NURSE};
const enum eResearchersPrint { ALL = 1, DOC_RESEARCHER_ONLY };
const enum eDoctorsType {NONE, SURGEON, DOC_RESEARCHER, SUR_RESEARCHER};
const int MAX_NAME_LEN = 100;

void printMenu();
bool checkSelection(int selection);
void executeSelection(Hospital& mainHospital, int selection);

void addDepartment(Hospital& mainHospital);
void addNurse(Hospital& mainHospital);
void addDoctor(Hospital& mainHospital);
void addVisit(Hospital& mainHospital);
void addResearcher(Hospital& mainHospital);
void addArticle(Hospital& mainHospital);

Nurse* readNurse();
Doctor* readDoctor(ResearchInstitute& research_institute) noexcept(false);
Patient* readPatient(int patient_id) noexcept(false);
VisitCard* readVisit(Doctor& pDoctor, bool surgery_flag) noexcept(false);
Researcher* readResearcher();
void readArticles(Researcher& pResearcher);
Article* readArticle();

void showDepartmentPatients(Hospital& mainHospital);
void showAllHospitalEmployees(Hospital& mainHospital);
void showResearchInstituteResearchers(Hospital& mainHospital);
void showPatientVisitsByID(Hospital& mainHospital);

void checkOpPlusEqual(Hospital& mainHospital);
void checkOpGt(Hospital& mainHospital);
void checkOpLtLt(Hospital& mainHospital);

#endif // __MENU_H