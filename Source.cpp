#include<iostream>
#include <conio.h>


using namespace std;
const char * crt = "\n---------------------------\n";

void Login(const char* validPass) {
	char buffer[255];
	int i = 0;
	do{
	cout << "Password: " << endl;
	do{
		buffer[i] = _getch();
		cout << "*";
		i++;
	} while (buffer[i-1]!=13);
	} while (strcmp(buffer,validPass)!=0);
}

struct Datum {
	int dan, mjesec, godina;
};
struct PolozeniPredmet {
	char * nazivPredmeta;
	int ocjena;
	Datum datumPolaganja;
	char * napomena;
};
struct Student {
	char * imePrezime;
	PolozeniPredmet polozeni[40];
	int brojPolozenih;
};


int PrikaziMenu() {
	int izbor;
	cout << crt << "\t::MENU::" << crt;
	cout << "1. Dodaj studenta" << endl;
	cout << "2. Dodaj polozeni predmet" << endl;
	cout << "3. Pretraga" << endl;
	cout << "4. Kraj" << crt;
	do {
		cout << "Vas izbor -> ";
		cin >> izbor;
	} while (izbor < 1 || izbor>4);
	system("cls");
	return izbor;
}
/*UKOLIKO SMATRATE DA JE POTREBNO ZADATAK MOZETE PROSIRITI DODATNIM FUNKCIONALNOSTIMA, ALI PROSIRENJA MORAJU PRATITI ADEKVATNI KOMENTARI*/

void DodajStudenta(Student*& student) {
	student = new Student;
	char buffer[255];
	cout << "Unesi ime i prezime: " << endl;
	cin.ignore();
	cin.getline(buffer, 255);
	student->imePrezime = new char[strlen(buffer) + 1];
	strcpy_s(student->imePrezime, strlen(buffer) + 1, buffer);
	cout << "Koliko predmeta dodajete: " << endl;
	cin >> student->brojPolozenih;
	cin.ignore();
	for (int i = 0; i < student->brojPolozenih; i++) {
		cout << "Naziv predmeta: " << endl;
		cin.getline(buffer, 255);
		student->polozeni[i].nazivPredmeta = new char[strlen(buffer) + 1];
		strcpy_s(student->polozeni[i].nazivPredmeta, strlen(buffer) + 1, buffer);
		cout << "Datum polaganja: " << endl;
		cin >> student->polozeni[i].datumPolaganja.dan >> student->polozeni[i].datumPolaganja.mjesec >> student->polozeni[i].datumPolaganja.godina;
		cout << "Ocjena: " << endl;
		cin >> student->polozeni[i].ocjena;
		cout << "Napomena: " << endl;
		cin.ignore();
		cin.getline(buffer, 255);
		student->polozeni[i].napomena = new char[strlen(buffer) + 1];
		strcpy_s(student->polozeni[i].napomena,strlen(buffer)+1,buffer);
	}
}

void main() {
	const int maxStudenata = 6;
	int trenutnoStudenata = 0, izbor = 0;
	Student * studentiIgodina[maxStudenata];
	char validPass[] = "ispitPRII2017";
	/*VRSITI VALIDACIJU KORISNIKOVIH UNOSA TE GA ONEMOGUCITI DA UNOSI VRIJEDNOSTI KOJE NISU VALIDNE*/
	do {
		/*
		za pristup aplikaciji zahtijevati logiranje,
		prilikom unosa password maskirati koristeci crticu (-)
		*/
		Login(validPass);

		izbor = PrikaziMenu();
		if (izbor == 1) {
			DodajStudenta(studentiIgodina[trenutnoStudenata]);
			/*
			Ime i prezime -> Denis Mušic
			Koliko predmeta dodajete -> 1
			Naziv predmeta -> Uvod u informacijske tehnologije
			Datum polaganja -> 11 4 2017
			Ocjena -> 6
			Napomena -> seminarski rad nije sadrzavao sve zahtijevane funkcionalnosti
			*/
			trenutnoStudenata++;
		}
		else if (izbor == 2) {
			DodajPolozeniPredmet(studentiIgodina, trenutnoStudenata);
			/*
			Ime i prezime -> Denis Music
			STUDENT PRONADJEN....
			Naziv predmeta -> Racunarske mreze
			Datum polaganja -> 10 4 2017
			Ocjena -> 7
			Napomena -> studentu dodijeljen seminarski rad na temu OSI modela
			*/
		}
		else if (izbor == 3) {
			Pretraga(studentiIgodina, trenutnoStudenata);
			/*
			Pratraga (1. Datumu polaganja, 2. Napomeni) -> 1
			Unesite datum OD -> 12 1 2017
			Unesite datum DO -> 14 4 2017
			U periodu od 12.1.2017 do 14.4.2017 ispite su polozili sljedeci studenti:
			1. Denis Music -> Racunarske mreze (7) Prosjek studenta: 6.5
			2. Denis Music -> Uvod u informacijske tehnologije (6) Prosjek studenta: 6.5
			3. Adel Handzic -> Baze podataka (9) Prosjek studenta: 8.7

			----------UKOLIKO SE ODABERE OPCIJA 2---------------
			Pratraga (1. Datumu polaganja, 2. Napomeni) -> 2
			Unesite tekst -> nije sadrzavao
			Trazeni sadrzaj 'nije sadrzavao' u napomeni posjeduju sljedeci studenti:
			1. Denis Music, predmet Uvod u informacijske tehnologije
			2. ....
			*/
		}

	} while (izbor != 4);


	/*oslobada zauzetu memoriju*/
	Dealociraj(studentiIgodina, trenutnoStudenata);
}