#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
#define C 1000

typedef struct {
		int reference;
		char nom_modele[N];
		float prix;
		int stock;
		float valeur;
		} objet;

void ajout_catalogue (objet t[], int *nbe, objet new_element) // ok
{
	t[*nbe]=new_element;
	*nbe=*nbe+1;
	return;
}
int catalogue_plein (int nbe, int max) // ok
{
	int flag;

	flag=0;
	if (nbe==max)
		{
			flag = 1;
		}

	return flag;
}
int panier_vide (int nbe) //ok
{
	int flag;

	flag=0;
	if (nbe == 0)
		{
			flag = 1;
		}
	return flag;
}
int ajout_stock (objet t[], int nbe, int ref, int new_stock) // ok
{
	int i, flag;

	i=0;
	flag=0;
	while (i < nbe && flag == 0)
		{
			if (ref == t[i].reference)
				{
					t[i].stock=t[i].stock+new_stock;
					t[i].valeur=t[i].stock*t[i].prix;
					flag = 1;
				}
			i=i+1;
		}
	return flag;
}
int supprime_catalogue (objet t[], int *nbe, int ref)
{
	int i, isup, flag;

	i=0;
	flag=0;
	while (i < *nbe && flag == 0)
		{
			if (t[i].reference == ref)
				{
					flag = 1;
					isup = i;
				}
			i=i+1;	
		}

	if (flag == 1)
		{	
			i=isup;
			while (i < *nbe)
				{
					t[i]=t[i+1];
					i=i+1;
				}
		}
	*nbe=*nbe-1;

	return flag;
}
float cout_moyen (objet t[], int nbe, float *valeur_stock) // ok
{
	int i;
	float s, n, m;

	i=0;
	s=0;
	while (i<nbe)
		{
			s = s + t[i].prix*t[i].stock;
			n = n + t[i].stock;
			i=i+1; 
		}
	m=s/n;
	*valeur_stock=s;

	return m;
}
void remplit_panier (objet t[], int nbe, objet bag[], int *nbe_bag) // ok
{
	int i, j, continu, qte, flag1, flag2, plus;
	char element[N];

	continu=0;
	while (continu != 1)
		{
			if (continu == 0)
				{
					printf("\n\nEntrez le nom de l'element a ajouter au panier : ");
					fflush (stdin);
					gets (element);
					i = 0;
					flag1 = 0;
					while (i < nbe && flag1 == 0)
						{
							if (strcmp(t[i].nom_modele,element) == 0)
								{
									flag1 = 1;
									i=i-1;
								}
							i=i+1;
						}
					
					if (flag1 == 1)
						{
							printf ("Quel quantite souhaitez-vous commander : ");
							scanf("%d", &qte);

							if (qte <= 0)
								{
									j=0;
									flag2=0;
									while (j < *nbe_bag && flag2 == 0)
										{
											if (t[i].reference == bag[j].reference)
												{
													flag2 = 1;
												}
											j=j+1;
										}

									if (flag2 == 0)
										{
											printf("\nCette quantite est nulle, nous n'avons rien ajouter a votre panier");
										}
									else 
										{
											j=j-1;
											while (j < *nbe_bag)
												{
													bag[j]=bag[j+1];
													j=j+1;
												}
											printf ("\nNous avons bien supprimer cette element de votre panier");
										}
								}
							else
								{
									if (t[i].stock >= qte)
										{
											j=0;
											flag2=0;
											while (j < *nbe_bag && flag2 == 0)
												{
													if (t[i].reference == bag[j].reference)
														{
															flag2 = 1;
														}
													j=j+1;
												}
											if (flag2 == 0)
												{
													bag[*nbe_bag] = t[i];
													bag[*nbe_bag].stock = qte;
													bag[*nbe_bag].valeur=bag[*nbe_bag].stock*bag[*nbe_bag].prix;
													*nbe_bag = *nbe_bag + 1;
													printf ("\n\n* Cette element a bien ete ajoute a votre panier ! *\n\n");
												}
											else 
												{
													if (t[i].stock > qte)
														{	
															bag[j].stock = qte;
															bag[j].valeur = bag[j].stock*bag[j].prix;
															printf ("\n\n* Cette element a bien ete ajoute a votre panier ! *\n\n");
														}
													else
														{	
															printf("\nNous n'avons pas la quantite que vous demandez\n");
														}
												}
									
											printf (" 0 : Pour continuer vos achats \n");
											printf (" 1 : Pour arretez vos achats\n");
											printf ("Souhaitez vous continuer vos achats : ");
											scanf ("%d", &continu);
										}
									else 
										{
											printf ("\nDesole, nous n'avons pas une quantite suffisante pour satifaire votre demande\n");
										}
								}
						}
					else 
						{
							printf("\nDesole, nous n'avons pas cette element en stock\n\n");
							printf("0 : Pour continuer vos achats\n");
							printf("1 : Pour arreter vos achats\n");
							printf("Vous souhaitez ? ");
							scanf ("%d", &continu);
						}
				}
			else if (continu == 1)
				{	
					printf ("\n\n******** VOTRE PANIER EST TERMINE ********\n\n");
				}
			else 
				{
					printf("\n\nNous n'avons pas compris votre demande, recommencer\n\n");
					printf("0 : Pour continuer vos achats\n");
					printf("1 : Pour arreter vos achats\n");
					printf("Vous souhaitez ? ");
					scanf ("%d", &continu);
				}
		}
	return;
}
void affiche_tableau (objet t[], int nbe) // ok
{
	int i;
		
	i=0;
	while (i < nbe)
	{
		printf("   Indice : %d \n",i);
		printf("Nom : %s\n",t[i].nom_modele);
		printf("Reference : %d\n",t[i].reference);
		printf("Prix : %.2f\n",t[i].prix);
		printf("Quantite : %d\n",t[i].stock);
		printf("Valeur : %.2f\n\n",t[i].valeur);
		i=i+1;
	}
	return;
}
void vide_panier (objet bag[], int *nbe_bag, int indice) // ok
{
	int i;
	i=indice;

	while (i < *nbe_bag-1)
		{
			bag[i]=bag[i+1];
			i=i+1;
		}
	*nbe_bag=*nbe_bag-1;
	return;
}
int diminu_stock (objet t[], int nbe, objet bag[], int nbe_bag)
{
	int i, j, flag, sup;

	i=0;
	while (i < nbe_bag)
		{
			j=0;
			flag=0;
			while (j < nbe && flag == 0)
				{
					if (bag[i].reference == t[j].reference)
						{
							t[j].stock = t[j].stock - bag[i].stock;

							if (t[j].stock == 0)
							{
								sup=supprime_catalogue(t,&nbe,t[j].reference);
							}
							flag = 1;
						}
					j=j+1;
				}
			i=i+1;
		}
	return sup;
}
void tri_panier (objet bag[], int nbe_bag) 
{
 	int i,bi,bs,max;
 	objet stk;

	bi=0;
	bs=nbe_bag - 1;	
	while (bi != bs)
		{	
			i=bi;
			stk=bag[bi];	
			while (i<bs)
				{	
					if (bag[i].valeur >= stk.valeur)
						{	
							max=i;
							stk=bag[i];
						}
					i=i+1;
				}
			stk=bag[bi];
			bag[bi]=bag[max];
			bag[max]=stk;
			bi=bi+1;
		}
	return;
}

int main ()
{
	int i, choix, ne_cata, ne_panier, indice, ajout_stk, ref, flag, max, savoir, valider;
	float prix_panierHT, prix_final, prix_moyen, valeur_stk, TVA;
	objet catalogue[C], panier[C], element;


	ne_cata=0;
	ne_panier=0;
	while (choix != 9)
	{
		printf("\n\n********** MENU DU MAGASIN **********\n\n");
		printf(" 1 : Ajouter un element au catalogue\n");
		printf(" 2 : Ajouter du stock a un element\n");
		printf(" 3 : Afficher le catalogue\n");
		printf(" 4 : Afficher les informations du stock\n");
		printf(" 5 : Remplir le panier\n");
		printf(" 6 : Supprimer un element du panier\n");
		printf(" 7 : Afficher le panier\n");
		printf(" 8 : Valider le panier\n");
		printf(" 9 : Arreter le programme\n\n");
		printf(" Quel est votre choix ? ");
		scanf("%d",&choix);

		if (choix > 0 && choix < 10)
		{	
			if (choix == 1)
			{
				max=C;
				flag=catalogue_plein(ne_cata,max);
				if (flag == 0)
				{
					printf("\n\n*** Vous allez ajouter un nouvel element au catalogue du magasin ***\n\n");
					printf("Donnez la reference : ");
					scanf("%d",&element.reference);
					printf("Donnez le nom du modele : ");
					fflush(stdin);
					gets(element.nom_modele);
					printf("Donnez le prix unitaire HT : ");
					fflush(stdin);
					scanf("%f",&element.prix);
					fflush(stdin);
					printf("Donnez la quantite du stock : ");
					scanf("%d",&element.stock);
					element.valeur=element.prix*element.stock;

					ajout_catalogue(catalogue, &ne_cata, element);
				}
				else
				{
					printf(" \n\nCette action est impossible, le catalogue est plein");
				}
			}
			if (choix == 2)
			{
				printf("\n*** AUGMENTER LE STOCK ***\n\n");
				printf("Donnnez la reference de l'element du catalogue : ");
				scanf("%d",&ref);
				printf("Donner la quantita a ajouter : ");
				scanf("%d",&ajout_stk);

				flag=ajout_stock(catalogue,ne_cata,ref,ajout_stk);
				if (flag == 0)
				{
					printf("Une erreure c'est produite, cette reference n'existe pas");
				}
				else
				{
					printf("Le stock de l'element reference %d a ete modifie ",ref);
				}
			}
			if (choix == 3)
			{
				printf (" \n\n*** ELEMENT DU CATALOGUE ***\n\n");
				flag=panier_vide(ne_cata);
				if (flag == 1)
				{
					printf("Votre catalogue est vide\n\n");
				}
				else
				{
					affiche_tableau(catalogue, ne_cata);
				}
			}
			if (choix == 4)
			{
				prix_moyen=cout_moyen(catalogue,ne_cata,&valeur_stk);
				printf("\n\n*** INFORMATION STOCK ***\n\n");
				printf("Cout moyen des elements du catalogue : %.2f\n",prix_moyen);
				printf("Valeur du stock du magasin : %.2f\n",valeur_stk);
			}
			if (choix == 5)
			{
				printf("\n\n *** REMPLIT PANIER ***");
				remplit_panier (catalogue,ne_cata,panier,&ne_panier);
			}
			if (choix == 6)
			{
				flag=panier_vide(ne_panier);

				if (flag == 1)
				{
					printf("\nCette action est impossible, votre panier est vide\n\n");
				}
				else if (flag == 0)
				{
					printf("\n\nConnaissez vous l'indice de l'element a supprimer ?\n");
					printf("0 : Oui, vous connaissez l'indice de l'element\n");
					printf("1 : Non, vous ne connaisez pas l'indice de l'element\n");
					printf("Alors ? ");
					scanf("%d",&savoir);
					if (savoir == 0)
					{
						printf("Entrer l'indice de l'element a supprimer : ");
						scanf("%d",&indice);

						if (indice >= 0 && indice < ne_panier)
						{
							vide_panier (panier,&ne_panier,indice);
							printf("\n\n* Cette element a bien ete supprimer du panier *\n\n");
						}
						else
						{
							printf("\n\nCette indice ne correspond a aucun element dans votre panier\n\n");
						}	
					}
					else if ( savoir == 1)
					{
						printf("\n\nVous devriez afficher le contenu de votre panier\n");
						printf("Puis noter l'indice de l'element a supprimer\n\n");
					}
					else 
					{
						printf("\nNous n'avons pas compris\n\n");
						printf("Connaissez vous l'indice de l'element a supprimer ?\n");
						printf("0 : Oui, vous connaissez l'indice de l'element\n");
						printf("1 : Non, vous ne connaisez pas l'indice de l'élément\n");
						printf("Alors ? ");
						scanf("%d",&savoir);
					}
				}
				else
				{
					printf("\n\nNous n'avons pas compris votre demande\n\n");
				}
			}
			if (choix == 7)
			{
				printf("\n\n*** CONTENU DU PANIER ***\n\n");
				flag=panier_vide(ne_panier);
				if (flag == 1)
				{
					printf("  Votre panier est vide\n\n");
				}
				else
				{
					affiche_tableau(panier,ne_panier);
				}
			}
			if (choix == 8)
			{
				if (ne_panier != 0)
				{
					printf("\n\n****** VALIDER LE PANIER ******");
					printf("\n Vous allez valider votre panier\n\n");
					tri_panier(panier, ne_panier);

					affiche_tableau(panier, ne_panier);
					
					prix_panierHT=0;
					i=0;
					while (i < ne_panier)
					{
						prix_panierHT = prix_panierHT + panier[i].valeur;
						i=i+1;
					}

					TVA = prix_panierHT/5;
					prix_final = prix_panierHT + TVA;

					printf ("\nLe montant de votre panier hors taxe : %.2f\n", prix_panierHT);
					printf ("Le montant de votre panier avec les taxes : %.2f\n", prix_final);


					printf("\n 0 : Pour valider votre commande\n");
					printf(" 1 : Pour annuler\n");
					printf("Vous confirmez votre commande : ");
					scanf ("%d",&valider);

					if (valider == 0)
					{
						printf("\n* Merci pour votre commande ! * ");
						diminu_stock(catalogue, ne_cata,panier,ne_panier);
						i=0;
						while(i < ne_panier)
						{
							vide_panier(panier,&ne_panier,i);
							i=i+1;
						}
					}
					else
					{
						printf("\nLa confirmation de votre commande a ete interrompu");
						printf("\nVous pouvez continuer vos achats...");
					}
				}
				else
				{
					printf("\n\nCette action est impossible, votre panier est vide\n");
				}
			}
			if (choix == 9)
			{
				printf("\n\n Vous venez de fermer le menu    ");
				printf(" \n********** AU REVOIR **********\n");

			}
		}
		else 
		{
			printf("\n\nNous n'avons pas compris votre demande, recommencez");
		}
	}
	return 0;
}
