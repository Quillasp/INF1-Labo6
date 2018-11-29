/*
 -----------------------------------------------------------------------------------
 Laboratoire : 06
 Fichier     : Labo06.cpp
 Auteur(s)   : Yanik Lange, Soulaymane Lamrani, Gabrielle Thurnherr
 Date        : 28.11.2018

 But         : Faire un check vaudois. c'est à

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */


#include <string>
#include <iostream>
#include <cmath>

using namespace std;

string montantVaudois(double montant);
string montantDizaine(int montant);
string montantCentaine(int montant);

string unites(int montant);
string dizaines(int montant);
string centaines(int montant);
string montantMillier(int montant);

int main() {
	double montant;

	for(;;) {
		//cout << "Entrez une valeur :" << endl;
		cin >> montant;



		cout << montantVaudois(montant) << endl;
	}

	return 0;
}

string montantVaudois(double montant) {

	int montantEntier = (int)(montant + 0.005);
	return montantCentaine(montantEntier);
}

string montantDizaine(int montant) {

	if (montant >= 1 && montant <= 9)
		return unites(montant);

	else if (montant >= 11 && montant <= 16)
		return dizaines(montant);
	else if (montant >= 10 && montant <= 99) {
		int unite = montant % 10;
		if (unite == 0)
			return dizaines(montant);
		else if (unite == 1)
			return dizaines(montant - unite) + " et " + unites(montant % 10);
		else if (unite >= 1 && unite <= 9)
			return dizaines(montant - unite) + "-" + unites(montant % 10);
	}
}

string montantCentaine(int montant) {

	if (montant >= 100 && montant <= 999) {
		if (montant == 100)
			return centaines(montant);
		else if (montant > 100) {
			int dizaine = montant % 100;
			if (dizaine == 0)
				return unites(montant / 100) + " " + centaines(montant);
			else if (dizaine > 0 && montant < 200)
				return centaines(montant - dizaine) + " " + montantDizaine(dizaine);
			else if (dizaine > 0 && montant >= 200)
				return unites(montant / 100) + " " + centaines(100) + " " + montantDizaine(dizaine);
		}
	}
}

string unites(int montant) {

	switch (montant) {

		case 1 :
			return "un";
		case 2 :
			return "deux";
		case 3 :
			return "trois";
		case 4 :
			return "quatre";
		case 5 :
			return "cinq";
		case 6 :
			return "six";
		case 7 :
			return "sept";
		case 8 :
			return "huit";
		case 9 :
			return "neuf";
		default:
			return "0";
	}
}

string dizaines(int montant) {

	switch (montant) {

		case 10 :
			return "dix";
		case 11 :
			return "onze";
		case 12 :
			return "douze";
		case 13 :
			return "treize";
		case 14 :
			return "quatorze";
		case 15 :
			return "quinze";
		case 16 :
			return "seize";
		case 20 :
			return "vingt";
		case 30 :
			return "trente";
		case 40 :
			return "quarante";
		case 50 :
			return "cinquante";
		case 60 :
			return "soixante";
		case 70 :
			return "septante";
		case 80 :
			return "huitante";
		case 90 :
			return "nonante";
		default:
			return "0";
	}
}

string centaines(int montant) {

	switch (montant) {

		case 100 :
			return "cent";
		default:
			return "cents";
	}
}