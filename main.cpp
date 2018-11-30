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

string montantEnVaudois(double montant);
string montantDizaine(int montant);
string montantCentaine(int montant, int millier);
string montantMillier(int montant);

string unites(int montant);
string dizaines(int montant);
string centaines(int montant);

int main() {
	double d;

	while( cin >> d ) {
		cout << montantEnVaudois(d) << endl;
	}

	return 0;
}

string montantEnVaudois(double montant) {

	int montantEntier = (int)(montant + 0.005);
	int montantDecimal = (int)((montant + 0.005 - montantEntier) * 100);

	if (montantEntier == 0 && montantDecimal > 0)
		return montantCentaine(montantDecimal, 0) + (montantDecimal == 1 ? " centime" : " centimes");

	string montantTotal;
	if (montantEntier < 1000)
		if (montantEntier == 0 || montantEntier == 1)
			montantTotal = montantCentaine(montantEntier, 0) + " franc";
		else
			montantTotal = montantCentaine(montantEntier, 0) + " francs";
	else
		montantTotal = montantMillier(montantEntier) + " francs";


	if (montantDecimal > 0)
		montantTotal += " et " + montantCentaine(montantDecimal, 0) + (montantDecimal == 1 ? " centime" : " centimes");

	return montantTotal;
}

string montantDizaine(int montant) {

	if (montant >= 0 && montant <= 9)
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

string montantCentaine(int montant, int millier) {

	if (montant < 100)
		return montantDizaine(montant);

	else if (montant >= 100 && montant <= 999) {
		if (montant == 100)
			return centaines(montant);
		else if (montant > 100) {
			int dizaine = montant % 100;
			if (dizaine == 0)
				if (millier == 0)
					return unites(montant / 100) + " " + centaines(dizaine);
				else
					return unites(montant / 100) + " " + centaines(montant);
			else if (dizaine > 0 && montant < 200)
				return centaines(montant - dizaine) + " " + montantDizaine(dizaine);
			else if (dizaine > 0 && montant >= 200)
				return unites(montant / 100) + " " + centaines(montant) + " " + montantDizaine(dizaine);
		}
	}
}

string montantMillier(int montant) {

	int montantMille = montant / 1000;
	int montantCent = montant % 1000;

	if (montant == 1000)
		return "mille";
	else if (montant >= 1001 && montant <= 1999)
		return "mille " + montantCentaine(montantCent, 0);
	else if (montantCent == 0)
		return montantCentaine(montantMille, montantMille) + " mille ";
	else
		return montantCentaine(montantMille, montantMille) + " mille " + montantCentaine(montantCent, 0);
}

string unites(int montant) {

	switch (montant) {

		case 0 :
			return "zero";
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
		case 0 :
			return "cents";
		default:
			return "cent";

	}
}