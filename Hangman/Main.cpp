#include<iostream>
#include"User.h"

int main()
{
	User user = User("email", "name", "pass", 0);
	int a;
	std::cin >> a;
	std::cout << user.getEmail();
}