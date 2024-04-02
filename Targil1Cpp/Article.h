#ifndef __ARTICLE_H
#define __ARTICLE_H

#pragma warning(disable: 4996)
#include <fstream>
#include <iostream>
#include <string>
#include "Date.h"

class Article
{
private:
	Date m_publishedDate;
	std::string m_publishedMagazine;
	std::string m_name;

public:
	// C'tors
	Article(const Date& publishedDate, const std::string& publishedMagazine, const std::string& name) noexcept(false);
	Article(std::ifstream& in) noexcept;

	// Get Functions
	const Date& getPublishedDate() const noexcept;
	Date& getPublishedDate() noexcept;
	const std::string& getPublishedMagazine() const noexcept;
	const std::string& getName() const noexcept;

	// Set Functions
	void setPublishedDate(const Date& publishedDate) noexcept;
	void setPublishedMagazine(const std::string& publishedMagazine) noexcept(false);
	void setName(const std::string& articleName) noexcept(false);

	// Stream Functions
	void show(std::ostream& os = std::cout) const noexcept;
	friend std::ostream& operator<<(std::ostream& os, const Article& article) noexcept;
	friend std::istream& operator>>(std::istream& in, Article& article) noexcept;

	// Other Functions
	Article* clone() const noexcept;

private:
	Article() = default;
	Article(const Article& other) noexcept;
	Article(Article&& other) noexcept;
	const Article& operator=(const Article& other) noexcept;
	const Article& operator=(Article&& other) noexcept;
};

#endif // __ARTICLE_H