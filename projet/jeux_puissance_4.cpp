// Programme C++ du jeux de Puissance 4

#include <iostream>
#include <array>

using namespace std;

enum Couleur {vide, rouge, jaune};
typedef array < array < Couleur, 7 >, 6 > Grille;

// Fonction pour initialiser le tableau grille au vide

void initialisation (Grille& grille)
{
	for (auto& ligne : grille) 
	{
		for (auto& kase : ligne)
		{
			kase = vide;
		}
	}
}

// Fonction permettre afficher le tableau grille
void affiche (const Grille& grille)
{
	for (auto ligne : grille)
	{
		cout << " |";
		for (auto kase : ligne)
		{
			if (kase == vide) {cout << " ";}
			if (kase == rouge) {cout << "X";}
			if (kase == jaune) {cout << "O";}
			cout << "|";
		}
		cout << "\n";
	}
	cout << "==";
	for (size_t i(0); i < grille[0].size(); ++i)
	{
		cout << i+1 << "=";
	}
	cout << endl;		
}

// Fonction d'un tour de jeux
bool joue(Grille& grille, size_t colone, Couleur couleur)
{
	// colone est remplie! jouer ne peut plus jouer dans cette colone
	if (grille[0][colone] != vide) {return false;}
	
	// colone n'est pas remplie! 
	// Chercher le premier colone vide à partir du bas de la grille pour mettre un pion
	size_t i(grille.size()-1);
	while ((i >= 0) and (grille[i][colone] != vide))
	{
		--i;
	}
	grille[i][colone] = couleur;
	
	return true;
}

// Fonction pour demander le jouer entre un numero de colone et verifier si c'est valide ou pas
void demande_au_joue(Grille& grille, Couleur couleur_jouer)
{
	bool valide;
	cout << "Entre un numero de colone : ";
	int colone;
	do {
		cin >> colone;
		cout << endl;
		--colone;
		valide = joue (grille, colone, couleur_jouer);
		if (not valide) {
			cout << "Votre pion n'est pas valide, entre un autre numero de colone : ";
		}
	} while (valide != true);
}

// Fonction pour verifier si la grille est remplie ou pas!
bool remplir (const Grille& grille)
{
	for (auto ligne : grille)
	{
		for (auto kase : ligne)
		{
			if (kase == vide) {return false;}
		}
	}
	return true;
}

// Fonction pour verifier si le jouer est gargne ou pas 
bool est_gargne (const Grille& grille, Couleur couleur_jouer)
{
	bool est_gargne(false);
	int nb;
	for (size_t i(0); i < grille.size(); ++i)
	{
		for (size_t j(0); j < grille[i].size(); ++j)
		{
			nb=0;
			if (grille[i][j]==couleur_jouer)
			{
				nb=1;
				// on ne considere que 4 directions autour de cette grille
				// direction 1:
				int k(1);
				do {
					if (grille[i-k][j+k]==couleur_jouer) {++nb; ++k;}
					else {break;}
				}while (k<4 and i-k>=0 and j+k<7);
				if (nb==4) {est_gargne = true; break;}
				
				// direction 2: 
				k=1; nb=1;
				do {
					if (grille[i][j+k]==couleur_jouer) {++nb; ++k;}
					else {break;}
				} while (k<4 and j+k<7);
				if (nb==4) {est_gargne = true; break;}
				
				// direction 3:
				k=1; nb=1;
				do {
					if (grille[i+k][j+k]==couleur_jouer) {++nb; ++k;}
					else {break;}
				} while (k<4 and i+k<7 and j+k<7);
				if (nb==4) {est_gargne = true; break;}
				
				// direction 4:
				k=1; nb=1;
				do {
					if (grille[i+k][j]==couleur_jouer) {++nb; ++k;}
					else {break;}
				} while (k<4 and i+k<7);
				if (nb==4) {est_gargne = true; break;}
			}
		}
	}
					
	return est_gargne;
}


int main()
{
	Grille grille;
	initialisation(grille);
	affiche (grille);
	
	int numero_de_jouer;
	cout << "Voulez-vous etre quelle jouer (1er ou 2eme) ? ";
	cin >> numero_de_jouer;
	cout << endl;
	
	if (numero_de_jouer==1) {
		cout << "Vous etes le premier jouer, votre pion sera : " << "X" << endl;
	} else {
		cout << "Vous etes le deuxieme jouer, votre pion sera : " << "O" << endl;
	}
	
	cout << "Votre jeu commence!" << endl;
	
	Couleur couleur_jouer(rouge);
	
	bool gargne;
	do {
		demande_au_joue (grille, couleur_jouer);
		// affiche pour voir
		affiche(grille);
		
		// verifier si le jouer est gargne ou pas !
		gargne = est_gargne (grille, couleur_jouer);
		
		// Anoncer si le jouer est gargne et le jeux termine !
		if (gargne) {
			if (couleur_jouer == rouge) {cout << "Le pion X êste gargné !" << endl;}
			if (couleur_jouer == jaune) {cout << "Le pion 0 êste gargné !" << endl;}
			cout << "Félicitation !!!" << endl;
		}
		
		// Si personne gargne, changer le jouer !
		if (couleur_jouer == rouge) {couleur_jouer = jaune;}
		else {couleur_jouer = rouge;}
	} while ((not remplir(grille)) and (not gargne));
	
	
	
	
	return 0;
}
