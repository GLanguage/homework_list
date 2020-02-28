# include <iostream>
# include <fstream>
# include "cli.h"
# include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	string args[argc];
	for (int i = 0; i < argc; i++) {
		args[i] = string(argv[i]);
	}
	execute(argc, args);
	return 0;
}