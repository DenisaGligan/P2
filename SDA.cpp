// SDA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"

using namespace std;

void showMenu()
{
	cout << "-2.Date initiale" << endl;
	cout << "-1.Populati tabelul" << endl;
	cout << "0.Exit" << endl;
	cout << "1.Afiseaza tabel" << endl;
	cout << "2.Afiseaza punctele dintr-o coliziune" << endl;
	cout << "3.Adauga punct" << endl;
	cout << "4.Gaseste un punct dat prin coordonate" << endl;
	cout << "5.Sterge punct" << endl;

}

int main()
{
	Hash object;
	string lat;
	string longit;
	string utilitati[7];
	string st;
	string s[] = { "gaz","apa","0","0","0","0","0" };
	string s1[] = { "curent","internet","gaz","apa","electricitate","Tv subterane","cabluri telefonice" };
	string v[] = { "0","0","0","0","0","0","0" };
	string s2[] = { "apa","gaz","internet","curent","0","0","0" };
	while (true)
	{
		
		showMenu();
		int opt;
		cout << "optiune: ";
		cin >> opt;
		switch (opt)
		{
		case -2:
			object.addPunct("12.9100", "20.1782", s1);
			object.addPunct("12.9823", "20.0003", s2);
			object.addPunct("10.9875", "22.7813", v);
			object.addPunct("18.0005", "10.1201", s);
			object.addPunct("29.9823", "29.0008", v);
			object.addPunct("57.9875", "23.7813", s2);
			object.addPunct("12.0003", "10.1009", v);
			object.addPunct("34.1767", "11.7272", s);
			break;
		case -1:
			int n;
			cout << "Introduceti nr de puncte: "; cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << "Introduceti latitudinea: "; cin >> lat; cout << endl;
				cout << "Introduceti longitudinea: "; cin >> longit; cout << endl;
				cout << "Introduceti 7 utilitati (daca doriti mai putine utilitati, introduceti utilitatile dorite iar incontinuare 0 pt a ocupa toate cele 7 locuri) " << endl;
				for (int i = 0; i < 7; i++)
				{
					cout << i << ".";
					cin >> st;
					utilitati[i] = st;
				}
				object.addPunct(lat, longit, utilitati);
			}
			break;
		case 0:
			return 0;
		case 1:
			object.printTable();
			break;
		case 2:
			int c;
			cout << "Introduceti nr indexului pt care doriti sa aiba loc operatia (nr trebuie sa fie cuprins intre 0-9): "; cin >> c;
			object.printElemInIndex(c);
			break;
		case 3:
			cout << "Introduceti latitudinea: "; cin >> lat; cout << endl;
			cout << "Introduceti longitudinea: "; cin >> longit; cout << endl;
			cout << "Introduceti 7 utilitati (daca doriti mai putine utilitati, introduceti utilitatile dorite iar incontinuare 0 pt a ocupa toate cele 7 locuri) " << endl;
			for (int i = 0; i < 7; i++)
			{
				cout << i << ".";
				cin >> st;
				utilitati[i] = st;
			}
			object.addPunct(lat, longit, utilitati);
			break;
		case 4:
			cout << "Introduceti latitudinea: "; cin >> lat; cout << endl;
			cout << "Introduceti longitudinea: "; cin >> longit; cout << endl;
			object.find(lat, longit);
			cout << endl;
			break;
		case 5:
			cout << "Introduceti latitudinea: "; cin >> lat; cout << endl;
			cout << "Introduceti longitudinea: "; cin >> longit; cout << endl;
			object.remove(lat, longit);
			break;
		default:
			cout << "optiune invalida" << endl;
			break;
		}


	}


    return 0;
}

