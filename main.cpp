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

const int ZERO = 0;
const int UN = 1;
const int DIX = 10;
const int CENT = 100;
const int MILLE = 1000;

const double AJUSTEMENT = 0.005;


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

/**
 * [montantEnVaudois transcrit un nombre réel donne en toutes lettres]
 * @param  montant [montant  un réel compris entre 0 et 999999.99 CHF]
 * @return         [retourne une string ndiquant en vaudois le prix
 *									en francs et centimes]
 * Exemples:
 * 12.30  -> "douze francs et trente centimes"
 * 200.01 -> "deux cents francs et un centime"
 * 180    -> "cent huitante francs"
 * 1.80   -> "un franc et huitante centimes"
 * 0.20   -> "vingt centimes"
 * 0      -> "zéro franc"
 */
string montantEnVaudois(double montant) {

	int montantEntier = (int)(montant + AJUSTEMENT);
	int montantDecimal = (int)((montant + AJUSTEMENT - montantEntier) * CENT);

	if (montantEntier == ZERO && montantDecimal > ZERO)
		return montantCentaine(montantDecimal, ZERO) + (montantDecimal == UN ? " centime" : " centimes");

	string montantTotal;
	if (montantEntier < MILLE)
		if (montantEntier == ZERO || montantEntier == UN)
			montantTotal = montantCentaine(montantEntier, ZERO) + " franc";
		else
			montantTotal = montantCentaine(montantEntier, ZERO) + " francs";
	else
		montantTotal = montantMillier(montantEntier) + " francs";


	if (montantDecimal > ZERO)
		montantTotal += " et " + montantCentaine(montantDecimal, ZERO) + (montantDecimal == UN ? " centime" : " centimes");

		cout << "decimal: " << montantDecimal << endl;
cout << "entier: " << montantEntier << endl;

	return montantTotal;
}

/**
 * [montantDizaine retourne en lettres les nombres compris en 0 et 99]
 * @param  montant [montant compris entre 0 et 99]
 * @return         [retourne une string du nombre entre en lettres]
 */
string montantDizaine(int montant) {

	if (montant >= ZERO && montant < DIX)
		return unites(montant);

	else if (montant > DIX && montant <= 16)
		return dizaines(montant);
	else if (montant >= DIX && montant < CENT) {
		int unite = montant % DIX;
		if (unite == ZERO)
			return dizaines(montant);
		else if (unite == UN)
			return dizaines(montant - unite) + " et " + unites(montant % DIX);
		else if (unite > ZERO && unite < DIX)
			return dizaines(montant - unite) + "-" + unites(montant % DIX);
	}
}

/**
 * [montantCentaine description]
 * @param  montant [description]
 * @param  millier [description]
 * @return         [description]
 */
string montantCentaine(int montant, int millier) {

	if (montant < CENT)
		return montantDizaine(montant);

	else if (montant >= CENT && montant < MILLE) {
		if (montant == CENT)
			return centaines(montant);
		else if (montant > CENT) {
			int dizaine = montant % CENT;
			if (dizaine == ZERO)
				if (millier == ZERO)
					return unites(montant / CENT) + " " + centaines(dizaine);
				else
					return unites(montant / CENT) + " " + centaines(montant);
			else if (dizaine > ZERO && montant < 200)
				return centaines(montant - dizaine) + " " + montantDizaine(dizaine);
			else if (dizaine > ZERO && montant >= 200)
				return unites(montant / CENT) + " " + centaines(montant) + " " + montantDizaine(dizaine);
		}
	}
}

/**
 * [montantMillier description]
 * @param  montant [description]
 * @return         [description]
 */
string montantMillier(int montant) {

	int montantMille = montant / MILLE;
	int montantCent = montant % MILLE;

	if (montant == MILLE)
		return "mille";
	else if (montant > MILLE && montant <= 1999)
		return "mille " + montantCentaine(montantCent, ZERO);
	else if (montantCent == ZERO)
		return montantCentaine(montantMille, montantMille) + " mille ";
	else
		return montantCentaine(montantMille, montantMille) + " mille " + montantCentaine(montantCent, ZERO);
}

/**
 * [unites permet de retourner une unité entre 0 et 9 en toutes lettres]
 * @param  montant [nombre compris entre 0 et 9 à retourner en lettres]
 * @return         [retourne une string d'une unité en toutes lettres]
 */
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

/**
 * [dizaines détermine quelle dizaine en lettre il faut retourner, ainsi que les nombres entre 11 et 16]
 * @param  montant [dizaine entière comprise entre 10 et 90 à retourner en lettres + dizaines spéciales (11-16)]
 * @return         [retourne une string d'une dizaine entière ou une dizaine spéciale en lettres]
 */
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

/**
 * [centaines retourne le mot "cent" accordé correctement]
 * @param  montant [entier permettant de savoir quelle orthographe du mot "cent" utiliser]
 * @return         [retourne une string correctement orthographiée]
 */
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
