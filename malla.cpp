#include <bits/stdc++.h>
#include <sstream>
#include <fstream>

#define NOMBRE_ARCHIVO "Malla_Curricular.csv"
using namespace std;

template <class V, class A>
class Grafo
{
private:
    int n;
    vector<V> nombres;        // vertices
    map<V, int> mapn;         //
    vector<vector<A>> ady;    // Almacena las adyacencias
    vector<string> ordenados; // Almacena orden topológico
    vector<int> gradoE;       // Almacena el número de aristas dirigidas a cada nodo
public:
    Grafo() : n{0}, ady{0} {};
    Grafo<V, A> &operator=(const Grafo<V, A> &other)
    {
        this->n = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ady[i][j] = other[i][j];
            }
        }
    }

    Grafo(vector<vector<A>> x)
    {
        this->crearGrafo(x.size());
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                this->ady[i][j] = x[i][j];
            }
        }
    }
    void crearGrafo(int); // que crea un Grafo<V,A>::vacío.
    void insertarNodo(V);
    void veradyacencia();
    void insertarArista(V a, V b, A arista); // inserta una nueva arista con dirección en caso no exista
    void borrarNodo(V a);
    void graficar();             // que elimina un nodo en caso exista.
    void borrarArista(V a, V b); // que elimina una arista en caso esta exista.
    bool esVacio();              // que retorna true en caso el Grafo<V,A>::sea vacío.
    bool existeNodo(V a);        // que comprueba y retorna true si un nodo se encuentra en el
    A caminoMinimo(V a, V b);    // que retorna el camino mínimo de existir entre un nodo origen y un nodo destino.
    void ordenTopologico();      // que retorna el orden topológico del Grafo<V,A>::dirigido.
    // importantes
    void indices();
    void gradoEntrada();
    void printgradoEntrada();
    void adyacenciaUno(int a);
    void gradoCero(int i);

    void floyd(vector<vector<A>> &x);
    void floyd();
    void reordenarmatrix(vector<vector<A>> &x);
    void warshal(vector<vector<A>> &x);

    ~Grafo()
    {
        nombres.clear();
        mapn.clear();
        ady.clear();
    }
};

template <class V, class A>
void Grafo<V, A>::crearGrafo(int N)
{
    ady.resize(N);
    for (int i = 0; i < N; i++)
    {
        ady[i].resize(N);
    }
    n = N;
}

template <class V, class A>
void Grafo<V, A>::insertarNodo(V nodo)
{
    if (!existeNodo(nodo))
    {
        nombres.push_back(nodo);
        mapn[nodo] = nombres.size() - 1;
        // cout << mapn[nodo];
        n = n + 1;
        ady.resize(n);
        for (int i = 0; i < n; i++)
            ady[i].resize(n);
    }
}

template <class V, class A>
void Grafo<V, A>::veradyacencia()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout.width(2); cout << ady[i][j];
        }
        cout << endl;
    }
}

template <class V, class A>
void Grafo<V, A>::insertarArista(V a, V b, A arista)
{

    if (existeNodo(a) && existeNodo(b))
    {
        int pa = mapn[a];
        int pb = mapn[b];
        if (ady[pa][pb] == 0)
            ady[pa][pb] = arista;
    }
}

template <class V, class A>
void Grafo<V, A>::borrarNodo(V a)
{
    if (existeNodo(a))
    {
        int pos = mapn[a];
        int i = pos + 1;
        int j = 0;

        if (pos != n - 1)
        {
            while (i != n)
            {
                j = 0;
                while (j != n)
                {
                    ady[i - 1][j] = ady[i][j];
                    ++j;
                }
                cout << i;
                ++i;
            }

            j = pos + 1;
            while (j != n)
            {
                i = 0;
                while (i != n)
                {
                    ady[i][j - 1] = ady[i][j];
                    ++i;
                }
                cout << j;
                ++j;
            }
        }
        n = n - 1;
        ady.resize(n);
        for (int i = 0; i < n; i++)
        {
            ady[i].resize(n);
        }

        nombres.erase(nombres.begin() + pos);
        mapn.erase(mapn.find(a));
        for (int i = 0; i < n; i++)
        {
            mapn[nombres[i]] = i;
        }
    }
}
template <class V, class A>
void Grafo<V, A>::graficar()
{
    ofstream arch;
    arch.open("./Grafo_Malla.dot");
    if (arch.is_open())
    {
        arch << "strict digraph A { \n";
        for (int i = 0; i < n; i++)
        {
            arch << nombres[i] << endl;
            for (int j = 0; j < n; j++)
            {
                if (ady[i][j] != 0)
                {
                    arch << nombres[i] << "->" << nombres[j] << "[label =" << ady[i][j] << "]" << endl;
                }
            }
        }
        arch << "}\n";
        arch.close();
        system("dot -Tpng ./Grafo_Malla.dot -o ./Grafo_Malla.png ");
        system("./Grafo_Malla.png ");
    }
    else
    {
        cout << "error al crear archivo";
    }
}
template <class V, class A>
void Grafo<V, A>::borrarArista(V a, V b)
{
    if (existeNodo(a) && existeNodo(b))
    {
        int pa = mapn[a];
        int pb = mapn[b];
        if (ady[pa][pb] != 0)
            ady[pa][pb] = 0;
    }
}
template <class V, class A>
bool Grafo<V, A>::esVacio()
{
    if (nombres.empty())
        return true;
    return false;
}

template <class V, class A>
bool Grafo<V, A>::existeNodo(V a)
{
    if (mapn.find(a) != mapn.end())
        return true;
    else
        return false;
}

template <class V, class A>
A Grafo<V, A>::caminoMinimo(V a, V b)
{
    vector<vector<A>> x;
    warshal(x);
    int i = mapn[a];
    cout << i;
    int j = mapn[b];
    cout << j;
    return x[i][j];
}

template <class V, class A>
void Grafo<V, A>::floyd(vector<vector<A>> &x)
{

    x.resize(n);
    for (int i = 0; i < n; i++)
        x[i].resize(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            x[i][j] = ady[i][j];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (x[i][j] || (x[i][k] && x[k][j]))
                {
                    x[i][j] = 1;
                }
            }
        }
    }
}

template <class V, class A>
void Grafo<V, A>::reordenarmatrix(vector<vector<A>> &x)
{
    float a = std::numeric_limits<float>::infinity();
    x.resize(n);
    for (int i = 0; i < n; i++)
        x[i].resize(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!ady[i][j])
                x[i][j] = a;
            else
                x[i][j] = ady[i][j];
        }
    }
}

template <class V, class A>
void Grafo<V, A>::warshal(vector<vector<A>> &x)
{
    vector<V> s;
    reordenarmatrix(x);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                x[j][k] = min(x[j][k], x[j][i] + x[i][k]);
            }
        }
    }
}

template <class A>
void print(vector<vector<A>> x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x.size(); j++)
        {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
}

template <class V, class A>
void Grafo<V, A>::adyacenciaUno(int a)
{
    // cout<<endl<<"Adyacencia a "<<a<<" son :";

    for (int i = 0; i < n; i++)
    {
        if (ady[a][i] != 0)
        {
            gradoE[a] = gradoE[a] - 1;
            // cout<<gradoE[i]<<endl;
        }
        else if (gradoE[i] == 0 && (find(ordenados.begin(), ordenados.end(), nombres[i]) != ordenados.end()) == false)
        {
            // cout<<endl<<"HA SIDO INSERTADO: "<<nombres[i]<<endl;
            ordenados.push_back(nombres[i]);
        }
    }
    // cout<<"Adyacencia: ";
    // for(int i=0;i<n;i++)
    // cout<<gradoE[i]<<",";
}

template <class V, class A>
void Grafo<V, A>::ordenTopologico()
{
    for (int i = 0; i < n; i++)
    {
        if (gradoE[i] == 0)
        {
            adyacenciaUno(mapn[nombres[i]]);
        }
        if (gradoE[i] == 1)
        {
            adyacenciaUno(mapn[nombres[i]]);
        }
        if (gradoE[i] == 2)
        {
            adyacenciaUno(mapn[nombres[i]]);
        }
    }
    cout << "Lista de vertices ordenados:\n------------------------------\n";
    for (int i = 1; i < n; i++)
    {
        cout.width(10); cout << ordenados[i]; cout << "-->";
    }
    cout << endl;
}

template <class V, class A>
void Grafo<V, A>::indices()
{
    cout << "Código : Índice: \n-----------------\n";
    for (int i = 1; i < n; i++)
    {
        cout.width(10); cout<<right << nombres[i] << ":";
        cout.width(3); cout << mapn[nombres[i]];
    // cout<<endl;
    }
}

template <class V, class A>
void Grafo<V, A>::gradoEntrada()
{
    cout << "Código : Grado del vertice: \n----------------------------\n";

    for (int a = 0; a < n; a++)
    {
        cout.width(10); cout << nombres[a] << ":";

        int cont = 0;
        for (int j = 0; j < n; j++)
        {
            if (ady[a][j] != 0)
            {
                cont = cont + 1;
            }
        }
        gradoE.push_back(cont);
        cout.width(3); cout << cont;
    }
}

template <class V, class A>
void Grafo<V, A>::printgradoEntrada()
{
    cout << "\nGrado de entrada: ";
    for (int i = 0; i < n; i++)
        cout << gradoE[i] << ",";
}

int main()
{
    //////// GRAFO DE MALLA CURRICULAR  ////////
    Grafo<string, int> M;
    
    ifstream archivo("Malla_Curricular.csv");
    string linea;
    char delimitador = ',';
    cout << "==================" << endl;

    while (getline(archivo, linea))
    {

        stringstream stream(linea); // Convertir la cadena a un stream
        string Codigo, Nombre_Curso, Pre_Req1, Pre_Req2;

        getline(stream, Codigo, delimitador);
        getline(stream, Nombre_Curso, delimitador);
        getline(stream, Pre_Req1, delimitador);
        getline(stream, Pre_Req2, delimitador);
        // Imprimir
        // cout << "Codigo: " << Codigo << endl;
        M.insertarNodo(Codigo);
    }
    archivo.close();

    ///////////////////otro
    ifstream archivo2("Malla_Curricular.csv");

    cout<< setw(50) << left << "\nNOMBRE DEL CURSO";
    cout<< setw(10) << "CODIGO:\n";
    cout<< left << "---------------------------------------------------------\n";

    while (getline(archivo2, linea))
    {
        stringstream stream(linea); // Convertir la cadena a un stream
        string Codigo, Nombre_Curso, Pre_Req1, Pre_Req2;
        getline(stream, Codigo, delimitador);
        getline(stream, Nombre_Curso, delimitador);
        getline(stream, Pre_Req1, delimitador);
        getline(stream, Pre_Req2, delimitador);
        // Imprimir
        // cout.width(50);cout << Nombre_Curso;
        cout << setw(50) << left << Nombre_Curso;
        cout.widen(10); cout<< Codigo <<endl;
        // cout<<"Prequisito"<<Pre_Req1;
        M.insertarArista(Codigo, Pre_Req1, 1);
        M.insertarArista(Codigo, Pre_Req2, 1);
    }
    archivo2.close();
    M.graficar();
    cout << endl;
    
    cout << "\nVER MATRIZ DE ADYACENCIAS \n";
    M.veradyacencia();
    cout<<endl;


    cout << "\nVER INDICES \n";
    M.indices();
    cout<<endl;
    
    cout << "\nVER GRADOS DE LOS VERTICES \n";
    M.gradoEntrada();
    M.printgradoEntrada();
    cout<<endl;

    cout << "\nVER ORDEN TOPOLÓGICO \n";
    M.ordenTopologico();
    
    cout << "\nCORROBORAR ORDEN TOPOLÓGICO";
    M.printgradoEntrada();
    cout<<endl;
    cout<<endl;
}