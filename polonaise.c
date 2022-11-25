#include "polonaise.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/* Completer cette fonction */
int calc()
{
  pile_t donnescalcul; // On donne la strcture pile_t à donnescalcul 
  init_pile(&donnescalcul); // On initilise une pile vide qui est donnescalcul
  char chaine; // On initilise la chaine de caractére chaine 
  int resultat=0; // Initilisation en Int du résultat 
  int n1,n2,n3; // Initilisation des n1 n2 et n3 en int 
  int compteur_operateur_calc = 0; //Initilisation du compteur d'opérande de calcul, qui démare à zéro !
  int compteur_operateur_num = 0; //Initilisation du compteur d'opérande numéraire, qui lui aussi doit commencé comme celui des opérateurs soit zéro

  // Ici nous comparons une chaine de caractére char à un numéraire il est donc traduit en ascii donc nous avons par éxemple 61 = =, 48 = 9, 39 = ' (etc...)


  while(chaine != 61) // Tant que chaine n'est pas égale à '=' soit ce qui désigne la fin du calcul d'aprés l'exemple ennoncé
  {
    scanf("%c",&chaine);
    if (chaine >= 48 &&  chaine <= 57  ) //Si la chaine est un nombre entre 0 et 9 
    {
      empiler(&donnescalcul,chaine - 48); // Empiler le nombre en question
      compteur_operateur_num ++; // Incrémentation du compteur num 
    }

    if(chaine == 43 ) // 43 -> + 
    {
      n1 = sommet(&donnescalcul); // Nous donnons la valeur du sommet à n1
      depiler(&donnescalcul); // Nous dépilons pour avoir accés au second nombre pour faire l'opération
      n2 = sommet(&donnescalcul); // Nous donnons la valeur du second nombre soit le nouveau sommet à n2
      depiler(&donnescalcul);
      resultat = n1 + n2; // Nous donnons la valeur de l'adition (dans ce cas) de n1 et n2 à resultat 
      empiler(&donnescalcul,resultat); // Nous empilons le résultat 
      compteur_operateur_calc++; // Nous incrémentons le compteur calcul car nous avons traité un opérateur +
    }

    // Le processus vu plus haut s'appliquera de facon similaire sauf l'opérande qui changera pour - / ' et *


    else if(chaine == 45 )// 45 -> -
    {
      n1 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      n2 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      resultat = n2 - n1;
      empiler(&donnescalcul,resultat);
      compteur_operateur_calc++;
    }
    else if(chaine == 42 )// 42 -> *
    {
      n1 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      n2 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      resultat = n1 * n2;
      empiler(&donnescalcul,resultat);
      compteur_operateur_calc++;
    }
    else if(chaine == 47 )// 47 -> /
    {
      n1 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      n2 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      resultat = n2 / n1;
      empiler(&donnescalcul,resultat);
      compteur_operateur_calc++;
    }
    else if(chaine == 44 )// 44 -> ,
    {
      n1 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      resultat = n1 * -1 ;
      empiler(&donnescalcul,resultat);
      compteur_operateur_calc++;
      compteur_operateur_num++;
    }
    else if(chaine == 33)
    {
      n1=sommet(&donnescalcul);
      depiler(&donnescalcul);
      resultat = 1;
      for(int i = 1; i <= n1; i++)
      {
        resultat*= i;
      }
      empiler(&donnescalcul,resultat);
      compteur_operateur_calc++;
      compteur_operateur_num++;
    }
    else if(chaine == 39)
    {
      n1 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      n2 = sommet(&donnescalcul);
      depiler(&donnescalcul);
      resultat = n2;
      for(int i = 1; i < n1; i++)
      {
        resultat*=n2;
      }
      empiler(&donnescalcul,n3);
      compteur_operateur_calc++;
    }

  }
  
  if(compteur_operateur_calc >= compteur_operateur_num)
  {
    return -1;
    
  }
  else if (compteur_operateur_num != (compteur_operateur_calc + 1))
  {
    return -2;
  }
  return resultat;
}


int shunting_yard(char* e){
  pile_t p;
  init_pile(&p);
  char chaineSY;
  int poisition_espace = 0;

  scanf("%c",&chaineSY);
  while (chaineSY!='='){
    if (chaineSY >= 48 && chaineSY <= 59)
    {
      if (poisition_espace != 0 )
      {
        e[poisition_espace] = 32;
        poisition_espace++;
      }
      e[poisition_espace]=chaineSY;
      poisition_espace++;
    }
    if (chaineSY == 40)
    {
      empiler(&p,chaineSY);
    }
    if (chaineSY == 41)
    {
      while ( !(pile_vide(&p) ) && sommet(&p) != 40)
      {
        e[poisition_espace]= 32;
				poisition_espace++;
				e[poisition_espace]=sommet(&p);
				poisition_espace++;
				depiler(&p);
      }
      if (!(pile_vide(&p)))
      {
        depiler(&p);
      }
    }
    if ( chaineSY == 43 || chaineSY == 45 )
    {
      if (chaineSY== 43)
      {
        while ((!(pile_vide(&p))) && (sommet(&p) != 40 && (sommet(&p)!= 43)))
        {
          e[poisition_espace]= 32;
          poisition_espace++;
          e[poisition_espace]=sommet(&p);
          poisition_espace++;
          depiler(&p);
        }
        empiler(&p,chaineSY);
      }
      else
      {
        while ((!(pile_vide(&p))) && (sommet(&p) != 40 && (sommet(&p)!= 45)))
        {
          e[poisition_espace]=' ';
          poisition_espace++;
          e[poisition_espace]=sommet(&p);
          poisition_espace++;
          depiler(&p);
        }

        empiler(&p,chaineSY);
      }
    }  
    if (chaineSY== 42 )
    {
      while (!(pile_vide(&p)) && (sommet(&p) != 40 && sommet(&p)!= 45 && sommet(&p)!= 43 && sommet(&p)!= 42))
      {
				e[poisition_espace]= 32;
				poisition_espace++;
				e[poisition_espace]=sommet(&p);
				poisition_espace++;
				depiler(&p);
			}
			empiler(&p,chaineSY);
    }
    //
    if (chaineSY== 47 )
    {
      while (!(pile_vide(&p)) && (sommet(&p) != 40 && sommet(&p)!= 45 && sommet(&p)!= 43 && sommet(&p)!= 47))
      {
				e[poisition_espace]= 32;
				poisition_espace++;
				e[poisition_espace]=sommet(&p);
				poisition_espace++;
				depiler(&p);
			}
			empiler(&p,chaineSY);
    }
    //
    if (chaineSY == 39)
    {
      while (!(pile_vide(&p)) && (sommet(&p) != 40 && sommet(&p)!= 45 && sommet(&p)!= 43 && sommet(&p)!= 42 && sommet(&p)!= 47))
      {
				e[poisition_espace]= 32;
				poisition_espace++;
				e[poisition_espace]=sommet(&p);
				poisition_espace++;
				depiler(&p);
			}
			empiler(&p,chaineSY);
    }
    if (chaineSY == 33 )
    {
      while (!(pile_vide(&p)) && (sommet(&p) != 40 && sommet(&p)!= 45 && sommet(&p)!= 43 && sommet(&p)!= 42 && sommet(&p)!= 47 && sommet(&p)!=39))
      {
				e[poisition_espace]= 32;
				poisition_espace++;
				e[poisition_espace]=sommet(&p);
				poisition_espace++;
				depiler(&p);
			}
			empiler(&p,chaineSY);
    }
    if (chaineSY == 44)
    {
      while (!(pile_vide(&p)) && (sommet(&p) != 40 && sommet(&p)!= 45 && sommet(&p)!= 43 && sommet(&p)!= 42 && sommet(&p)!= 47 && sommet(&p)!= 39)){
				e[poisition_espace] = 32;
				poisition_espace++;
				e[poisition_espace]=sommet(&p);
				poisition_espace++;
				depiler(&p);
			}
			empiler(&p,chaineSY);
    }
    scanf("%c",&chaineSY);
  }
  while(!(pile_vide(&p)))
  {
    e[poisition_espace]= 32;
    poisition_espace++;
    e[poisition_espace]=sommet(&p);
    poisition_espace++;
    depiler(&p);
  }

  strcat(e,"\0");
  return 0;
}
