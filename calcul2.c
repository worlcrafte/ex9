#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
//!! le prog réalisé essaie de faire un peut tout à la fois il aurait fallu le partitionner en un peut plus de fct ex créer un fct push et pop.
char lettre[] ="0123456789ABCDEF";
char lettreMin[]="0123456789abcdef";

int teste (int base,char lettreAComparer){
    /* 
    //ne sert plus car on se place directement au niv du premier caractère diff d'un espace
    */
    if ((int)lettreAComparer == 0){ //je vérifie si je suis arrivé à la fin de la chaine.
        return 0 ;
    }
    for (int i=0; i<base;i++){
        if((lettre[i]==lettreAComparer) || (lettreMin[i] == lettreAComparer)){
            return 0;
        }
    }
    return 1;
}

int premierCaractere (char * mot){
    int i=0;
    while (mot[i]==' ')
    {
        i++;
    }
    return i; 
}

int verifBase (void){
    int base2;
    char *base=getenv("BASE");
    if (base == NULL){//regarde si la variable d'environnement base est définie. Si elle ne l'est pas on définie notre base par défaut à 10 sinon on l'identifie dans le else.
        return base2=10;
    }else{
        char * end;
        base2 = strtol(base,&end,10);
        if(base2>=2 && base2<=16){
            return base2;        
            //strtol convertie automatiquement le nb en base 10 à partir de la base fornie.
        }else{
            exit(250);
        }
    }
}

void depile(int* indexe, char signe, long* pile){
    if(*indexe<1){
        // printf("253\n");
        exit(253);
    }
    switch (signe)
    {
    case '-':
        pile[*indexe-1]=pile[*indexe-1]-pile[*indexe];
        pile[*indexe]='\0';
        *indexe-=1;
        break;
    case '+':
        pile[*indexe-1]=pile[*indexe-1]+pile[*indexe];
        pile[*indexe]='\0';
        *indexe-=1;
        break;
        
    case '*':
        pile[*indexe-1]=pile[*indexe-1]*pile[*indexe];
        pile[*indexe]='\0';
        *indexe-=1;
        break;
    case '/':
        if(pile[*indexe]==0){
            // printf("252\n");
            exit(252);
        }else{
            pile[*indexe-1]=pile[*indexe-1]/pile[*indexe];
            pile[*indexe]='\0';
            *indexe-=1;
            break;
        }
    default:
        // printf("251\n");
        exit(251);
        break;
    }
}

void empile(char* laChaine){
    int base = verifBase();
    long *pile = calloc(128,sizeof(long));
    //le strtol donne un long.
    int indexe =0;
    char *end;
    int carDifEsp =0;
    while (1){
        if(indexe==128){
            // printf("128\n");
            exit(254);
        }
        pile[indexe]=strtol(laChaine,&end,base);
        // printf("%li",pile[indexe]);
        if(laChaine==end){
            break;
        }
        carDifEsp=premierCaractere(end);//fonction qui permet de se placer au premier caractère diff d'un espace.
        while(teste(base,end[carDifEsp])){ 
            depile(&indexe,end[carDifEsp],pile);
            end[carDifEsp]=' ';
            carDifEsp=premierCaractere(end);
        }
        indexe++;
        laChaine=end;
    }
    // printf("%i<-\n",indexe);
    indexe--;
    if(indexe!=0){
        // printf("%li",pile[indexe]);
        // printf("255\n");
        exit(255);
    }else{
        printf("%li\n",pile[indexe]);
        // exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[])
{
    empile(argv[argc-1]);//!Il faut vérifier qu'on a une valeur dans argv !!!
    return EXIT_SUCCESS;
}
