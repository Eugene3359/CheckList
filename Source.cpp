#include "cl_bascom.h"
#include "cl_menu.h"
#include "cl_loadsave.h"

int main() {
	system("title ToDo List");
	system("mode con:cols=150 lines=50");
	system("color 75");

	createFile();
	Task* Tasks = Load();
	menu(Tasks);
	Save(Tasks);
	return 0;
}