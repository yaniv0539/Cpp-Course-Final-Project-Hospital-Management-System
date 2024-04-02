#include "Article.h"
using namespace std;

Article::Article(const Date& publishedDate, const string& publishedMagazine, const string& name) noexcept(false) : m_publishedDate(publishedDate)
{
	setPublishedMagazine(publishedMagazine);
	setName(name);
}

Article::Article(ifstream& in) noexcept
{
	in >> *this;
}

const Date& Article::getPublishedDate() const noexcept
{
	return m_publishedDate; 
}

Date& Article::getPublishedDate() noexcept
{ 
	return m_publishedDate; 
}

const string& Article::getPublishedMagazine() const noexcept
{ 
	return m_publishedMagazine;
}

const string& Article::getName() const noexcept
{ 
	return m_name;
}

void Article::setPublishedDate(const Date& publishedDate) noexcept
{ 
	m_publishedDate = publishedDate; 
}

void Article::setPublishedMagazine(const string& publishedMagazine) noexcept(false)
{
	if (publishedMagazine == "") 
		throw invalid_argument("Published magazine name can not be empty");
	m_publishedMagazine = publishedMagazine;
}

void Article::setName(const string& name) noexcept(false)
{
	if (name == "") 
		throw invalid_argument("Article name can not be empty");
	m_name = name;
}

void Article::show(ostream& os) const noexcept
{
	os << "Name: " << m_name
		<< ", Published at: " << m_publishedMagazine
		<< ", Published on: " << m_publishedDate;
}

ostream& operator<<(ostream& os, const Article& article) noexcept
{
	if (typeid(os) == typeid(ofstream))
	{
		os << article.m_name.length() << " " << article.m_name << "\n"
			<< article.m_publishedMagazine.length() << " " << article.m_publishedMagazine << "\n"
			<< article.m_publishedDate;
	}
	else
	{
		article.show(os);
	}
	return os;
}

istream& operator>>(std::istream& in, Article& article) noexcept
{
	if (typeid(in) == typeid(ifstream))
	{
		int name_len, publishedMagazine_len;
		in >> name_len;
		in.ignore();
		getline(in, article.m_name);
		in >> publishedMagazine_len;
		in.ignore();
		getline(in, article.m_publishedMagazine);
		in >> article.m_publishedDate;
	}
	return in;
}

Article::Article(const Article& other) noexcept : m_publishedDate(other.m_publishedDate)
{
	*this = other;
}
	
Article::Article(Article&& other) noexcept : m_publishedDate(std::move(other.m_publishedDate))
{
	*this = std::move(other);
}

const Article& Article::operator=(const Article& other) noexcept
{
	if (this != &other)
	{
		setName(other.m_name);
		setPublishedMagazine(other.m_publishedMagazine);
	}
	return *this;
}

const Article& Article::operator=(Article&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_name, other.m_name);
		std::swap(m_publishedMagazine, other.m_publishedMagazine);
	}
	return *this;
}

Article* Article::clone() const noexcept
{
	return new Article(*this);
}