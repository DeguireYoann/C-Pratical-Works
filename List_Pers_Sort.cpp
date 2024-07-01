/*
Yoann Deguire
2024/06/30
IFT 1166 TP3 NumA Ete 2024
fichier: List_Pers_Sort.cpp
Ce script sert nottament à :
- Déclarer une classe Personne
- Lire un fichier txt et remplir une liste
- Afficher des personnes et leur props.
- Validation et affichage d'une personne à partir de son index dans la liste.
- Permuter deux personnes dans la liste.
- Rechercher d'une personne par son nom.
- Recherche dicho pour trouver une personne dans la liste.

Utilisation de documentation supplémentaire pour les iterators:
- Ressource utilisée: https://cplusplus.com/reference/iterator/
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

// Déclaration de la classe Personne
class Personne
{
   private :
      string nom;
      char sexe;
      float taille, poids;
      int numero;
    public :

        // Constructeur complet
        Personne(string nomComplet, char sex, int num, float tail, float poid)
        {
            nom = nomComplet;
            sexe = sex;
            taille = tail;
            poids = poid;
            numero = num;
        }  
        
        // Constructeur vide
        Personne()
        {
        }  

        // Constructeur avec nom
        Personne(string nomComplet)
        {
            nom = nomComplet;
            sexe = 'F';
            taille = 0.0;
            poids = 0.0;
            numero = 0000;
        }  
      
        string getNom()
        {
            return nom;
        }

        void setNom(string nouveauNom)
        {
            nom = nouveauNom;
        }

        char getSexe()
        {
            return sexe;
        }

        void setChar(char nouveauSexe)
        {
            sexe = nouveauSexe;
        }

        int getNumero()
        {
            return numero;
        }

        void setNumero(int nouveauNumero)
        {
            numero = nouveauNumero;
        }

        float getTaille()
        {
            return taille;
        }

        void setTaille(float nouvelleTaille)
        {
            taille = nouvelleTaille;
        }

        float getPoids()
        {
            return poids;
        }

        float setPoids(float nouveauPoids)
        {
            poids = nouveauPoids;
        }

        // Surchage d'opérateur < == <<
        bool operator<(const Personne& other)
        const {
            return nom < other.nom;
        }

        bool operator==(const Personne& other)
        const {
            return nom == other.nom;
        }

        friend ostream& operator<<(ostream& sortie, const Personne& personne)
        {
            sortie << fixed << setprecision(2) << left << setw(36) << personne.nom << "sexe: " << personne.sexe << setw(10) << " "
                << "taille: " << setw(8) << personne.taille << " metre" << setw(10) << " "
                << "poids: " << setw(8) << personne.poids << "kg" << setw(10) << " "
                << "numero: " << personne.numero << endl;
            return sortie;
        }
};

// Lire le fichier et remplir la liste
void lireRemplir(string nomALire, list<Personne> & liste, int & n)
{   
    int numero;
    float taille, poids;
    char sexe;
    string nom, prenom;
        
    ifstream  aLire (nomALire, ios::in);
    n = 0;				
    while (aLire >> nom >> prenom >> sexe >> taille >> poids >> numero)
    {
        string nomComplet = nom + " " + prenom;
        liste.push_back(Personne(nomComplet, sexe, numero, taille, poids));
        n++;
    }
    aLire.close();
}

// Valider si il y une personne dans la liste a un index donnee
void validerPersonneParIndex(list<Personne> & liste, int index)
{
    if (index > liste.size())
    {
        cout << "Aucune personne a la position " << index << endl;
        return;
    }

    list<Personne>::iterator pers = liste.begin();
    advance(pers, index -1);
    if (pers != liste.end())
    {
        cout << "La personne a la position " << index << " est\n" << *pers;
    }
    else
    {
        cout << "Acunne personne a la position " << index << endl;
    }
}

// permutation
void permuter(Personne& x, Personne& y)
{
    Personne tempo = x;
    x = y;
    y = tempo;
}

// Permute deux personne par leur index
void permuterDeuxPersonne(list<Personne> & liste, int premierIndex, int deuxiemeIndex)
{
    if (premierIndex <= liste.size() && premierIndex > 0 && deuxiemeIndex <= liste.size() && deuxiemeIndex > 0)
    {
        list<Personne>::iterator pers1 = liste.begin();
        list<Personne>::iterator pers2 = liste.begin();

        advance(pers1, premierIndex -1);
        advance(pers2, deuxiemeIndex  -1);

        permuter(*pers1, *pers2);
    }
    else
    {
        cout << "Permutation echouer\n";
    }
}

// Afficher la liste donnee
void afficherPersonnes(list<Personne> & liste)
{
    list<Personne>::iterator pers = liste.begin();
    while(pers != liste.end())
    {
        cout << *pers;
        pers++;
    }
}

// cherche un personne par find
void chercherPersonne(list<Personne> & liste, Personne aChercher)
{
    list<Personne> personneTrouve;
    int nbTrouver = 0;
    list<Personne>::iterator pers = find(liste.begin(), liste.end(), aChercher);
    if (pers != liste.end())
    {
        do {
            personneTrouve.push_back(*pers);
            nbTrouver++;
            pers = find(next(pers), liste.end(), aChercher);
        } while (pers != liste.end());
        
        cout << "Nombre de " << aChercher.getNom() << " trouves: " << nbTrouver << endl;
        afficherPersonnes(personneTrouve);
    }
    else
    {
        cout << aChercher << " n'existe pas\n";    
    }
}

// Valide si une personne existe par recherche binaire
void personneExiste(list<Personne> & liste, Personne & pers)
{
    if(binary_search(liste.begin(), liste.end(), pers))
    {
        cout << "La recherche binaire indique que " << pers.getNom() << " existe dans la liste\n";
    }
    else 
    {
        cout << "La recherche binaire indique que " << pers.getNom() << " existe PAS dans la liste\n";
    }
}

// Recherche Dicho
void dicho(list<Personne> liste, Personne aChercher)
{
    int mini = 0, maxi = liste.size() - 1;
    bool trouve = false;

    cout << "Recherche dichotomique de " << aChercher.getNom() << " :\n";
    
    while (mini <= maxi)
    {
        int milieu = (mini + maxi) / 2;
        auto cestLui = liste.begin();
        advance(cestLui, milieu);

        if (aChercher < *cestLui)
        {
            maxi = milieu - 1;
        }
        else if (*cestLui < aChercher)
        {
            mini = milieu + 1;
        }
        else
        {
            cout << "On trouve un(e) " << aChercher.getNom() << endl;
            trouve = true;
            break;
        }
    }

    if (!trouve)
    {
        cout << "On ne trouve pas " << aChercher.getNom() << endl;
    }
}


int main()
{
    list<Personne> listePersonne;
    int nbPers;

    lireRemplir("met_e24.txt", listePersonne, nbPers);

    // Afficher la liste complete
    afficherPersonnes(listePersonne);

    // Afficher le premiere et derniere personne de la liste
    cout << "\nPremiere personne\n" << listePersonne.front() << endl;
    cout << "Derniere personne\n" << listePersonne.back() << endl;

    // Prouver que la septième (7ème) personne existe, mais pas la 29ème personne
    validerPersonneParIndex(listePersonne, 7);
    validerPersonneParIndex(listePersonne, 29);

    //Permuter la 3ème et la 7ème personne, puis afficher dans la console la liste des 10 premières personnes avant le tri.
    permuterDeuxPersonne(listePersonne, 3, 7);

    // Afficher les 10 premier de la liste
    list<Personne> dixPremier;
    list<Personne>::iterator it = listePersonne.begin();
    for(int i = 0; i < 10; i++)
    {
        dixPremier.push_back(*it);
        it++;
    }
    cout << "\nLes dix premieres personnes : \n";
    afficherPersonnes(dixPremier);
    cout << endl;

    // Compter et afficher dans la console, le nombre de personnes ayant comme nom et prénom : MOLAISON CLAUDINE, ROY SERGE, ROBITAILLE SUZANNE.
    Personne suzanne = Personne("ROBITAILLE SUZANNE");
    Personne serge = Personne("ROY SERGE");
    Personne claudine = Personne("MOLAISON CLAUDINE");
    chercherPersonne(listePersonne, claudine);
    cout << endl;
    chercherPersonne(listePersonne, serge);
    cout << endl;
    chercherPersonne(listePersonne, suzanne);
    cout << endl;

    // Utilisation de la methode sort pour le tri
    listePersonne.sort();

    // Utiliser les fonctions find et count pour afficher toutes les personnes qui se nomment « ROBITAILLE SUZANNE » dans la liste déjà triée (donc après le tri).
    chercherPersonne(listePersonne, suzanne);
    cout << endl;

    // Utiliser la fonction binary_search pour prouver que la personne nommée MOLAISON CLAUDINE existe mais pas ROY SERGE.
    personneExiste(listePersonne, claudine);
    personneExiste(listePersonne, serge);
    cout << endl;

    // Chercher à l’aide de la recherche dichotomique puis afficher dans la console, les coordonnées d’une seule personne nommée ROBITAILLE SUZANNE.
    dicho(listePersonne, suzanne);
    cout << endl;

    // Afficher dans la console, de nouveau, toutes les personnes nommées ROBITAILLE SUZANNE
    chercherPersonne(listePersonne, suzanne);

    return 0;
}

/*
Resultat:
ROY CHANTAL                         sexe: F          taille: 1.75     metre          poids: 57.90   kg          numero: 2754
MOLAISON CLAUDINE                   sexe: F          taille: 1.57     metre          poids: 62.20   kg          numero: 1848
ROBITAILLE CHANTALE                 sexe: F          taille: 1.79     metre          poids: 72.30   kg          numero: 2007
BEDARD MARC-ANDRE                   sexe: M          taille: 1.43     metre          poids: 55.50   kg          numero: 2636
MONAST STEPHANE                     sexe: M          taille: 1.65     metre          poids: 61.70   kg          numero: 1750
ROBITAILLE SUZANNE                  sexe: F          taille: 1.67     metre          poids: 65.90   kg          numero: 2399
JALBERT LYNE                        sexe: F          taille: 1.63     metre          poids: 52.60   kg          numero: 2168
DUBE FRANCOISE                      sexe: F          taille: 1.68     metre          poids: 67.50   kg          numero: 4612
ROBITAILLE SUZANNE                  sexe: F          taille: 1.72     metre          poids: 75.40   kg          numero: 2325
LEMELIN SOPHIE                      sexe: F          taille: 1.88     metre          poids: 57.80   kg          numero: 7777
LABELLE LISE                        sexe: F          taille: 1.79     metre          poids: 68.00   kg          numero: 1512
CHOQUETTE HELENE                    sexe: F          taille: 1.71     metre          poids: 60.80   kg          numero: 2340
ROBITAILLE SUZANNE                  sexe: F          taille: 1.82     metre          poids: 76.10   kg          numero: 8007
MICHAUD NORMAND                     sexe: M          taille: 1.73     metre          poids: 103.70  kg          numero: 3428
RICHER AGATHE                       sexe: F          taille: 1.65     metre          poids: 53.10   kg          numero: 3563
BEGIN MARIE-LUCE                    sexe: F          taille: 1.62     metre          poids: 49.00   kg          numero: 4101
ROBITAILLE SUZANNE                  sexe: F          taille: 1.63     metre          poids: 75.10   kg          numero: 7654
COUTU PIERRE                        sexe: M          taille: 1.72     metre          poids: 62.10   kg          numero: 4008
TREMBLAY SUZANNE                    sexe: F          taille: 1.48     metre          poids: 61.50   kg          numero: 4371
BERGEVIN GUILLAUME                  sexe: M          taille: 1.84     metre          poids: 86.40   kg          numero: 2277
DUMITRU PIERRE                      sexe: M          taille: 1.82     metre          poids: 99.40   kg          numero: 3629
ROBITAILLE LUCIE                    sexe: F          taille: 1.78     metre          poids: 85.10   kg          numero: 6002
FILLION ERIC                        sexe: M          taille: 1.78     metre          poids: 75.70   kg          numero: 2630
DESMARAIS DENIS                     sexe: M          taille: 1.79     metre          poids: 58.70   kg          numero: 3215
TREMBLAY MARC                       sexe: M          taille: 1.79     metre          poids: 64.90   kg          numero: 3529
TREMBLAY SYLVAIN                    sexe: M          taille: 1.83     metre          poids: 86.20   kg          numero: 1538
ROBITAILLE SUZANNE                  sexe: F          taille: 1.68     metre          poids: 60.20   kg          numero: 4119

Premiere personne
ROY CHANTAL                         sexe: F          taille: 1.75     metre          poids: 57.90   kg          numero: 2754

Derniere personne
ROBITAILLE SUZANNE                  sexe: F          taille: 1.68     metre          poids: 60.20   kg          numero: 4119

La personne a la position 7 est
JALBERT LYNE                        sexe: F          taille: 1.63     metre          poids: 52.60   kg          numero: 2168
Aucune personne a la position 29

Les dix premieres personnes :
ROY CHANTAL                         sexe: F          taille: 1.75     metre          poids: 57.90   kg          numero: 2754
MOLAISON CLAUDINE                   sexe: F          taille: 1.57     metre          poids: 62.20   kg          numero: 1848
JALBERT LYNE                        sexe: F          taille: 1.63     metre          poids: 52.60   kg          numero: 2168
BEDARD MARC-ANDRE                   sexe: M          taille: 1.43     metre          poids: 55.50   kg          numero: 2636
MONAST STEPHANE                     sexe: M          taille: 1.65     metre          poids: 61.70   kg          numero: 1750
ROBITAILLE SUZANNE                  sexe: F          taille: 1.67     metre          poids: 65.90   kg          numero: 2399
ROBITAILLE CHANTALE                 sexe: F          taille: 1.79     metre          poids: 72.30   kg          numero: 2007
DUBE FRANCOISE                      sexe: F          taille: 1.68     metre          poids: 67.50   kg          numero: 4612
ROBITAILLE SUZANNE                  sexe: F          taille: 1.72     metre          poids: 75.40   kg          numero: 2325
LEMELIN SOPHIE                      sexe: F          taille: 1.88     metre          poids: 57.80   kg          numero: 7777

Nombre de MOLAISON CLAUDINE trouves: 1
MOLAISON CLAUDINE                   sexe: F          taille: 1.57     metre          poids: 62.20   kg          numero: 1848

ROY SERGE                           sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
 n'existe pas

Nombre de ROBITAILLE SUZANNE trouves: 5
ROBITAILLE SUZANNE                  sexe: F          taille: 1.67     metre          poids: 65.90   kg          numero: 2399
ROBITAILLE SUZANNE                  sexe: F          taille: 1.72     metre          poids: 75.40   kg          numero: 2325
ROBITAILLE SUZANNE                  sexe: F          taille: 1.82     metre          poids: 76.10   kg          numero: 8007
ROBITAILLE SUZANNE                  sexe: F          taille: 1.63     metre          poids: 75.10   kg          numero: 7654
ROBITAILLE SUZANNE                  sexe: F          taille: 1.68     metre          poids: 60.20   kg          numero: 4119

Nombre de ROBITAILLE SUZANNE trouves: 5
ROBITAILLE SUZANNE                  sexe: F          taille: 1.67     metre          poids: 65.90   kg          numero: 2399
ROBITAILLE SUZANNE                  sexe: F          taille: 1.72     metre          poids: 75.40   kg          numero: 2325
ROBITAILLE SUZANNE                  sexe: F          taille: 1.82     metre          poids: 76.10   kg          numero: 8007
ROBITAILLE SUZANNE                  sexe: F          taille: 1.63     metre          poids: 75.10   kg          numero: 7654
ROBITAILLE SUZANNE                  sexe: F          taille: 1.68     metre          poids: 60.20   kg          numero: 4119

La recherche binaire indique que MOLAISON CLAUDINE existe dans la liste
La recherche binaire indique que ROY SERGE existe PAS dans la liste

Recherche dichotomique de ROBITAILLE SUZANNE :
On trouve un(e) ROBITAILLE SUZANNE

Nombre de ROBITAILLE SUZANNE trouves: 5
ROBITAILLE SUZANNE                  sexe: F          taille: 1.67     metre          poids: 65.90   kg          numero: 2399
ROBITAILLE SUZANNE                  sexe: F          taille: 1.72     metre          poids: 75.40   kg          numero: 2325
ROBITAILLE SUZANNE                  sexe: F          taille: 1.82     metre          poids: 76.10   kg          numero: 8007
ROBITAILLE SUZANNE                  sexe: F          taille: 1.63     metre          poids: 75.10   kg          numero: 7654
ROBITAILLE SUZANNE                  sexe: F          taille: 1.68     metre          poids: 60.20   kg          numero: 4119
*/