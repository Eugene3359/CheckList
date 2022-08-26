#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

static size_t capacity;


void displayTitle();
std::string toLower(std::string str);


struct Date {
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
};

bool isEmpty(Date& date);
Date str_to_date(const std::string& str);
std::string date_to_str(const Date& date);
Date curentDate();


struct Task {
	std::string name;
	std::string description;
	unsigned short priority;
	Date deadline;
};

bool isEmpty(Task& task);
void copyTasks(Task* source, Task* destination, size_t n = capacity);
Task* extendTasks(Task Tasks[]);
void clearTasks(Task Tasks[]);