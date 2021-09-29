#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define  name "database.txt"				
#define  fname "password.txt"
#define nomefile "temporaneo.txt"
#define nfile "temppassword.txt"
#define delim "	"
int login();										//effettua il login per le operazioni
void pwdgenerator (char s[]); 						//generatore di password
void nuovecredenziali(char nuovoutente[]);			//crea nuovi dati nel file password
void crea();										//crea nuovi dati nel file database
void modifica();									//modifica i dati nel database
void visualizzadb();								//visualizza il database
void cerca();										//effettua la ricerca tramite parola chiave nel database
void cercamodifica(char st[]);						//effettua la ricerca del dato da modificare e/o eliminare
void visualizzapwd();								//visualizza un riepilogo delle credenziali degli utenti
void elimina();										//elimina dati anagrafici
void modificautente();								//modifica dati d'accesso (username e pass)
void cercamodificacredenziali(char st[]);			//effettua la ricerca del dato da modificare e/o eliminare (credenziali d'accesso)
void eliminautente();								//elimina dati d'accesso (credenziali)

int main()
{
    int r,risp,rispadmin,rispuser,rr;
    char str[256];
    printf("\t\t\t***GESTIONE DATABASE ANAGRAFICO***\n ");
    printf ("Salve, vuole effettuare il login nel sistema? Inserisca 1 per 'si' 2 per 'no'\n");
    scanf("%d",&r);
    do
    {
        if(r==1)
        {
            risp=login();					//chiama la funzione per il login
        }
        else
        {
            printf("...Chiusura del programma... \n");
            return 0;
        }
        if(risp==0)
        {
            printf("Riconosciuto come admin \n\n");
            printf("Quale operazione vuole effettuare?\n");
            printf("1:Crea nuovo utente (Nuove credenziali)"
                    "\n2:Inserimento nuovi dati anagrafici"
                    "\n3:Modifica database"
                    "\n4:Visualizzazione database"
                    "\n5:Ricerca nel database"
                    "\n6:Visualizzazione username e password utenti"
                    "\n7: Modifica dati accesso (credenziali)"
                    "\n0:Uscita dal programma\n");
            scanf("%d",&rispadmin);
            if(rispadmin==1)
            {
                nuovecredenziali(str);							//chiama funzione per creazione nuove credenziali
                printf("\n\t\t\t ***RIEPILOGO DELLE CREDENZIALI*** \n %s",str);
            }
            else if(rispadmin==2)
            {
                crea();											//chiama la funzione per creare nuovi dati anagrafici
            }
            else if(rispadmin==3)
            {
                modifica();										//chiama funzione per modificare i dati presenti
            }
            else if(rispadmin==4)
            {
                visualizzadb();									//chiama funzione per visualizzare il database
            }
            else if(rispadmin==5)
            {
                cerca();									//chiama funzione per effettuare una ricerca nel database
            }
            else if(rispadmin==6)
            {
                visualizzapwd();								//chiama funzione per visualizzare il riepilogo delle credenziali
            }
            else if(rispadmin==7)
            {
            	modificautente();								//chiama funzione per modificare credenziali
			}
            else if(rispadmin==0)
            {
                printf("...Chiusura del programma... \n");
                return 0;
            }
		}
        else if(risp==1)
        {
            printf("Riconosciuto come utente \n");
            printf("Inserisca '1' per visionare il database;\nInserisca '2' per effettuare una ricerca tramite parola chiave;\nInserisca '0' per uscire\n");
            scanf("%d",&rispuser);
            if(rispuser==1)
            {
                visualizzadb();									//chiama funzione per visualizzare il database
            }
            else if(rispuser==2)
            {
                cerca(str);										//chiama funzione per effettuare una ricerca nel database
            }
            else
            {
                return 0;
            }
        }
        printf("\n \nVuole effettuare altre operazioni? \n 1 si; \n 0 no.\n");
        scanf("%d",&rr);
    }while(rr!=0);
    printf("\n ...Chiusura del programma... \n \n Francesco Avantaggiato Matr:942790 \n");
    return 0;
}
int login()
{
    FILE *lp;
    char str[256],user[128],pass[128],a[3]="a\n";
    char *token;
    int cmpusr,cmppwd,cmpup;
    lp=fopen(fname, "rw");
    if(lp==NULL)
    {
        printf("il file non e' stato trovato \n");
    }
    printf("Inserisca username: \n"); 							//effettuo il login e controllo l'accesso
    scanf("%s",user);
    printf("Inserisca password: \n");
    scanf("%s",pass);
    while(fgets(str,256,lp)!=NULL)
    {
        token=strtok(str,delim);								/*utilizzando la funzione strtok dell'header file string.h,la stringa viene suddivisa in una serie
                                                                  di token attraverso un delimitatore chiamato "delim"(in questo caso il delimitatore è il tab).*/
        cmpusr=strcmp(user,token);								//la funzione strcmp confronta le due stringhe inserite per valutarne l'uguaglianza o meno
        if(cmpusr==0)
        {
            token=strtok(NULL,delim);
            cmppwd=strcmp(pass,token);
            if(cmppwd==0)
            {
                token=strtok(NULL,delim);
                if(token[0]=='a')
                {
                    fclose(lp);
					return 0;
				}
                else
                {
                	fclose(lp);
                    return 1;
                }
            }
            else
            {
                printf("password sbagliata \n");
                fclose(lp);
                return 3;
            }
        }
	}
    printf ("Username o password errati \n");
    fclose(lp);
    return 2;
}
void pwdgenerator (char s[])										
{
    char c;
    int n,i,x;
    printf("\t\t\t ***PASSWORD GENERATOR*** \n ");
    do{
        srand(time(NULL));								/*la funzione srand inizializzala funzione per la generazione dei numeri casuali
        												e la funzione time restituisce il tempo attuale in secondi dall'epoca (01/01/1970)*/
        printf("\n Inserisca 1: Genera password \n inserisca 0: Uscita dal programma\n");
        scanf("%d",&x);
        if(x==1)
        {

            do{
                printf("\nQuanto deve essere lunga la password? (Minimo 8 caratteri):\n");
                scanf("%d",&n);
            }while(n<8);
            i=0;
            printf("la password generata e':\n");
            while (i<n)
            {
                c=33+rand() % 93;				/*per una password alfanumerica con caratteri speciali prendiamo in considerazione
                								i caratteri ASCII tra il 33 ed il 126*/
                printf("%c",c);
                s[i]=c;
                i++;
            }
            s[i]='\0';
            printf("\n(invio per andare avanti)\n ");
            do
            {
                getchar();					/*la funzione getchar legge un singolo carattere in input, in questo caso l'invio per chiudere
                                              il password generator*/
            }while(!getchar());
            return;
        }
    }while(x!=0);
}
void nuovecredenziali(char nuovoutente[])
{
    int fine,r;
    char user[128],a[3],pass[128];
    FILE *cfp;
    cfp=fopen(fname,"a+");
    if(cfp==NULL)
    {
        printf("il file non e' stato trovato \n");
        return;
    }
    do
    {
        printf("\t***CREAZIONE DATI PER L'ACCESSO***\t \n");
        printf("Inserisci username utente: \n");
        scanf("%s",user);
        printf("Vuole generare la password? 1: apre il Password Generator, 0:inserimento manuale \n");
        scanf("%d",&r);
        if(r==1)
        {
            pwdgenerator(pass);
        }
        else
        {
            printf("Inserisca password manualmente: \n");
            scanf("%s",pass);
        }
        printf("Inserisca:\n'a' se il nuovo utente e' un admin;\n'u' se il nuovo utente e' un utente semplice.\n");
        scanf("%s",a);
        fprintf(cfp,"%s\t%s\t%s\n",user,pass,a);
        sprintf(nuovoutente,"%s\t%s\t%s\n",user,pass,a);
        printf("Ha concluso? '0' per si; '1' per no.\n");
        scanf("%d",&fine);
    }while(fine!=0);
    fclose(cfp);
}
void crea()
{
    int r;
    char nome[128],cognome[128],data[128],paese[128],tel[128];
    FILE *fp;
    fp=fopen(name,"a+");
    if(fp==NULL)
    {
        printf("file non trovato\n");
        return;
    }
    printf("\t ***INSERIMENTO NUOVI DATI ANAGRAFICI***\t\n");
    do
    {
        printf("Inserisca il nome: \n");
        scanf("%s",nome);
        printf("Inserisca il cognome: \n");
        scanf("%s",cognome);
        printf("Inserisca la data di nascita (in formato gg/mm/aaaa):\n");
        scanf("%s",data);
        printf("Inserisca il paese di residenza:\n ");
        scanf("%s",paese);
        printf("Inserisca il numero di telefono:\n");
        scanf("%s",tel);
        fprintf(fp,"%s\t%s\t%s\t%s\t%s\n",nome,cognome,data,paese,tel);
        printf("Vuole inserire altri dati anagrafici?\n'1':si\n'0':no\n");
        scanf("%d",&r);
    }while(r!=0);
    fclose(fp);
}
void modifica()
{
	int risp;
    printf("\t\t\t***MODIFICA DATI ANAGRAFICI***\n");
    printf("Inserisca la scelta: \n 1: aggiornare dati anagrafici\n2:eliminare dati anagrafici\n ");
    scanf("%d",&risp);
    if(risp==2)
    {
        elimina();
        return;
    }
    else
    {
    	char stringa[256],str[256],temp[256],*token,*m[5]; //m[5] è un vettore di puntatori (stringhe)
    	int r,cmp,i;
    	FILE *fp,*fv;
    	fp=fopen(name,"r");
    	fv=fopen(nomefile,"w+");
    	if(fp==NULL)
    	{
        	printf("Il file non e' stato trovato \n");
        	return;
    	}
    	if(fv==NULL)
    	{
        	printf("Il file non e' stato trovato \n");
        	return;
    	}
		printf("Quale dato vuole modificare?\n 1:nome\n2:cognome\n3:data di nascita\n4:paese di residenza\n5:numero di telefono\n");
        scanf("%d",&r);
        cercamodifica(str);
        printf("Inserisca il nuovo valore: \n");
        scanf("%s",temp);
        while(fgets(stringa,256,fp)!=NULL)
        {
            cmp=strcmp(stringa,str);
            if(cmp!=0)
            {
                fprintf(fv,"%s",stringa);
            }
        }
        token=strtok(str,delim);
        m[0]=token;
        for(i=1;i<5;i++)
        {
            token=strtok(NULL,delim);
            m[i]=token;
        }
        m[r-1]=temp;
        fprintf(fv,"%s\t%s\t%s\t%s\t%s\n",m[0],m[1],m[2],m[3],m[4]);
        fclose(fp);
        fclose(fv);
        if(remove(name))
        {
            printf("Impossibile rimuovere il file 'database.txt'\n");

        }

        if(rename(nomefile,name))
        {
            printf("Impossibile rinominare il file \n");
        }
    }
}
void visualizzadb()
{
    char str[256];
    FILE *fp;
    fp=fopen(name,"r");
    if(fp==NULL)
    {
        printf("il file non e' stato trovato \n");
        return;
    }
    while (fgets(str,256,fp)!=NULL)
    {
        printf("%s",str);
    }
    fclose(fp);
}
void cerca()
{
    char str[256],nome[128],cognome[128];
    FILE *fp;
    fp=fopen(name,"r");
    if(fp==NULL)
    {
        printf("il file non e' stato trovato \n");
        return;
    }
    printf("\t***RICERCA DATI***\t\n");
    printf("Inserisca la chiave di ricerca (nome/cognome/data di nascita/paese di residenza/numero telefonico): \n");
    scanf("%s",nome);
    while(fgets(str,256,fp)!=NULL)
    {
        if(strstr(str,nome)!=NULL)
        {
            printf("\n %s \n",str);
        }
    }
    fclose(fp);
}
void cercamodifica(char st[])
{
    char nome[128];
    FILE *fp;
    fp=fopen(name,"r");
    if(fp==NULL)
    {
        printf("il file non e' stato trovato \n");
        return;
    }
    printf("\t***RICERCA DATI***\t\n");
    printf("Inserisca la chiave di ricerca (nome/cognome/data di nascita/paese di residenza/numero telefonico): \n");
    scanf("%s",nome);
    while(fgets(st,256,fp)!=NULL)
    {
        if(strstr(st,nome)!=NULL)
        {
            printf("\n %s \n",st);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
}
void visualizzapwd()
{
    char str[256];
    FILE *fp;
    fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("il file non e' stato trovato\n");
        return;
    }
    printf("\t***RIEPILOGO CREDENZIALI UTENTI***\t\n");
    while (fgets(str,256,fp)!=NULL)
    {
        printf("%s",str);
    }
    fclose(fp);
}
void elimina()
{
	char stringa[256],str[256]; 
    int cmp,risp;
    FILE *fp,*fv;
    fp=fopen(name,"r");
    fv=fopen(nomefile,"w+");
    if(fp==NULL)
    {
        printf("Il file non e' stato trovato \n");
        return;
    }
    if(fv==NULL)
    {
        printf("Il file non e' stato trovato \n");
        return;
    }
   		printf("\t\t\t***ELIMINA DATI ANAGRAFICI***\n");
        cercamodifica(str);
        printf("Conferma di eliminare i dati?\n1: si\n2:no\n");
        scanf("%d",&risp);
        if(risp==2)
        {
        	return;
		}
        while(fgets(stringa,256,fp)!=NULL)
        {
            cmp=strcmp(stringa,str);
            if(cmp!=0)
            {
                fprintf(fv,"%s",stringa);
            }
        }
        fclose(fp);
        fclose(fv);
        if(remove(name))
        {
            printf("Impossibile rimuovere il file 'database.txt'\n");

        }

        if(rename(nomefile,name))
        {
            printf("Impossibile rinominare il file \n");
        }
}
void modificautente()
{
	int risp;
    printf("\t\t\t***MODIFICA DATI ACCESSO***\n");
    printf("Inserisca la scelta: \n1: aggiornare dati accesso\n2:eliminare dati accesso\n ");
    scanf("%d",&risp);
    if(risp==2)
    {
        eliminautente();
        return;
    }
    else
    {
    	char stringa[256],str[256],temp[256],*token,*m[3]; 
    	int r,cmp,i;
    	FILE *fp,*fv;
    	fp=fopen(fname,"r");
    	fv=fopen(nfile,"w+");
    	if(fp==NULL)
    	{
        	printf("Il file non e' stato trovato \n");
        	return;
    	}
    	if(fv==NULL)
    	{
        	printf("Il file non e' stato trovato \n");
        	return;
    	}
		printf("Quale dato vuole modificare?\n 1:username\n2:password\n");
        scanf("%d",&r);
        cercamodificacredenziali(str);
        printf("Inserisca il nuovo valore: \n");
        scanf("%s",temp);
        while(fgets(stringa,256,fp)!=NULL)
        {
            cmp=strcmp(stringa,str);
            if(cmp!=0)
            {
                fprintf(fv,"%s",stringa);
            }
        }
        token=strtok(str,delim);
        m[0]=token;
        for(i=1;i<3;i++)
        {
            token=strtok(NULL,delim);
            m[i]=token;
        }
        m[r-1]=temp;
        fprintf(fv,"%s\t%s\t%s\n",m[0],m[1],m[2]);
        fclose(fp);
        fclose(fv);
        if(remove(fname))
        {
            printf("Impossibile rimuovere il file 'password.txt'\n");

        }
		if(rename(nfile,fname))
        {
            printf("Impossibile rinominare il file \n");
        }
    }
}
void cercamodificacredenziali(char st[])
{
    char nome[128];
    FILE *fp;
    fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("il file non e' stato trovato \n");
        return;
    }
    printf("\t***RICERCA DATI***\t\n");
    printf("Inserisca la chiave di ricerca (username/password): \n");
    scanf("%s",nome);
    while(fgets(st,256,fp)!=NULL)
    {
        if(strstr(st,nome)!=NULL)
        {
            printf("\n %s \n",st);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
}
void eliminautente()
{
	char stringa[256],str[256];
    int cmp,risp;
    FILE *fp,*fv;
    fp=fopen(fname,"r");
    fv=fopen(nfile,"w+");
    if(fp==NULL)
    {
        printf("Il file non e' stato trovato \n");
        return;
    }
    if(fv==NULL)
    {
        printf("Il file non e' stato trovato \n");
        return;
    }
   		printf("\t\t\t***ELIMINA DATI ACCESSO***\n");
        cercamodificacredenziali(str);
        printf("Conferma di eliminare i dati?\n1: si\n2:no\n");
        scanf("%d",&risp);
        if(risp==2)
        {
        	return;
		}
        while(fgets(stringa,256,fp)!=NULL)
        {
            cmp=strcmp(stringa,str);
            if(cmp!=0)
            {
                fprintf(fv,"%s",stringa);
            }
        }
        fclose(fp);
        fclose(fv);
        if(remove(fname))
        {
            printf("Impossibile rimuovere il file 'password.txt'\n");
		}
		if(rename(nfile,fname))
        {
            printf("Impossibile rinominare il file \n");
        }
}
