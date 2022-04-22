#pragma once
#include<iostream>

class String
{
private:
	char* data;
	size_t size;

	void resize(size_t);
	void copy(const String&);
	void free();
public:
	String();
	String(const char*);
	String(const String&);
	~String();

	const char* getData() const;

	bool contains(const char*);
	const char* getStartingFrom(size_t index);
	const char* getInterval(size_t beg, size_t end);
	const String& operator=(const String&);
	const String& operator=(const char*);
	const String operator*(size_t k);
	char& operator[](size_t index);
};

size_t stringLen(const char*);
void stringCopy(char*, const char*);
void stringCopy(char*, const char*, size_t);
bool stringCompare(const char* str1, const char* str2);

const String& operator+(const String& lhs, const String& rhs);
const String& operator+=(String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::ostream& is, String& str);

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
