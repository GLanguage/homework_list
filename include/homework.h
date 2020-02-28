# ifndef HOMEWORK_H
# define HOMEWORK_H

# include <fstream>
# include <vector>
# include <string>

using namespace std;

struct Item
{
	string desc;
	Item();
	Item(string d);
};

struct Subject
{
	string name;
	vector<Item> itemList;
	Subject();
	Subject(string n);
	void append(Item item);
	void remove(int num);
	bool operator == (const string n) const ;
};

void rdinfo(ifstream &in, vector<Subject> &subjList);

void wtinfo(ofstream &out, vector<Subject> subjList);

# endif