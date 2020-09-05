/*
 * phone_number.cpp
 *
 *  Created on: 16 июл. 2020 г.
 *      Author: Zarka
 */

#include <iostream>
#include "phone_number.h"
#include <stdexcept>

void SkipSpace(const string & str, unsigned int &iter) {
	while (iter < str.size() && isspace(str[iter]))
		++iter;
}

PhoneNumber::PhoneNumber(const string &international_number) {
	unsigned int iter = 0;
	SkipSpace(international_number, iter);

//	cerr << international_number << "international_number[iter] = " << international_number[iter] << endl;
	if (international_number[iter] != '+')
		throw invalid_argument("invalid argument");
	else
		++iter;

	while(iter < international_number.size() && international_number[iter] != '-')
		country_code_ += international_number[iter++];
	++iter;

//	cerr << country_code_ << endl;
	if (country_code_.empty())
		throw invalid_argument("invalid argument");

	while(iter < international_number.size() && international_number[iter] != '-')
		city_code_ += international_number[iter++];
	++iter;

//	cerr << city_code_ << endl;
	if (city_code_.empty())
			throw invalid_argument("invalid argument");

	while(iter < international_number.size() && !isspace(international_number[iter]))
		local_number_ += international_number[iter++];
	++iter;

//	cerr << local_number_ << endl;
	if (local_number_.empty())
		throw invalid_argument("invalid argument");
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

/* авторсое решение
#include <stdexcept>
#include <string>
#include <sstream>
#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream is(international_number);

  char sign = is.get();
  getline(is, country_code_, '-');
  getline(is, city_code_, '-');
  getline(is, local_number_);

  if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
  }
}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

string PhoneNumber::GetCityCode() const {
  return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
  return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
 */

