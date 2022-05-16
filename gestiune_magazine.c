#define _CRT_SECURE_NO_WARNINGS //pentru a nu mai primi eroarea de la scanf/ putem sa adaugam 4996 la propietati
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *f;//  variabila "f" este un pointer catre tipul FILE definit in stdlib.h
typedef struct oferta { 
	char *nume_produs; 
	float pret,cantitate;
	struct oferta *urmator2; //pointer la urmatoarea oferta din sublista=camp de inlantuire
}ofe; 
typedef struct magazin{
	char *nume_magazin; 
	struct magazin *urmator1; // pointer pentru urmatorul magazin
	struct oferta *sublista; //pointer la sublista de oferte 
}maga;//o variabila maga de tip magazin 
maga *primul = NULL; // primul nod radacina il initializam cu null 
ofe *introducere_oferta(ofe *lista, ofe *aux)
{
	ofe *q1, *q2;
	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->nume_produs, aux->nume_produs) > 0; q2 = q1, q1 = q1->urmator2);
	if (q1 == q2) { //daca il punem la inceput
		aux->urmator2 = lista;
	lista = aux; }
	else { q2->urmator2 = aux; //daca il punem pe parcurs
	aux->urmator2 = q1; }
	return lista;//asa am adaugat numele produsului in sublista 
	for (q1 = q2 = lista; q1 != NULL && q1->pret<aux->pret; q2 = q1, q1 = q1->urmator2);
	if (q1 == q2) { 
		aux->urmator2 = lista; 
		lista = aux; 
	}
	else { q2->urmator2 = aux; 
	aux->urmator2 = q1; }
	return lista;//am adaugat pretul
	for (q1 = q2 = lista; q1 != NULL && q1->cantitate < aux->cantitate; q2 = q1, q1 = q1->urmator2);
	if (q1 == q2) {
		aux->urmator2 = lista;
		lista = aux;
	}
	else {
		q2->urmator2 = aux;
		aux->urmator2 = q1;
	}
	return lista;// am adaugat cantitatea
}
maga *introducere_magazin(maga *lista,maga *aux, ofe *aux_s)// functie pentru a adaugarea unui magazin in lista de magazine ordonata alfabetic
{
	maga *a1, *a2;// folosim 2 pointeri de tip maga 

	for (a1 = a2 = lista; a1 != NULL && strcmp(a1->nume_magazin, aux->nume_magazin) < 0; a2 = a1, a1 = a1->urmator1); 
	//avem ; la final pt ca rolul for ului este doar de initializare, test si deplasare pentru a cauta locul potrivit de inserare
	//al nodului astfel incat lista sa fie ordonata
		
		//verificam daca nu exista deja acest nod in lista 
	if (a1 != NULL && strcmp(a1->nume_magazin, aux->nume_magazin)==0) //daca nodul listei e null sau e la fel ca unul pe care l am adaugat deja
	{																//apelam functia de introducere a info in sublista de oferte
		a1->sublista= introducere_oferta(a1->sublista, aux_s);		
		free(aux); //eliberam memoria alocata pt aux deoarece nu il vom folosii 
		return lista;//returnam lista de noduri in care au fost adaugate si nodurile sublistei mai sus
	}// daca nodul este inserat la inceputul listei 
		if (a1 == a2)
		{
			aux->urmator1 = lista; 
			lista = aux;
		}
		//daca nodul este inserat pe parcurs 
		else
		{
			a2->urmator1 = aux;
			aux->urmator1 = a1;
		}aux->sublista = introducere_oferta(aux->sublista, aux_s);
		return lista;

}

void citire()
{
	maga *aux;
	ofe *aux_s;
	char nume_magazin[20], nume_produs[20];
	float pret, cantitate;
	if ((f = fopen("magazine.txt", "r")) == NULL) //incercam sa deschidem fisierul in care avem salvata informatia 
	{											  // il deschidem pentru citire de aceea avem nevoie de "r"
		printf("eroare la deschiderea fisierului\n");   // in cazul in care nu se poate afisam un mesaj de atentionare
		exit(1);	// iesim din program cu 1 care indica o eroare

	}
	while (!feof(f))//atat timp cat nu am ajuns la finalul fisierului citim informatii
	{
		fscanf(f, "%s%s%f%f", nume_magazin, nume_produs, &pret, &cantitate);
		aux = (maga*)malloc(sizeof(maga));
		aux->nume_magazin = (char*)malloc(strlen(nume_magazin) + 1);
		strcpy(aux->nume_magazin, nume_magazin);
		aux->sublista = NULL;
		aux_s = (ofe*)malloc(sizeof(ofe));
		aux_s->nume_produs = (char*)malloc(strlen(nume_produs) + 1);
		strcpy(aux_s->nume_produs, nume_produs);
		aux_s->pret = pret;
		aux_s->cantitate = cantitate;
		primul = introducere_magazin(primul, aux, aux_s);
	}
}
void introducere()
{//chiar daca nu am mai verificat aici daca cumva mai exista acel nod am facut-o in functia de adaugare si e suficient 
	maga *aux;
	ofe *aux_s;
	char nume_magazin[20], nume_produs[20];
	float pret, cantitate;
		printf("dati numele magazinului:");//citim numele magazinului pe care vrem sa il introducem
		scanf("%s", nume_magazin);
		printf("dati numele produsului:");//citim numele produsului
		scanf("%s", nume_produs);
		printf("dati pretul:");
		scanf("%f", &pret);
		printf("dati cantitatea:");
		scanf("%f", &cantitate);
		aux = (maga*)malloc(sizeof(maga));//alocam spatiu pt nodul din lista
		aux->nume_magazin = (char*)malloc(strlen(nume_magazin) + 1);//alocam spatiu pentru numele magazinului din lista
		strcpy(aux->nume_magazin, nume_magazin);//copiem numele citit in lista
		aux->sublista = NULL;//astfel ne asiguram legatura cu urmatoarea sublista
		aux_s = (ofe*)malloc(sizeof(ofe));//alocam memorie pt sublista
		aux_s->nume_produs = (char*)malloc(strlen(nume_produs) + 1);//alocam memorie pt numele produsului
		strcpy(aux_s->nume_produs, nume_produs);//il copiem in sublista
		aux_s->pret = pret;//copiem pretul in sublista
		aux_s->cantitate = cantitate;//introducem cantitatea in sublista
		primul = introducere_magazin(primul, aux, aux_s);//apelam functia de creare a nodului unei liste 
	
}


void afisare( maga *lista)
{
	maga *q;//lista
	ofe *p;//sublista
	for (q = lista; q != NULL; q = q->urmator1)//q pleaca de la primul nod al listei si atata timp cat nu ajunge la nodul null printeaza numele magazinului
	{									//si apoi trece la urmatorul nod 
			printf("%s:\n", q->nume_magazin);       //printeza numele magazinului
			for (p = q->sublista;q!=NULL&& p != NULL ; p = p->urmator2)  //p pleaca de la primul nod al sublistei si cat timp e diferit de null printeaza oferta din magazin
			{
				printf("\t%s\t%.2f\t%.2f\t\n", p->nume_produs, p->pret, p->cantitate);
			}printf("\n");
	}

}
maga * sterge(maga*lista, char cautat[20])
{
	maga *prede, *curent;
	for (prede = NULL, curent = lista; curent; prede = curent, curent = curent->urmator1)
	{
		if (strcmp(curent->nume_magazin, cautat) == 0)
		{
			if (prede == NULL)
			{
				lista = lista->urmator1;
			}
			else
			{
				prede->urmator1 = curent->urmator1;//daca stergem ceva din interiorul listei
			}
			free(curent);//eliberam memoria  
			return lista;
		}
	}
	printf("nu s a gasit ce cautati\n");
	return lista; //daca nu s a gasit elementul cautat nu stergem nimic si returnam lista asa cum a fost la inceput
}

void stoc(maga*lista, char cautat[20]) {
	maga *q;//lista
	ofe *p;//sublista
	float suma_1 = 0, suma_2=0,stocul=1;//variabile pentru stoc
	for (q = lista; q != NULL; q = q->urmator1) // strabatem lista 
	{
		if (strcmp(q->nume_magazin, cautat) == 0)//verificam daca acesta este magazinul pentru care vrem sa calculam
		{
			for (p = q->sublista; p != NULL; p = p->urmator2) //daca este acesta calculam stocul
			{												//strabatem sublista si calculam suma preturilor si suma cantitatiilor
				suma_1 += p->pret;
				suma_2 += p->cantitate;
				stocul = suma_1 * suma_2;
				
			}
		}
		
	}
	if (stocul== 1) 
		{	
			printf("magazinul pe care l-ati introdus nu exista in lista!\n");
		}
	else
	{
		printf("stocul din acest magazin este:%.2f", stocul);
	}
}
	maga *stergere_sublista(maga *lista,char n[20])
{
	maga *q;
	ofe *a1, *a2;
	for (q = lista; q != NULL; q = q->urmator1)//parcurg lista
	{
		for (a1 = a2 = q->sublista; a1 != NULL && strcmp(a1->nume_produs, n) != 0; a2 = a1, a1 = a1->urmator2);//parcurgem sublista
		if (a1 != NULL && strcmp(a1->nume_produs, n) == 0)//verificam daca am gasit produsul cautat
		{
			if (a1 == a2)
				q->sublista = a1->urmator2;
			else
				a2->urmator2 = a1->urmator2;
			free(a1->nume_produs); //eliberam memoria pt numele produsului
			free(a1);//eliberam memoria pt nod 
			return lista;
		}
	}

}

	maga *cautare(maga* lista,char n[20])//functie pentru cautarea unui magazin in lista
	{
		maga *p;
		for (p = lista; p != NULL && strcmp(p->nume_magazin, n) < 0; p = p->urmator1);
		if (p != NULL && strcmp(p->nume_magazin, n) == 0)
			return p;//adica daca acest nod a fost gasit
		return NULL;

	}
	ofe *cautare_produs(ofe *lista,char n[20])//functie pentru cautarea unui produs in sublista dupa nume
	{
		maga *q;
		ofe *p;
		for (q = lista; q != NULL; q = q->urmator1)//strabatem lista de magazine
		{
			for (p = q->sublista; p != NULL && strcmp(p->nume_produs, n)!=0; p = p->urmator2);
			{
				if ( p != NULL && strcmp(p->nume_produs, n) == 0)
					return p;//daca mi a gasit produsul imi returneaza un pointer de tip ofe
				//daca nu imi returneaza NULL
			}
		}return NULL;
	}
	ofe *cautare_produs_pret(ofe *lista, float n)//functie pentru cautarea unui produs in sublista dupa pret
	{
		maga *q;
		ofe *p;
		for (q = lista; q != NULL; q = q->urmator1)//strabatem lista de magazine
		{
			for (p = q->sublista; p != NULL && p->pret==n; p = p->urmator2);
			{
				if (p != NULL && p->pret == n) printf("dsfcds");
					return p;
			}return NULL;
		}
	}
	ofe *rescriere(ofe *lista, char n[20],float pret,float cantitate)//functie pentru rescrierea datelor unui produs in sublista
	{
		maga *q;
		ofe *p;
		for (q = lista; q != NULL; q = q->urmator1)//strabatem lista de magazine
		{
			for (p = q->sublista; p != NULL && strcmp(p->nume_produs, n) != 0; p = p->urmator2);
			{
				if (p != NULL && strcmp(p->nume_produs, n) == 0)//daca l a gasit in sublista
				{
					p->pret = pret;// rescriu peste pretul de la acea pozitie noul pret 
					p->cantitate = cantitate;//rescriu peste cantitatea de la acea pozitie noua cantitate
				}

			}
		}
	}

maga * modificare(maga *lista,char n[20],char m[20])//pt numele magazinului si pentru numele produsului
	{//functia 7										pe care le am citit in main 
		maga *q;
		ofe *p,*u=NULL;
		float pret, cantitate;
		if (cautare(primul,n))//daca avem acest magazin in lista 
		{
			
				if(cautare_produs(primul,m))//verificam daca il avem acest produs in sublista
						{
							//daca il avem trebuie sa ii modificam datele adica pretul si cantitatea
							printf("dati noul pret pe care doriti sa il aiba produsul:");//le afiseaza de prea multe ori 
							scanf("%f", &pret);
							printf("dati noua cantitate pe care doriti sa o aiba produsul:");
							scanf("%f", &cantitate);//punem noua cantitate peste cea din lista

							if (cantitate == 0)//verificam daca cumva cantitatea este 0 si daca trebuie sa stergem produsul din lista
							{
								stergere_sublista(primul, m);//functie care sterge produsul din sublista de oferta a magazinului
								afisare(primul);
							}else
							{
							
									rescriere(primul, m, pret, cantitate);//functie care actualizeaza datele noi despre produs
									afisare(primul);
							}
						 }else //daca nu avem acest produs trebuie sa il adaugam
							{
								printf("dati datele si numele magazinului pe care doriti sa le introduceti:\n");
								introducere();
								afisare(primul);
									
						    }
		}
		else
		{
			printf("Acest magazin nu se afla in lista!\n"); 
		}
	}


int main()
{   
	char nume_cautat[20],n_pr[20];
	int opt,ok=0;// o variabila care ne va permite sa citim ce dorim sa facem
	while (1) //folosim o bucla infinita pentru a afisa meniul pana cand se selecteaza optiunea de iesire
	{
		printf("\n");
		printf("0.iesire\n");
		printf("1.Incarca din fisier datele intr-o lista cu subliste\n");//magazinele sunt alfabetic doar X citire si afisare
		printf("2.Sa se afiseze lista de magazine in ordine alfabetica si la fiecare magazine produsele in ordine decrescatoare dupa pret\n");
		printf("3.Sa se calculeze valoarea stocului dintr-un magazin citit de la tastatura\n");//X stoc
		printf("4.Sa se afiseze produsele dintr-un magazin in ordinea descrescatoare a pretului.\n");
		printf("5.Sa se adauge un magazin in lista de magazine\n");//X introducere
		printf("6.Sa se stearga un magazin din lista de magazine\n");// X functia sterge
		printf("7. Sa se modifice datele (cantitatea/pretul) de la un produs din cadrul unui magazin.\n In caz de cantitate 0 produsul este sters din lista.Daca produsul nu exista se va adauga in lista\n");
		printf("dati optiunea:\n");
		scanf("%d", &opt);// selectam optiunea prin citirea var "opt"
		printf("\n");
		switch (opt)
		{
		case 0:exit(0);
			break;
		case 1: ok++;
				citire();
				afisare(primul);
			break;
		case 2:	if (ok == 0)
			{
				printf("mai intai trebuie selectata optiunea 1 pt a putea fi incarcate datele!\n"); return;
			}
				afisare(primul);
			break;
		case 3:if (ok == 0)
			{
				printf("mai intai trebuie selectata optiunea 1 pt a putea fi incarcate datele!\n"); return;
			}
			   printf("dati numele magazinului unde doriti sa calculati stocul:");  
			   scanf("%s", nume_cautat);
			   stoc(primul, nume_cautat);
			break;
		case 4:if (ok == 0)
			{
				printf("mai intai trebuie selectata optiunea 1 pt a putea fi incarcate datele!\n"); return;
			}
			   printf("dati numele magazinului unde doriti sa afisati produsele:");
			   scanf("%s", nume_cautat);
			break;
		case 5:if (ok == 0)
			{
				printf("mai intai trebuie selectata optiunea 1 pt a putea fi incarcate datele!\n"); return;
			}
			   introducere();
			   afisare(primul);
			break;
		case 6:if (ok == 0)
		{
			printf("mai intai trebuie selectata optiunea 1 pt a putea fi incarcate datele!\n"); return;
		}
			printf("dati numele magazinului pe care doriti sa il stergeti:"); 
			scanf("%s", nume_cautat);
				primul=sterge(primul,nume_cautat); 
				afisare(primul);
		
			break;
		case 7:		if (ok == 0)
		{
			printf("mai intai trebuie selectata optiunea 1 pt a putea fi incarcate datele!\n"); return;
		}
			printf("dati numele magazinului in care doriti sa faceti modificari:"); 
					scanf("%s", nume_cautat);
					printf("dati numele produsului caruia doriti sa ii faceti modificari:"); 
					scanf("%s", n_pr);
					modificare(primul, nume_cautat, n_pr);
			break;
		default:printf("selectati o optiune posibila!\n");
			break;
		}
	}
		system("pause");
		return 0;
	}
