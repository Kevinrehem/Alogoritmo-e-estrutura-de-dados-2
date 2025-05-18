#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

typedef int KEY; //define o tipo comparável da chave a ser utilizada na estrutura Node da árvore

//Estrutura que armazena o valor de um nó da árvore e o próximo valor menor e maior que ele
struct Node{
    KEY value;
    Node *left, *right;
};

//identifica um ponteiro do tipo node como  POINT para facilitar a identificação
typedef Node* POINT;

//inicializa o primeiro node de uma árvore, que terá um Node apontando para nulo
POINT start(){
    return NULL;
}

//inicializa um novo node de forma que ele não aponte para nenhum outro node (nó folha)
POINT create_node(KEY value){
    POINT aux = new Node;
    aux->value=value;
    aux->left=NULL;
    aux->right=NULL;
    return aux;
}

//adiciona um novo nó na árvore recursivamente
POINT add_node(POINT root, POINT node){
    if(!root){
        return node;
    }
    if (node->value < root->value){
        root->left = add_node(root->left, node);
    }else{
        root->right = add_node(root->right, node);
    }
    return root;  
}

//imprime, em ordem crescente ou decrescente, os nós contidos na árvore
void show_elements(POINT root, bool key){
    if(root){
        if(key){
            show_elements(root->left, key);
            cout << root->value << " ";
            show_elements(root->right, key);
        }else{
            show_elements(root->right, key);
            cout << root->value << " ";
            show_elements(root->left, key);
        }
    }

}

int main(){
    POINT root = start();
    int op=-1;
    KEY value;
    srand(time(0));
    for(int i = 0; i<10; i++){
        value = (rand()%100)+1;
        bool minus = rand()%2;
        if(minus) value*=-1;
        root = add_node(root, create_node(value));
    }
    
    //Menu
    while(op!=0){
        cout << "1 - Inserir novo elemento na arvore\n";
        cout << "2 - Imprimir elementos em ordem crescente\n";
        cout << "3 - Imprimir elementos em ordem decrescente\n";
        cout << "0 - Sair\n";
        cin >> op;
        switch (op){
            case 1:
                cout << "Valor: "; cin >> value;
                root = add_node(root, create_node(value));
                break;

            case 2:
                show_elements(root, true);
                cout << endl;
                break;

            case 3:
                show_elements(root, false);
                cout << endl;
                break;
            
            default:
                cout << "Opcao invalida\n";
                break;
        }
    }

}