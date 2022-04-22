#include "String.h"
//Constructors/destructor/operators/private functions
String::String():size(1)
{
	data = new char[1]{ '\0' };
}

String::String(const char* text) : size(stringLen(text))
{
	data = new char[size + 1];
	stringCopy(data, text);
}

String::String(const String& other)
{
	copy(other);
}

String::~String()
{
	free();
}

const String String::operator*(size_t k)
{
	String temp;
	temp.resize(size * k);
	for (size_t i = 0; i < (k - 1) * size; i += size)
	{
		stringCopy(&temp.data[i], data);
	}
	return temp;
}

const String& String::operator=(const String& other)
{
	free();
	copy(other);
	return *this;
}

const String& String::operator=(const char* toAssign)
{
	if(!stringCompare(data, toAssign))
	{
		resize(stringLen(toAssign));
		stringCopy(data, toAssign);
	}

	return *this;
}

void String::resize(size_t newSize)
{
	if (newSize > 0 || newSize!=size)
	{
		size = newSize;
		char* temp = new char[newSize + 1];
		free();
		data = temp;
	}

}

void String::copy(const String& other)
{
	size = other.size;
	data = new char[size + 1];
	stringCopy(data, other.data);
}

void String::free()
{
	delete[] data;
}

//helper functions
size_t stringLen(const char* str)

{
	int len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}

void stringCopy(char* dest, const char* source)
{
	size_t copyingLen = stringLen(source);
	for (size_t i = 0; i < copyingLen; i++)
	{
		dest[i] = source[i];
	}
	dest[copyingLen] = '\0';
}

void stringCopy(char* dest, const char* source, size_t copyingLen)
{
	for (size_t i = 0; i < copyingLen; i++)
	{
		dest[i] = source[i];
	}
	dest[copyingLen] = '\0';
}

bool stringCompare(const char* str1, const char* str2)
{
	size_t str1Len = stringLen(str1);
	if (str1Len != stringLen(str2))
		return false;
	for (size_t i = 0; i < str1Len; i++)
	{
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}

//functions/operators
const char* String::getData() const
{
	return data;
}

bool String::contains(const char* searched)
{
	size_t searchedLen = stringLen(searched);
	if (searchedLen > size)
		return false;
	size_t searchIterations = size - searchedLen + 1;
	for (size_t i = 1; i < searchIterations; i++)
	{
		if (stringCompare(searched, getInterval(i, i + searchedLen - 1)) == 1)
			return true;
	}
	return false;
}

const char* String::getStartingFrom(size_t index)
{
	return &data[index];
}

const char* String::getInterval(size_t beg, size_t end)
{
	const size_t substrLen = end - beg + 1;
	char* subString = new char[substrLen + 1];
	stringCopy(subString, &data[beg - 1], substrLen);
	return subString;
}

char& String::operator[](size_t index)
{
	try
	{
		if (index > size || index < 0)
			throw std::exception();
		return data[index];
	}
	catch(std::exception& e)
	{
		std::cout << "Error";
	}
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.getData();
	return os;
}

