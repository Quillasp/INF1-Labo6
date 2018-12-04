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

const string MILLIER = "mille";
const string MONNAIE = "franc";
const string CENTIME = "centime";
const string ET = " et ";

const char PLURIEL = 's';
const char ESPACE = ' ';
const char TIRET = '-';

//Prototypes de foncions. Utilisés pour pouvoir ajouter des fonctions après le main (au lieu d'avant).
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
 * @return         [retourne une string indiquant en vaudois le prix
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

	//vérifie que l'entrée utilisateur est comprise entre 0 et 1000000 (non compris)
	if (montant < 0 || montant >= 1000000)
		return "Entrée invalide";


	// fait un arrondi au centieme a la decimale la plus proche peut importe le nombre entre
	montant = floor(montant * CENT + 0.05) / CENT;
	//prend la partie entière du montant
	int montantEntier = (int) (montant + AJUSTEMENT);

	// après l'ajustement de la partie entière, vérifie que ça ne dépasse pas les bornes
	if (montantEntier < 0 || montantEntier >= 1000000)
		return "Entrée invalide";

	//prend la valeur décimale du montant, la converti en dizaine entiere (0.60 devient 60) et la stocke dans montantDecimal.
	int montantDecimal = (int) ((montant + AJUSTEMENT - montantEntier) * CENT);
	//si la partie entière vaut zero et la partie decimale est plus grande que zero alors on traite que le partie decimale et la partie entière vaut 0.
	if (montantEntier == ZERO && montantDecimal > ZERO)
		//Si le montantDecimal vaut 1 alors CENTIME est au singulier sinon CENTIME est au PLURIEL.
		return montantCentaine(montantDecimal, ZERO) +
			   (montantDecimal == UN ? ESPACE + CENTIME : ESPACE + CENTIME + PLURIEL);

	string montantTotal;
	//Si le montant entier est plus petit que 1000 on traite qu'une fois le nombre dans montantCentaine. L'idée c'est
	//qu'avec des nombres plus grand on separe le nombre en deux et on traite chaque partie avec la même fonction (montantCentaine).
	//Sinon traitement du nombre avec la fonction montantMillier.
	if (montantEntier < MILLE)
		//Traitement du cas où le montant vaut 0 ou 1 ce qui implique que franc est au singulier.
		//Sinon franc est au PLURIEL.
		if (montantEntier == ZERO || montantEntier == UN)
			montantTotal = montantCentaine(montantEntier, ZERO) + ESPACE + MONNAIE;
		else
			montantTotal = montantCentaine(montantEntier, ZERO) + ESPACE + MONNAIE + PLURIEL;
	else
		montantTotal = montantMillier(montantEntier) + ESPACE + MONNAIE + PLURIEL;

	//Traitement du cas où ni l'entier ni la décimale sont nulles. On ajoute au montantTotal tout simplement la décimale.
	if (montantDecimal > ZERO)
		montantTotal += ET + montantCentaine(montantDecimal, ZERO) +
						(montantDecimal == UN ? ESPACE + CENTIME : ESPACE + CENTIME + PLURIEL);

	return montantTotal;
}

/**
 * [montantDizaine retourne en lettres les nombres compris en 0 et 99]
 * @param  montant [montant compris entre 0 et 99]
 * @return         [retourne une string du nombre entier en en lettres]
 */
string montantDizaine(int montant) {
	//Si le montant  est plus grand que zero et plus petit que 10 on retourne la valeur donnée par la fonction unites.
	if (montant >= ZERO && montant < DIX)
		return unites(montant);
	//Sinon si le montant est plus grand que 10 et plus petit ou égal à 16 on retourne la valeur donnée par la fonction dizaine.
	else if (montant > DIX && montant <= 16)
		return dizaines(montant);
	//Si le montant vaut 10 et est comprise entre 17 et 99 on prend l'unité du montant.
  //Si l'unité vaut 0 on traite le montant avec la fonction dizaine normalement. Si elle vaut 1
  //on ajoute le ''et'' et sinon on ajoute le trait d'Union. Dans ces deux cas on traite les dizaines et unités séparement
  //avec les fonctions dizaines et unites.
	else if (montant >= DIX && montant < CENT) {
		int unite = montant % DIX;
		if (unite == ZERO)
			return dizaines(montant);
		else if (unite == UN)
			return dizaines(montant - unite) + ET + unites(montant % DIX);
		else if (unite > ZERO && unite < DIX)
			return dizaines(montant - unite) + TIRET + unites(montant % DIX);
	}
	return "0";
}

/**
 * [montantCentaine traduit des nombres entiers compris entre]
 * @param  montant [nombre entier à renvoyer en toutes lettres]
 * @param  millier [nombre entier permettant de controler si le nombre entre par l'utilisateur est supérieur a 999]
 * @return         [retourne une string de centaines en lettres]
 */
string montantCentaine(int montant, int millier) {

	// gere le cas ou le nombre est inferieur a 100
	if (montant < CENT)
		return montantDizaine(montant);
	// gere les cas ou le nombre est compris entre 100 et 999
	else if (montant >= CENT && montant < MILLE) {
		// gere le cas ou le montant vaut 100
		if (montant == CENT)
			return centaines(montant);
		// gere le cas ou le montant est suerieur a 100
		else if (montant > CENT) {
			// declaration d'une variable qui stocke les dizaines
			int dizaine = montant % CENT;
			// gere le cas des centaines ronde, cest a dire si 100 prend un "s" a la fin ou pas
			if (dizaine == ZERO)
				// si c'est des centaines de milliers 100 ne prendra pas de "s", exemple : deux cent mille
				if (millier == ZERO)
					return unites(montant / CENT) + ESPACE + centaines(dizaine);
				// sinon 100 prendra un "s", exemple deux cents
				else
					return unites(montant / CENT) + ESPACE + centaines(montant);
			// gere le cas des nombres compris entre 101 et 199 afin d'éviter le cas du "un cent.."
			else if (dizaine > ZERO && montant < 200)
				return centaines(montant - dizaine) + ESPACE + montantDizaine(dizaine);
			// permet d'ecrire le nombre de centaines et le reste des nombres
			else if (dizaine > ZERO && montant >= 200)
				return unites(montant / CENT) + ESPACE + centaines(montant) + ESPACE + montantDizaine(dizaine);
		}
	}
	return "0";
}

/**
 * [montantMillier traduit des nombres supérieur ou égale à 1000 en toutes lettres]
 * @param  montant [montant supérieur ou égale à 1000 à retranscrire en lettres]
 * @return         [retourne une string contenant le nombre entier en lettres]
 */
string montantMillier(int montant) {

	//déclaration d'entiers afin de nous permettre de séparer la partie des milliers et la partie des centaines
	int montantMille = montant / MILLE;
	int montantCent = montant % MILLE;

	// gère le cas d'un montant égal à mille
	if (montant == MILLE)
		return MILLIER;
	// gère le cas d'un montant compris entre 1001 et 1999
	else if (montant > MILLE && montant <= 1999)
		return MILLIER + ESPACE + montantCentaine(montantCent, ZERO);
	// gère le cas ou il n'y a pas de centaines après les milliers
	else if (montantCent == ZERO)
		return montantCentaine(montantMille, montantMille) + ESPACE + MILLIER;
	// gère tous les autres cas
	else
		return montantCentaine(montantMille, montantMille) + ESPACE + MILLIER + ESPACE + montantCentaine(montantCent, ZERO);
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