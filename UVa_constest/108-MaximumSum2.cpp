
// Programme C++ pour UVa constest, probleme 108-MaximumSum

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrice;

void initialisation (Matrice& mat)
{
	cout << "Entrer les élément du tableau ligne par ligne";
	for (auto& ligne : mat) {
		for (auto& element : ligne) {
			cin >> element;
		}
	}
	cout << endl;
}

void affiche (const Matrice& mat)
{
	for (size_t i(0); i < mat.size(); ++i) {
		cout << "|";
		for (size_t j(0); j < mat[i].size(); ++j) {
			cout << mat[i][j] << "|";
		}
		cout << "\n";
	}
	cout << endl;
}

// Fonction pour calculer "cummulative sum" d'un sub_regtangle d'une matrice
int cummulative (const Matrice& mat, int pos_row, int pos_col, int nb_row, int nb_col)
{
	int cummulative (0);
	for (int i(pos_row); i <= pos_row + nb_row; ++i) {
		for (int j(pos_col); j <= pos_col + nb_col; ++j) {
			cummulative += mat[i][j];
		}
	}
	return cummulative;
}

// Fonction pour afficher sub_rectagle d'une matrice
void sub_rectangle (const Matrice& mat, int pos_row, int pos_col, int nb_row, int nb_col)
{
	for (int i(pos_row); i <= pos_row+nb_row; ++i) {
		cout << "|";
		for (int j(pos_col); j <= pos_col+nb_col; ++j) {
			cout << mat[i][j] << "|";
		}
		cout << "\n";
	}
}

int main()
{
	cout << "Entrer la dimention du tableau (nxn) : n = ";
	int n;
	cin >> n;
	
	Matrice mat(n,vector<int>(n));
	initialisation(mat);
	affiche(mat);
	
	int max=-1e9;
	int max_pos_row, max_pos_col;
	int max_nbrow, max_nbcol;
	int sum;
	sum=cummulative(mat,0,0,3,3);
		
	for (size_t i(0); i<mat.size(); ++i) {
		for (size_t j(0); j< mat[i].size(); ++j) {
			for (size_t k(0); k<mat.size()-i; ++k) {
				for (size_t l(0); l<mat[i].size()-j; ++l) {
					sum = cummulative(mat,i,j,k,l);
					if (sum > max) {
						max = sum;
						max_pos_row = i;
						max_pos_col = j;
						max_nbrow = k;
						max_nbcol = l;
					}
				}
			}
		}
	}
	
 	cout << "Sum max = " << max << " de sub_rectangle : " << endl;		
	sub_rectangle(mat,max_pos_row,max_pos_col,max_nbrow,max_nbcol);
	
	return 0;
}
