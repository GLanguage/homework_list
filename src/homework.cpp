# include "homework.h"

# include <fstream>
# include <vector>
# include <string>
# include <iostream>

using namespace std;

const string START_STR = "START";
const string END_STR = "END";

const int MAX_SIZE = 1024;

Item::Item() {
	desc = "";
}

Item::Item(string d) {
	desc = d;
}

Subject::Subject() {
	name = "";
}

Subject::Subject(string n) {
	name = n;
}

void Subject::append(Item item) {
	itemList.push_back(item);
}

void Subject::remove(int num) {
	itemList.erase(itemList.begin() + num - 1);
}

bool Subject::operator == (const string n) const {
	return name == n;
}

void rdinfo(ifstream &in, vector<Subject> &subjList) {
	subjList.clear();

	Subject tsub;
	bool rddesc = false;
	while(!in.eof()) {
		char crt_cstr[MAX_SIZE];
		in.getline(crt_cstr, MAX_SIZE);
		string crt(crt_cstr);

		if (crt == START_STR) {
			tsub = Subject();
			rddesc = false;
		}
		else if (crt == END_STR) {
			subjList.push_back(tsub);
		}
		else if (!rddesc) {
			tsub.name = crt;
			rddesc = true;
		}
		else if (rddesc) {
			tsub.append(Item(crt));
		}
	}
}

void wtinfo(ofstream &out, vector<Subject> subjList) {
	cout << "Writing...";
	vector<Subject>::iterator i;
	for (i = subjList.begin(); i != subjList.end(); ++i) {
		out << START_STR << endl;
		Subject tsub = *i;
		out << tsub.name << endl;
		vector<Item>::iterator j;
		for (j = tsub.itemList.begin(); j != tsub.itemList.end(); ++j) {
			out << (*j).desc << endl;
		}
		out << END_STR << endl;
	}
	cout << "Done." << endl;
}
