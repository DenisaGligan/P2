#include "stdafx.h"
#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

Hash::Hash()
{
	for (int i = 0; i < tableSize; i++)		//parcurgem toate indexurile din hash table pt a le initializa cu valori vide
	{
		hashTable[i] = new punct;			//se creeaza un punct
		hashTable[i]->lat = "empty";		// initializam latitudinea	
		hashTable[i]->longit = "empty";		//initializam longitudinea
		for (int j = 0; j < 7; j++)		//parcurge tot sirul de utilitati pt un punct 
		{
			hashTable[i]->utilitati[j] = "0";					//initializeaza fiecare pozitie astfel incat sa fie vida
		}
		hashTable[i]->next = NULL;		//nu e pointer catre un alt punct, nu mai exista legatura

	}
}

int Hash::hash(string key)
{
	int h=0;	//variabila de tip intreg in care se stocheaza nr din codul ascii al unei var de tip string
	int index;

	for (int i = 0; i < key.length(); i++)
	{
		h = h + (int)key[i];		//converteste cheia, care e de tip string, intr-un intreg (cod ascii); calculeaza suma codurilor intregii chei
		//cout << "h= " << h << endl;
	}
	index = h % tableSize;	//calculeaza indexul, impartind suma obtinuta la dimensiunea tabelului (restul impartirii o sa fie indicele punctului respectiv din tabel)
	
	return index;
	
}

void Hash::addPunct(string lat, string longit, string utilitati[7])
{
	string key;
	key = lat + longit;		//construieste cheia punctului din cele 2 coordonate(latitudine si longitudine)
	int index;
	index = hash(key);		//memoreaza pozitia unde trebuie adaugat elementul
	if (hashTable[index]->lat == "empty" && hashTable[index]->longit=="empty")		//verifica daca elementul care trebuie adaugat este primul pe locul obtinut(index)
	{
		hashTable[index]->lat = lat;			//pune latitudinea in hash table
		hashTable[index]->longit = longit;		//pune longitudinea in hash table
		for (int j = 0; j < 7; j++)		//parcurge tot sirul de utilitati pt un punct 
		{
			hashTable[index]->utilitati[j] = utilitati[j];					//pune in hash table utilitatile punctului dat
		}
	}
	else 
	{
		punct* ptr = hashTable[index];			//in caz contrar, se stabileste o noua legatura intre elementul existent pe pozitia index, si cel care trebuie adaugat
		punct* n = new punct;					//se creeaza un loc pt punct
		n->lat = lat;
		n->longit = longit;
		for (int j = 0; j <7; j++)		//parcurge tot sirul de utilitati pt un punct 
		{
			n->utilitati[j] = utilitati[j];					//pune in hash table utilitatile punctului dat
		}
		n->next = NULL;
		while (ptr->next != NULL)				//cauta locul unde trebuie adaugat elementul, in cazul in care mai sunt alte elemente in coliziune.
		{
			ptr = ptr->next;
		}
		ptr->next = n;			//adauga elementul
	}

}

int Hash::numberOfPuncteInIndex(int index)
{
	int count = 0;
	
	if (hashTable[index]->lat == "empty" && hashTable[index]->longit=="empty")		//verificam daca exista un element in index, daca nu exista returnam 0
	{
		return count;
	}
	else
	{
		count++;								//in cazul in care exista, incrementam contorul
		punct* ptr = hashTable[index];			//creeaza un nou pointer catre inceputul "listei"
		while (ptr->next != NULL)				//parcurge toate elementele existente in acea coliziune
		{
			count++;
			ptr = ptr->next;
		}
	}
	return count;								//returneaza nr de elemente din coliziune
}

void Hash::printTable()
{

	int nr;
	for (int i = 0; i < tableSize; i++)		//se parcurge tabelul
	{
		nr = numberOfPuncteInIndex(i);		//se retine nr de puncte dintr-un index
		cout << "-------------------" << endl;
		cout << "index= " << i << endl;
		cout << "latitudine: " << hashTable[i]->lat << "  longitudine: " << hashTable[i]->longit << endl;		//afiseaza lat si longit
		cout << "utilitati: ";
		for (int j = 0; j < 7; j++)			//parcurge sirul de utilitati pt un punct
		{
			cout << hashTable[i]->utilitati[j] << ", ";		//afiseaza utilitatile unui punct
		}
		cout << endl;
		cout << "numar de puncte= " << nr << endl;
		cout << "-------------------" << endl;
		
		
	}
}

void Hash::printElemInIndex(int index)
{
	punct* ptr = hashTable[index];
	if (ptr->lat == "empty" && ptr->longit=="empty")		//verifica daca exista vreun punct in index, iar daca nu exista afiseaza mesaj
	{
		cout << "index-ul " << index << " este gol" << endl;
	}
	else 
	{
		cout << "index-ul: "<<index <<" contine: "<< endl;		//daca exista parcurge toate punctele din index si le afiseaza 
		while (ptr != NULL)
		{
			cout << "-------------------" << endl;
			cout << "latitudine: " << ptr->lat << "  longitudine: " << ptr->longit << endl;
			cout << "utilitati: ";
			for (int j = 0; j < 7; j++)
			{
				cout << ptr->utilitati[j] << ", ";
			}
			cout << endl;
			cout << "-------------------" << endl;
			ptr = ptr->next;
		}
	}
}

void Hash::find(string lat, string longit)
{
	string c;
	c = lat + longit;		//construieste cheia
	int index;
	bool found=false;		//indica daca a fost gasit punctul sau nu
	index = hash(c);		//obtine indexul pe baza cheii construite
	punct* ptr = hashTable[index];
	while ((ptr != NULL) and (found == false))		//parcurgem cat timp mai exista elemente si cat timp nu a fost gasit punctul cautat
	{
		if ((ptr->lat == lat) and (ptr->longit == longit))		//verifica daca punctul gasit corespunde cu cel cautat de noi
		{
			found = true;
			cout << "index: " << index << endl;
			cout << "utilitati: ";
			for (int i = 0; i <7; i++)
			{
				cout << ptr->utilitati[i] << ", ";
			}
		}
		ptr = ptr->next;	//trece la urmatorul punct
	}
	if (found == false)		//daca punctul nu a fost gasit afiseaza mesaj
		cout << "punct inexistent " << endl;

}

void Hash::remove(string lat, string longit)
{
	string c;
	c = lat + longit;
	int index = hash(c);		//aflam indexul(pozitia) elementului in tabel
	punct* delPtr;
	punct* p1;
	punct* p2;

	//1.cazul in care pozitia respectiva nu contine nici un element

	if (hashTable[index]->lat == "empty" && hashTable[index]->longit == "empty")
	{
		cout << "Pentru coordonatele: " << lat << " si " << longit << " nu a fost gasit nici un punct." << endl;
	}
	//2.pe pozitia respectiva se afla un singur element si este cel cautat

	else if (hashTable[index]->lat == lat && hashTable[index]->longit == longit && hashTable[index]->next==NULL)
	{
		hashTable[index]->lat = "empty";
		hashTable[index]->longit = "empty";
		for (int j = 0; j < 7; j++)		//parcurge tot sirul de utilitati pt un punct 
		{
			hashTable[index]->utilitati[j] = "0";					//initializeaza fiecare pozitie astfel incat sa fie vida
		}
		cout << "Punctul de la coordonatele " << lat << ", " << longit << " a fost sters." << endl;
	}
	//3.pe pozitia respectiva se afla mai multe elemente, iar cel cautat este primul

	else if (hashTable[index]->lat == lat && hashTable[index]->longit == longit)
	{
		delPtr = hashTable[index];		//se retine valoarea cautata
		hashTable[index] = hashTable[index]->next;		//al doilea element devine primul
		delete delPtr;		//se sterge elementul cautat

		cout << "Punctul de la coordonatele " << lat << ", " << longit << " a fost sters." << endl;

	}
	//4.pe pozitia respectiva se afla mai multe elemente, iar cel cautat nu este primul

	else
	{
		p1 = hashTable[index]->next;		//pointer catre al doilea punct
		p2 = hashTable[index];		//pointer catre primul punct
		while (p1 != NULL && p1->lat != lat && p1->longit != longit)
		{
			p2 = p1;		//inainteaza pe puncte (devine pointer catre al doilea punct)
			p1 = p1->next;
		}
		//4.1.nu este gasit

		if (p1 == NULL)
		{
			cout << "Pentru coordonatele: " << lat << " si " << longit << " nu a fost gasit nici un punct." << endl;
		}
		//4.2. este gasit
		else
		{							//stergem elem catre catre p1 e pointer
			delPtr = p1;		//p1 e pointer catre elem pe care vrem sa il eliminam
			p1 = p1->next;		//pointer catre urmatorul element
			p2->next = p1;		//pointer catre noul element la care se refera p1

			delete delPtr;
			cout << "Punctul de la coordonatele " << lat << ", " << longit << " a fost sters." << endl;
		}
	}
}
