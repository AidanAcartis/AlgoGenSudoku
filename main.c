#include <stdio.h>
#include <stdlib.h>

void afficheTableau(int Tableau[],int TailleTableau);
void afficheTableauLigne(int Tableau[], int TailleTableau);
void afficheMatrice(int matrice[10][10],int Taille);
void InitialiserTableau(int Tableau[],int TailleTableau);
int Total(int a);
int Puissance(int a, int b);
void BoucleCompteur(int boucle[10][10],int Uplet[10][10],int Classe[10][10],int Compteur[], int Taille);
void TableauBoucle(int boucle[10][10], int Compteur[],int counter,int Taille);
void InitialiserMatrice(int matrice[10][10],int Taille);
int ConditionLigne(int a,int b,int ligne,int Tableau[10][10], int TailleTableau);
int ConditionBloc(int a,int b,int ligne,int Tableau[10][10],int TailleTableau);
int ConditionFinale(int a,int b,int ligne,int Tableau[10][10],int TailleTableau);
int TestPresence(int a,int b,int Tableau[10][10],int Taille);
int LigneDeA(int a,int dimension);
int TestCarre(int a);
int CalculCounter(int Tableau[],int TailleTableau);
void TableauCompteur(int boucle[10][10],int Compteur[],int Taille);
void RemplirUpletComplet(int Uplet[10][10],int Classe[10][10],int boucle[10][10],int Taille);
void RetablirBoucle(int boucle[10][10],int Taille);
int main()
{
	int *Compteur = NULL;
	int dimension = 0;
	int i,j;
	int boucle[10][10];
	int Classe[10][10];
	int UpletComplet[10][10];
	printf("\nEntrer la dimension du tableau compteur:");
	scanf("%d", &dimension);

    if(TestCarre(dimension)==0)
	{
    do
	{
	  printf("\nLa dimension d'un tableau de Sudoku devrait uniquement un nombre qui est le carré d'un autre nombre");
      printf("\nEntrer un autre nombre comme dimension:");
	  scanf("%d", &dimension);
	}while(TestCarre(dimension)==0);
	}
	Compteur = malloc((dimension)*sizeof(int));
	printf("\nTotal(dimension) = %d", Total(dimension));
	InitialiserTableau(Compteur,dimension);
	InitialiserMatrice(boucle,dimension);
	InitialiserMatrice(UpletComplet,dimension);
	InitialiserMatrice(Classe,dimension);
	for(i=0;i<dimension;i++)
	{
		for(j=0;j<dimension;j++)
		{
			if(j==0)
			{
                Classe[i][j] = i+1;
			}
			else
			{
			  Classe[i][j] = Classe[i][j-1]+dimension;
			}
		}
	}
	afficheMatrice(Classe,dimension);
	//afficheMatrice(boucle,dimension);
	BoucleCompteur(boucle,UpletComplet,Classe,Compteur,dimension);

    free(Compteur);
    return 0;
}
void InitialiserTableau(int Tableau[],int TailleTableau)
{
	int i;
	for(i=0;i<TailleTableau;i++)
	{
        Tableau[i] = 0;
	}
	//printf("\nIntialisation de Uplet");
	//afficheTableauLigne(Tableau,TailleTableau);
}
void afficheMatrice(int matrice[10][10],int Taille)
{
	int i,j;
	printf("\n");
	for(i=0;i<Taille;i++)
	{
		for(j=0;j<Taille;j++)
		{
			printf("%3d", matrice[i][j]);
		}
		printf("\n");
	}
}
void afficheTableau(int Tableau[],int TailleTableau)
{
    int i;
    for(i=0;i<TailleTableau;i++)
	{
		printf("boucle[%d] = %d\n", i,Tableau[i]);
	}
}
void afficheTableauLigne(int Tableau[], int TailleTableau)
{
	int i;
	printf("\n");
	for(i=0;i<TailleTableau;i++)
	{
		printf("%4d\t",Tableau[i]);
	}
}
void BoucleCompteur(int boucle[10][10],int Uplet[10][10],int Classe[10][10],int Compteur[], int Taille)
{
   int total,counter = 0;
   int i,j;
   int pow,multiple,a = 0;
   total = Total(Taille);
   int stop;
   int arret;

   do
   {
	  //printf("\narret = %d",arret);
      for(i=(Taille-1);i>=0;i--)
	  {
        if(counter==0)
		{
            Compteur[i] = Compteur[i];
		}
		else
	    {
          pow = (Taille-1)-i;
          multiple = Puissance(total,pow);
          if((counter%multiple)==0)
		  {
            Compteur[i] = (Compteur[i]+1)%total;
		  }
		  else
		  {
            Compteur[i] = Compteur[i];
		  }
	    }
	  }
	  //afficheTableauLigne(Compteur,Taille);
	  TableauBoucle(boucle,Compteur,counter,Taille);
	  //printf("\nBOUCLE");
	  //afficheMatrice(boucle,Taille);
      RemplirUpletComplet(Uplet,Classe,boucle,Taille);
      //printf("\nVoici le tableau boucle:");
	  //afficheMatrice(boucle,Taille);
	  RetablirBoucle(boucle,Taille);
	  TableauCompteur(boucle,Compteur,Taille);
	  counter = CalculCounter(Compteur,Taille);
	  //printf("\ncounter = %d",counter);
	  //printf("\nAppuier sur 1 pour continuer");
	  //scanf("\n%d",&stop);

      a = 0;
      for(j=0;j<Taille;j++)
	  {
	  	if(Compteur[j]==total-1)
		{
		  a++;
		}
		else
		{
			j = Taille;
		}
		if(Compteur[0] == total)
		{
			a = Taille;
			j = Taille;
		}
	  }
	  if(a==Taille)
	  {
	  	arret = 1;
	  }
	  else
	  {
	  	arret = 0;
	  }
   }while(arret != 1);
}
int Total(int a)
{
  int compteur = 0;
  int total = 1;
  do
	{
       total = total * a;
       compteur++;
    }while(compteur != (a-2));
    return total;
}
int Puissance(int a,int b)
{
	int compteur = 0;
	int Pow = 1;
	if(b==0)
	{
		Pow = 1;
	}
	else
	{
	do
		{
			Pow = Pow * a;
	        compteur++;
		}while(compteur != b);
	}
        return Pow;
}
void TableauBoucle(int boucle[10][10], int Compteur[],int counter,int Taille)
{
   int ligne,colonne;
   int pow,multiple = 0;
   int powL,multipleL = 0;
   int total = Total(Taille);

   for(ligne=0;ligne<Taille;ligne++)
   {
     for(colonne=(Taille-2);colonne>=1;colonne--)
	 {
        if(Compteur[ligne]==0)
		{
            boucle[ligne][colonne] = 0;
		}
		else
		{
            pow = (Taille-2)-colonne;
            multiple = Puissance(Taille,pow);
            powL = (Taille-1)-ligne;
            multipleL = Puissance(total,powL);
            if((Compteur[ligne]%multiple)==0)
			{
                if((counter%multipleL)==0)
				{
                  boucle[ligne][colonne] = (boucle[ligne][colonne]+1)%Taille;
				}
				else
				{
					boucle[ligne][colonne] = boucle[ligne][colonne];
				}
			}
			else
			{
                boucle[ligne][colonne] = boucle[ligne][colonne];
			}
		}
	 }
   }
}
void InitialiserMatrice(int matrice[10][10],int Taille)
{
	int i,j;

	for(i=0;i<Taille;i++)
	{
		for(j=0;j<Taille;j++)
		{
			matrice[i][j] = 0;
		}
	}
}
int ConditionLigne(int a,int b,int ligne,int Tableau[10][10],int TailleTableau)
{
  int i;
  int compteur = 0;
  int testLigne;
  int DebutLigne = 0;
  int FinLigne = 0;
  DebutLigne = LigneDeA(a,TailleTableau);
  FinLigne = DebutLigne + (TailleTableau-1);
  //printf("\n");
  //printf("\nTEST CONDITION LIGNE");
  for(i=0;i<b;i++)
  {
	 //printf("\ndebutligne de %d est %d",a,DebutLigne);
	 //printf("\nFinligne de %d est %d",a,FinLigne);
	 if(Tableau[ligne][i]>=DebutLigne && Tableau[ligne][i]<=FinLigne)
	 {
	 	//printf("\n%d est sur la meme ligne que %d",a,Tableau[i]);
	 	//printf("\nUplet[%d] = %d",i,Tableau[i]);
	 	i = b;
	 }
	 else
	 {
	 	//printf("\n%d n'est pas sur la meme ligne que %d", a,Tableau[i]);
	 	//printf("\nUplet[%d] = %d",i,Tableau[i]);
		compteur++;
		//printf("\ncompteur = %d", compteur);
	 }
  }
  if(compteur == b)
  {
  	//printf("\ncompteur = %d\n b = %d",compteur,b);
  	testLigne = 1;
  }
  else
  {
  	testLigne = 0;
  }
  //printf("\n testligne = %d", testLigne);
  return testLigne;
}
int ConditionBloc(int a,int b,int ligne,int Tableau[10][10],int TailleTableau)
{
    int i;
    int moduloDim = 0;
    int piste = 0;
    int quotient = 0;
    int m = 0;
    int debutRect = 0;
    int finRect = 0;
    int debutBloc,finBloc = 0;
    int x,y,modulo = 0;
    int testBloc;
    int r,j=0;
    int Carre = 0;
    int Debut,Fin = 0;
    int compteur,arretBoucle,Compter = 0;
    //int stop;
    Carre = TestCarre(TailleTableau);
    for(i=0;i<b;i++)
	{
		arretBoucle = 0;
		compteur = 0;

       moduloDim = Tableau[ligne][i]%TailleTableau;
       if(moduloDim==0)
	   {
	   	 moduloDim = TailleTableau;
	   }
	   modulo = moduloDim%Carre;
             if(modulo==0)
			 {
			 	modulo = Carre;
			 }

	   //printf("\nmoduloDim = %d = Tableau[%d] MOD %d = %d MOD %d",moduloDim,i,TailleTableau,Tableau[i],TailleTableau);
       piste = Tableau[ligne][i]-moduloDim;
       if(piste==0)
	   {
	   	 piste = TailleTableau;
	   }
	   //printf("\npiste = %d = %d - %d",piste,Tableau[i],moduloDim);
       quotient = piste / TailleTableau;
       m = quotient % Carre;
       //printf("\nquotient = %d\nm = %d",quotient,m);

       if(m==1)
	   {
          debutRect = piste-(TailleTableau-1);
          finRect = piste+(TailleTableau*(Carre-1));
          //printf("\n\ndebutRect = %d\nfinRect = %d",debutRect,finRect);

          if(a>=debutRect && a<=finRect)
		  {
             if(modulo==1)
			 {
			 	debutBloc = debutRect+(moduloDim-1);
			 	finBloc = (debutBloc+(Carre-1))+(TailleTableau*(Carre-1));
			 }
			 else
			 {
			 	x = modulo-1;
			 	y = moduloDim-x;
			 	debutBloc = debutRect+(y-1);
			 	finBloc = (debutBloc+(Carre-1))+(TailleTableau*(Carre-1));
			 }
			 Debut = debutBloc;
			 Fin = Debut+(Carre-1);
			 //printf("\n\ndebutBloc = %d\nfinBloc = %d",debutBloc,finBloc);
			 do
			 {

                if(a>=Debut && a<=Fin)
				{
					//printf("\n\nDebut = %d\nFin = %d",Debut,Fin);
					testBloc = 0;
					//printf("\n\n%d est dans le meme bloc que %d",a,Tableau[i]);
					arretBoucle = Carre;
				}
				else
				{
				//printf("\n\nDebut = %d\nFin = %d",Debut,Fin);
				//printf("\n\n%d n'est pas entre %d et %d\narretBoucle = %d",a,Debut,Fin,arretBoucle);
				Debut = Debut+TailleTableau;
                Fin = Fin+TailleTableau;
                compteur++;
                arretBoucle++;
                }

			 }while(arretBoucle != Carre);
			 //printf("\nAppuier sur 1 pour continuer");
                //scanf("%d", &stop);

		  }
		  else
		  {
		  	 testBloc = 1;
		  	 //printf("\n\n%d n'est pas dans le meme bloc que %d",a,Tableau[i]);
		  }
	   }
	   else if(m==0)
	   {
          debutRect = piste+1;
          finRect = (debutRect+(TailleTableau-1)) + (TailleTableau*(Carre-1));
          //printf("\n\ndebutRect = %d\nfinRect = %d",debutRect,finRect);

           if(a>=debutRect && a<=finRect)
		  {
             if(modulo==1)
			 {
			 	debutBloc = debutRect+(moduloDim-1);
			 	finBloc = (debutBloc+(Carre-1))+(TailleTableau*(Carre-1));
			 }
			 else
			 {
			 	x = modulo-1;
			 	y = moduloDim-x;
			 	debutBloc = debutRect+(y-1);
			 	finBloc = (debutBloc+(Carre-1))+(TailleTableau*(Carre-1));
			 }
			 Debut = debutBloc;
			 Fin = Debut+(Carre-1);
			 //printf("\n\ndebutBloc = %d\nfinBloc = %d",debutBloc,finBloc);
			 do
			 {

                if(a>=Debut && a<=Fin)
				{
					//printf("\n\nDebut = %d\nFin = %d",Debut,Fin);
					testBloc = 0;
					//printf("\n\n%d est dans le meme bloc que %d",a,Tableau[i]);
					arretBoucle = Carre;
				}
				else
				{
				//printf("\n\nDebut = %d\nFin = %d",Debut,Fin);
				//printf("\n\n%d n'est pas entre %d et %d\narretBoucle = %d",a,Debut,Fin,arretBoucle);
				Debut = Debut+TailleTableau;
                Fin = Fin+TailleTableau;
                compteur++;
                arretBoucle++;
                }

			 }while(arretBoucle != Carre);
			 //printf("\nAppuier sur 1 pour continuer");
                //scanf("%d", &stop);

		  }
		  else
		  {
		  	 testBloc = 1;
		  	 //printf("\n\n%d n'est pas dans le meme bloc que %d",a,Tableau[i]);
		  }
	   }
	   else
	   {
         r = m-1;
         j = piste-(TailleTableau*r);
         debutRect = j-(TailleTableau-1);
         finRect = j+(TailleTableau*(Carre-1));
         //printf("\n\ndebutRect = %d\nfinRect = %d",debutRect,finRect);

		   if(a>=debutRect && a<=finRect)
		  {
             if(modulo==1)
			 {
			 	debutBloc = debutRect+(moduloDim-1);
			 	finBloc = (debutBloc+(Carre-1))+(TailleTableau*(Carre-1));
			 }
			 else
			 {
			 	x = modulo-1;
			 	y = moduloDim-x;
			 	debutBloc = debutRect+(y-1);
			 	finBloc = (debutBloc+(Carre-1))+(TailleTableau*(Carre-1));
			 }
			 Debut = debutBloc;
			 Fin = Debut+(Carre-1);
			 //printf("\n\ndebutBloc = %d\nfinBloc = %d",debutBloc,finBloc);
			 do
			 {

                if(a>=Debut && a<=Fin)
				{
					//printf("\n\nDebut = %d\nFin = %d",Debut,Fin);
					testBloc = 0;
					//printf("\n\n%d est dans le meme bloc que %d",a,Tableau[i]);
					arretBoucle = Carre;
				}
				else
				{
				//printf("\n\nDebut = %d\nFin = %d",Debut,Fin);
				//printf("\n\n%d n'est pas entre %d et %d\narretBoucle = %d",a,Debut,Fin,arretBoucle);
				Debut = Debut+TailleTableau;
                Fin = Fin+TailleTableau;
                compteur++;
                arretBoucle++;
                }

			 }while(arretBoucle != Carre);
			 //printf("\nAppuier sur 1 pour continuer");
                //scanf("%d", &stop);

		  }
		  else
		  {
		  	 testBloc = 1;
		  	 //printf("\n\n%d n'est pas dans le meme bloc que %d",a,Tableau[i]);
		  }
	   }

	   if(testBloc == 0)
	   {
	   	 //printf("\nsi le nombre est deja dans le meme bloc qu'un autre;on arrete");
	   	 i = b;
	   }
	   else
	   {
         Compter++;
	   }
	}
	//printf("\n\ncompteurB = %d",compteur);
 if(Compter == b)
 {
 	testBloc = 1;
 	//printf("\n\n%d n'est dans aucun bloc des nombres deja choisis",a);
 }
 else
 {
 	testBloc = 0;
 }
 return testBloc;
}
int ConditionFinale(int a,int b,int ligne,int Tableau[10][10],int TailleTableau)
{
	int testUn,testDeux,test;
	int CondLigne,CondBloc,TestP;
	CondLigne = ConditionLigne(a,b,ligne,Tableau,TailleTableau);
	CondBloc = ConditionBloc(a,b,ligne,Tableau,TailleTableau);
	TestP = TestPresence(a,ligne,Tableau,TailleTableau);

	if(CondLigne==1 && CondBloc==1)
	{
        testUn = 1;
	}
	else
	{
		testUn = 0;
		//printf("\n\nTestligne = %d",CondLigne);
		//printf("\n\ntestbloc = %d",CondBloc);
		//printf("\n\ntestfinale = %d",test);
	}
	if(TestP==1)
	{
		testDeux = 1;
	}
	else if(TestP==0)
	{
        testDeux = 0;
	}

	if(ligne==0)
	{
        test = testUn;
	}
	else
	{
        if(testUn==1 && testDeux==1)
		{
			test = 1;
		}
		else
		{
			test = 0;
		}
	}

	//printf("\ntest = %d",test);
	return test;

}
int TestPresence(int a,int b,int Tableau[10][10],int Taille)
{
	int test;
	int nCase,compteur = 0;
	int ligne,colonne;

	for(ligne=0;ligne<b;ligne++)
	{
		for(colonne=0;colonne<Taille;colonne++)
		{
            if(Tableau[ligne][colonne]==a)
			{
                colonne = Taille;
                ligne = b;
			}
			else
			{
               compteur++;
			}
		}
	}
	nCase = Taille*b;
	if(compteur == nCase)
	{
		test = 1;
	}
    else
		{
			test = 0;
		}
	return test;
}
int LigneDeA(int a,int dimension)
{
	int Ligne = 0;
	Ligne = a%dimension;

	if(Ligne != 1)
	{
	  if(Ligne == 0)
	  {
		Ligne = dimension;
	  }
	  do
	  {
	  	a--;
        Ligne = a%dimension;
	  }while(Ligne != 1);
	}
	return a;
}
int TestCarre(int a)
{
    int i;
    int Carre = 0;
    int square = 0;
    int compteur = 0;
    for(i=2;i<=a;i++)
	{
       Carre = i*i;
       if(Carre == a)
	   {
	   	 square = i;
	   	 i = a+1;
	   }
	   compteur++;
	}
	return square;
}
int CalculCounter(int Tableau[],int TailleTableau)
{
	int i,x,y,pow,rang = 0;
	int total = 0;
	int compteur = 0;
	i = 0;
	y = 0;
		total = Total(TailleTableau);
	do
	{
		//printf("\n");
		pow = ((TailleTableau-1)-i);
		//:printf("\npow = %d",pow);
		rang = Puissance(total,pow);
		//printf("\nrang = %d",rang);
		x = rang*Tableau[i];
		//printf("\nx = %d*%d = %d",rang,Tableau[i],(rang*Tableau[i]));
        y = y+x;
        //printf("\ny = %d+%d = %d",y,x,(y+x));

        //scanf("%d", &stop);
        i++;
	}while(i != TailleTableau);
    compteur = y+1;
    //printf("\ncounter = %d",(y+1));
    return compteur;
}
void TableauCompteur(int boucle[10][10],int Compteur[],int Taille)
{
    int ligne,colonne;
    int x,y,pow,rang = 0;
    for(ligne=0;ligne<Taille;ligne++)
	{    y =0;
		for(colonne=0;colonne<(Taille-1);colonne++)
		{   //printf("\n");
		    //printf("\nligne = %d\ncolonne = %d",ligne,colonne);
			pow = ((Taille-2)-colonne);
			//printf("\npow = %d",pow);
			rang = Puissance(Taille,pow);
			//printf("\nrang = %d",rang);
			//printf("\nboucle[%d][%d] = %d",ligne,colonne,boucle[ligne][colonne]);
			x = rang*boucle[ligne][colonne];
			//printf("\nx = %d*%d = %d", rang,boucle[ligne][colonne],(rang*boucle[ligne][colonne]));
			y = y+x;
			//printf("\n y = %d+%d = %d",y,x,(x+y));
		}
		Compteur[ligne] = y;
	}
	//afficheTableauLigne(Compteur,Taille);
}
void RemplirUpletComplet(int Uplet[10][10],int Classe[10][10],int boucle[10][10],int Taille)
{
    int ligne,colonne;
    int j,Ligne = 0;
    int testNombreChoisi;
    int signalFin = 0;
    int stop;
    //printf("\nUPLET");
    //afficheMatrice(Uplet,Taille);
    for(ligne=0;ligne<Taille;ligne++)
	{
		for(colonne=0;colonne<Taille;colonne++)
		{
			//4printf("\n");
			//printf("\nligne = %d\ncolonne = %d",ligne,colonne);

			Ligne = (ligne+colonne)%Taille;
            for(j=boucle[ligne][colonne];j<Taille;j++)
             {
                testNombreChoisi = 	ConditionFinale(Classe[Ligne][boucle[ligne][colonne]],colonne,ligne,Uplet,Taille);
                if(testNombreChoisi==1)
				{
                    Uplet[ligne][colonne] = Classe[Ligne][boucle[ligne][colonne]];
                    j = Taille;
				}
				else if(testNombreChoisi==0)
				{
                    boucle[ligne][colonne] = boucle[ligne][colonne]+1;
                    if(boucle[ligne][colonne]>=Taille)
					{
                        boucle[ligne][colonne] = boucle[ligne][colonne]%Taille;
                        do
						{
							colonne--;
							//printf("\ncolonne first do = %d",colonne);
                            if(colonne==0)
							{
                                boucle[ligne][colonne] = 0;
                                ligne--;
                                do
								{
                                   colonne--;
                                   if(colonne<0)
								   {
								   	 colonne = colonne+Taille;
								   	 if(colonne>Taille)
									 {
									 	colonne = colonne%Taille;
									 }
								   }
                                   //printf("\ncolonne second do = %d",colonne);
								}while(colonne==0 || colonne==(Taille-1));

							}
                            boucle[ligne][colonne] = (boucle[ligne][colonne]+1)%Taille;
                            RetablirBoucle(boucle,Taille);
                            if(boucle[0][1]==0)
							{
								printf("\nC'est fini.");
								colonne--;
								boucle[ligne][colonne] = 1;
                                signalFin = 1;
							}
                            //afficheMatrice(boucle,Taille);
						}while(boucle[ligne][colonne]==0);
						colonne--;
						//printf("\nfin colonne = %d",colonne);
					}
					  if(signalFin==1)
					  {
                        j=Taille;
                        colonne = Taille;
                        ligne = Taille;
					  }
					  //afficheMatrice(boucle,Taille);
					  //printf("\nAppuier sur 1 pour continuer");
	                  //scanf("\n%d",&stop);
				}
				 else
				 {
				 	printf("\nError");
				 	printf("\ntestNombreChoisi = %d",testNombreChoisi);
				 	exit(0);
				 }
             }
		}
	}
	   if(signalFin == 1)
	   {
	   	 //printf("\nBOUCLE");
	   	 //afficheMatrice(boucle,Taille);
	   	 //printf("\nUPLET ERROR");
	   	 //afficheMatrice(Uplet,Taille);
         printf("\n\tFIN");
	   }
	   else
	   {
	   	 //printf("\nUplet:");
         afficheMatrice(Uplet,Taille);
	   }
	   InitialiserMatrice(Uplet,Taille);
}
void RetablirBoucle(int boucle[10][10],int Taille)
{
	int ligne;
	for(ligne=0;ligne<Taille;ligne++)
	{
        boucle[ligne][Taille-1] = 0;
	}
	//afficheMatrice(boucle,Taille);
}
