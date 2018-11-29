/*
 -----------------------------------------------------------------------------------
 Laboratoire : 06
 Fichier     : Labo06.cpp
 Auteur(s)   : Yanik Lange, Soulyman Lamrani, Gabrielle Thurnherr
 Date        : 28.11.2018

 But         : Faire un check vaudois. c'est à

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */


#include <string>
#include <iostream>

using namespace std;
enum class dizaineSpeciale{onze, douze, treize, quatorze, quinze, seize};
enum class unite{zero, un, deux, trois, quatre, cinq, six, sept, huit, neuf};
enum class dizaine{dix, vingt, trente, quarante, cinquante, soixante, septante, huitante, nonante};
const string et = "et";
const char traitUnion = '-';

string plurielCent(double montant);
string montantEnVaudois(double montant);

string calculDizaine(int montant);
string calculCentaine(double montant);
string calculMille(double montant);
string calculCentime(double montant);
int main()
{
	double d;

	while( cin >> d ) {
		cout << montantEnVaudois(d) << endl;
	}

	return 0;
}
string calculDizaine(int montant)
{
	if (montant > 10 && montant < 17)
	{
		switch (dizaineSpeciale(montant))
		{
			case dizaineSpeciale::onze:
				return "onze";
				break;




		}
	}
}
string calculCentaine(double montant)
{

}
string montantEnVaudois(double d)
{

}

