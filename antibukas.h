#ifndef BUKAS_PROOF_FUNCS
#define BUKAS_PROOF_FUNCS
#include <bits/stdc++.h>
#define MAX_MATRIX_SIZE 1000
using namespace std;

bool isOdd(int x) {
    if(x % 2 != 0) {
        return true;
    }
    return false;
}

long long int SumToN(int n) {
    return n * (n+1) / 2;
}

int lnko(int a, int b) {
    if (a == 0)
        return b;
    return lnko(b % a, a);
}

int lkkt(int a, int b) {
    return (a * b) / lnko(a, b);
}

void inArr(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
}

void outArr(int array[], int size) {
    for(int i = 0; i < size; i++) {
        cout <<array[i];
    }
    cout <<endl;
}

void inMat(int matrix[][MAX_MATRIX_SIZE], int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            cin >> matrix[i][j];
        }
    }
}

void outMat(int matrix[][MAX_MATRIX_SIZE], int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            cin >> matrix[i][j];
        }
    }
}

bool ifPrim(int n) {
    if (n == 1 || n == 0) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int sizeofArr(int arr[]) {
    return sizeof(arr) / sizeof(arr[0]);
}

int binarySearch(int array[], int left, int right, int x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (array[mid] == x)
            return mid;

        if (array[mid] > x)
            return binarySearch(array, left, mid - 1, x);

        return binarySearch(array, mid + 1, right, x);
    }

    return -1;
}

//!!!NEEDED FOR QUICKSORT
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
//!!!NEEDED FOR QUICKSORT

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void mergeArrs() {

}

typedef struct seg {
    int info;
    seg *kov;
    seg *elo;
    //!!! main.cpp template
    /*
    LIST *lista = new LIST;
    lista->head = NULL;
    */
} node;

typedef struct doubly_circular_linked{
    node *head;

    void besz_head(int x) {
        node *uj = new node;

        uj->info = x;

        uj->kov = (head);
        uj->elo = NULL;

        if ((head) != NULL)
            (head)->elo = uj;

        (head) = uj;
    }
    //!!! IDK WHAT IT DOES
    void besz_qelott(int x) {
        node *q = head;
        node *temp = new node;
        temp->info = x;

        if (q == NULL) {
            cout << "NULL";
        }

        temp->elo = q->elo;
        temp->kov = q;
        q->elo = temp;

        if (temp->elo != NULL) {
            temp->elo->kov = temp;
        }
        else {
            head = temp;
        }
    }

    void besz_qutan(node *elo, int x) {
        if (elo == NULL) {
            return;
        }

        node *uj = new node;

        uj->info = x;

        uj->kov = elo->kov;

        elo->kov = uj;

        uj->elo = elo;

        if (uj->kov != NULL)
            uj->kov->elo = uj;
    }

    void besz_last(int x) {
        node *uj = new node;

        node *last = head;

        uj->info = x;

        uj->kov = NULL;

        if (head == NULL) {
            uj->elo = NULL;
            head = uj;
            return;
        }

        while (last->kov != NULL)
            last = last->kov;
        last->kov = uj;

        uj->elo = last;
        return;
    }

    void besz_pos(int x, int pos) {
        node *temp = new node, *s;
        temp->info = x;
        temp->kov = NULL;
        temp->elo = NULL;
        if (pos == 1) {
            temp->kov = head;
            head = temp;
            return;
        }
        node *temp2 = head;
        for (int i = 0; i < pos - 2; i++) {
            temp2 = temp2->kov;
        }
        temp->kov = temp2->kov;
        temp2->kov = temp;
    }

    void Kiirjobb() {
        node *iter = head;

        while (iter->kov != NULL) {
            cout << iter->info << "<==>";
            iter = iter->kov;
        }
        cout << iter->info << endl;
    }

    void Kiirbal() {
        node *last = head;

        while (last->kov != NULL) {
            last = last->kov;
        }
        while (last != head) {
            cout << last->info << "<==>";
            last = last->elo;
        }
        cout << last->info << endl;
    }

    void torles(node *del) {
        if (head == NULL || del == NULL)
            return;

        if (head == del)
            head = del->kov;

        if (del->kov != NULL)
            del->kov->elo = del->elo;

        if (del->elo != NULL)
            del->elo->kov = del->kov;
        free(del);
        return;
    }

    void torlpos(int n) {
        if (head == NULL || n <= 0)
            return;

        node *curr = head;

        for (int i = 1; curr != NULL && i < n; i++)
            curr = curr->kov;

        if (curr == NULL)
            return;

        torles(curr);
    }
} LIST;

typedef struct st {
    int data;
    st *first;

    //!!! main.cpp template
    /*
    STACK *stack = new STACK;
    stack_node *top = new stack_node;
    top->first = NULL;
    top->data = -1;
    */
} stack_node;

typedef struct stack_struct{
    stack_node *top;

    void push(int val) {
        stack_node *x = new stack_node;
        x->data = val;
        x->first = top;

        top = x;
    }

    int pop(int x) {
        if (top == NULL)
            return 0;
        else {
            x = top->data;
            top = top->first;
        }
    }

    int Top() {
        return top->data;
    }
} STACK;

typedef struct nd {
    int data;
    nd* next;

    //!!! main.cpp template
    /*
    QUEUE *queue = new QUEUE;
    queue_node *first = NULL;
    queue_node *last = NULL;
    */
} queue_node;

typedef struct queue_struct {
    queue_node *first;
    queue_node *last;

    bool ok() {
        if (first == NULL) {
            return true;
        }
        return false;
    }

    void push(int ert) {
        queue_node *x = new queue_node;
        x->data = ert;
        x->next = NULL;
        if (ok()) {
            first = last = x;
        }
        else {
            last->next = x;
            last = x;
        }
    }

    int pop() {
        int x;
        queue_node *p;
        if (ok()) {
            return -1;
        }
        else {
            p = first;
            x = first->data;
            first = p->next;
            free(p);
            return x;
        }
    }

    void display() {
        queue_node *p;
        p = first;
        while (p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
    }
} QUEUE;

bool intIsPal(int n) {
    int temp = n, dig, rev = 0;
    do {
        dig = temp % 10;
        rev = (rev * 10) + dig;
        temp /= 10;
    } while(temp  != 0);

    if(n == rev) {
        return true;
    } else {
        return false;
    }
}
//!!!NEEDED FOR CHARISPAL
bool isPal(char str[], int s, int e) {
    if (s == e)
        return true;

    if (str[s] != str[e])
        return false;

    if (s < e + 1)
        return isPal(str, s + 1, e - 1);

    return true;
}
//!!!NEEDED FOR CHARISPAL

bool isVow(char ch) {
    ch = toupper(ch);
    return (ch == 'A' || ch == 'E' || ch == 'I' ||
            ch == 'O' || ch == 'U');
}

int charCVow(char str[]) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (isVow(str[i]))
            ++count;
    return count;
}

int charCCons(char str[]) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (isVow(str[i]) == false)
            ++count;
    return count;
}

bool charIsPal(char str[]) {
    int n = strlen(str);

    if (n == 0)
        return true;

    return isPal(str, 0, n - 1);
}

void sortCharMat(char str[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int n) {
    char temp[255];
    for(int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (strcmp(str[j - 1], str[j]) > 0) {
                strcpy(temp, str[j - 1]);
                strcpy(str[j - 1], str[j]);
                strcpy(str[j], temp);
            }
        }
    }
}

void MatrixPrimDiag(int mat[][MAX_MATRIX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                cout << mat[i][j] << ", ";
        }
    }
    cout << endl;
}

void MatrixSecDiag(int mat[][MAX_MATRIX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) == (n - 1))
                cout << mat[i][j] << ", ";
        }
    }
    cout << endl;
}

void MatrixSpiralPrint(int a[][MAX_MATRIX_SIZE], int m, int n) {
    int i, k = 0, l = 0;

    /* k - sor első indexe
        m - sor utolsó indexe
        l - oszlop első indexe
        n - oszlop utolsó indexe
        i - iterator
    */

    while (k < m && l < n) {
        for (i = l; i < n; ++i) {
            cout << a[k][i] << " ";
        }
        k++;

        for (i = k; i < m; ++i) {
            cout << a[i][n - 1] << " ";
        }
        n--;

        if (k < m) {
            for (i = n - 1; i >= l; --i) {
                cout << a[m - 1][i] << " ";
            }
            m--;
        }
        if (l < n) {
            for (i = m - 1; i >= k; --i) {
                cout << a[i][l] << " ";
            }
            l++;
        }
    }
}

int Fact(int n) {
    if (n > 1)
        return n * Fact(n - 1);
    else
        return 1;
}

int nVk(int n, int k) {
    return Fact(n) / Fact(n - k);
}

int nCk(int n, int k) {
    return Fact(n) / (Fact(k) * Fact(n - k));
}

#endif