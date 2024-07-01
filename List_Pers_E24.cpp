/*
Yoann Deguire
2024/06/30
IFT 1166 TP3 NumB Ete 2024
fichier: List_Pers_E24.cpp
Ce script sert nottament à :
- Déclarer une classe Personne
- Lire un fichier txt et remplir une liste
- Afficher des personnes et leur props.
- Validation et affichage d'une personne à partir de son index dans la liste.
- Permuter deux personnes dans la liste.
- Rechercher d'une personne par son nom.
- Trie de la liste
- Calcule du poids et de la taille moyenne

Utilisation de documentation supplémentaire pour les queues (swap):
- Ressource utilisée: https://en.cppreference.com/w/cpp/container/queue
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
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
void lireRemplir(string nomALire, deque<Personne> & liste, int & n)
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
void validerPersonneParIndex(deque<Personne> & liste, int index)
{
    if (index > liste.size() || index < 0)
    {
        cout << "Aucune personne a la position " << index << endl;
        return;
    }
    cout << "La personne a la position " << index << " est\n" << liste[index];
}

// Permute deux personne par leur index à l'aide du swap
void permuterDeuxPersonne(deque<Personne> & liste, int premierIndex, int deuxiemeIndex)
{
    if (premierIndex <= liste.size() && premierIndex > 0 && deuxiemeIndex <= liste.size() && deuxiemeIndex > 0)
    {
        swap(liste[premierIndex -1], liste[deuxiemeIndex -1]);
    }
    else
    {
        cout << "Permutation echouer\n";
    }
}

// Afficher la liste donnee
void afficherPersonnes(deque<Personne> & liste)
{
    deque<Personne>::iterator pers = liste.begin();
    while(pers != liste.end())
    {
        cout << *pers;
        pers++;
    }
}

// fonction de tri comme vue en cours
void trierListe(deque<Personne> & liste)
{
    for(int i = 0; i < liste.size(); i++)
  	{ 
        int indMin = i;
        for(int j = i+1; j < liste.size(); j++)
        {
            if (liste[j] < liste[indMin])
            {
                indMin = j;
            }
        }
        if (indMin != i)
        { 
            swap(liste[i], liste[indMin]);
        }
  	} 
}

// cherche un personne par l'opérateur surchargé = et une boucle for
void chercherPersonne(deque<Personne> & liste, Personne aChercher)
{
    deque<Personne> personneTrouve;
    int nbTrouver = 0;

    for(int i =0; i < liste.size(); i++)
    {
        if (liste[i] == aChercher)
        {
            personneTrouve.push_back(aChercher);
            nbTrouver++;
        }
    }

    if (personneTrouve.size() > 0)
    {
        cout << "Nombre de " << aChercher.getNom() << " trouves: " << nbTrouver << endl;
        afficherPersonnes(personneTrouve);
    }
    else
    {
        cout << aChercher << " n'existe pas\n";    
    }
}

float calculerMoyennePoids(deque<Personne> & liste)
{
    float moyenne = 0.0;
    for (int i =0; i < liste.size(); i++)
    {
        moyenne += liste[i].getPoids();
    }
    return moyenne / liste.size();
}

float calculerMoyenneTailles(deque<Personne> & liste)
{
    float moyenne = 0.0;
    for (int i =0; i < liste.size(); i++)
    {
        moyenne += liste[i].getTaille();
    }
    return moyenne / liste.size();
}



int main()
{
    deque<Personne> listePersonne;
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
    deque<Personne> dixPremier;
    deque<Personne>::iterator it = listePersonne.begin();
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
    trierListe(listePersonne);

    // Afficher le premiere et derniere personne de la liste trier (mini, maxi)
    cout << "\nPremiere personne\n" << listePersonne.front() << endl;
    cout << "Derniere personne\n" << listePersonne.back() << endl;

    // Utiliser les fonctions find et count pour afficher toutes les personnes qui se nomment « ROBITAILLE SUZANNE » dans la liste déjà triée (donc après le tri).
    chercherPersonne(listePersonne, suzanne);
    cout << endl;

    cout << fixed << setprecision(2);
    // Calculer et afficher dans la console, la taille moyenne de toutes les personnes.
    float moyenneTaille = calculerMoyenneTailles(listePersonne);
    cout << "La moyenne des tailles de la liste de " << listePersonne.size() << " est de " << moyenneTaille << " metre\n";

    // Calculer et afficher dans la console, le poids moyen de toutes les personnes.
    float poidsMoyen = calculerMoyennePoids(listePersonne);
    cout << "La moyenne des poids de la liste de " << listePersonne.size() << " est de " << poidsMoyen << " kg\n";
    
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
DUBE FRANCOISE                      sexe: F          taille: 1.68     metre          poids: 67.50   kg          numero: 4612
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
MOLAISON CLAUDINE                   sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0

ROY SERGE                           sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
 n'existe pas

Nombre de ROBITAILLE SUZANNE trouves: 5
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0


Premiere personne
BEDARD MARC-ANDRE                   sexe: M          taille: 1.43     metre          poids: 55.50   kg          numero: 2636

Derniere personne
TREMBLAY SYLVAIN                    sexe: M          taille: 1.83     metre          poids: 86.20   kg          numero: 1538

Nombre de ROBITAILLE SUZANNE trouves: 5
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0
ROBITAILLE SUZANNE                  sexe: F          taille: 0.00     metre          poids: 0.00    kg          numero: 0

La moyenne des tailles de la liste de 27 est de 1.71 metre
La moyenne des poids de la liste de 27 est de 68.70 kg
*/