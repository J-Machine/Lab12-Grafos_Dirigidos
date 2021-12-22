#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#define NOMBRE_ARCHIVO "Malla_Curricular.csv"
using namespace std;

template < class V , class A>
class Grafo{
    private:
        int n; 
        vector<V> nombres; 
        map<V,int> mapn;
        vector<vector<A>> ady;
        vector<int> ordenados;
        vector<int> gradoE;
    public: 

    Grafo(): n{0} , ady{0} {};
    Grafo<V,A> & operator = (const Grafo<V,A>  & other){
            this->n=0;
            for(int i  = 0 ; i < n; i++)
            {
                for(int j  = 0 ; j < n; j++)
                {
                    ady[i][j] = other[i][j];
                }
            }
    }

    Grafo(vector<vector<A>> x)
    {
        this->crearGrafo(x.size());
        for(int i  = 0 ; i < n; i++)
        {
            for(int j  = 0 ; j < n; j++)
            {
                this->ady[i][j] = x[i][j];
            }
        } 
    }    
    void crearGrafo(int); //que crea un Grafo<V,A>::vacío.
    void insertarNodo(V);
    void veradyacencia();
    void insertarArista(V a , V b , A arista); //inserta una nueva arista con dirección en caso no exista
    void borrarNodo(int a);// que elimina un nodo en caso exista.
    void borrarArista(V a , V b); //que elimina una arista en caso esta exista.
    bool esVacio(); //que retorna true en caso el Grafo<V,A>::sea vacío.
    bool existeNodo(V a);//que comprueba y retorna true si un nodo se encuentra en el
    int caminoMinimo(int a , int b); //que retorna el camino mínimo de existir entre un nodo origen y un nodo destino.
    void ordenTopologico(); //que retorna el orden topológico del Grafo<V,A>::dirigido.
    //importantes
    void indices();
    void gradoEntrada();
    void printgradoEntrada();
    void adyacenciaUno(int a);
    void gradoCero(int i);

    void floyd (vector<vector<A>> & x );
    void floyd ();
    void reordenarmatrix (vector<vector<A>> & x);
    void warshal(vector<vector<A>> & x , V ,V);
    };

    template <class V , class A>
    void Grafo<V,A>::crearGrafo(int N){
        ady.resize(N);
        for(int i = 0 ;i < N; i++)
        {
            ady[i].resize(N);
        }
        n = N;
    }

    template < class V , class A>
    void Grafo<V,A>::insertarNodo(V nodo){
        if(!existeNodo(nodo)) {
            nombres.push_back(nodo);
            mapn[nodo] = nombres.size() - 1;
            cout<<mapn[nodo];
            n = n + 1;
            ady.resize(n);
            for(int i = 0 ;i < n; i++) ady[i].resize(n);
        }
    }

    template < class V , class A>
    void Grafo<V,A>::veradyacencia(){
        for(int i = 0; i < n ; i++)
        {
            for(int j = 0; j < n ; j++)
            {
               cout<<ady[i][j];
            } 
            cout<<endl;
        } 
    }

    template < class V , class A>
    void Grafo<V,A>::insertarArista(V a , V b , A arista)
    {
        cout<<"seco";
            int pa = mapn[a];
            cout<<pa;
            int pb = mapn[b];
            cout<<pb;
            if (ady[pa][pb] == 0) ady[pa][pb] = arista;
        
    }

    template < class V , class A>
    void Grafo<V,A>::borrarNodo(V a)
    {
          for(int i = 0 ; i < n ; i++)
          {
              if(nombres[i] == a)
              {
                  
              }
          }
    }
    template < class V , class A>
    void Grafo<V,A>::borrarArista(V a , V b)
    {
        if(existeNodo(a) && existeNodo(b))
        {
            int pa = mapn[a];
            int pb = mapn[b];
            if (ady[pa][pb] != 0) ady[pa][pb] = 0;
        }
    }
    template < class V , class A>
    bool Grafo<V,A>::esVacio()
    {
        if(nombres.empty()) return true;
        return false;
    }

    template < class V , class A>
    bool Grafo<V,A>::existeNodo(V a)
    {
        if(mapn.find(a) != mapn.end()) return true;
        else return false;
    }

    template < class V , class A>
    void Grafo<V,A>::floyd (vector<vector<A>> & x)
    {
        
        x.resize(n);
        for(int i = 0 ;i < n; i++) x[i].resize(n);
        
        for(int i = 0; i < n ; i++) {
            for(int j = 0; j < n ; j++)   
                x[i][j] = ady[i][j]; } 

        for(int i = 0; i < n  ; i++)
        {
            for(int j = 0; j < n ; j++)
            {
                for(int k = 0; k < n ; k++)
                {
                    if(x[i][j] || (x[i][k] && x[k][j]))
                    {
                        x[i][j] = 1;
                    }
                }  
            } 
        }
    }

    template < class V , class A>
    void Grafo<V,A>::reordenarmatrix(vector<vector<A>> & x)
    {
        float a = std::numeric_limits<float>::infinity();
        x.resize(n);
        for(int i = 0 ;i < n; i++) x[i].resize(n);

        for(int i = 0; i < n ; i++) {
            for(int j = 0; j < n ; j++) 
            {
                if(!ady[i][j]) x[i][j] = a;
                else x[i][j] = ady[i][j];
            }  
        } 
    }

    template < class V , class A>
    void Grafo<V,A>::warshal(vector<vector<A>> & x , V a , V b)
    {
        vector<V> s; 
        reordenarmatrix(x);
        for(int i = 0; i < n  ; i++)
        {
            for(int j = 0; j < n ; j++)
            {
                for(int k = 0; k < n ; k++)
                {
                    x[j][k] = min(x[j][k] , x[j][i] + x[i][k]);
                }  
            } 
        }
    }

    template < class A>
    void print(vector<vector<A>> x){
    for(int i = 0; i < x.size() ; i++)
    {
        for(int j = 0; j < x.size() ; j++)
        {
            cout<<x[i][j]<<" ";
        } 
        cout<<endl;
    } 
    }

    template < class V , class A>
    void Grafo<V,A>::adyacenciaUno(int a){
        //cout<<endl<<"Adyacencia a "<<a<<" son :";
        
        for(int i = 0; i < n ; i++)
        {
            if(ady[a][i]!=0){              
                gradoE[i]=gradoE[i]-1;
                
            }
            if(gradoE[i]==0 && (find(ordenados.begin(), ordenados.end(), mapn[i]) != ordenados.end())==false){
                //cout<<endl<<"HA SIDO INSERTADO: "<<mapn[i]<<endl;
                ordenados.push_back(mapn[i]);

            }
   
        } 
    }
    

    template < class V , class A>
    void Grafo<V,A>::ordenTopologico()
    {
        for(int i=0;i<n;i++){
            if (gradoE[i]==0){
                adyacenciaUno(mapn[i]);
                
            }
            if(gradoE[i]==1) {
                adyacenciaUno(mapn[i]);
            }
        }
        cout<<endl;
        cout<<"Lista de ordenados:  ";
        for(int i=0;i<n;i++){
            
            cout<<ordenados[i]<<"-->";
        }
        cout<<endl;
    }


    template < class V , class A>
    void Grafo<V,A>::indices()
    {
        cout<<"INDICES : ";
        for(int i=0;i<n;i++)
            cout<<nombres[i]<<"indice: "<<mapn[nombres[i]]<<" , ";
        //cout<<endl;  
    }

    template < class V , class A>
    void Grafo<V,A>::gradoEntrada()
    {
        cout<<"INDICES : ";
        
        for(int a=0;a<n;a++){
            cout<<mapn[a]<<" tiene ";
            
                int cont=0;
                for(int j = 0; j < n ; j++){
                    if(ady[j][a]!=0){
                        //cout<<<<" ";
                        cont=cont+1;
                    }
                    
                }
                gradoE.push_back(cont); 
                cout<<cont;
                cout<<endl;

        }      
        
    }

    template < class V , class A>
    void Grafo<V,A>::printgradoEntrada(){
        cout<<"Grado de entrada: ";
        for(int i=0;i<n;i++)
            cout<<gradoE[i]<<",";
    }


int main ()
{
   /* Grafo<int , float > M;
    
    M.insertarNodo(0);
    M.insertarNodo(1);
    M.insertarNodo(2);
    M.insertarNodo(3);
    M.insertarNodo(4);
    M.insertarNodo(5);
    M.insertarArista(0,1,1);
    M.insertarArista(0,2,2);
    M.insertarArista(0,4,3);
    M.insertarArista(1,3,4);
    M.insertarArista(2,1,1);
    M.insertarArista(2,3,2);
    M.insertarArista(3,5,3);
    M.insertarArista(5,4,1);*/
    //M.borrarArista(7,4);

    //otro ejemplo
    /*
    M.insertarNodo(0);
    M.insertarNodo(1);
    M.insertarNodo(2);
    M.insertarNodo(3);
    M.insertarNodo(4);
    M.insertarNodo(5);
    M.insertarNodo(6);

    M.insertarArista(0,2,1);
    M.insertarArista(1,2,2);
    M.insertarArista(1,3,3);
    M.insertarArista(3,5,4);
    M.insertarArista(2,6,1);
    M.insertarArista(2,4,2);
    M.insertarArista(3,5,3);*/


    
    Grafo<string , int > M;
    ifstream archivo("Malla_Curricular.csv");
    string linea;
    char delimitador = ',';
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(archivo, linea);
    // Leemos todas las líneas
    while (getline(archivo, linea))
    {

        stringstream stream(linea); // Convertir la cadena a un stream
        string Codigo,Nombre_Curso,Pre_Req1,Pre_Req2;

        getline(stream, Codigo, delimitador);
        getline(stream, Nombre_Curso, delimitador);
        getline(stream, Pre_Req1, delimitador);
        getline(stream, Pre_Req2, delimitador);
        // Imprimir
        cout << "==================" << endl;
        

        cout << "Codigo: " << Codigo << endl;
        M.insertarNodo(Codigo);
        //cout << "Nombre_Curso: " << Nombre_Curso << endl;
        //cout << "Pre_Req1: " << atoi(Pre_Req1.c_str()) << endl;
        //cout << "Pre_Req2: " << atoi(Pre_Req2.c_str())<< endl;
        
    }
    archivo.close();
    ///////////////////otro
    ifstream archivo2("Malla_Curricular.csv");

    while (getline(archivo2, linea))
    {
        stringstream stream(linea); // Convertir la cadena a un stream
        string Codigo,Nombre_Curso,Pre_Req1,Pre_Req2;
        cout<<"hecho";
        getline(stream, Codigo, delimitador);
        getline(stream, Nombre_Curso, delimitador);
        getline(stream, Pre_Req1, delimitador);
        getline(stream, Pre_Req2, delimitador);
        // Imprimir
        cout << "==================" << endl;
        

        cout << "Codigo: " << Codigo<< endl;
        M.insertarArista(Codigo  , Pre_Req1,1);
        M.insertarArista(Codigo  , Pre_Req2,1);
        //cout << "Nombre_Curso: " << Nombre_Curso << endl;
        //cout << "Pre_Req1: " << atoi(Pre_Req1.c_str()) << endl;
        //cout << "Pre_Req2: " << atoi(Pre_Req2.c_str())<< endl;
        
    }
    archivo2.close();
    cout<<"hecho";
    
    M.veradyacencia();
    M.indices();
    //M.gradoEntrada();
    //M.printgradoEntrada();
    //M.ordenTopologico();
    
    //M.printgradoEntrada();
    //M.adyacenciaUno(3);
    //M.adyacenciaUno(4);
    //M.adyacenciaUno(5);
}