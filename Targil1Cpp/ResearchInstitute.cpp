#include "ResearchInstitute.h"
#include "Hospital.h"
using namespace std;

ResearchInstitute::ResearchInstitute() : m_hospital(nullptr), m_pureResearchers(0) 
{
}

const set<Researcher*>& ResearchInstitute::getAllResearchers() const noexcept
{ 
	return m_researchers;
}

set<Researcher*>& ResearchInstitute::getAllResearchers() noexcept
{ 
	return m_researchers; 
}

void ResearchInstitute::addResearcher(Researcher& researcher) noexcept
{
	m_researchers.insert(&researcher);
	if (typeid(researcher) == typeid(Researcher))
		m_pureResearchers++;
}

Researcher* ResearchInstitute::searchResearcher(int researcher_id) const noexcept
{
	set<Researcher*>::iterator found = find_if(m_researchers.begin(), m_researchers.end(),
		[researcher_id](Researcher* researcher) { return researcher->getEmployeeId() == researcher_id; });

	return found == m_researchers.end() ? nullptr : *found;
}

void ResearchInstitute::showResearchers() const noexcept
{
	cout << "The Researchers In The Reserach Institute Are:" << endl;
	cout << "------------------------------------------------------------" << endl;

	if (m_researchers.empty())
	{
		cout << "There are no researchers in the research institute." << endl;
		return;
	}

	for (Researcher* researcher : m_researchers)
		cout << *researcher;
	cout << endl;
}

void ResearchInstitute::showDoctorResearchers() const noexcept
{
	int count = 0;
	cout << "The Doctors who are also researchers In The Reserach Institute Are:" << endl;
	cout << "------------------------------------------------------------" << endl;

	if (m_researchers.empty())
	{
		cout << "There are no researchers in the research institute." << endl;
		return;
	}

	for (Researcher* researcher : m_researchers)
	{
		Doctor* temp = dynamic_cast<Doctor*>(researcher);
		if (temp)
		{
			cout << *researcher;
			count++;
		}
	}
	if (count == 0)
		cout << "There are no doctors who are also researchers in the research institute." << endl;
	cout << endl;
}

void ResearchInstitute::saveResearchInstitute(const string& filename) const noexcept
{
	ofstream outFile(filename, ios::app);

	outFile << m_pureResearchers << endl;
	for (Researcher* researcher : m_researchers)
		if (typeid(*researcher) == typeid(Researcher))
			outFile << typeid(*researcher).name() + 6 << " " << *researcher << endl;
	outFile << endl;

	outFile.close();
}

void ResearchInstitute::loadResearchInstitute(ifstream& inFile) noexcept
{
	inFile >> m_pureResearchers;

	for (int i = 0; i < m_pureResearchers; i++)
	{
		Researcher* researcher;
		char type[20];
		inFile >> type;

		researcher = new Researcher(inFile);
		m_hospital->m_employees.insert(researcher);
		m_researchers.insert(researcher);
	}
}