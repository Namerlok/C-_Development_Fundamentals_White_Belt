//============================================================================
// Name        : 14_Implement_fun_declared_in_header_2.cpp
// Author      : Arkadiy Zagrebelnyi
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>
#include "phone_number.h"
#include "test_runner.h"
using namespace std;

void test_phone_number() {
	string str1 = "+7-495-111-22-33";
	PhoneNumber num1(str1);
	AssertEqual(num1.GetCountryCode(), "7", "+7-495-111-22-33");
	AssertEqual(num1.GetCityCode(), "495", "+7-495-111-22-33");
	AssertEqual(num1.GetLocalNumber(), "111-22-33", "+7-495-111-22-33");
	AssertEqual(num1.GetInternationalNumber(), "+7-495-111-22-33", "+7-495-111-22-33");

	const string str2 = "+7-495-1112233";
	PhoneNumber num2(str2);
	AssertEqual(num2.GetCountryCode(), "7", "+7-495-1112233");
	AssertEqual(num2.GetCityCode(), "495", "+7-495-1112233");
	AssertEqual(num2.GetLocalNumber(), "1112233", "+7-495-1112233");
	AssertEqual(num2.GetInternationalNumber(), "+7-495-1112233", "+7-495-1112233");

	const string str3 = "+323-22-460002";
	PhoneNumber num3(str3);
	AssertEqual(num3.GetCountryCode(), "323", "+323-22-460002");
	AssertEqual(num3.GetCityCode(), "22", "+323-22-460002");
	AssertEqual(num3.GetLocalNumber(), "460002", "+323-22-460002");
	AssertEqual(num3.GetInternationalNumber(), "+323-22-460002", "+323-22-460002");

	const string str4 = "+1-2-coursera-cpp";
	PhoneNumber num4(str4);
	AssertEqual(num4.GetCountryCode(), "1", "+1-2-coursera-cpp");
	AssertEqual(num4.GetCityCode(), "2", "+1-2-coursera-cpp");
	AssertEqual(num4.GetLocalNumber(), "coursera-cpp", "+1-2-coursera-cpp");
	AssertEqual(num4.GetInternationalNumber(), "+1-2-coursera-cpp", "+1-2-coursera-cpp");
}

int main() {
	TestRunner test;
	test.RunTest(test_phone_number, "test_phone_number");

	return 0;
}

