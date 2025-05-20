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


typedef Node* POINT; //identifica um ponteiro do tipo node como POINT para facilitar a identificação

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

//função que devolve um node procurado na arvore e seu node pai, caso solicitado
POINT search(POINT root, KEY value, POINT *parent){
    POINT current = root;
    *parent = NULL;
    while (current){
        if(current->value == value) return current;
        *parent = current;
        if (value<current->value)current = current->left;
        else current = current->right;
    }
    return current;
}

//função que exclui um nó da árvore a partir de um valor do seu atributo chave
POINT erase(POINT root, KEY value){
    POINT node, parent, p, q;
    node = search(root, value, &parent);
    if(!node) return root;
    if(!node->left || !node->right){
        if(!node->left) q = node->right;
        else q = node->left;
    }else{
        q = node->left;//pega a sub-árvore à esquerda do nó a ser excluido
        p = node;
        //percorre até o nó mais à direita da sub-árvore à esquerda
        while(q->right){
            p=q;
            q=q->right;
        }
        if(p!=node){
            p->right=q->left;
            q->left=node->left;
        }
        q->right=node->right;
    }
    if(!parent){
        free(node);
        return q;
    }
    if(value < parent->value) parent->left = q;
    else parent->right = q;
    free(node);
    return root;
}

//metodo principal
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
        cout << "4 - Buscar um elemento na arvore\n";
        cout << "5 - Excluir um elemento da arvore\n";
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

            case 4:
                cout << "Valor buscado: "; cin >> value;
                if(search(root, value, NULL)){
                    cout << value << " encontrado na posicao de memoria: " << search(root, value, NULL);
                }else{
                    cout << value << " nao foi encontrado";
                }
                break;

            case 5:
                cout << "Valor a excluir: "; cin >> value;
                root = erase(root, value);
                break;

            default:
                cout << "Opcao invalida\n";
                break;
        }
    }

}