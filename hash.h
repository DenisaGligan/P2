#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class Hash
{
private:
	static const int tableSize=10;		//permite definirea dimensiunii tabelei in interiorul clasei si folosirea dimensiunii incontinuare
	struct punct {
		string lat;
		string longit;
		string utilitati[7];
		punct* next;		// pointer catre un alt punct
	};
	punct* hashTable[tableSize];		//declarare hash table (un fel de array)
public:
	Hash(); //contructor
	int hash(string key);	//functie care returneaza indexul, numarul unui punct din hash table
	void addPunct(string lat, string longit, string utilitati[7]);		//adauga un punct
	int numberOfPuncteInIndex(int index);	//returneaza nr de puncte dintr-o coliziune
	void printTable();					//afisare tabel
	void printElemInIndex(int index);		//afiseaza elem dintr-o coliziune
	void find(string lat, string longit);	//gaseste un punct dat de la tastatura in cazul in care exista, in caz contrat mesaj
	void remove(string lat, string longit);		//sterge un punct dat de la tastatura 

};

