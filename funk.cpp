#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <Windows.h>
using namespace std;

// Funk that check the input
bool InputEn(string a) {
	string EnAlphabet = "abcdefghijklmnopqrstuvwxyz";
	bool check;
	for (int i = 0; i < a.length(); i++) {
		check = false;
		for (int j = 0; j < EnAlphabet.length(); j++) {
			if (tolower(a[i]) == EnAlphabet[j]) check = true;
		}
		if (!check) return false;
	}
	return true;
}

// Funk that checks the file
bool Filecheck(string namer) {
	ifstream f1;
	string a;
	bool coun = false;
	f1.open(namer);
	if (f1.is_open()) {
		while (f1 >> a) {
			coun = true;
			if (!InputEn(a)) {
				f1.close();
				return false;
			}
		}
	}
	else {
		return false;
	}
	f1.close();
	return coun;
}

//Funk that find the meaning 
void GetMeaning(string a) {
	string link = "https://en.wikipedia.org/wiki/" + a;
	ShellExecuteA(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

// Funk that return the number of elem in file
int GetLeng(string namer) {
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
	string buffer;
	bool tryer = false;
	int h = 0;
	cout << "Type what word do you want to guess!" << endl;
	cout << "1 - test!" << endl;
	cout << "2 - fruits!" << endl;
	cout << "3 - vegetables!" << endl;
	cout << "4 - weather!" << endl;
	cout << "5 - materials!" << endl;
	cout << "6 - food!" << endl;
	cout << "7 - animals!" << endl;
	cout << "8 - your file!" << endl;
	cout << "-> ";
	cin >> Input;

	if (Input == "1")
		word = "baza.txt";
	else if (Input == "2")
		word = "fruits.txt";
	else if (Input == "3")
		word = "vegetables.txt";
	else if (Input == "4")
		word = "weather.txt";
	else if (Input == "5")
		word = "materials.txt";
	else if (Input == "6")
		word = "food.txt";
	else if (Input == "7")
		word = "animals.txt";
	else if (Input == "8") {
		cout << "Type name of your file!" << endl;
		cout << "-> ";
		cin >> Input;
		word = " ";
		for (int ch = 0; ch < Input.length(); ch++) {
			if (Input[ch] == '.' || word[0] == '.') {
				word += Input[ch];
			}
		}
		if (word == ".txt") {
			word = Input;
		}
		else if (word == " ") {
			word = Input + ".txt";
		}
		else {
			word = "Null";
		}
	}
	else {
		cout << "Incorrect input!" << endl;
		cout << "You will be guesting..." << endl;
		srand(time(0));
		switch (rand() % 7 + 1)
		{
		case 1: word = "baza.txt"; cout << "test" << endl; break;
		case 2: word = "fruits.txt"; cout << "fruits" << endl; break;
		case 3: word = "vegetables.txt"; cout << "vegetables" << endl; break;
		case 4: word = "weather.txt"; cout << "weather" << endl; break;
		case 5: word = "materials.txt"; cout << "materials" << endl;break;
		case 6: word = "food.txt"; cout << "food" << endl; break;
		case 7: word = "animals.txt"; cout << "animals" << endl; break;
		}
	}	

	if (word != "Null" && Filecheck(word)) {
		GetWord(word);
		buffer = "";
		for (int i = 0; i < word.length(); i++)
			buffer += tolower(word[i]);
		word = buffer;
		tryer = true;
	}
	else cout << "Error with file!" << endl;

	if (tryer) {
		string Inp = "asd";
		int att = 5;
		cout << "Type word that you predict!" << endl;
		while (Inp != word && att >= 0) {
			cin.seekg(cin.eof());
			getline(cin, Inp);
			buffer = "";
			for (int i = 0; i < Inp.length(); i++) {
				if (Inp[i] == ' ') buffer += ' ';
				else buffer += tolower(Inp[i]);
			}
			Inp = buffer;
			if (InputEn(Inp)) {
				if (Inp.length() > word.length()) {
					for (int i = 0; i < Inp.length(); i++) {
						if (i < word.length()) cout << " ";
						else if (i == word.length()) cout << "_" << endl;
					}
				}
				for (int i = 0; i < Inp.length(); i++) {
					if (i < word.length()) {
						if (tolower(Inp[i]) == tolower(word[i])) {
							cout << "+";
						}
						else {
							tryer = false;
							for (int j = 0; j < word.length(); j++) {
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
					else {
						tryer = false;
						for (int j = 0; j < word.length(); j++) {
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
					h = i;
				}
				while (++h < word.length()) cout << "._.";
				cout << endl;
				att--;
			}
			else {
				cout << "Write word in English!" << endl;
			}
		}
		if (att > 0) {
			cout << "You get it!" << endl;
		}
		else {
			cout << "Not this time! The word was - " << word << endl;
		}
		cout << "Do you want to get meaning? Y/N" << endl;
		cin >> Inp;
		if (Inp == "y" || Inp == "Y") {
			GetMeaning(word);
		}
	}
}