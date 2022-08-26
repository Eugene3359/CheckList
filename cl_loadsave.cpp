#include "cl_loadsave.h"

//--------------------------------------------------------------------------------

void createFile() {
	std::ifstream input;
	input.open("save.txt");
	if (!input.is_open()) {
		std::ofstream output;
		output.open("save.txt");
		output << 10;
		output.close();
	}
	input.close();
}

Task* Load() {
	Task* Tasks;
	std::ifstream load;
	std::string str;

	load.open("save.txt");

	getline(load, str);
	capacity = std::stoi(str);
	Tasks = new Task[capacity];

	for (size_t i = 0; !load.eof(); i++) {
		getline(load, Tasks[i].name);
		getline(load, Tasks[i].description);
		getline(load, str);
		Tasks[i].priority = (unsigned short)str[0] - '0';
		getline(load, str);
		Tasks[i].deadline = str_to_date(str);
	}
	load.close();
	return Tasks;
}

void Save(Task Tasks[]) {
	std::ofstream save;
	save.open("save.txt");
	save << capacity << '\n';
	for (size_t i = 0; i < capacity && !isEmpty(Tasks[i]); i++) {
		save << Tasks[i].name << "\n"
			<< Tasks[i].description << "\n"
			<< Tasks[i].priority << "\n"
			<< Tasks[i].deadline.day << "."
			<< Tasks[i].deadline.month << "."
			<< Tasks[i].deadline.year << " "
			<< Tasks[i].deadline.hour << ":"
			<< Tasks[i].deadline.minute << '\n';
	}
	save.close();
}

//--------------------------------------------------------------------------------