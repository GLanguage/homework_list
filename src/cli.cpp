# include "cli.h"

# include "homework.h"
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <algorithm>

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
"\tshow\t - Show the details of the homework (with args)\n"
"\tappend\t - Append a new piece of homework (with args)\n"
"\tremove\t - Remove a piece of homework (with args)\n"
"For any option with a \'(with args)\' mark,\n"
"type \'help\' after it (as arg1) to see the further details about it.\n"
"\n";

const string LIST_HELP_STR = "\n"
"\033[1mHomework List: Option \'list\' Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework list ( all | <subject_name> )\n"
"where  <subject_name> is the name of the subject you want to list.\n"
"\n";

const string SHOW_HELP_STR = "\n"
"\033[1mHomework List: Option \'show\' Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework show ( subject | item )\n"
"The subject name and/or the item number will be needed later.\n"
"\n";

const string APPEND_HELP_STR = "\n"
"\033[1mHomework List: Option \'append\' Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework append ( subject | item )\n"
"The subject name and/or the item description will be needed later.\n"
"\n";

const string REMOVE_HELP_STR = "\n"
"\033[1mHomework List: Option \'remove\' Help\033[0m\n"
"\n"
"\033[1mUsage:\033[0m\n"
"homework remove ( subject | item )\n"
"The subject name and/or the item number will be needed later.\n"
"\n";

void help(int cont) {
	switch (cont) {
		case 0: // General Help
			cout << HELP_STR;
			break;
		case 1: // List Help
			cout << LIST_HELP_STR;
			break;
		case 2: // Show Help
			cout << SHOW_HELP_STR;
			break;
		case 3: // Append Help
			cout << APPEND_HELP_STR;
			break;
		case 4: // Remove Help
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
	}
}

void showhmw(string mode) {
	ifstream in;
	bool flag = safe_open(in);
	if (!flag) return;
	vector<Subject> subjList;
	rdinfo(in, subjList);
	in.close();
	if (mode == "subject") {
		cout << "The subject name: ";
		string subjname;
		cin >> subjname;
		vector<Subject>::iterator isubj = safe_find(subjList.begin(), subjList.end(), subjname);
		if (isubj == subjList.end()) return;
		Subject subj = *isubj;
		cout << "Subject: " << subj.name << " (with " << subj.itemList.size() << " items)" << endl;
	}
	else if (mode == "item") {
		cout << "In subject: ";
		string subjname;
		cin >> subjname;
		vector<Subject>::iterator isubj = safe_find(subjList.begin(), subjList.end(), subjname);
		if (isubj == subjList.end()) return;
		Subject subj = *isubj;
		cout << "The item number: ";
		int num;
		cin >> num;
		if (num > subj.itemList.size()) {
			cerr << "Invalid Number! " << endl;
		}
		cout << (*(subj.itemList.begin() + num - 1)).desc << endl;
	}
}

void appendhmw(string mode) {
	ifstream in;
	bool flag = safe_open(in);
	if (!flag) return;
	vector<Subject> subjList;
	rdinfo(in, subjList);
	in.close();
	if (mode == "subject") {
		cout << "The subject name: ";
		string subjname;
		cin >> subjname;
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
		cout << "Append to subject: ";
		string subjname;
		cin >> subjname;
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

void removehmw(string mode) {
	ifstream in;
	bool flag = safe_open(in);
	if (!flag) return;
	vector<Subject> subjList;
	rdinfo(in, subjList);
	in.close();
	if (mode == "subject") {
		cout << "The subject name: ";
		string subjname;
		cin >> subjname;
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
		cout << "In subject: ";
		string subjname;
		cin >> subjname;
		vector<Subject>::iterator isubj = safe_find(subjList.begin(), subjList.end(), subjname);
		if (isubj == subjList.end()) return;
		Subject &subj = *isubj;
		cout << "The item number: ";
		int num;
		cin >> num;
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
				listhmw(argv[2]);
			}
		}
		else {
			help(1);
		}
	}
	else if (argv[1] == "show") {
		if (argc >= 3) {
			if (argv[2] == "help") {
				help(2);
			}
			else {
				showhmw(argv[2]);
			}
		}
		else {
			help(2);
		}
	}
	else if (argv[1] == "append") {
		if (argc >= 3) {
			if (argv[2] == "help") {
				help(3);
			}
			else {
				appendhmw(argv[2]);
			}
		}
		else {
			help(3);
		}
	}
	else if (argv[1] == "remove") {
		if (argc >= 3) {
			if (argv[2] == "help") {
				help(4);
			}
			else {
				removehmw(argv[2]);
			}
		}
		else {
			help(4);
		}
	}
	else {
		help(0);
	}
}
