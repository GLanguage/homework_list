# include "cli.h"

# include "homework.h"
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <algorithm>
# include <cstring>

using namespace std;

const string ROOT = "/Users/Alan/homework_list/";

const string LOAD_FILE = ROOT + "homework.hmw";

const string HELP_STR = "\n"
"\033[1mHomework List Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework [option] [arg1[ arg2[ ...]]]\n"
"where \033[1moption\033[0m is one of:\n"
"\tclear\t - Clear the homework list\n"
"\thelp\t - Show this help\n"
"\tlist\t - List the homework (with args)\n"
"\tappend\t - Append a new piece of homework (with args)\n"
"\tremove\t - Remove a piece of homework (with args)\n"
"For any option with a \'(with args)\' mark,\n"
"type \'help\' after it (as arg1) to see the further details about it.\n"
"\n";

const string LIST_HELP_STR = "\n"
"\033[1mHomework List: Option \'list\' Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework list all\n"
"homework list <subject_name_1>[ <subject_name_2>[ ...]]\n"
"\n";

const string APPEND_HELP_STR = "\n"
"\033[1mHomework List: Option \'append\' Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework append subject <subject_name_1>[ <subject_name_2>[ ...]]\n"
"homework append item <subject_name> (Item description will be needed later) \n"
"\n";

const string REMOVE_HELP_STR = "\n"
"\033[1mHomework List: Option \'remove\' Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework remove subject <subject_name_1>[ <subject_name_2>[ ...]]\n"
"homework remove item <subject_name> <item_number_1>[ <item_number_2>[ ...]]\n"
"\n";

void help(int cont) {
	switch (cont) {
		case 0: // General Help
			cout << HELP_STR;
			break;
		case 1: // List Help
			cout << LIST_HELP_STR;
			break;
		case 2: // Append Help
			cout << APPEND_HELP_STR;
			break;
		case 3: // Remove Help
			cout << REMOVE_HELP_STR;
			break;
		default:
			break;
	}
}

void clearhmw() {
	ofstream clrf;
	clrf.open(LOAD_FILE, ios::out | ios::trunc );
	clrf.close();
	cout << "The homework list has been cleared! " << endl;
}

bool safe_open(ifstream &in) {
	in.open(LOAD_FILE.c_str(), ios::in );
	if (!in) {
		in.close();
		ofstream nfile;
		nfile.open(LOAD_FILE.c_str(), ios::out | ios::trunc );
		if (!nfile) {
			cerr << "Cannot open file: " << LOAD_FILE << " for reading! " << endl;
			nfile.close();
			return false;
		}
		cout << "New file: " << LOAD_FILE << " has been created! " << endl;
		nfile.close();
		in.open(LOAD_FILE.c_str(), ios::in );
	}
	return true;
}

vector<Subject>::iterator safe_find(vector<Subject>::iterator b, vector<Subject>::iterator e, string subjname) {
	vector<Subject>::iterator isubj = find(b, e, subjname);
	if (isubj == e) {
		cerr << "Cannot find the subject: " << subjname << endl;
	}
	return isubj;
}

void listhmw(string mode) {
	ifstream in;
	bool flag = safe_open(in);
	if (!flag) return;
	vector<Subject> subjList;
	rdinfo(in, subjList);
	in.close();
	if (mode == "all") {
		vector<Subject>::iterator i;
		for (i = subjList.begin(); i != subjList.end(); ++i) {
			Subject tsub = *i;
			cout << "Subject: " << tsub.name << endl;
			vector<Item>::iterator j;
			for (j = tsub.itemList.begin(); j != tsub.itemList.end(); ++j) {
				cout << j - tsub.itemList.begin() + 1 << ". " << (*j).desc << endl;
			} 
			cout << endl;
		}
	}
	else {
		string subjname = mode;
		vector<Subject>::iterator isubj = safe_find(subjList.begin(), subjList.end(), subjname);
		if (isubj == subjList.end()) return;
		Subject subj = *isubj;
		cout << "Subject: " << subj.name << endl;
		vector<Item>::iterator i;
		for (i = subj.itemList.begin(); i != subj.itemList.end(); ++i) {
			cout << i - subj.itemList.begin() + 1 << ". " << (*i).desc << endl;
		}
		cout << endl;
	}
}

void appendhmw(string mode, string subjname) {
	ifstream in;
	bool flag = safe_open(in);
	if (!flag) return;
	vector<Subject> subjList;
	rdinfo(in, subjList);
	in.close();
	if (mode == "subject") {
		vector<Subject>::iterator isubj = find(subjList.begin(), subjList.end(), subjname);
		if (isubj != subjList.end()) {
			cerr << "Subject already exists: " << subjname << endl;
			return;
		}
		subjList.push_back(Subject(subjname));
		ofstream out;
		out.open(LOAD_FILE, ios::out | ios::trunc );
		wtinfo(out, subjList);
		out.close();
		cout << "Successfully appended subject: " << subjname << endl;
	}
	else if (mode == "item") {
		vector<Subject>::iterator isubj = safe_find(subjList.begin(), subjList.end(), subjname);
		if (isubj == subjList.end()) return;
		Subject &subj = *isubj;
		cout << "Item Description: ";
		string d;
		cin >> d;
		subj.append(Item(d));
		ofstream out;
		out.open(LOAD_FILE, ios::out | ios::trunc );
		wtinfo(out, subjList);
		out.close();
		cout << "Successfully appended an item in subject: " << subjname << endl;
	}
}

void removehmw(string mode, string subjname, int num = 0) {
	ifstream in;
	bool flag = safe_open(in);
	if (!flag) return;
	vector<Subject> subjList;
	rdinfo(in, subjList);
	in.close();
	if (mode == "subject") {
		vector<Subject>::iterator isubj = safe_find(subjList.begin(), subjList.end(), subjname);
		if (isubj == subjList.end()) return;
		subjList.erase(isubj);
		ofstream out;
		out.open(LOAD_FILE, ios::out | ios::trunc );
		wtinfo(out, subjList);
		out.close();
		cout << "Successfully removed subject: " << subjname << endl;
	}
	else if (mode == "item") {
		vector<Subject>::iterator isubj = safe_find(subjList.begin(), subjList.end(), subjname);
		if (isubj == subjList.end()) return;
		Subject &subj = *isubj;
		if (num > subj.itemList.size()) {
			cerr << "Invalid Number! " << endl;
		}
		subj.remove(num);
		ofstream out;
		out.open(LOAD_FILE, ios::out | ios::trunc );
		wtinfo(out, subjList);
		out.close();
		cout << "Successfully removed an item in subject: " << subjname << endl;
	}
}

void execute(int argc, string argv[]) {
	if (argc == 1) {
		help(0);
		return;
	}
	if (argv[1] == "clear") {
		clearhmw();
	}
	else if (argv[1] == "help") {
		help(0);
	}
	else if (argv[1] == "list") {
		if (argc >= 3) {
			if (argv[2] == "help") {
				help(1);
			}
			else {
				if (argv[2] == "all") {
					listhmw("all");
				}
				else {
					for (int i = 2; i < argc; ++i) {
						listhmw(argv[i]);
					}
				}
			}
		}
		else {
			help(1);
		}
	}
	else if (argv[1] == "append") {
		if (argc >= 3) {
			if (argv[2] == "help") {
				help(2);
			}
			else {
				if (argv[2] == "subject") {
					for (int i = 3; i < argc; ++i) {
						appendhmw("subject", argv[i]);
					}
				}
				else if (argv[2] == "item") {
					appendhmw("item", argv[3]);
				}
				else {
					help(2);
				}
			}
		}
		else {
			help(2);
		}
	}
	else if (argv[1] == "remove") {
		if (argc >= 3) {
			if (argv[2] == "help") {
				help(3);
			}
			else {
				if (argv[2] == "subject") {
					for (int i = 3; i < argc; ++i) {
						removehmw("subject", argv[i]);
					}
				}
				else if (argv[2] == "item") {
					int numlist[argc];
					for (int i = 4; i < argc; ++i) {
						numlist[i] = stoi(argv[i]);
					}
					sort(numlist + 4, numlist + argc);
					for (int i = 4; i < argc; ++i) {
						removehmw("item", argv[3], numlist[i] - (i - 4));
					}
				}
				else {
					help(3);
				}
			}
		}
		else {
			help(3);
		}
	}
	else {
		help(0);
	}
}
