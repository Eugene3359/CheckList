#pragma once
#include "cl_bascom.h"


int reader(std::string& str);

Task* setTask(Task Tasks[]);
void deleteTask(Task Tasks[]);
void changeTask(Task Tasks[]);
void list(Task Tasks[]);
void listDay(Task Tasks[]);
void listWeek(Task Tasks[]);
void listMonth(Task Tasks[]);
void sort(Task Tasks[]);
void listTasks(Task Tasks[]);
void searchTask(Task Tasks[]);

void menu(Task Tasks[]);