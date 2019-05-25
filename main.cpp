#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {

   char letra;
   int cont;
   node * folhas[51];
};
struct pilha {

  char vet [200];
  int topo;
};

   typedef struct node node;
   typedef node * arvore;
   typedef node * posicao;
   typedef struct pilha pilha;


int equivalentNum (char c);
void folhasNULL (arvore posic);
void criaArvore (arvore raiz, FILE* ent);
void inicPilha (pilha *p1);
int tamanho (pilha p1);
int isEmpty (pilha p1);
void push (pilha *p1, char valor);
void pop (pilha *p1);
void escreveCont (arvore raiz, FILE* saida, pilha* p1);


int equivalentNum (char c){
 int num;
  c =tolower(c);
  num= c-96;
   return num;

}

void folhasNULL (arvore posic) {
   for (int i=0; i<51; i++)
     (posic)->folhas[i]=NULL;
   (posic)->cont=0;
   return;
}

void criaArvore (arvore raiz, FILE* ent) {

   char c;
   arvore apontador;
   apontador = (raiz);
   int num;

     while (!feof(ent)){
         fscanf(ent, "%c", &c);
            if (isalpha(c)){
                c=tolower(c);
                num=equivalentNum(c);

                if (apontador->folhas[num]==NULL){
                    apontador->folhas[num]=(node*)malloc(sizeof(node));
                    apontador=apontador->folhas[num];
                    folhasNULL(apontador);
                    apontador->letra=c;
                }

                else
                apontador=apontador->folhas[num];

                while (isalpha(c)){
                     fscanf(ent, "%c", &c);

                      if (isalpha(c)){
                         num=equivalentNum(c);

                          if (apontador->folhas[num]==NULL){
                             apontador->folhas[num]=(node*)malloc(sizeof(node));
                             apontador=apontador->folhas[num];
                             folhasNULL(apontador);
                             apontador->letra=c;

                          }

                          else
                            apontador=apontador->folhas[num];
                      }
                    if (!isalpha(c))
                        apontador->cont++;
                }
            }
            apontador=(raiz);
     }
}

void inicPilha(pilha *p1){
   p1->topo=-1;
    return;
}

int tamanho (pilha p1){
   int tam;
   tam=p1.topo+1;
   return tam;
}

int isEmpty(pilha p1){
    int elem=0;
    if (p1.topo>=0)
        elem++;
    return elem;

}

void push (pilha *p1, char valor){
    int tam;
    tam = tamanho (*p1);

    if (tam==200)
    {
        printf("Palavra muito grande\n");
     return;
  }
  else{
    p1->topo++;
    p1->vet[p1->topo]=valor;
    return;
  }

}

void pop (pilha *p1){
    int elem;
    elem = isEmpty (*p1);

    if (elem==0) {
        return;
    }
  else{
    p1->topo--;
    return;
  }
}

void escreveCont(arvore raiz, FILE* saida, pilha*p1){
   arvore apontador;
   apontador=raiz;

   if (apontador==NULL)
    return;

   if (isalpha(apontador->letra)){

     push (p1, apontador->letra);

      if (apontador->cont!=0){
        fprintf (saida, "%d ", apontador->cont);
         for (int i=0; i<tamanho(*p1); i++)
            fprintf(saida,"%c", p1->vet[i]);
         fprintf(saida," \n");
      }
   }

   for (int i=0; i<26; i++)
     escreveCont(apontador->folhas[i], saida, p1);

   pop (p1);




}

int main () {


  FILE* ent, * saida;
  ent = fopen("othello.txt","rt");

  saida = fopen("saida.txt", "wt");

  arvore raiz;
  raiz = (node*)malloc(sizeof(node));
  folhasNULL(raiz);

  (raiz)->letra='!';


  pilha p1;
  inicPilha(&p1);

  criaArvore(raiz, ent);

  escreveCont(raiz, saida, &p1);

   fclose(ent);

   fclose(saida);
system ("pause");
   return 0;



}
