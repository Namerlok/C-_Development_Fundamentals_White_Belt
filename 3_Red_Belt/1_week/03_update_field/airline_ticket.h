/*
 * airline_ticket.h
 *
 *  Created on: 27 сент. 2020 г.
 *      Author: Zarka
 */

#pragma once

#ifndef AIRLINE_TICKET_H_
#define AIRLINE_TICKET_H_

#include <string>

using namespace std;

struct Date {
	int year;
	int month;
	int day;
};

struct Time {
	int hours;
	int minutes;
};

struct AirlineTicket {
	string from;
	string to;
	string airline;
	Date departure_date;
	Time departure_time;
	Date arrival_date;
	Time arrival_time;
	int price;
};

#endif /* AIRLINE_TICKET_H_ */

