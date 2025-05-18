#include<iostream>
using namespace std;

typedef int KEY; //define o tipo comparável da chave a ser utilizada na estrutura Node da árvore

//Estrutura que armazena o valor de um nó da árvore e o próximo valor menor e maior que ele
struct Node{
    KEY key;
    Node *left, *right;
};

//identifica um ponteiro do tipo node como  POINT para facilitar a identificação
typedef Node* POINT;

//inicializa o primeiro node de uma árvore, que terá um Node apontando para nulo
POINT start(){
    return NULL;
}


int main(){

}