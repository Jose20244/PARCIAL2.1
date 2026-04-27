//JOSÉ GUILLERMO OLIVA VELÁSQUEZ
//9941-23-6578
#include <iostream>
#include <climits>
#include <cmath>
using namespace std;


struct NodoPila {
    int dato;
    NodoPila* sig;
};

struct NodoCola {
    int dato;
    NodoCola* sig;
};

struct NodoSimple {
    int dato;
    NodoSimple* sig;
};

struct NodoDoble {
    int dato;
    string tipo;
    int orden;
    NodoDoble* ant;
    NodoDoble* sig;
};

struct NodoBST {
    int dato;
    NodoBST* izq;
    NodoBST* der;
};

NodoPila* pila = NULL;
NodoCola* frente = NULL;
NodoCola* fin = NULL;
NodoSimple* listaNeg = NULL;
NodoDoble* historial = NULL;
NodoBST* arbol = NULL;

int pares = 0, impares = 0, negativos = 0, ceros = 0;
int mayor = INT_MIN, menor = INT_MAX;
int orden = 1;


void insertarPila(int x) {
    NodoPila* nuevo = new NodoPila();
    nuevo->dato = x;
    nuevo->sig = pila;
    pila = nuevo;
}

void mostrarPila() {
    if (!pila) { cout << "Pila vacia\n"; return; }
    NodoPila* aux = pila;
    while (aux) {
        cout << aux->dato << " ";
        aux = aux->sig;
    }
    cout << endl;
}

void insertarCola(int x) {
    NodoCola* nuevo = new NodoCola();
    nuevo->dato = x;
    nuevo->sig = NULL;

    if (!frente)
        frente = fin = nuevo;
    else {
        fin->sig = nuevo;
        fin = nuevo;
    }
}

void mostrarCola() {
    if (!frente) { cout << "Cola vacia\n"; return; }
    NodoCola* aux = frente;
    while (aux) {
        cout << aux->dato << " ";
        aux = aux->sig;
    }
    cout << endl;
}

void insertarListaSimple(int x) {
    NodoSimple* nuevo = new NodoSimple();
    nuevo->dato = x;
    nuevo->sig = listaNeg;
    listaNeg = nuevo;
}

void mostrarLista() {
    if (!listaNeg) { cout << "Lista vacia\n"; return; }
    NodoSimple* aux = listaNeg;
    while (aux) {
        cout << aux->dato << " ";
        aux = aux->sig;
    }
    cout << endl;
}

void insertarHistorial(int x, string tipo) {
    NodoDoble* nuevo = new NodoDoble();
    nuevo->dato = x;
    nuevo->tipo = tipo;
    nuevo->orden = orden++;
    nuevo->sig = historial;
    nuevo->ant = NULL;

    if (historial)
        historial->ant = nuevo;

    historial = nuevo;
}

void mostrarHistorial() {
    if (!historial) { cout << "Historial vacio\n"; return; }
    NodoDoble* aux = historial;
    while (aux) {
        cout << aux->orden << ": " << aux->dato << " -> " << aux->tipo << endl;
        aux = aux->sig;
    }
}

NodoBST* insertarBST(NodoBST* r, int x) {
    if (!r) {
        NodoBST* nuevo = new NodoBST();
        nuevo->dato = x;
        nuevo->izq = nuevo->der = NULL;
        return nuevo;
    }
    if (x < r->dato)
        r->izq = insertarBST(r->izq, x);
    else
        r->der = insertarBST(r->der, x);

    return r;
}

void inOrden(NodoBST* r) {
    if (r) {
        inOrden(r->izq);
        cout << r->dato << " ";
        inOrden(r->der);
    }
}

void preOrden(NodoBST* r) {
    if (r) {
        cout << r->dato << " ";
        preOrden(r->izq);
        preOrden(r->der);
    }
}

void postOrden(NodoBST* r) {
    if (r) {
        postOrden(r->izq);
        postOrden(r->der);
        cout << r->dato << " ";
    }
}

bool buscarBST(NodoBST* r, int x) {
    if (!r) return false;
    if (r->dato == x) return true;
    if (x < r->dato)
        return buscarBST(r->izq, x);
    else
        return buscarBST(r->der, x);
}

void eliminarMenores10() {
    NodoSimple* actual = listaNeg;
    NodoSimple* ant = NULL;
    int eliminados = 0;

    while (actual) {
        if (abs(actual->dato) < 10) {
            eliminados++;
            if (!ant) {
                listaNeg = actual->sig;
                delete actual;
                actual = listaNeg;
            } else {
                ant->sig = actual->sig;
                delete actual;
                actual = ant->sig;
            }
        } else {
            ant = actual;
            actual = actual->sig;
        }
    }
    cout << "Eliminados: " << eliminados << endl;
}

void clasificar(int num) {
    if (num == 0) {
        ceros++;
        cout << "Valor invalido\n";
        return;
    }

    if (num > 0) {
        if (num % 2 == 0) {
            insertarCola(num);
            insertarHistorial(num, "COLA");
            pares++;
        } else {
            insertarPila(num);
            insertarHistorial(num, "PILA");
            impares++;
        }
    } else {
        insertarListaSimple(num);
        insertarHistorial(num, "LISTA SIMPLE");
        negativos++;
    }

    if (num > mayor) mayor = num;
    if (num < menor) menor = num;
}

void construirBSTDesdeDatos() {
    arbol = NULL;

    NodoPila* p = pila;
    while (p) {
        arbol = insertarBST(arbol, p->dato);
        p = p->sig;
    }

    NodoCola* c = frente;
    while (c) {
        arbol = insertarBST(arbol, c->dato);
        c = c->sig;
    }

    cout << "InOrden: "; inOrden(arbol);
    cout << "\nPreOrden: "; preOrden(arbol);
    cout << "\nPostOrden: "; postOrden(arbol);
    cout << endl;
}

void mostrarEstadisticas() {
    cout << "Pares: " << pares << endl;
    cout << "Impares: " << impares << endl;
    cout << "Negativos: " << negativos << endl;
    cout << "Ceros: " << ceros << endl;
    cout << "Total validos: " << (pares + impares + negativos) << endl;
    cout << "Mayor: " << mayor << endl;
    cout << "Menor: " << menor << endl;
}

void reorganizar() {
    NodoSimple* aux1 = NULL;
    NodoSimple* aux2 = NULL;

    while (pila) {
        NodoSimple* nuevo = new NodoSimple();
        nuevo->dato = pila->dato;
        nuevo->sig = aux1;
        aux1 = nuevo;

        NodoPila* temp = pila;
        pila = pila->sig;
        delete temp;
    }

    while (frente) {
        NodoSimple* nuevo = new NodoSimple();
        nuevo->dato = frente->dato;
        nuevo->sig = aux2;
        aux2 = nuevo;

        NodoCola* temp = frente;
        frente = frente->sig;
        delete temp;
    }

    cout << "Lista desde pila:\n";
    NodoSimple* t = aux1;
    while (t) { cout << t->dato << " "; t = t->sig; }

    cout << "\nLista desde cola:\n";
    t = aux2;
    while (t) { cout << t->dato << " "; t = t->sig; }

    arbol = NULL;

    t = aux1;
    while (t) {
        arbol = insertarBST(arbol, t->dato);
        t = t->sig;
    }

    t = aux2;
    while (t) {
        arbol = insertarBST(arbol, t->dato);
        t = t->sig;
    }

    cout << "\nBST reconstruido (InOrden): ";
    inOrden(arbol);
    cout << endl;
}

int main() {
    int op, n, x;

    do {
        cout << "\n1. Ingresar N numeros";
        cout << "\n2. Mostrar pila";
        cout << "\n3. Mostrar cola";
        cout << "\n4. Mostrar negativos";
        cout << "\n5. Historial";
        cout << "\n6. Construir BST";
        cout << "\n7. Eliminar negativos <10";
        cout << "\n8. Buscar en BST";
        cout << "\n9. Estadisticas";
        cout << "\n10. Reorganizar";
        cout << "\n0. Salir\n";
        cin >> op;

        switch (op) {
            case 1:
                cout << "Cantidad: ";
                cin >> n;
                if (n <= 0) { cout << "Invalido\n"; break; }
                for (int i = 0; i < n; i++) {
                    cout << "Numero: ";
                    cin >> x;
                    clasificar(x);
                }
                break;

            case 2: mostrarPila(); break;
            case 3: mostrarCola(); break;
            case 4: mostrarLista(); break;
            case 5: mostrarHistorial(); break;
            case 6: construirBSTDesdeDatos(); break;
            case 7: eliminarMenores10(); break;

            case 8:
                cout << "Valor a buscar: ";
                cin >> x;
                if (buscarBST(arbol, x))
                    cout << "Encontrado\n";
                else
                    cout << "No encontrado\n";
                break;

            case 9: mostrarEstadisticas(); break;
            case 10: reorganizar(); break;
        }

    } while (op != 0);

    return 0;
}