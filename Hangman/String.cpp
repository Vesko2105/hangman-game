#include "String.h"

const size_t BUFF_SIZE = 1024;

//helper functions
template<class T>
size_t stringLen(T str)
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

void stringCopy(String& dest, const char* source)
{
	size_t copyingLen = stringLen(source);
	for (size_t i = 0; i < copyingLen; i++)
	{
		dest[i] = source[i];
	}
	dest[copyingLen] = '\0';
}

void stringCopy(String& dest, const char* source, size_t copyingLen)
{
	for (size_t i = 0; i < copyingLen; i++)
	{
		dest[i] = source[i];
	}
	dest[copyingLen] = '\0';
}

//Constructors/destructor/operators/private functions
String::String() :size(1)
{
	data = new char[1]{ '\0' };
}

String::String(const char* text)
{
	copy(text);
}

String::String(const String& other)
{
	copy(other);
}

String::~String()
{
	free();
}

const String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

const String& String::operator=(const char* text)
{
	free();
	copy(text);
	return *this;
}

const String& String::operator=(char letter)
{
	free();

	size = 2;
	data = new char[size];
	data[0] = letter;
	data[1] = '\0';

	return *this;
}

void String::copy(const String& other)
{
	size = other.size;
	data = new char[size];
	stringCopy(data, other.data);
}

void String::copy(const char* string)
{
	size = stringLen(string) + 1;
	data = new char[size];
	stringCopy(data, string);
}

void String::free()
{
	delete[] data;
}

//functions/operators
const char* String::getData() const
{
	return data;
}

size_t String::getSize() const
{
	return size;
}

const String& String::get(const String& src, size_t beg, char terminating)
{
	size_t srcIndex = beg;
	size_t destIndex = 0;
	char* temp = new char[src.getSize()];
	while (src[srcIndex] != terminating)
	{
		temp[destIndex++] = src[srcIndex++];
	}
	temp[destIndex] = 0;
	*this = temp;
	return *this;
}


int String::contains(const String& searched) const
{
	size_t searchedLen = stringLen(searched);
	if (searchedLen > size)
		return -1;
	size_t searchIterations = size - searchedLen + 1;
	for (size_t i = 1; i <= searchIterations; i++)
	{
		if (searched == substring(i, i + searchedLen - 1))
			return i;
	}
	return -1;
}

int String::contains(char letter) const
{
	for (size_t i = 1; i < size; i++)
	{
		if (data[i] == letter)
			return i;
	}
	return -1;
}

const String String::substring(size_t index) const
{
	return &data[index];
}

const String String::substring(size_t beg, size_t end) const
{
	size_t intervalLen = end - beg + 1;
	char* temp = new char[intervalLen + 1];
	stringCopy(temp, &data[beg - 1], intervalLen);
	String interval = temp;
	return interval;
}

const String& String::reverse(String& str)
{
	if (str.getSize() > 2)
	{
		size_t lastIndex = str.getSize() - 2;
		for (size_t i = 0; i < lastIndex; i++)
		{
			char temp = str[lastIndex - i];
			str[lastIndex - i] = str[i];
			str[i] = temp;
		}
	}
	return str;
}


char& String::operator[](size_t index)
{
	if (index >= size || index < 0)
		throw "Invalid index!";
	else
		return data[index];
}

const char& String::operator[](size_t index) const
{
	if (index < 0 || index >= size)
		throw "Invalid index";
	return data[index];
}


String operator*(const String& str, size_t k)
{
	String multiplied = str;
	size_t ogLen = str.getSize() - 1;
	size_t newSize = ogLen * k + 1;
	char* temp = new char[newSize];
	if (k > 1)
	{
		for (size_t i = 0; i <= (k - 1) * ogLen; i += ogLen)
		{
			stringCopy(&temp[i], str.getData(), ogLen);
		}
		temp[newSize - 1] = '\0';
		multiplied = temp;
	}
	return multiplied;
}

String operator+(const String& lhs, const String& rhs)
{
	size_t lhsSize = lhs.getSize();
	size_t rhsSize = rhs.getSize();
	size_t newSize = lhsSize + rhsSize - 1;
	char* temp = new char[newSize];
	stringCopy(temp, lhs.getData());
	stringCopy(&temp[lhsSize - 1], rhs.getData());
	return temp;
}

String operator+(const String& lhs, char rhs)
{
	size_t newSize = lhs.getSize() + 1;
	char* concat = new char[newSize];
	stringCopy(concat, lhs.getData());
	concat[newSize - 2] = rhs;
	concat[newSize - 1] = '\0';
	return concat;
}

const String& operator+=(String& lhs, const String& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

const String& operator+=(String& lhs, char rhs)
{
	lhs = lhs + rhs;
	return lhs;
}


std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.getData();
	return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[BUFF_SIZE];
	is >> buff;
	str = buff;
	return is;
}

bool operator==(const String& lhs, const String& rhs)
{
	size_t lhsLen = lhs.getSize();
	if (lhsLen != rhs.getSize())
		return false;
	for (size_t i = 0; i < lhsLen; i++)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

bool operator==(const String& lhs, const char* rhs)
{
	size_t lhsLen = lhs.getSize();
	if (lhsLen != stringLen(rhs))
		return false;
	for (size_t i = 0; i < lhsLen; i++)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

bool operator==(const char* lhs, const String& rhs)
{
	size_t lhsLen = stringLen(lhs);
	if (lhsLen != rhs.getSize())
		return false;
	for (size_t i = 0; i < lhsLen; i++)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator!=(const String& lhs, const char* rhs)
{
	return !(lhs == rhs);
}

bool operator!=(const char* lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator>=(const String& lhs, const String& rhs)
{
	size_t lhsLen = lhs.getSize(), rhsLen = rhs.getSize();
	bool isLongerOrEqual = false;
	size_t shortest = lhsLen;
	if (shortest >= rhsLen)
	{
		shortest = rhsLen;
		isLongerOrEqual = true;
	}
	for (size_t i = 0; i < shortest; i++)
	{
		if (lhs[i] < rhs[i])
			return false;
	}
	return isLongerOrEqual;

}

bool operator>(const String& lhs, const String& rhs)
{

	size_t lhsLen = lhs.getSize(), rhsLen = rhs.getSize();
	bool isLonger = false;
	size_t shortest = lhsLen;
	if (shortest > rhsLen)
	{
		shortest = rhsLen;
		isLonger = true;
	}
	for (size_t i = 0; i < shortest; i++)
	{
		if (lhs[i] < rhs[i])
			return false;
	}
	return isLonger;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return !(lhs > rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
	return !(lhs >= rhs);
}

const String getReversed(const String& str)
{
	String reversed = str;
	if (str.getSize() > 2)
	{
		size_t lastIndex = str.getSize() - 2;
		for (size_t i = 0; i < lastIndex; i++)
		{
			char temp = reversed[lastIndex - i];
			reversed[lastIndex - i] = str[i];
			reversed[i] = temp;
		}
	}
	return reversed;
}

const String intToString(int x)
{
	size_t reversed = 0;
	while (x != 0)
	{
		(reversed *= 10) += x % 10;
		x /= 10;
	}

	String num;
	size_t index = 0;
	while (reversed != 0)
	{
		num += (reversed % 10) + '0';
		reversed /= 10;
		index++;
	}
	return num;
}
