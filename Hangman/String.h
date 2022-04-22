#pragma once
#include<iostream>

class String
{
private:
	char* data;
	size_t length;

	void copy(const String&);
	void copy(const char*);
	void free();

public:
	String();
	String(const char*);
	String(const String&);
	~String();

	const char* const getData() const;
	size_t getSize() const;

	const String& get(const String&, size_t, char);

	int contains(const String&) const;
	int contains(char) const;

	const String substring(size_t index) const;
	const String substring(size_t beg, size_t end) const;

	const String& reverse(String&);

	const String& operator=(const String&);
	const String& operator=(const char*);
	const String& operator=(char);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	String& getline(std::istream& is, size_t buffSize);
};

String operator*(const String&, size_t);
String operator+(const String&, const String&);
String operator+(const String&, char);
String operator+(const String&, int);
const String& operator+=(String&, const String&);
const String& operator+=(String&, char);

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);

bool operator==(const String&, const String&);
bool operator==(const String&, const char*);
bool operator==(const char*, const String&);
bool operator!=(const String&, const String&);
bool operator!=(const String&, const char*);
bool operator!=(const char*, const String&);
bool operator>=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);

const String getReversed(const String&);
const String intToString(int x);
