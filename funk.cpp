#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <Windows.h>
using namespace std;

// Funk that checks the file
bool Filecheck(string namer) {
	ifstream f1;
	string a;
	bool check = true;
	f1.open(namer);
	while (f1 >> a && check) {
		for (int i = 0; i < a.length(); i++) {
			if (isdigit(a[i])) check = false;
		}
	}
	f1.close();
	return check;
}

//Funk that find the meaning 
void GetMeaning(string a) {
	string link = "https://en.wikipedia.org/wiki/" + a;
	ShellExecuteA(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

// Funk that return the number of elem in file
int GetLeng(string namer) {
	setlocale(LC_ALL, "");
	ifstream f1;
	string a;
	int i = 0;
	f1.open(namer);
	while (f1.peek() != EOF) {
		f1 >> a;
		i++;
	}
	f1.close();
	return i;
}

// Funk thet generate Word
void GetWord(string& namer) {
	setlocale(LC_ALL, "");
	ifstream f1;
	string a;
	srand(time(0));
	int l = GetLeng(namer);
	int i = rand() % l;
	f1.open(namer);
	while (i >= 0) {
		f1 >> namer;
		i--;
	}
	f1.close();
}

void generator() {
	string Input;
	string word;
	bool tryer;
	cout << "Type what word do you want to guess!" << endl;
	cout << "1 - full random!" << endl;
	cout << "-> ";
	cin >> Input;
	if (Input == "1") {
		word = "baza.txt";
		if (Filecheck(word)) GetWord(word);
		else cout << "Error with file!" << endl;
	}
	if (Filecheck(word)) {
		string Inp = "asd";
		int att = 5;
		cout << "Type word that you predict!" << endl;
		while (Inp != word && att >= 0) {
			cin >> Inp;
			if (Inp.length() == 5) {
				for (int i = 0; i < 5; i++) {
					if (Inp[i] == word[i]) {
						cout << "+";
					}
					else {
						tryer = false;
						for (int j = 0; j < 5; j++) {
							if (tryer == false && Inp[i] == word[j]) {
								tryer = true;
							}
						}
						if (tryer == false) {
							cout << "-";
						}
						else {
							cout << "~";
						}
					}
				}
				cout << endl;
				att--;
			}
			else {
				cout << "Error!" << endl;
			}
		}
		if (att > 0) {
			cout << "You get it!" << endl;
		}
		else {
			cout << "Not this time!" << endl;
		}
		cout << "Do you want to get meaning? Y/N" << endl;
		cin >> Inp;
		if (Inp == "y" || Inp == "Y") {
			GetMeaning(word);
		}
	}
}