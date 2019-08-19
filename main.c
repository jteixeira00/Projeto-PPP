#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


void clrscr(){
    system("@cls||clear");
}

void presscontinue(){
    printf("\nPrima Enter para continuar");
    _getch();

}
                                    /*STRUCTS*/
typedef struct pdi{
    char *nome;
    char *descript;
    char *horario;
    int id;
    int popp;
    int hotpoints;
    int local;
    struct pdi *prox;
}t_pdi;

typedef struct local{
    int id;
    char *nome;
    int popl;
    struct local *prox;

}t_local;

typedef struct pessoa{
    char *nome;
    char *morada;
    char *datanasc;
    int n_telem;
    int hotspot;
    t_pdi *pdis;
    t_local *local;
    struct pessoa *prox;
}t_person;






                                    /*CRIAR CABEÇALHOS*/


t_person *cria_cabecalhoP(void){
    t_person *lista = (t_person*)malloc(sizeof(t_person));
    if (lista != NULL){
        lista->nome = NULL;
        lista->morada = NULL;
        lista->datanasc = NULL;
        lista->n_telem = NULL;
        lista->pdis = NULL;
        lista->prox = NULL;

    }
    return lista;
}

t_pdi *cria_cabecalhoPDI(void){
    t_pdi *lista = (t_pdi*)malloc(sizeof(t_pdi));
    if (lista != NULL){
        lista->nome = NULL;
        lista->descript = NULL;
        lista->horario = NULL;
        lista->id = NULL;
        lista->popp = NULL;
        lista->hotpoints = NULL;
        lista->prox = NULL;
    }
    return lista;
}

t_local *cria_cabecalhoL(void){
    t_local *lista = (t_local*)malloc(sizeof(t_local));
    if (lista != NULL){
        lista->id = NULL;
        lista->nome = NULL;
        lista->popl = NULL;
        lista->prox = NULL;
    }
    return lista;
}


                                    /*CALCULAR TAMANHO DAS LISTAS*/
int tamanholistal(t_local *cabeca_l){
    t_local *temp1 = cabeca_l;
    int i;
    i = -1;
    while (temp1!=NULL){
        i++;
        temp1=temp1->prox;
    }
    return i;
}

int tamanholistap(t_person *cabeca_p){
    t_person *temp1 = cabeca_p;
    int i;
    i = -1;
    while (temp1!=NULL){
        i++;
        temp1=temp1->prox;
    }
    return i;
}

int tamanholistapdi(t_pdi *cabeca_pdi){
    t_pdi *temp1 = cabeca_pdi;
    int i;
    i = -1;
    while (temp1!=NULL){
        i++;
        temp1=temp1->prox;
    }
    return i;
}


                                    /*IMPRIMIR NODE*/


void printnodelocal(t_local *node_l){
    puts(node_l->nome);

}

void printnodepessoa(t_person *node_p){
    puts(node_p->nome);
    puts(node_p->morada);
    puts(node_p->datanasc);
    printf("%d\n", node_p->n_telem);
}

void printnodepdi(t_pdi *node_pdi){
    printf("%d\n", node_pdi->id);
    puts(node_pdi->nome);
    puts(node_pdi->descript);
    puts(node_pdi->horario);
}



                                    /*CRIAR LISTAS A PARTIR DE FICHEIROS*/


t_pdi *inserepdialfa(t_pdi *cabeca_pdia, char *nome, char *descript,char *horario, int id, int popp, int hotpoints, int local){

    t_pdi *novo1;
    t_pdi *node = cabeca_pdia;
    novo1 = cria_cabecalhoPDI();
    if (novo1==NULL)
        return NULL;
    while((node->prox!=NULL) && (strcmp(node->prox->nome, nome)<0)){
        node = node->prox;
    }
    novo1->nome = strdup(nome);
    novo1->horario = strdup(horario);
    novo1->descript = strdup(descript);
    novo1->id = id;
    novo1->popp = popp;
    novo1->hotpoints = hotpoints;
    novo1->local = local;
    novo1->prox = node->prox;
    node->prox = novo1;
}
t_pdi *inserepdipop(t_pdi *cabeca_pdi, char *nome, char *descript,char *horario, int id, int popp, int hotpoints, int  local){

    t_pdi *novo1;
    t_pdi *node = cabeca_pdi;
    novo1 = cria_cabecalhoPDI();
    if (novo1==NULL)
        return NULL;
    while((node->prox!=NULL) && ( node->prox->popp > popp)){
        node = node->prox;
    }
    novo1->nome = strdup(nome);
    novo1->horario = strdup(horario);
    novo1->descript = strdup(descript);
    novo1->id = id;
    novo1->popp = popp;
    novo1->hotpoints = hotpoints;
    novo1->local = local;
    novo1->prox = node->prox;
    node->prox = novo1;
}



void crialistapdis(t_pdi *cabeca_pdia, t_pdi *cabeca_pdip){
    FILE *fp;
    char *linha = malloc(300*sizeof(char));
    char *nome = malloc(100*sizeof(char));
    char *descript = malloc(100*sizeof(char));
    char *horario = malloc(100*sizeof(char));
    int id;
    int pop, hot;
    int local;
    fp = fopen("pdi.txt", "r");
    fgets(linha, 150, fp);

    while(strcmp(linha, "end")!=0){
        id = atoi(strtok(linha, "/"));
        nome = strtok(NULL, "/");
        descript = strtok(NULL, "/");
        horario = strtok(NULL, "/");
        pop = atoi(strtok(NULL, "/"));
        hot = atoi(strtok(NULL, "/"));
        local = atoi(strtok(NULL,"/"));

        inserepdialfa(cabeca_pdia, nome, descript, horario, id, pop, hot, local);
        inserepdipop(cabeca_pdip, nome, descript, horario, id, pop, hot, local);
        fgets(linha, 150, fp);

    }

    fclose(fp);
    }

                        /* INSERE NAS LISTAS*/

t_person *inserePessoaalfa(t_person *cabeca_p, char *nome, char *morada, char *datanasc, int numtel, int hotspot, t_local *listalocal, t_pdi *listapdi){
    t_person *novo;
    t_person *node = cabeca_p;
    t_local *nodel = listalocal;
    nodel = nodel->prox;
    novo = cria_cabecalhoP();
    if (novo== NULL)
        return NULL;

    while((node->prox!=NULL)){
        node = node->prox;
    }
    novo->nome = strdup(nome);
    novo->morada = strdup(morada);
    novo->datanasc = strdup(datanasc);
    novo->n_telem = numtel;
    novo->hotspot = hotspot;
    novo->pdis = listapdi;
    novo->local = nodel;
    novo->prox = node->prox;
    node->prox = novo;
}

t_person *inserePessoaalfa_semlistas(t_person *cabeca_p, char *nome, char *morada, char *datanasc, int numtel){
    t_person *novo;
    t_person *node = cabeca_p;

    t_pdi *temppdi = cria_cabecalhoPDI();
    t_local *templocal = cria_cabecalhoPDI();
    temppdi->id = 0;
    templocal->id = 1000;

    novo = cria_cabecalhoP();
    if (novo== NULL)
        return NULL;
    while((node->prox!=NULL)){
        node = node->prox;
    }
    novo->nome = strdup(nome);
    novo->morada = strdup(morada);
    novo->datanasc = strdup(datanasc);
    novo->n_telem = numtel;


    novo->local = templocal;
    novo->pdis = temppdi;
    novo->prox = node->prox;
    node->prox = novo;

    return novo;


}

void crialistapessoas(t_person *cabeca_p, t_pdi *cabeca_pdi, t_local *cabeca_l){
    FILE *fp;
    t_pdi *novalistapdi;
    t_pdi *nodepdi;
    t_pdi *novopdi;
    t_local *novol;
    t_local *novalistalocais;
    t_local *nodelocal;
    t_local *tempnodel;
    t_pdi *tempnodepdi;
    char *nome = malloc(200*sizeof(char));
    char *linha = malloc(200*sizeof(char));
    char *morada = malloc(200*sizeof(char));
    char *datanasc = malloc(200*sizeof(char));
    int numtelem;
    int tempid,i, n, hotspot;
    fp = fopen("nomes.txt", "r");
    fgets(linha, 150, fp);
    while(strcmp(linha, "end")!=0){
        nome = strtok(linha, "/");
        morada = strtok(NULL, "/");
        datanasc = strtok(NULL, "/");
        numtelem = atoi(strtok(NULL, "/"));
        hotspot = atoi(strtok(NULL, "/"));
        novalistapdi = cria_cabecalhoPDI();
        novalistalocais = cria_cabecalhoL();
        nodepdi = novalistapdi;
        nodelocal = novalistalocais;
        n = atoi(strtok(NULL,"/"));
        if(n==0){
            novalistalocais = cria_cabecalhoL();
            novalistapdi = cria_cabecalhoPDI();
        }
        for(i=0;i<n;i++){
            tempid = atoi(strtok(NULL,"/"));
            if(tempid>1000){
                tempnodel = cabeca_l;
                while(tempnodel!=NULL && tempnodel->id != tempid){
                    tempnodel = tempnodel->prox;
                }
                novol = cria_cabecalhoL();
                novol->id=tempid;
                novol->nome = strdup(tempnodel->nome);
                novol->popl = tempnodel->popl;
                novol->prox = nodelocal->prox;
                nodelocal->prox = novol;
                nodelocal = nodelocal->prox;
            }
            else{
                tempnodepdi = cabeca_pdi;

                while(tempnodepdi!=NULL && tempnodepdi->id != tempid){
                    tempnodepdi = tempnodepdi->prox;
                }
                novopdi = cria_cabecalhoPDI();
                novopdi->id = tempid;
                novopdi->nome = strdup(tempnodepdi->nome);
                novopdi->descript = strdup(tempnodepdi->descript);
                novopdi->horario = strdup(tempnodepdi->horario);
                novopdi->hotpoints = tempnodepdi->hotpoints;
                novopdi->popp = tempnodepdi->popp;
                novopdi->local = tempnodepdi->local;
                novopdi->prox = nodepdi->prox;
                nodepdi->prox = novopdi;
                nodepdi = nodepdi->prox;
            }
        }
        nodelocal = novalistalocais;

        inserePessoaalfa(cabeca_p, nome, morada, datanasc, numtelem,hotspot, novalistalocais, novalistapdi);
        fgets(linha, 150, fp);
    }

   fclose(fp);
}

t_local *inserelocalalfa(t_local *cabeca_la, char *nome, int id, int popl){
    t_local *novo;
    t_local *node = cabeca_la;
    novo = cria_cabecalhoL();
    if(novo==NULL)
        return NULL;
    while((node->prox!=NULL)&&(strcmp(node->prox->nome, nome)<0)){
        node = node->prox;
    }
    novo->nome=strdup(nome);
    novo->id = id;
    novo->popl = popl;
    novo->prox = node->prox;
    node->prox = novo;
}

t_local *inserelocalpop(t_local *cabeca_la, char *nome, int id, int popl){
    t_local *novo;
    t_local *node = cabeca_la;
    novo = cria_cabecalhoL();
    if(novo==NULL)
        return NULL;
    while((node->prox!=NULL)&&(node->prox->popl > popl)){
        node = node->prox;
    }
    novo->nome=strdup(nome);
    novo->id = id;
    novo->popl = popl;
    novo->prox = node->prox;
    node->prox = novo;
}

void crialistalocais(t_local *cabeca_la, t_local *cabeca_lp){
    FILE *fp;
    int pop, id;
    char *linha = malloc(150*sizeof(char));
    char *name = malloc(150*sizeof(char));
    fp = fopen("locais.txt","r");
    fgets(linha, 150, fp);
    while (strcmp(linha, "end")!=0){
        id = atoi(strtok(linha, "/"));
        name =strtok(NULL, "/");
        pop = atoi(strtok(NULL, "/"));
        inserelocalalfa(cabeca_la, name, id, pop);
        inserelocalpop(cabeca_lp, name, id, pop);
        fgets(linha, 150, fp);
    }
    while(cabeca_la->nome==NULL){
        cabeca_la = cabeca_la->prox;
    }
    while(cabeca_lp->nome==NULL){
        cabeca_lp = cabeca_lp->prox;
    }
    fclose(fp);

}


t_person *procurausernalista(t_person *cabeca_p, int numtele){
    t_person *node = cabeca_p;
    while(node!=NULL && node->n_telem!=numtele){
        node = node->prox;
    }
    return node;
}

int printfavs(t_local *cabeca_l, t_pdi *cabeca_pdi, t_person *user){


    t_local *node_local;
    t_pdi *node_pdi;
    node_local = cabeca_l;

    if((contalocaisuser(user)==0)&&(contapdisuser(user)!=0)){
        while(cabeca_pdi->nome==NULL){
            cabeca_pdi = cabeca_pdi->prox;
        }
        node_pdi = cabeca_pdi;
        while(node_pdi!=NULL){
                if (node_pdi->local == node_local->id){
                    printf("\t%s, id: %d\n",node_pdi->nome, node_pdi->id);

                }
                node_pdi = node_pdi->prox;
            }

    }

    else if((contalocaisuser(user)!=0)&&(contapdisuser(user)==0)){
        while(node_local->nome==NULL){
            node_local = node_local->prox;
        }

        while(node_local!=NULL){
            printf("%s (id:%d):\n", node_local->nome, node_local->id);
            node_local = node_local->prox;

        }

    }

    else{
        while(cabeca_pdi->nome==NULL){
            cabeca_pdi = cabeca_pdi->prox;
        }
        while(node_local->nome==NULL){
            node_local = node_local->prox;
        }
        while(node_local!=NULL){
            node_pdi = cabeca_pdi;
            printf("%s (id:%d):\n", node_local->nome, node_local->id);
            while(node_pdi!=NULL){
                if (node_pdi->local == node_local->id){
                    printf("\t%s, id: %d\n",node_pdi->nome, node_pdi->id);

                }
                node_pdi = node_pdi->prox;
            }
            node_local = node_local->prox;
        }

    }




}


int printtodos(t_local *cabeca_l, t_pdi *cabeca_pdi){


    t_local *node_local;
    t_pdi *node_pdi;
    node_local = cabeca_l;


        while(cabeca_pdi->nome==NULL){
            cabeca_pdi = cabeca_pdi->prox;
        }
        while(node_local->nome==NULL){
            node_local = node_local->prox;
        }
        while(node_local!=NULL){
            node_pdi = cabeca_pdi;
            printf("%s (id:%d):\n", node_local->nome, node_local->id);
            while(node_pdi!=NULL){
                if (node_pdi->local == node_local->id){
                    printf("\t%s, id: %d\n",node_pdi->nome, node_pdi->id);

                }
                node_pdi = node_pdi->prox;
            }
            node_local = node_local->prox;
        }

}

void screen_printfavs(t_person *user, t_person *cabeca_p, t_local *cabeca_lpop, t_local *cabeca_lalfa, t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfa){
    int option;
    printf("Deseja: \n(1) Apresentar por ordem alfabética\n\n(2) Apresentar por ordem de popularidade\n");
    scanf("%d", &option);
    switch(option){
    case 1:
        clrscr();
        printfavs(cabeca_lalfa, cabeca_pdialfa, user);
        presscontinue();
        menuposlogin(user, cabeca_p, cabeca_lpop, cabeca_lalfa, cabeca_pdipop,cabeca_pdialfa);
        break;

    case 2:
        clrscr();
        printfavs(cabeca_lpop, cabeca_pdipop, user);
        presscontinue();
        menuposlogin(user, cabeca_p, cabeca_lpop, cabeca_lalfa, cabeca_pdipop,cabeca_pdialfa);
        break;
    }


}
int replacechar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}

t_person *menu_inicial(t_person *cabeca_p, t_person *user){
    int i, n;

    char *nome = malloc(100*sizeof(char));
    char *morada = malloc(100*sizeof(char));
    char *datanasc = malloc(50*sizeof(char));
    t_person *node = cabeca_p;
    printf("-----------------------\n");
    printf("Insira o numero correspondente à opção que deseja:\n(1) Login \n(2) Registar-se:\n");
    fflush(stdin);
    scanf("%d", &i);
    switch(i){
    case 1:
        printf("-----------------------\n");
        printf("Insira o seu numero de telemovel: ");
        scanf("%d", &n);
        printf("\n");

        if (procurausernalista(cabeca_p, n) == NULL){
            printf("-----------------------\n");
            printf("O seu numero nao se encontra registado, por favor registe-se primeiro.\n");
            presscontinue();
            main();
        }
        user = procurausernalista(cabeca_p, n);
        presscontinue();
        printf("\n");
        return user;
        break;
    case 2:
        printf("-----------------------\n");
        printf("Insira o seu numero de telemovel: ");
        fflush(stdin);
        scanf("%d", &n);
        printf("\n");
        node = procurausernalista(cabeca_p, n);

        if(node!=NULL){
            printf("\nO seu numero ja se encontra registado.\n");
            presscontinue();
            printf("\n");
            clrscr();
            menu_inicial(cabeca_p, user);

        }
        else{
            clrscr();
            printf("Insira o seu nome: ");
            fflush(stdin);
            fgets(nome, 100, stdin);
            nome = strtok(nome, "\n");
            replacechar(nome, '/', '-');
            printf("\n");
            printf("Insira a sua morada: ");
            fflush(stdin);
            fgets(morada, 100, stdin);
            morada = strtok(morada, "\n");
            replacechar(morada, '/', '-');
            printf("\nInsira a sua data de nascimento: ");
            fflush(stdin);
            scanf("%s", datanasc);
            datanasc = strtok(datanasc, "\n");
            replacechar(datanasc, '/', '-');
            user = inserePessoaalfa_semlistas(cabeca_p, nome, morada, datanasc, n);
            presscontinue();
            printf("\n");
            return user;
        }
        break;
    default:
        printf("Por favor insira uma opção válida\n");
        presscontinue();
        printf("\n");
        menu_inicial(cabeca_p, user);
        break;

    }

}
int contalocaisuser(t_person *user){
    t_local *node;
    int i;
    i=0;
    node = user->local;
    if(node==NULL){
        return 0;
    }
    if(node->nome==NULL && node->prox==NULL){
        return 0;
    }
    while(node->nome==NULL && node!=NULL){
        node=node->prox;
    }

    while(node!=NULL){

        node=node->prox;
        i++;
    }
    return i;
}
int contapdisuser(t_person *user){
    t_pdi *node;
    int i;
    i=0;
    node = user->pdis;
    if(node==NULL){
        return 0;
    }
    if(node->nome==NULL && node->prox==NULL){
        return 0;
    }
    while(node->nome==NULL){
        node=node->prox;
    }

    while(node!=NULL){

        node=node->prox;
        i++;
    }
    return i;


}

int verificanalistal(t_person *user, int id){
    t_local *node = user->local;

    while(node!=NULL){

        if(node->id==id){
            return 1;
        }
        node = node->prox;
    }

    return 0;

}

int verificanalistapdi(t_person *user, int id){
    t_pdi *node = user->pdis;
    while(node!=NULL){

        if(node->id==id){
            return 1;
        }
        node = node->prox;
    }

    return 0;
}


void escolherfavs_alfa(t_person *user, t_person *cabeca_p,t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfa, t_local *cabeca_localpop, t_local *cabeca_localalfa){
        int id;
        char *input = malloc(20*sizeof(char));
        t_pdi *novopdi, *nodepdi, *tempnodepdi;
        t_local *novolocal, *nodelocal, *tempnodelocal,*tempnodelocal2;
        clrscr();
        printtodos(cabeca_localalfa, cabeca_pdialfa);


        printf("\nA qualquer momento pode escrever 'menu' para regressar ao menu");
        printf("\nInsira o id do local que deseja escolher como favorito: ");
        scanf("%s", input);
        if (strcmp(input, "menu")==0){
            menuposlogin(user, cabeca_p, cabeca_localpop, cabeca_localalfa, cabeca_pdipop, cabeca_pdialfa);
        }
        id = atoi(input);
        if(id>1000){

                if(verificanalistal(user, id)==1){
                    printf("Esse local já se encontra nos seus favoritos\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

                }

                else if(contalocaisuser(user)==3){
                    printf("Já possui 3 locais favoritos.\nPor favor escolha apenas PDIs, ou regresse ao menu para apagar locais favoritos.");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
                }
                else if(contalocaisuser(user)!=0){
                    tempnodelocal = cabeca_localalfa;
                    nodelocal = user->local;
                    while(nodelocal->prox!=NULL){
                        nodelocal = nodelocal->prox;
                    }

                    while(tempnodelocal!=NULL && tempnodelocal->id != id){
                        tempnodelocal = tempnodelocal->prox;
                    }
                    novolocal = cria_cabecalhoL();
                    novolocal->id = id;
                    novolocal->nome = strdup(tempnodelocal->nome);
                    tempnodelocal->popl = tempnodelocal->popl +1;
                    tempnodelocal2 = cabeca_localpop;
                    while(tempnodelocal2->id != novolocal->id){
                        tempnodelocal2 = tempnodelocal2->prox;
                    }
                    tempnodelocal2->popl = nodelocal->popl +1;
                    novolocal->popl = tempnodelocal->popl;
                    novolocal->prox = nodelocal->prox;
                    nodelocal->prox = novolocal;


                    tempnodelocal = user->local;
                    printf("Local escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

                }

                if(contalocaisuser(user)==0){

                    tempnodelocal = cabeca_localalfa;
                     while(tempnodelocal!=NULL && tempnodelocal->id != id){
                            tempnodelocal = tempnodelocal->prox;
                        }
                    novolocal = cria_cabecalhoL();
                    novolocal->id = id;
                    novolocal->nome = strdup(tempnodelocal->nome);
                    novolocal->popl = tempnodelocal->popl;
                    novolocal->prox = NULL;
                    user->local = novolocal;
                    printf("Local escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
                }
        }
        else{

            if (verificanalistapdi(user, id)==1){
                printf("O PDI escolhido já se encontra nos seus favoritos\n");
                presscontinue();
                escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);


            }

            else{
                tempnodepdi = cabeca_pdipop;
                while(tempnodepdi!=NULL && tempnodepdi->id != id){
                    tempnodepdi = tempnodepdi->prox;
                }

                novopdi = cria_cabecalhoPDI();
                novopdi->id = id;
                novopdi->nome = strdup(tempnodepdi->nome);

                novopdi->descript = strdup(tempnodepdi->descript);
                novopdi->horario = strdup(tempnodepdi->horario);
                tempnodepdi->popp = tempnodepdi->popp+1;

                nodepdi = cabeca_pdialfa;

                while(nodepdi->id != novopdi->id){
                    nodepdi = nodepdi->prox;
                }

                nodepdi->popp = nodepdi->popp +1;
                novopdi->hotpoints = tempnodepdi->hotpoints;
                novopdi->popp = tempnodepdi->popp;

                novopdi->prox = NULL;

                if (contapdisuser(user)==0){
                    user->pdis = novopdi;
                    printf("PDI escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

                }

                else{
                    nodepdi = user->pdis;
                    while(nodepdi->prox!=NULL){
                        nodepdi = nodepdi->prox;
                    }

                    nodepdi->prox = novopdi;
                    printf("PDI escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
                }
            }

        }

        escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

}



void escolherfavs_pop(t_person *user, t_person *cabeca_p, t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfa, t_local *cabeca_localpop, t_local *cabeca_localalfa){
         int id;
        char *input = malloc(20*sizeof(char));
        t_pdi *novopdi, *nodepdi, *tempnodepdi;
        t_local *novolocal, *nodelocal, *tempnodelocal, *tempnodelocal2;
        clrscr();
        printtodos(cabeca_localpop, cabeca_pdipop);


        printf("\nA qualquer momento pode escrever 'menu' para regressar ao menu");
        printf("\nInsira o id do local que deseja escolher como favorito: ");
        scanf("%s", input);
        if (strcmp(input, "menu")==0){
            menuposlogin(user, cabeca_p, cabeca_localpop, cabeca_localalfa, cabeca_pdipop, cabeca_pdialfa);
        }
        id = atoi(input);
        if(id>1000){

                if(verificanalistal(user, id)==1){
                    printf("Esse local já se encontra nos seus favoritos\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

                }
                else if(contalocaisuser(user)==3){
                    printf("Já possui 3 locais favoritos.\nPor favor escolha apenas PDIs, ou regresse ao menu para apagar locais favoritos.");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
                }
                else if(contalocaisuser(user)!=0){
                    tempnodelocal = cabeca_localalfa;
                    nodelocal = user->local;
                    while(nodelocal->prox!=NULL){
                        nodelocal = nodelocal->prox;
                    }

                    while(tempnodelocal!=NULL && tempnodelocal->id != id){
                        tempnodelocal = tempnodelocal->prox;
                    }
                    novolocal = cria_cabecalhoL();
                    novolocal->id = id;
                    novolocal->nome = strdup(tempnodelocal->nome);
                    tempnodelocal->popl = tempnodelocal->popl +1;
                    tempnodelocal2 = cabeca_localalfa;
                    while(tempnodelocal2->id != novolocal->id){
                        tempnodelocal2 = tempnodelocal2->prox;
                    }
                    tempnodelocal2->popl = nodelocal->popl +1;
                    novolocal->popl = tempnodelocal2->popl;
                    novolocal->prox = nodelocal->prox;
                    nodelocal->prox = novolocal;


                    tempnodelocal = user->local;
                    printf("Local escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

                }

                if(contalocaisuser(user)==0){
                    printf("vim aqui");
                    tempnodelocal = cabeca_localalfa;
                     while(tempnodelocal!=NULL && tempnodelocal->id != id){
                            tempnodelocal = tempnodelocal->prox;
                        }
                    novolocal = cria_cabecalhoL();
                    novolocal->id = id;
                    novolocal->nome = strdup(tempnodelocal->nome);
                    novolocal->popl = tempnodelocal->popl;
                    novolocal->prox = NULL;
                    user->local = novolocal;
                    printf("Local escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
                }
        }
        else{
             if (verificanalistapdi(user, id)==1){
                printf("O PDI escolhido já se encontra nos seus favoritos\n");
                presscontinue();
                escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);


            }

            else{
                tempnodepdi = cabeca_pdipop;
                while(tempnodepdi!=NULL && tempnodepdi->id != id){
                    tempnodepdi = tempnodepdi->prox;
                }

                novopdi = cria_cabecalhoPDI();
                novopdi->id = id;
                novopdi->nome = strdup(tempnodepdi->nome);
                novopdi->descript = strdup(tempnodepdi->descript);
                novopdi->horario = strdup(tempnodepdi->horario);
                tempnodepdi->popp = tempnodepdi->popp+1;
                nodepdi = cabeca_pdialfa;
                while(nodepdi->id != novopdi->id){
                    nodepdi = nodepdi->prox;
                }
                nodepdi->popp = nodepdi->popp +1;
                novopdi->hotpoints = tempnodepdi->hotpoints;
                novopdi->popp = tempnodepdi->popp;

                novopdi->prox = NULL;
                if (contapdisuser(user)==0){
                    user->pdis = novopdi;
                    printf("PDI escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

                }

                else{
                    nodepdi = user->pdis;
                    while(nodepdi->prox!=NULL){
                        nodepdi = nodepdi->prox;
                    }

                    nodepdi->prox = novopdi;
                    printf("PDI escolhido com êxito.\n");
                    presscontinue();
                    escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
                }
            }

        }

        escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
}

void menu_escolherfavs(t_person *user, t_person *cabeca_p, t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfa, t_local *cabeca_localpop, t_local *cabeca_localalfa){
    int choice;
    printf("\t\t Escolha de Locais e PDIs");
    printf("Deseja: \n(1) Apresentar por ordem alfabética\n\n(2) Apresentar por ordem de popularidade\n");

    scanf("%d", &choice);
    switch(choice){
    case 1:
        escolherfavs_alfa(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
        break;
    case 2:
        escolherfavs_pop(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

        break;
    default:
        printf("Por favor insira uma opção válida.");
        presscontinue();
        clrscr();
        menu_escolherfavs(user,cabeca_p, cabeca_pdipop, cabeca_pdialfa, cabeca_localpop, cabeca_localalfa);
        break;
    }

}
void escolherhotspot_alfa(t_person *user, t_person *cabeca_p, t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfa, t_local *cabeca_localpop, t_local *cabeca_localalfa){
    t_pdi *temp;
    char *tempstring = malloc(30*sizeof(char));
    int id, choice;
    t_pdi *nodepdi;
    temp = cabeca_pdipop;
    while(temp->id==NULL){
        temp = temp->prox;
    }
    clrscr();
    while(temp!=NULL){
        printf("%s (id:%d)\n", temp->nome, temp->id);
        temp = temp->prox;
    }
    printf("\nA qualquer momento pode escrever 'menu' para regressar ao menu");
    printf("\nInsira o id do local que deseja escolher como hotspot: ");
    fflush(stdin);
    scanf("%s", tempstring);
    if (strcmp(tempstring, "menu")==0){
         menuposlogin(user, cabeca_p, cabeca_localpop, cabeca_localalfa, cabeca_pdipop,cabeca_pdialfa);
    }
    id = atoi(tempstring);
    if(user->hotspot==NULL || user->hotspot == 0){

        user->hotspot=id;
        printf("Hotspot atribuído.\n");
        nodepdi=cabeca_pdialfa;
        while(nodepdi->id != id){
            nodepdi =nodepdi->prox;
        }
        nodepdi->hotpoints+=1;
        nodepdi=cabeca_pdipop;
        while(nodepdi->id != id){
            nodepdi =nodepdi->prox;
        }
        nodepdi->hotpoints+=1;
        presscontinue();
        menuposlogin(user, cabeca_p, cabeca_localpop, cabeca_localalfa, cabeca_pdipop,cabeca_pdialfa);
    }
    else{
        if(id=user->hotspot){
            printf("Esse já é o seu hotspot.\n");
            presscontinue();
            menu_escolherhotspot(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);

        }
        printf("\nO seu hotspot atual é o %d, deseja substituir?\n(1) Sim\n(2) Não\n", user->hotspot);
        scanf("%d", &choice);
        if(choice==1){
            user->hotspot = id;
            nodepdi=cabeca_pdialfa;
            while(nodepdi->id != id){
                nodepdi =nodepdi->prox;
            }
            nodepdi->hotpoints+=1;
            nodepdi=cabeca_pdipop;
            while(nodepdi->id != id){
                nodepdi =nodepdi->prox;
            }
            nodepdi->hotpoints+=1;
                printf("Hotspot atualizado para %d\n", user->hotspot);
            }
        if(choice==2){
            printf("Escolheu não atualizar o seu hotspot.\n");
        }
        printf("Será levado de volta para o menu.\n");
        presscontinue();
        menuposlogin(user, cabeca_p, cabeca_localpop, cabeca_localalfa, cabeca_pdipop,cabeca_pdialfa);

    }
}
void escolherhotspot_pop(t_person *user, t_person *cabeca_p, t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfa, t_local *cabeca_localpop, t_local *cabeca_localalfa){
    t_pdi *temp;
    t_pdi *node;
    char *tempstring = malloc(30*sizeof(char));

    int id, choice;
    temp = cabeca_pdialfa;
    while(temp->id==NULL){
        temp = temp->prox;
    }
    clrscr();
    while(temp!=NULL){
        printf("%s (id:%d)\n", temp->nome, temp->id);
        temp = temp->prox;
    }
    printf("\nA qualquer momento pode escrever 'menu' para regressar ao menu");
    printf("\nInsira o id do local que deseja escolher como hotspot: ");
    scanf("%s", tempstring);
    if (strcmp(tempstring, "menu")==0){
        clrscr();
        menuposlogin(user, cabeca_p, cabeca_localpop, cabeca_localalfa, cabeca_pdipop, cabeca_pdialfa);
    }
    id = atoi(tempstring);
    if(user->hotspot==NULL || user->hotspot == 0){
        node = cabeca_pdialfa;
        while(node->id!=id){
            node= node->prox;
        }
        node->hotpoints = node->hotpoints +1;
        user->hotspot=id;
        printf("Hotspot atribuído.\n");
        presscontinue();
        clrscr();
        menuposlogin(user, cabeca_p, cabeca_localpop, cabeca_localalfa, cabeca_pdipop, cabeca_pdialfa);
    }
    else{
        printf("\nO seu hotspot atual é o %d, deseja substituir?\n(1) Sim\n(2) Não\n", user->hotspot);
        scanf("%d", &choice);
        if(choice==1){
            user->hotspot = id;
            node = cabeca_pdialfa;
            while(node->id!=id){
                node= node->prox;
            }
            node->hotpoints = node->hotpoints +1;
            printf("Hotspot atualizado para %d\n", user->hotspot);
        }
        if(choice==2){
            printf("Escolheu não atualizar o seu hotspot.\n");
        }
        printf("Será levado de volta para o menu.\n");
        presscontinue();
        clrscr();
        menuposlogin(user,cabeca_p,cabeca_localpop,cabeca_localalfa,cabeca_pdipop,cabeca_pdialfa);

    }
}

void menu_escolherhotspot(t_person *user, t_person *cabeca_p, t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfa, t_local *cabeca_localpop, t_local *cabeca_localalfa){
    escolherhotspot_pop(user,cabeca_p,cabeca_pdipop,cabeca_pdialfa,cabeca_localpop,cabeca_localalfa);
}

void menu_definicoesuser(t_person *user, t_person *cabeca_p, t_local *cabeca_lpop, t_local *cabeca_lalfabetica,t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfabetica){
    char *temps = malloc(100*sizeof(char));
    int choice, n, i, tester;
    t_person *tempnode;
    printf("\t\tAlterar informações do utilizador %s\n\n", user->nome);
    printf("(1) Nome\n(2) Morada\n(3) Data de nascimento\n(4)Número de telemóvel\n");
    printf("\nPode escrever 'menu' para regressar ao menu\n");
    printf("Insira o número da opção que pretende alterar: ");
    scanf("%s", temps);
    printf("\n");
    if(strcmp(temps, "menu")==0){
        printf("Será levado para o menu anterior.\n");
        presscontinue();
        clrscr();
        menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
    }
    choice = atoi(temps);
    switch(choice){
        case 1:
            printf("O seu nome atual é: %s\n", user->nome);
            printf("Pretende mesmo alterar o seu nome?\n(1) Sim\n(2) Não\n");
            scanf("%d", &i);
            fflush(stdin);
            if (i==1){
                printf("Insira o nome novo: \n");
                fgets (temps, 100, stdin);
                strtok(temps, "\n");
                user->nome = strdup(temps);
                clrscr();
                printf("Nome alterado com sucesso. O novo nome é: %s\n", user->nome);
                printf("Será levado para a alteração de dados do utilizador novamente.");
                presscontinue();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);

            }
            else if (i == 2){
                printf("Será levado de volta para o menu.\n");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
            else{
                printf("Inseriu uma opção inválida, será levado novamente para o menu de alteração de informações");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
        case 2:
            printf("A sua morada atual é: %s\n", user->morada);
            printf("Pretende mesmo alterar a sua morada?\n(1) Sim\n(2) Não\n");
            scanf("%d", &i);
            fflush(stdin);
            if (i==1){
                printf("Insira a morada nova: \n");
                fgets (temps, 100, stdin);
                strtok(temps, "\n");
                user->morada = strdup(temps);
                printf("Morada atualizada com êxito");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);

            }
            else if (i == 2){
                printf("Será levado de volta para o menu.\n");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
            else{

                printf("Inseriu uma opção inválida, será levado novamente para o menu de alteração de informações");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
        case 3:
            printf("A sua data de nascimento atual é: %s\n", user->datanasc);
            printf("Pretende mesmo alterar a sua data de nascimento?\n(1) Sim\n(2) Não\n");
            scanf("%d", &i);
            fflush(stdin);
            if (i==1){
                printf("Insira a data de nascimento nova: \n");
                fgets (temps, 100, stdin);
                strtok(temps, "\n");
                user->datanasc = strdup(temps);
                printf("Data de nascimento atualizada com êxito.");
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
            else if (i== 2){
                printf("Será levado de volta para o menu.\n");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
            else{

                printf("Inseriu uma opção inválida, será levado novamente para o menu de alteração de informações");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
        case 4:

            printf("O seu número de telemóvel atual é: %d", user->n_telem);
            printf("Pretende mesmo alterar o seu número de telemóvel?\n(1) Sim\n(2) Não\n");
            scanf("%d", &i);

            if (i==1){
                printf("Insira o seu número de telemóvel novo: \n");
                scanf("%d", &n);
                tempnode = cabeca_p;
                while(tempnode!=NULL){
                    if(tempnode->n_telem == n){
                        tester = 1;
                    }
                    tempnode = tempnode->prox;
                }
                if(tester==1){
                    printf("\n Inseriu um número de telemóvel que já está associado a outro utilizador\n");
                    presscontinue();
                    clrscr();
                    menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);

                }
                user->n_telem =n;
                printf("Número de telemóvel atualizado com êxito\n");
                presscontinue();
                printf("\n");
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
            else if (i== 2){
                printf("Será levado de volta para o menu.\n");
                presscontinue();
                printf("\n");
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
            else{
                printf("Inseriu uma opção inválida, será levado novamente para o menu de alteração de informações");
                presscontinue();
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            }
        default:
            printf("Por favor insira uma opção válida.\n");
            presscontinue();
            clrscr();
            menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
    }

}

void remover_pdilocal(t_person *user, t_person *cabeca_p, t_local *cabeca_lpop, t_local *cabeca_lalfabetica,t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfabetica){
    int id;
    int verifier = 0;
    char *temps = malloc(20*sizeof(char));
    t_local *templocal, *proxlocal, *printlocal;
    t_pdi *temppdi, *proxpdi, *printpdi;


    if(contalocaisuser(user)==0 && contapdisuser(user)==0){
        printf("Por favor escolha PDIs ou locais favoritos antes de tentar remover.\n");
        presscontinue();
        menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
    }
    else{
        printlocal = user->local;
        printpdi = user->pdis;

        if(contalocaisuser(user)!=0){
            printf("Locais:\n");

            while(printlocal!=NULL){
                printf("\t%s (id: %d)\n", printlocal->nome, printlocal->id);
                printlocal = printlocal->prox;
            }
            printf("\n");
        }
        if(contapdisuser(user)!=0){
            printf("PDIs:\n");
            while(printpdi->nome==NULL){
                printpdi = printpdi->prox;
            }
            while(printpdi!=NULL){
                printf("\t%s (id: %d) (id do local: %d)\n", printpdi->nome, printpdi->id, printpdi->local);
                printpdi = printpdi->prox;
            }
        }
        printf("Insira o ID do PDI ou local que pretende remover\nPode escrever 'menu' para regressar ao menu:\n");
        fflush(stdin);
        scanf("%s", temps);
        if(strcmp(temps, "menu")==0){
            clrscr();
            menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
        }

        id = atoi(temps);

        if(id>1000){

            templocal = user->local;
            proxlocal = templocal->prox;
            if(templocal->id==id){
                if(contalocaisuser(user)==1){
                    user->local=cria_cabecalhoL();

                }
                else{
                    user->local = user->local->prox;
                }
                verifier = 1;
            }
            printf("2");
            if(verifier==0){
                while(proxlocal->id==NULL){
                templocal = templocal->prox;
                proxlocal = proxlocal->prox;
            }
                while(proxlocal->id!=id){
                    templocal = templocal->prox;
                    if(proxlocal->prox==NULL){
                        break;
                    }
                    proxlocal = proxlocal->prox;

                }
                templocal->prox = proxlocal->prox;
            }
        }
        else{
            temppdi = user->pdis;
            proxpdi = temppdi->prox;
            while(proxpdi->id!=id){
                temppdi = temppdi->prox;
                if (proxpdi->prox == NULL){
                    break;
                }
                proxpdi = temppdi->prox;
            }
            temppdi->prox = proxpdi->prox;
        }
         menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);

    }

}

void remover_hotspot(t_person *user, t_person *cabeca_p, t_local *cabeca_lpop, t_local *cabeca_lalfabetica,t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfabetica){
    int choice, old_hot;
    t_pdi *nodepdi;
    printf("Deseja mesmo remover o hotspot com o id %d?", user->hotspot);
    printf("\n\t(1) Sim\n\t(2) Não\n");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            old_hot = user->hotspot;
            user->hotspot = 0;
            nodepdi = cabeca_pdialfabetica;
            while(nodepdi->id!=old_hot){
                nodepdi = nodepdi->prox;
            }
            nodepdi->hotpoints = nodepdi->hotpoints -1;
            nodepdi = cabeca_pdipop;
            while(nodepdi->id!=old_hot){
                nodepdi = nodepdi->prox;
            }
            nodepdi->hotpoints = nodepdi->hotpoints -1;
            printf("Hotspot removido com êxito.");
            presscontinue();
            menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
        case 2:
            clrscr();
            menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);

        default:
            printf("Por favor insira uma opção válida.");
            remover_hotspot(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
    }
}


t_pdi *procuralocaldopdi(t_pdi *cabeca_pdi, int id){
    t_pdi *node;
    node = cabeca_pdi;

    while(node->nome==NULL){
        node = node->prox;
    }
    if(id == 0){
        return NULL;
    }

    while(node->id != id){
        node = node->prox;
    }
    return node;
}

int procurapdinalista(int id, t_pdi *listapdi){
    t_pdi *node = listapdi;

    while(node!=NULL){
        if (node->id == id){
            return 0;
        }
         node = node->prox;

    }
    return 1;
}

int verificanalistap(t_person *listausers, t_person *user){
    t_person *tempnode = listausers;
    while(tempnode!=NULL){
        if(tempnode->n_telem==user->n_telem){
            return 1;
        }
    }

    return 0;

}
int contausers(t_person *lista){
    t_person *node;
    int count = 0;
    node = lista;

    while(node!=NULL){
        if(node->nome!=NULL){
            count++;
        }
        node = node->prox;

    }

    return count;
}

void calculaviagem(t_person *user, t_person *cabeca_p, t_local *cabeca_lpop, t_local *cabeca_lalfabetica,t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfabetica){
    t_local *local_user;
    float pop1, pop2, pop3, poptotal;
    t_person *tempuser;
    t_local *templocal;
    t_local *locaisuser;
    t_pdi *temppdi;
    t_pdi *pdiuser, *pdilista;
    int id_local;
    int counter;
    int check;
    int totalusers;
    float res;
    pop1=0;
    pop2 = 0;
    pop3 = 0;
    poptotal = 0;

    totalusers = contausers(cabeca_p);
    local_user = user->local;

    if(contalocaisuser(user)<3){
        printf("Esta opção só está disponível com 3 locais preferidos selecionados.\n");
        presscontinue();
        menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
    }
    while(local_user->nome==NULL){
        local_user = local_user->prox;
    }
    /*contar popularidade A*/
    tempuser = cabeca_p;
    while(tempuser->nome==NULL){
        tempuser = tempuser->prox;
    }
    while(tempuser!=NULL){
        check=0;
        locaisuser = tempuser->local;
        templocal = local_user;

        while((locaisuser!=NULL)&&(check!=1)){

            while((templocal!=NULL)&&(check!=1)){

                if(templocal->id == locaisuser->id){
                    pop1= pop1+1;
                    check=1;
                }
                templocal = templocal->prox;
            }
            locaisuser = locaisuser->prox;
        }
        tempuser = tempuser->prox;
    }

    local_user = user->local;
    while(local_user->nome==NULL){
        local_user = local_user->prox;
    }
    while(local_user!=NULL){


        printf("%s(id: %d)\n", local_user->nome, local_user->id);
        counter =0;
        id_local = local_user->id;
        temppdi=procuralocaldopdi(cabeca_pdipop, user->hotspot);
        if(temppdi!=NULL){
            if(temppdi->local ==id_local){
                tempuser = cabeca_p;
                while(tempuser!=NULL){

                    if(tempuser->hotspot==temppdi->id){
                        pop2=pop2+1;

                    }
                    tempuser = tempuser->prox;

                }
                pop3 = pop3 + temppdi->popp;
                printf("\t%s (id: %d)\n", temppdi->nome, temppdi->id);
                counter++;
            }
        }

        pdilista = cabeca_pdipop;
        while(pdilista->nome==NULL){
            pdilista = pdilista->prox;

        }

        pdiuser = user->pdis;
        if(contapdisuser(user)>1){
            while(pdiuser->nome==NULL){
                pdiuser = pdiuser->prox;
            }
        }
        while(pdilista!=NULL && contapdisuser(user)>0){
            pdiuser = user->pdis;
            while(pdiuser->nome==NULL){
                pdiuser = pdiuser->prox;
            }

            while(pdiuser!=NULL){
                if((pdilista->id == pdiuser->id) && (pdiuser->local == id_local)&&(counter<3)){

                    tempuser = cabeca_p;
                    while(tempuser!=NULL){
                        if(tempuser->hotspot==pdiuser->id){
                            pop2=pop2+1;


                        }
                        tempuser = tempuser->prox;

                    }
                    pop3 = pop3 + pdiuser->popp;
                    printf("\t%s (id: %d)\n", pdiuser->nome, pdiuser->id);
                    counter++;
                }
                pdiuser = pdiuser->prox;
            }
            pdilista = pdilista -> prox;
        }
        while(counter<3){

            pdiuser = user->pdis;
            while(pdiuser->nome==NULL && contapdisuser(user)>0){
                pdiuser = pdiuser->prox;
            }


                pdilista = cabeca_pdipop;
                while(pdilista->nome==NULL){
                    pdilista = pdilista->prox;
                }
                while(pdilista!=NULL){
                    if((pdilista->local==id_local)&&(procurapdinalista(pdilista->id, pdiuser))&&(pdilista->id!=user->hotspot)&&(counter<3)){
                        tempuser = cabeca_p;
                        while(tempuser!=NULL){
                            if(tempuser->hotspot==pdilista->id){
                                pop2=pop2+1;

                            }
                        tempuser = tempuser->prox;

                        }
                        pop3 = pop3 + pdilista->popp;
                        printf("\t%s (id: %d) \n", pdilista->nome, pdilista->id);
                        counter++;
                    }
                   pdilista = pdilista->prox;
                }
            }
        local_user = local_user->prox;
    }

    poptotal = 0;

    temppdi = cabeca_pdipop;
    while(temppdi->nome==NULL){
        temppdi = temppdi->prox;
    }
    while(temppdi!=NULL){
        poptotal = poptotal+temppdi->popp;
        temppdi = temppdi->prox;
    }

    templocal = cabeca_lpop;
    while(templocal->nome == NULL){
        templocal = templocal->prox;

    }
    while(templocal!=NULL){

        poptotal = poptotal + templocal->popl;
        templocal=templocal->prox;
    }
    res = ((double)pop3/(double)poptotal)*100;
    res = res + ((double)pop2/(double)totalusers)*100;
    res = res + ((double)pop1/(double)totalusers)*100;
    res = res/3;

    printf("A taxa de popularidade desta viagem é: %.1f%%\n", res);
    presscontinue();
    menuposlogin(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
}

void mostrarinfouser(t_person *user){
    clrscr();
    printf("Nome: %s\n", user->nome);
    printf("Data de Nascimento: %s\n", user->datanasc);
    printf("Número de telemóvel: %d\n", user->n_telem);
    printf("Morada: \n", user->morada);
    printf("ID do hotspot: %d\n", user->hotspot);
    printf("Número de locais favoritos: %d\n", contalocaisuser(user));
    printf("Número de pontos de interesse favoritos: %d\n", contapdisuser(user));
    presscontinue();
}



void menuposlogin(t_person *user, t_person *cabeca_p, t_local *cabeca_lpop, t_local *cabeca_lalfabetica,t_pdi *cabeca_pdipop, t_pdi *cabeca_pdialfabetica){
    char choice;
    t_local *node;
    clrscr();
    printf("Insira a letra correspondente à opção que pretende:\n");
    printf("(A) Mostrar locais e pontos de interesse\n(B) Escolher locais e/ou pontos de interesse favoritos\n(C) Escolher um hotspot\n");
    printf("(D) Remover Hotspot\n(E) Alterar informações do utilizador\n(F) Remover locais e/ou pontos de interesse favoritos\n");
    printf("(G) Gerar viagem e calcular taxa de popularidade\n(H) Mostrar informações do utilizador\n\n(X) Guardar alterações e fechar o programa\n> ");

    node = user->local;
    fflush(stdin);
    if(scanf("%c", &choice)==1){
        choice = tolower(choice);

        switch(choice){
            case 'a':
                clrscr();
                screen_printfavs(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
                break;
            case 'b':
                clrscr();
                menu_escolherfavs(user,cabeca_p,cabeca_pdipop,cabeca_pdialfabetica,cabeca_lpop,cabeca_lalfabetica);
                break;
            case 'c':
                clrscr();
                menu_escolherhotspot(user,cabeca_p,cabeca_pdipop,cabeca_pdialfabetica,cabeca_lpop,cabeca_lalfabetica);
                break;
            case 'd':
                clrscr();
                remover_hotspot(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
                break;

            case 'e':
                clrscr();
                menu_definicoesuser(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
                break;
            case 'f':
                clrscr();
                remover_pdilocal(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
                break;
            case 'g':
                clrscr();
                calculaviagem(user,cabeca_p,cabeca_lpop,cabeca_lalfabetica,cabeca_pdipop,cabeca_pdialfabetica);
            case 'h':
                clrscr();
                mostrarinfouser(user);
                menuposlogin(user, cabeca_p, cabeca_lpop, cabeca_lalfabetica, cabeca_pdipop, cabeca_pdialfabetica);
            case 'x':
                guardarinfolocais(cabeca_lalfabetica, cabeca_pdialfabetica);
                guardarinfouser(cabeca_p);
                guardarinfopdis(cabeca_pdialfabetica);
                freeeverything(cabeca_p, cabeca_pdialfabetica, cabeca_pdipop, cabeca_lalfabetica, cabeca_lpop);
                exit(0);
                break;
            default:
                menuposlogin(user, cabeca_p, cabeca_lpop, cabeca_lalfabetica, cabeca_pdipop, cabeca_pdialfabetica);
    }

    }
}

void guardarinfouser(t_person *cabeca_p){
    FILE *fp;
    t_person *aux;
    t_local *templocal;
    t_pdi *temppdi;
    int a;
    fp = fopen("nomes.txt", "w");

    aux = cabeca_p;

    while(aux->nome==NULL){
        aux = aux->prox;
    }
    while(aux!=NULL){
        a = contalocaisuser(aux) + contapdisuser(aux);
        fprintf(fp, "%s/%s/%s/%d/%d/%d/", aux->nome, aux->morada, aux->datanasc, aux->n_telem, aux->hotspot,a);
        if((contalocaisuser(aux)>0) && (contapdisuser(aux)>0)){

           templocal = aux->local;
           while(templocal->nome==NULL){
            templocal = templocal->prox;
           }
           temppdi = aux->pdis;
           while(temppdi->nome==NULL){
            temppdi = temppdi->prox;
           }

           while(templocal!=NULL){
            fprintf(fp, "%d/", templocal->id);
            templocal = templocal->prox;

           }
           while(temppdi!=NULL){
            fprintf(fp, "%d/", temppdi->id);
            temppdi = temppdi->prox;
           }

        }

        if((contalocaisuser(aux)>0) && (contapdisuser(aux)==0)){

            templocal = aux->local;
           while(templocal->nome==NULL){
            templocal = templocal->prox;
           }
            while(templocal!=NULL){
            fprintf(fp, "%d/", templocal->id);
            templocal = templocal->prox;
           }
        }
        if((contalocaisuser(aux)==0) && (contapdisuser(aux)>0)){
            temppdi = aux->pdis;
           while(temppdi->nome==NULL){
            temppdi = temppdi->prox;
           }

            while(temppdi!=NULL){
            fprintf(fp, "%d/", temppdi->id);
            temppdi = temppdi->prox;
           }
        }

        aux = aux->prox;
        fprintf(fp,"\n");
    }
    fprintf(fp, "end");
    fclose(fp);
}

void freeusers(t_person *nodep){
    t_person *prox;
    while(nodep!=NULL){
        prox = nodep->prox;
        freepdi(nodep->pdis);
        free(nodep);
        nodep = prox;
    }
}

void freelocal(t_local *nodel){
    t_local *prox;
    while(nodel != NULL){
        prox = nodel->prox;
        free(nodel);
        nodel = prox;

    }

}

void freepdi(t_pdi *nodepdi){
    t_pdi *prox;
    while(nodepdi!=NULL){

        prox = nodepdi->prox;
        free(nodepdi);
        nodepdi = prox;
    }
}

void freeeverything(t_person *cabeca_p, t_pdi *cabeca_pdialfa, t_pdi *cabeca_pdipop, t_local *cabeca_localalfa, t_local *cabeca_localpop){

    freeusers(cabeca_p);
    freepdi(cabeca_pdialfa);
    freepdi(cabeca_pdipop);
    freelocal(cabeca_localalfa);
    freelocal(cabeca_localpop);


}

void guardarinfopdis(t_pdi *cabeca_pdi){
    FILE *fp;
    t_pdi *auxpdi;
    fp = fopen("pdi.txt", "w");
    auxpdi = cabeca_pdi;
    while(auxpdi->nome == NULL){
        auxpdi = auxpdi->prox;
    }
    while(auxpdi!=NULL){
        fprintf(fp,"%d/%s/%s/%s/%d/%d/%d\n", auxpdi->id, auxpdi->nome, auxpdi->descript, auxpdi->horario, auxpdi->popp, auxpdi->hotpoints, auxpdi->local);
        auxpdi = auxpdi->prox;
    }
    fprintf(fp, "end");
    fclose(fp);
}
void guardarinfolocais(t_local *cabeca_lalfabetica, t_pdi *cabeca_pdi){
    FILE *fp;
    t_local *aux;
    fp = fopen("locais.txt", "w");
    aux = cabeca_lalfabetica;
    while(aux->nome == NULL){
        aux = aux->prox;
    }

    while(aux!=NULL){
        fprintf(fp, "%d/%s/%d/", aux->id, aux->nome, aux->popl);
        aux = aux->prox;
        fprintf(fp, "\n");
    }
    fprintf(fp, "end");
    fclose(fp);


}

int main()
{
    setlocale(LC_ALL, "Portuguese");  /* para aceitar acentuaçao portuguesa*/
    t_pdi *cabeca_pdialfabetica = cria_cabecalhoPDI();
    t_pdi *cabeca_pdipop = cria_cabecalhoPDI();
    t_local *cabeca_lalfabetica = cria_cabecalhoL();
    t_local *cabeca_lpop = cria_cabecalhoL();
    t_person *cabeca_p = cria_cabecalhoP();
    t_person *user = cria_cabecalhoP();


    crialistalocais(cabeca_lalfabetica, cabeca_lpop);
    crialistapdis(cabeca_pdialfabetica, cabeca_pdipop);
    crialistapessoas(cabeca_p, cabeca_pdialfabetica, cabeca_lalfabetica);
    user = menu_inicial(cabeca_p, user);
    clrscr();
    printf("\nBem vindo %s\n", user->nome);
    presscontinue();
    clrscr();

    menuposlogin(user, cabeca_p, cabeca_lpop, cabeca_lalfabetica, cabeca_pdipop, cabeca_pdialfabetica);

    return 0;

}
