#include "cl_bascom.h"

//--------------------------------------------------------------------------------

std::string toLower(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

void displayTitle() {
	system("cls");
	std::cout << std::setw(83) << "---ToDo List---\n\n";
}

//--------------------------------------------------------------------------------

bool isEmpty(Date& date) {
	return date.day == 50;
}

Date str_to_date(const std::string& str) {
	// [dd.mm.yy hh:mm]
	// перевірка довжини прийнятого аргумента
	size_t size = str.length();
	if (size < 9 || size > 14) {
		return { 50, 0, 0, 0, 0 };
	}

	// оголошення змінних
	Date result;
	unsigned short* sequence[5] = { &result.day, &result.month,
		&result.year, &result.hour, &result.minute };
	unsigned short number = 0;
	size_t i = 0;
	
	// заповнення 5 полів структури Date
	for (size_t parts = 0; parts < 5; parts++) {
		while (isdigit(str[i]) && i < size) {
			number *= 10;
			number += str[i] - '0';
			i++;
		}
		*sequence[parts] = number;
		number = 0;
		i++;
	}

	// перевірка корректності дати
	if (result.day > 31 || result.month > 12 || result.hour > 24 || result.minute > 60) {
		return { 50, 0, 0, 0, 0 };
	}
	return result;
}

std::string date_to_str(const Date& date) {
	std::string str = (date.day < 10) ? "0" + std::to_string(date.day) : std::to_string(date.day);
	str = (date.month < 10) ? str + ".0" + std::to_string(date.month) : str + "." + std::to_string(date.month);
	str = (date.year < 10) ? str + ".0" + std::to_string(date.year) : str + "." + std::to_string(date.year);
	str = (date.hour < 10) ? str + " 0" + std::to_string(date.hour) : str + " " + std::to_string(date.hour);
	str = (date.minute < 10) ? str + ":0" + std::to_string(date.minute) : str + ":" + std::to_string(date.minute);
	return str;
}

Date curentDate() {
	char str[15];

	// отримання часу
	time_t t = time(NULL);
	tm* local = localtime(&t);

	// форматування часу
	char format[] = "%d.%m.%y %R";
	strftime(str, 15, format, local);

	return str_to_date(str);
}

//--------------------------------------------------------------------------------

bool isEmpty(Task& task) {
	return (task.name == "" && task.description == "");
}

void copyTasks(Task* source, Task* destination, size_t n) {
	for (size_t i = 0; i < n; i++) {
		destination[i] = source[i];
	}
}

Task* extendTasks(Task Tasks[]) {
	// створення нового масиву
	Task* new_tasks = new Task[capacity + 10];

	// перенесення завдань
	copyTasks(Tasks, new_tasks);
	capacity += 10;
	return new_tasks;
}

void clearTasks(Task Tasks[]) {
	Task empty = { "", "", NULL, {NULL, NULL, NULL, NULL, NULL} };
	for (size_t i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
		Tasks[i] = empty;
	}
}

//--------------------------------------------------------------------------------