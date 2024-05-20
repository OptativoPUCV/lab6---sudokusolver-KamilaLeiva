#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   for(int i=0;i<9;i++){
      int* fila = (int*) calloc(10,sizeof(int));
      int* columna = (int*) calloc(10,sizeof(int));
      for(int j=0;j<9;j++){
         if(n->sudo[i][j]!=0){
            if(fila[n->sudo[i][j]]==1) return 0;
            fila[n->sudo[i][j]]=1;
         }
         if(n->sudo[j][i]!=0){
            if(columna[n->sudo[j][i] ]==1) return 0;
            columna[n->sudo[j][i]]=1;
         }
      }
   }
   int k = 0;
   while(k<9){
      int* subcuadrado = (int*) calloc(10,sizeof(int));
      for(int i=0;i<9;i++){
         int x = 3*(k/3) + (i/3);
         int y = 3*(k%3) + (i/3);
         if(n->sudo[x][y]!=0){
            if(subcuadrado[n->sudo[x][y]]==1) return 0;
            subcuadrado[n->sudo[x][y]]=1;
         }
      }      
   }
      k++;
    return 1;
}


List* get_adj_nodes(Node* n){ 
   List* list=createList();
   int i,j;
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
         if(n->sudo[i][j]==0){
            int k = 1;
            while(k<10){
               Node* adj=copy(n);
               adj->sudo[i][j]=k;
               if(is_valid(adj)){
                  pushBack(list,adj);
               }
               k++;
            }
         } 
      }
   }
   return list;
}


int is_final(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(n->sudo[i][j]==0){
             return 0;
          }
       }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S=createStack();
   push(S,initial);

   while(get_size(S) != 0){
      Node* n = top(S);
      pop(S);
      if(is_final(n)){
         return n;
      }
      List* list = get_adj_nodes(n);
      Node* aux = first(list);
      while(aux){
         push(S,aux);
         aux = next(list);
      }
   }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/