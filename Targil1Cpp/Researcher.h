#ifndef __RESEARCHER_H
#define __RESEARCHER_H

#include "Article.h"
#include "Employee.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Array.h"

class Researcher : virtual public Employee
{
protected:
	Array<Article*> m_articles;

public:
	// C'tors
	Researcher(const std::string& name, const Array<Article*>& articles) noexcept(false);
	Researcher(const std::string& name) noexcept(false);
	Researcher(std::ifstream& in) noexcept;
	virtual ~Researcher() noexcept;

	// Get Functions
	const Array<Article*>& getArticles() const noexcept;
	
	// Set Functions
	void setArticles(Array<Article*> articles) noexcept;
	
	// Add Functions
	void addArticle(const Article& new_article) noexcept;

	// Operator Functions
	bool operator>(const Researcher& researcher) noexcept;

	// Stream Functions
	virtual void toOs(std::ostream& os = std::cout) const noexcept override;
	void showArticles(std::ostream& os) const noexcept;
	virtual void fromOs(std::istream& in) noexcept override;
	
	// Other Functions
	virtual Employee* clone() const noexcept override;

	// Deleted Functions
	const Researcher& operator=(const Researcher& other) = delete;

protected:
	// C'tors
	Researcher(const Researcher& researcher) noexcept;
	Researcher(Researcher&& researcher) noexcept;
};

#endif // __RESEARCHER_H