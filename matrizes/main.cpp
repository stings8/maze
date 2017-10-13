#include "libs/ed_base.h"
#include "libs/ed_mat.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>


using namespace std;

int nlinhas = 20;
int ncolunas = 35;

const char PAREDE = 'k';
const char VAZIO = 'w';
const char CAMINHO = 'r';

//MAPA DE CORES
//r red
//g green
//b blue
//m magenta
//c cyan -
//y yellow
//w white
//k black

struct Node{
    Par par;
    Node * next;
    Node(Par par = 0, Node * next = nullptr){
        this->par = par;
        this->next = next;
    }
};

struct Pilha{
    Node * topo;

    Pilha(){
      topo = nullptr;
    }

    void push_front(Par par){
        auto node = new Node(par, topo);
        topo = node;

    }

    void pop_front(){
        if(topo == nullptr)
            return;
        auto node = topo;
        topo = topo->next;
        delete node;
        node = nullptr;
    }

     bool pilha_vazia(){
      if(topo == nullptr)
          return true;
      return false;
   }
     Par  get_front(){
         if(topo != nullptr)
             return topo->par;
     }

     int size(){
         auto node = topo;
         int cont = 0;
         while(node != nullptr){
             cont++;
             node = node->next;
         }
         return cont;
     }
};

vector<Par>get_vizinhos = {Par(-1, 0), Par(0, -1), Par(1, 0), Par(0, 1)};
vector<Par>get_all_vizinhos = {Par(-1, 0), Par(0, -1), Par(1, 0), Par(0, 1), Par (-1, 1), Par (1, 1), Par (-1, -1), Par (1, -1)};
vector<Par>shuffle(vector<Par>vet){
    random_shuffle(vet.begin(), vet.end());
    return vet;
}


bool eh_furavel(matchar &mat, Par pos){
    int cont = 0;
    if(!mat.equals(pos, PAREDE))
        return false;
    for(auto v : get_vizinhos){
        auto viz = pos + v;
        if(!mat.is_inside(viz))
            cont++;
        else if(mat.get(viz) == VAZIO)
            cont++;
    }
    return (cont <2);

}


void create_lab_pilha(matchar &mat){
    mat.get(Par(5,5)) = VAZIO;
    stack<Par> pilha;
    pilha.push(Par(5,5));
    while(!pilha.empty()){
        vector<Par>validos;
        for(auto v : get_vizinhos){
            auto viz = pilha.top() + v;
            if(eh_furavel(mat,viz))
                validos.push_back(viz);

        }
        if(validos.size() == 0){
            pilha.pop();
            mat_draw(mat);
            ed_show();
        }else{
            int ran = rand() % validos.size();
            pilha.push(validos[ran]);
            mat.get(validos[ran]) = VAZIO;
            mat_draw(mat);
            ed_show();
        }

    }


}

void floodfill(matchar &mat, Par pos, char cor){
    queue<Par>fila;
    mat.get(pos) = 'c';
    fila.push(pos);

    while(!fila.empty()){
        mat.get(fila.front()) = 'g';
        auto frente = fila.front();
        for(auto v : get_vizinhos){
            auto viz = frente + v;
            if(mat.is_inside(viz)){
                if(mat.get(viz) == cor){
                    mat.get(viz) = 'r';
                    fila.push(viz);
                }
                mat_draw(mat);
                mat_focus(pos, 'b');
                ed_show();
            }
        }
        fila.pop();
    }
}

void pintarParth(matchar &mat, matriz<int> &mati, Par dest){
    auto atual = dest;
    while(mati.get(atual) != 0){
        for(auto v : get_vizinhos){
            auto viz = atual + v;
            if(mati.get(viz) == mati.get(atual) -1){
                mat.get(viz) = 'y';
                atual = viz;
                mat_draw(mat);
                mat_focus(atual, 'r');
                ed_show();
                break;
            }
        }
    }
}
bool pathfloodfill(matchar &mat, matriz<int> &mati, Par inicio, Par fim){
    queue<Par>fila;

    if(mat.get(inicio) == VAZIO){
        mat.get(inicio) = 'r';
        mati.get(inicio) = 0;
        fila.push(inicio);
        mat_draw(mat);
        mat_focus(inicio, 'r');
    }
    while(!fila.empty()){
        auto frente = fila.front();
        for(auto v : get_vizinhos){
            auto viz = frente + v;
            if(mat.get(viz) == VAZIO){
                mat.get(viz) = 'y';
                mati.get(viz) = mati.get(frente) + 1;
                mat_draw(mat);
                mat_focus(fim, 'r');
                ed_show();
                if(viz == fim)
                    return true;
                fila.push(viz);
            }
        }
        fila.pop();
    }
    return false;
}

void resolveLab(matchar &mat, matriz<int> &mati, Par origem, Par Destino){
    stack<Par>pilha;
    pilha.push(origem);
    auto topo = pilha.top();

    while(topo != Destino){
        mat.get(topo) = 'b';

        for(auto v : get_vizinhos){
            auto viz = topo + v;
            if(mati.get(viz) == topo -1){
                mat.get(viz) = 'b';
                pilha.
            }
        }





    }




}

void main1(){
      matriz<int>mati(nlinhas, ncolunas, -1);
      matchar matc(nlinhas, ncolunas, PAREDE);
       mat_paint_brush(matc, "kw");
       create_lab_pilha(matc);
       Par inicio = mat_get_click(matc, " ");
       Par fim = mat_get_click(matc, " ");
       pathfloodfill(matc, mati,inicio, fim);
       //char cor = matc.get(pos);

       //floodfill(matc,pos, cor);
       mat_draw(matc);
       ed_lock();

}

int main(){
    main1();
}



#if 0
//void inicio(){
//    matchar matc(nlinhas, ncolunas, PAREDE);
//    matriz<int>mati(nlinhas, ncolunas, -1);
//    Pilha pilha;

//    mat_paint_brush(matc, "kw");
//    Par pos = mat_get_click(matc," ");
//    create_lab(matc, pos);
//    Par inicio = mat_get_click(matc, " ");
//    Par fim = mat_get_click(matc, " ");
//    PathfloodFill(matc, mati, inicio, fim);

//    //create_lab_pilha(matc);

//    ed_lock();
//}

bool achar(matchar &mat, Par inicio, Par fim,Par par){
    //PONTOS DE PARADA
    if(!mat.is_inside(par))//se estiver fora da matriz
        return false;
    if(mat.get(par) != VAZIO)//se nao for arvore
        return false;
    if(par == fim){
        mat.get(par) = CAMINHO;
        draw(mat,inicio, fim, par);
        return true;
    }
    //ACAO
    mat.get(par) = MIGALHA;

    //DESENHO
    draw(mat,inicio, fim, par);

    //RECURSAO
    for(auto desl : delta_par){
        auto viz = par + desl;
        if(achar(mat,inicio, fim, viz)){
            mat.get(par) = CAMINHO;
            draw(mat,inicio, fim, par);
            return true;
        }


    }
    mat.get(par) = 'b';
    draw(mat, inicio, fim, par);
    return false;



}

//void floodfill(matchar &mat, Par pos){
//    Pilha pilha;
//    if(!mat.is_inside(pos))
//        return;
//    if(mat.get(pos) == 'w'){
//        mat.get(pos) == 'k';
//        pilha.push_front(pos);
//        mat_draw(mat);
//        mat_focus(pos, 'b');
//        ed_show();
//    }
//    while(!pilha.pilha_vazia()){
//        auto topo = pilha.get_front();
//        mat_draw(mat);
//        pilha.pop_front();
//        for(auto par : get_vizinhos){
//            auto viz = topo + par;
//            if(mat.get(viz) == 'w'){
//                mat.get(viz) == 'k';
//                pilha.push_front(viz);

//            }
//            mat_draw(mat);
//            ed_show();

//        }
//    }
//}

void draw(matchar &mat, Par inicio, Par fim,  Par par){

    mat_draw(mat);//desenha a matriz
    mat_focus(inicio, 'g');
    mat_focus(fim, 'r');
    mat_focus(par, 'm');//faz uma bolinha em par
    ed_show();//mostra na tela

}

//}

//void create_lab_pilha(matchar &mat){
//    Pilha pilha;
//    Par par{1,2};
//    pilha.push_front(par);
//    mat.get(par)= VAZIO;
//    mat_draw(mat);
//    mat_focus(par, 'm');
//    ed_show();

//    while(!pilha.pilha_vazia()){

//        auto topo = pilha.get_front();
//        pilha.pop_front();
//        for(auto pos : shuffle(get_vizinhos)){
//            auto viz = topo + pos;
//            mat_focus(topo, 'm');


//            if(contar_vizinhos(mat, viz) <= 1){
//                pilha.push_front(viz);
//                mat.get(viz) = VAZIO;
//                mat_draw(mat);
//                mat_focus(viz, 'm');
//                ed_show();
//            }
//        }


//        }

//}

//void PathfloodFill(matchar &mat, matriz<int> &mati, Par inicio,Par fim){


//    }





//void create_lab(matriz<char> &mat, Par pos){
//    if(!mat.is_inside(pos))
//        return;
//    if(mat.get(pos) != PAREDE )
//        return;
//    if(contar_vizinhos(mat, pos) > 1)
//        return;
//    mat.get(pos) = VAZIO;
//    mat_draw(mat);
//    mat_focus(pos, 'm');
//    ed_show();
//    for(auto par : shuffle(get_vizinhos)){
//        auto viz = pos + par;
//        mat_focus(pos,'m');
//        create_lab(mat, viz);
//    }

int main(){

    //cria uma matriz de caracteres de 15 linhas por 20 colunas, e preenche todos os elementos
    //com 'y'
    matriz<char> matc(nlinhas, ncolunas, 'y');
    matriz<int> mati(nlinhas, ncolunas, '0');




    //chama o metodo de desenho livre onde a cor primeira default eh branca
    mat_paint_brush(mat, "kw");


    Par inicio = mat_get_click(mat, " ");
    Par fim = mat_get_click(mat, " ");
    achar(mat, inicio, fim, inicio);//chama a função recursiva

    ed_lock();//impede que termine abruptamente

    return 0;
}

#endif
