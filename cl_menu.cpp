#include "cl_menu.h"

//--------------------------------------------------------------------------------

int reader(std::string& str) {
	str = toLower(str);
	if (str == "help") {
		return 0;
	}
	else if (str == "set") {
		return 1;
	}
	else if (str == "delete") {
		return 2;
	}
	else if (str == "change") {
		return 3;
	}
	else if (str == "list") {
		return 4;
	}
	else if (str == "name") {
		return 5;
	}
	else if (str == "description") {
		return 6;
	}
	else if (str == "priority") {
		return 7;
	}
	else if (str == "deadline") {
		return 8;
	}
	else if (str == "day") {
		return 9;
	}
	else if (str == "week") {
		return 10;
	}
	else if (str == "month") {
		return 11;
	}
	else if (str == "sort") {
		return 12;
	}
	else if (str == "search") {
		return 13;
	}
	else if (str == "clear") {
		return 98;
	}
	else if (str == "back") {
		return 99;
	}
	else if (str == "exit") {
		return 100;
	}
	return -1;
}

//--------------------------------------------------------------------------------

Task* setTask(Task Tasks[]) {
	size_t n = 0;
	std::string data;

	// підрахунок скільки вже є завдань
	while (n < capacity && !isEmpty(Tasks[n])) {
		n++;
	}

	// якщо список завдань переповнений - розширюємо масив
	if (n == capacity) {
		Tasks = extendTasks(Tasks);
	}

	// заповнення завдання
	std::cout << "Enter name of a task (up to 21 symbols): ";
	std::cin.get();
	getline(std::cin, Tasks[n].name);
	if (Tasks[n].name.length() > 21) Tasks[n].name = Tasks[n].name.substr(0, 21);
	std::cout << "Enter description of a task: ";
	getline(std::cin, Tasks[n].description);
	std::cout << "Enter priority of a task (0-9): ";
	std::cin >> Tasks[n].priority;
	do {
		std::cout << "Enter deadline of a task in format [dd.mm.yy hh:mm] or \"N\" if there is no deadline: ";
		std::cin.get();
		getline(std::cin, data);
		if (data == "N" || data == "n") {
			data = "00.00.00 00:00";
		}
		Tasks[n].deadline = str_to_date(data);
		if (isEmpty(Tasks[n].deadline)) std::cout << "Wrong input!\n";
	} while (isEmpty(Tasks[n].deadline));
	return Tasks;
}

void deleteTask(Task Tasks[]) {
	size_t n = 0;
	Task empty = { "", "", NULL, {NULL, NULL, NULL, NULL, NULL} };

	// отримання позиції завдання для видалення
	std::cout << "Enter position of a task in the list that must be deleted: ";
	std::cin >> n;

	// перевірка на коректність вводу
	if (n < 1 || n > capacity) {
		std::cout << "A task in not found\n";
		return;
	}

	// стерання
	n--;
	Tasks[n] = empty;
	while (n < capacity && !isEmpty(Tasks[n + 1])) {
		Tasks[n] = Tasks[n + 1];
		n++;
	}
	Tasks[n] = empty;
	std::cout << "Deleted\n";
}

void changeTask(Task Tasks[]) {
	size_t n = 0;
	int code = -1;
	std::string command;

	// отримання позиції завдання
	std::cout << "Enter position of the task in list that must be changed: ";
	std::cin >> n;

	// перевірка на коректність вводу
	if (n < 1 || n > capacity || isEmpty(Tasks[n - 1])) {
		std::cout << "The task in not found\n";
		return;
	}

	// вибір поля для зміни
	n--;
	while (code != 99) {
		std::cout << "Enter field you want to change, \"help\" to see list of commands: ";
		std::cin >> command;
		std::cin.get();
		code = reader(command);
		switch (code) {
		case 0: // help
			std::cout << "help - show available commands\n"
				<< "name - change the name of the task\n"
				<< "description - change the description of the task\n"
				<< "priority - change the priority of the task\n"
				<< "deadline - change the deadline of the task\n"
				<< "clear - clear the screen\n"
				<< "back - back to main menu\n\n";
			break;
		case 5: // name
			std::cout << "Enter new name of the task: ";
			getline(std::cin, Tasks[n].name);
			if (Tasks[n].name.length() > 21) Tasks[n].name = Tasks[n].name.substr(0, 21);
			break;
		case 6: // description
			std::cout << "Enter new description of the task: ";
			getline(std::cin, Tasks[n].description);
			break;
		case 7: // priority
			std::cout << "Enter new priority of the task: ";
			std::cin >> Tasks[n].priority;
			break;
		case 8: // data
		{
			std::string date;
			do {
				std::cout << "Enter new deadline of the task in format [dd.mm.yy hh:mm] or \"N\" if there is no deadline:\n";
				getline(std::cin, date);
				if (date == "N" || date == "n") {
					date = "00.00.00 00:00";
				}
				Tasks[n].deadline = str_to_date(date);
				if (isEmpty(Tasks[n].deadline)) std::cout << "Wrong input!\n";
			} while (isEmpty(Tasks[n].deadline));
		}
		break;
		case 98: // очистка екрана
			displayTitle();
			break;
		case 99: // back
			break;
		default:
			std::cout << "Wrong input.\n";
			break;
		}
	}
}

void list(Task Tasks[]) {
	std::string str;
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------";
	std::cout << "| Position" << "\t" << "| Name" << "\t\t\t| " << "Priority" << "\t| " << "Deadline" << "\t\t| " << "Description\n";
	for (size_t i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
		str = "";
		for (size_t j = ((Tasks[i].name.length()) + 2) / 8; j < 3; j++) {
			str = str + "\t";
		}
		std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------";
		std::cout << "| " << i + 1 << ".\t\t| " << Tasks[i].name << str;
		std::cout << "| " << Tasks[i].priority << ".\t\t| ";
		str = date_to_str(Tasks[i].deadline);
		std::cout << str << "\t| " << Tasks[i].description << '\n';
	}
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void listDay(Task Tasks[]) {
	Date date = curentDate();
	Task* dayTasks = new Task[capacity];
	size_t n = 0;
	for (size_t i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
		if (Tasks[i].deadline.day == date.day
			&& Tasks[i].deadline.month == date.month
			&& Tasks[i].deadline.year == date.year) {
			dayTasks[n] = Tasks[i];
			n++;
		}
	}
	list(dayTasks);
	delete[] dayTasks;
}

void listWeek(Task Tasks[]) {
	Date date = curentDate();
	short int calendar[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // кількість днів в місяці
	if (date.year % 4 == 0) { // високосний рік
		calendar[1]++;
	}
	Task* weekTasks = new Task[capacity];
	size_t n = 0;
	for (size_t j = 0; j < 7; j++) {
		for (size_t i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
			if (Tasks[i].deadline.day == date.day
				&& Tasks[i].deadline.month == date.month
				&& Tasks[i].deadline.year == date.year) {
				weekTasks[n] = Tasks[i];
				n++;
			}
		}
		if (date.day == calendar[date.month - 1]) {
			date.day = 1;
			if (date.month == 12) {
				date.month = 1;
				date.year++;
			}
			else {
				date.month++;
			}
		}
		else {
			date.day++;
		}
	}
	list(weekTasks);
	delete[] weekTasks;
}

void listMonth(Task Tasks[]) {
	Date data = curentDate();
	Task* monthTasks = new Task[capacity];
	size_t n = 0;
	for (size_t i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
		if ((Tasks[i].deadline.month == data.month
			&& Tasks[i].deadline.year == data.year)
			|| (Tasks[i].deadline.day <= data.day
				&& Tasks[i].deadline.month == data.month + 1
				&& Tasks[i].deadline.year == data.year)
			|| (Tasks[i].deadline.day <= data.day
				&& 13 == data.month + 1
				&& Tasks[i].deadline.year == data.year + 1)) {
			monthTasks[n] = Tasks[i];
			n++;
		}
	}
	list(monthTasks);
	delete[] monthTasks;
}

void sort(Task Tasks[]) {
	// оголошення локальних змінних
	std::string command;
	int code = 0;
	int i, j;
	Task mediator;
	int n = 0;

	while (code == 0) {
		// вибір параметру за яким має відбуватись сортування
		std::cout << "Enter a parameter list must be sorted by, or \"help\" to see list of commands\n";
		std::cin >> command;
		code = reader(command);
		switch (code) {
		case 0: // help
			std::cout << "help - show available commands\n"
				<< "name - sort tasks by name\n"
				<< "priority - sort tasks by priority\n"
				<< "deadline - sort tasks by deadline\n"
				<< "clear - clear the screen\n"
				<< "back - back to main menu\n\n";
			break;
		case 5: // name
			while (n < capacity && !isEmpty(Tasks[n])) {
				n++;
			}
			for (i = 0; i < n; i++) {
				mediator = Tasks[i];
				for (j = i - 1; j >= 0 && mediator.name < Tasks[j].name; j--) {
					Tasks[j + 1] = Tasks[j];
				}
				Tasks[j + 1] = mediator;
			}
			break;
		case 7: //priority
			while (n < capacity && !isEmpty(Tasks[n])) {
				n++;
			}
			for (i = 0; i < n; i++) {
				mediator = Tasks[i];
				for (j = i - 1; j >= 0 && mediator.priority < Tasks[j].priority; j--) {
					Tasks[j + 1] = Tasks[j];
				}
				Tasks[j + 1] = mediator;
			}
			break;
		case 8: //deadline
			while (n < capacity && !isEmpty(Tasks[n])) {
				n++;
			}
			for (i = 0; i < n; i++) {
				mediator = Tasks[i];
				for (j = i - 1; j >= 0 && mediator.deadline.day < Tasks[j].deadline.day; j--) {
					Tasks[j + 1] = Tasks[j];
				}
				Tasks[j + 1] = mediator;
			}
			for (i = 0; i < n; i++) {
				mediator = Tasks[i];
				for (j = i - 1; j >= 0 && mediator.deadline.month < Tasks[j].deadline.month; j--) {
					Tasks[j + 1] = Tasks[j];
				}
				Tasks[j + 1] = mediator;
			}
			for (i = 0; i < n; i++) {
				mediator = Tasks[i];
				for (j = i - 1; j >= 0 && mediator.deadline.year < Tasks[j].deadline.year; j--) {
					Tasks[j + 1] = Tasks[j];
				}
				Tasks[j + 1] = mediator;
			}
			break;
		case 98: // очистка екрана
			displayTitle();
			break;
		case 99: // back
			break;
		default:
			std::cout << "Wrong input.\n";
			break;
		}
	}
	std::cout << "Sorted\n";
}

void listTasks(Task Tasks[]) {
	std::string command;
	int code = -1;
	list(Tasks);

	while (code != 99) {
		std::cout << "Enter command (list menu), or \"help\" to see list of commands\n";
		std::cin >> command;
		code = reader(command);
		switch (code) {
		case 0: // help
			std::cout << "help - show available commands\n"
				<< "list - show all list of tasks\n"
				<< "day - show tasks for today\n"
				<< "week - show tasks for this week\n"
				<< "month - show tasks for this month\n"
				<< "sort - sort list of tasks\n"
				<< "clear - clear the screen\n"
				<< "back - back to main menu\n\n";
			break;
		case 4:
			list(Tasks);
			break;
		case 9: // day
			listDay(Tasks);
			break;
		case 10: // week
			listWeek(Tasks);
			break;
		case 11: // month
			listMonth(Tasks);
			break;
		case 12: // sort
			sort(Tasks);
			break;
		case 98: // очистка екрана
			displayTitle();
			break;
		case 99: // back
			break;
		default:
			std::cout << "Wrong input.\n";
			break;
		}
	}
}

void searchTask(Task Tasks[]) {
	Task* findedTasks = new Task[capacity];
	std::string command, str;
	int code = 0, n = 0;

	while (code != 99) {
		std::cout << "Enter a parameter to search by, or \"help\" to see list of commands\n";
		std::cin >> command;
		code = reader(command);
		switch (code) {
		case 0: // help
			std::cout << "help - show available commands\n"
				<< "name - search tasks by name\n"
				<< "description - search tasks by description\n"
				<< "priority - search tasks by priority\n"
				<< "deadline - search tasks by deadline\n"
				<< "clear - clear the screen\n"
				<< "back - back to main menu\n\n";
			break;
		case 5: // name
			std::cout << "Enter a value of the parameter\n";
			std::cin.get();
			getline(std::cin, command);
			for (int i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
				str = Tasks[i].name;
				if (str.find(command) != -1) {
					findedTasks[n] = Tasks[i];
					n++;
				}
			}
			list(findedTasks);
			break;
		case 6: // description
			std::cout << "Enter a value of the parameter\n";
			std::cin.get();
			getline(std::cin, command);
			for (int i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
				str = Tasks[i].description;
				if (str.find(command) != -1) {
					findedTasks[n] = Tasks[i];
					n++;
				}
			}
			list(findedTasks);
			break;
		case 7: // priority
			std::cout << "Enter a value of the parameter\n";
			std::cin.get();
			getline(std::cin, command);
			for (int i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
				if ((command[0] - '0') == Tasks[i].priority) {
					findedTasks[n] = Tasks[i];
					n++;
				}
			}
			list(findedTasks);
			break;
		case 8: // deadline
			std::cout << "Enter a value of the parameter\n";
			std::cin.get();
			getline(std::cin, command);
			for (int i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
				str = date_to_str(Tasks[i].deadline);
				if (str.find(command) != -1) {
					findedTasks[n] = Tasks[i];
					n++;
				}
			}
			list(findedTasks);
			break;
		case 98: // очистка екрана
			displayTitle();
			break;
		case 99: // back
			break;
		default:
			std::cout << "Wrong input.\n";
			break;
		}
		clearTasks(findedTasks);
		n = 0;
	}
}

//--------------------------------------------------------------------------------

void menu(Task Tasks[]) {
	// оголошення локальних змінних
	std::string command;
	int code;

	do {
		displayTitle();
		std::cout << "Enter command, or \"help\" to see list of commands\n";
		std::cin >> command;
		code = reader(command);
		switch (code) {
		case 0:
			std::cout << "help - show available commands\n"
				<< "set - set a new task\n"
				<< "delete - delete a task\n"
				<< "change - change a task\n"
				<< "list - show list of tasks\n"
				<< "search - search the task\n"
				<< "clear - clear the screen\n"
				<< "exit - exit the program\n\n";
			break;
		case 1: // set
			Tasks = setTask(Tasks);
			break;
		case 2: // delete
			deleteTask(Tasks);
			break;
		case 3: // change
			changeTask(Tasks);
			break;
		case 4: // list
			listTasks(Tasks);
			break;
		case 13: // search
			searchTask(Tasks);
			break;
		case 98: // clear
			displayTitle();
			break;
		case 100: // exit
			std::cout << "Exiting...";
			break;
		default: // error
			std::cout << "Wrong input.\n";
			break;
		}
		if (code != 98) std::cout << '\n';
	} while (code != 100);
}

//--------------------------------------------------------------------------------