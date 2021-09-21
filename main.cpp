#include <bits/stdc++.h>
#include "antibukas.h"
#define MAX_MATRIX_SIZE 1000
using namespace std;

int main() {
    LIST *lista = new LIST; //(LIST *)malloc(sizeof(node));
    lista->head = NULL;
    lista->besz_last(40);
    lista->besz_head(20);
    lista->besz_head(10);
    lista->besz_utan(lista->head->kov->kov, 50);
    lista->besz_qutan(lista->head->kov, 30);
    lista->Kiirbal();
    lista->torlpos(5);
    lista->Kiirbal();
    lista->megforditas();
    lista->Kiirbal();
    lista->besz_pos(50, 5);
    lista->Kiirjobb();
    return 0;
}