#include "Researcher.h"
using namespace std;

Researcher::Researcher(const string& name, const Array<Article*>& articles) noexcept(false) : Employee(name)
{ 
	setArticles(articles); 
}

Researcher::Researcher(const string& name) noexcept(false) : Employee(name)
{ 
	m_articles.reserve(1);
}

Researcher::Researcher(ifstream& in) noexcept : Employee(in)
{
	fromOs(in);
}

Researcher::Researcher(const Researcher& researcher) noexcept : Employee(researcher)
{ 
	setArticles(researcher.m_articles); 
}

Researcher::Researcher(Researcher&& researcher) noexcept : Employee(std::move(researcher))
{
	std::swap(m_articles, researcher.m_articles);
}

Researcher::~Researcher() noexcept
{
	for (Article* article : m_articles)
		delete article;
}

const Array<Article*>& Researcher::getArticles() const noexcept
{ 
	return m_articles;
}

void Researcher::setArticles(Array<Article*> articles) noexcept
{
	for (Article* article : m_articles)
		delete article;

	m_articles.reserve(articles.capacity());

	for (Article* article : articles)
		m_articles.push_back(article->clone());
}

void Researcher::addArticle(const Article& new_article) noexcept
{
	m_articles.push_back(new_article.clone());
}

bool Researcher::operator>(const Researcher& researcher) noexcept
{
	return (m_articles.size() > researcher.m_articles.size());
}

void Researcher::toOs(ostream& os) const noexcept
{
	Employee::toOs(os);
	showArticles(os);
}

void Researcher::showArticles(ostream& os) const noexcept
{
	if (typeid(os) == typeid(ofstream))
	{
		os << m_articles.size() << endl;
		for (Article* article : m_articles)
			os << *article << endl;
	}
	else
	{
		int i = 1;
		if (m_articles.empty())
			os << endl << "-->No articles published." << endl;
		else
		{
			os << endl << "-->Articles:" << endl;
			for (Article* article : m_articles)
				os << "   #" << i++ << ": " << *article << endl;
		}
		os << endl;
	}
}

void Researcher::fromOs(istream& in) noexcept
{
	int nofArticles;
	in >> nofArticles;

	m_articles.reserve(nofArticles);

	for (int i = 0; i < nofArticles; i++)
	{
		Article* article = new Article((ifstream&)in);
		m_articles.push_back(article);
	}
}

Employee* Researcher::clone() const noexcept
{
	return new Researcher(*this);
}