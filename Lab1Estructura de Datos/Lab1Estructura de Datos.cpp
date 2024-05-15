
#include <iostream>
#include <json/json.h>
#include <string>
#include <fstream>
#include <list>
#include "Apartment.h"



using namespace std;


/**
* @brief Verificar igualdad entre dos objetos de puntuación
*
* Esta función compara dos objetos de puntuación (Score) para determinar si son iguales.
* Compara los valores máximos, mínimos y totales de las puntuaciones y retorna true si son
* iguales en todos los aspectos, o false en caso contrario.
*
* @param No1 Primer objeto de puntuación a comparar.
* @param No2 Segundo objeto de puntuación a comparar.
* @return true si los objetos de puntuación son iguales en todos los aspectos, o false en caso contrario.
*/
bool Equals(Score No1, Score No2)
{
    // Compara los valores máximos, mínimos y totales de las puntuaciones
    if (No1.GetMax() == No2.GetMax() && No1.GetMin() == No2.GetMin() && No1.GetTotal() == No2.GetTotal())
    {
        return true; // Retorna true si son iguales en todos los aspectos
    }
    else
    {
        return false; // Retorna false si hay alguna diferencia en las puntuaciones
    }
}







 /**
  * @brief Buscar Apartamento más cercano a un negocio dado
  *
  * Esta función busca el apartamento más cercano a un negocio específico en un
  * mapa de apartamentos, a partir de un índice dado en el mapa. Calcula la cantidad
  * de pasos necesarios para llegar al negocio desde el apartamento en ambas direcciones
  * (hacia arriba y hacia abajo en el mapa), y retorna la cantidad mínima de pasos requeridos.
  *
  * @param Mapa Vector que contiene los apartamentos disponibles en el mapa.
  * @param negocio Nombre del negocio que se desea encontrar.
  * @param index Índice del apartamento desde el cual comenzar la búsqueda en el mapa.
  * @return La cantidad mínima de pasos necesarios para llegar al negocio desde el apartamento
  *         especificado. Si no se encuentra el negocio en ningún apartamento, se retorna -1.
  */
 int BuscarApartamento(vector<Apartment> Mapa, string negocio, int index)
 {
     // Inicialización de pasos que debe recorrer hacia arriba y hacia abajo
     int pasosBack = -1;
     int pasosFront = -1;

     // Lista temporal de strings para almacenar los negocios de cada apartamento
     list<string> Temp;

     // Iterador que recorre el mapa de apartamentos del índice seleccionado hacia atrás
     auto it = Mapa.begin() + index;
     while (it >= Mapa.begin())
     {
         Temp = it->getBusiness();

         // Verifica si el negocio está presente en el apartamento actual
         if (find(Temp.begin(), Temp.end(), negocio) != Temp.end())
         {
             // Obtiene la distancia desde el apartamento hasta el negocio
             pasosBack = distance(it, Mapa.begin() + index);
             break;
         }

         // Verifica si hemos alcanzado el principio del vector
         if (it == Mapa.begin()) {
             // Realiza la comparación con el primer elemento
             Temp = it->getBusiness();
             if (find(Temp.begin(), Temp.end(), negocio) != Temp.end()) {
                 // Obtiene la distancia desde el apartamento hasta el negocio
                 pasosBack = distance(it, Mapa.begin() + index);
             }
             break;
         }

         --it;
     }

     // Iterador que recorre el mapa de apartamentos del índice seleccionado hacia adelante
     auto it2 = Mapa.begin() + index;
     while (it2 <= Mapa.end())
     {
         // Verifica si hemos alcanzado el final del vector
         if (it2 == Mapa.end())
         {
             // Verifica si el negocio está presente en el apartamento actual
             if (find(Temp.begin(), Temp.end(), negocio) != Temp.end())
             {
                 // Obtiene la distancia desde el apartamento hasta el negocio
                 pasosFront = distance(Mapa.begin() + index, it2);
             }
             break;
         }

         Temp = it2->getBusiness();

         // Verifica si el negocio está presente en el apartamento actual
         if (find(Temp.begin(), Temp.end(), negocio) != Temp.end())
         {
             // Obtiene la distancia desde el apartamento hasta el negocio
             pasosFront = distance(Mapa.begin() + index, it2);
             break;
         }

         ++it2;
     }

     // Si no encontró un negocio en un recorrido hacia abajo o hacia arriba, devuelve el máximo de los dos
     if (pasosFront == -1 || pasosBack == -1)
     {
         return max(pasosBack, pasosFront);
     }
     // Si no se encontró el negocio en el mapa, retorna -1
     else if (pasosFront == -1 && pasosBack == -1)
     {
         return -1;
     }

     // Retorna la cantidad mínima de pasos necesarios para encontrar el negocio
     return min(pasosBack, pasosFront);
 }










/**
 * Recomendación de apartamento basada en la cercanía a negocios
 *
 * Esta función recomienda un apartamento dentro de un mapa de apartamentos
 * basándose en la cercanía a una lista de negocios dados. Calcula la cantidad
 * mínima de pasos necesarios para visitar todos los negocios desde cada apartamento,
 * y selecciona el apartamento con el menor total de pasos como el recomendado.
 * Si hay varios apartamentos con la misma cantidad mínima de pasos, se selecciona
 * el que tenga la menor cantidad de pasos máxima en su recorrido.
 *
 * @param Mapa: Vector que contiene los apartamentos disponibles para recomendación.
 * @param B: Vector de strings que representa la lista de negocios a visitar.
 * @return; El índice del apartamento recomendado en el vector Mapa. Si no se puede
 *         encontrar un apartamento que permita visitar todos los negocios, se retorna -1.
 *  y se coloca un espacio vacío.
 */

int Recomendacion(vector<Apartment> &Mapa, vector<string> B)
{   
    //Inicialización de variables comparativas
    int MinPasos = numeric_limits<int>::max(); // Cantidad mínima de pasos (Total de pasos del Apartamento Recomendado)
    int BestIndex = -1; // Índice del apartamento recomendado
    int BestMaxpasitos = 0; // Máxima cantidad de pasos en el recorrido recomendado
    int BestMinpasitos = 0; // Mínima cantidad de pasos en el recorrido recomendado


    //Recorre el mapa de apartamentos
    for(int i = 0; i < Mapa.size(); i++)
    {
        //Inicialización de variables contadoras de pasos
        int totalPasos = 0; // Total de pasos en el recorrido desde este apartamento
        int Maxpasitos = 0; // Máxima cantidad de pasos en el recorrido desde este apartamento
        int Minpasitos = numeric_limits<int>::max(); // Mínima cantidad de pasos en el recorrido desde este apartamento

        //Foreach que recorre el vector de negocios
        for(const string& negocio:B)
        {
            // Calcula la cantidad de pasos necesarios para encontrar un negocio desde este apartamento
            int pasitos = BuscarApartamento(Mapa,negocio,i);

            // Detiene la función si no se encontró un negocio desde este apartamento
            if(pasitos == -1)
            {
               
                return -1;
            }

            // Registra la mayor cantidad de pasos por recorrido desde este apartamento
            if(pasitos > Maxpasitos)
            {
                Maxpasitos = pasitos;
            
            }

            // Registra la menor cantidad de pasos por recorrido desde este apartamento
            if(pasitos < Minpasitos)
            {
            
                Minpasitos = pasitos;
            
            }

            
        
            // Realiza la sumatoria de pasos desde este apartamento
            totalPasos += pasitos;

        }

        // Crea un objeto Score que representa la puntuación del apartamento actual
        Score score(Maxpasitos, Minpasitos, totalPasos);

        // Asigna la puntuación al apartamento actual en el mapa
        Mapa[i].setPuntaje(score);

        // Compara la cantidad total de pasos para cada apartamento
        if(totalPasos < MinPasos)
        {
            /// Si es menor, el apartamento Actual  se vuelve el "Recomendado"
            MinPasos = totalPasos;
        
            BestIndex = i;

            BestMaxpasitos = Maxpasitos;

            BestMinpasitos = Minpasitos;            
         
        }else if(totalPasos == MinPasos)
        {
            // Si hay varios apartamentos con la misma cantidad total de pasos
           if(Maxpasitos < BestMaxpasitos) // Verifica la máxima cantidad de pasos recorridos en ambos apartamentos
           {
               // Si la máxima cantidad de pasos del apartamento actual es menor que el "Recomendado",
                // se declara el nuevo "Recomendado"
               MinPasos = totalPasos;

               BestIndex = i;

               BestMaxpasitos = Maxpasitos;

               BestMinpasitos = Minpasitos;

             
            
           }else if(Maxpasitos == BestMaxpasitos && Minpasitos < BestMinpasitos)
           {
               // Si hay varios apartamentos con la misma cantidad total y máxima de pasos
                   // pero menor cantidad mínima de pasos, se selecciona el que tiene la menor cantidad mínima de pasos de los apartamentos comparados
                   MinPasos = totalPasos;

                   BestIndex = i;

                   BestMaxpasitos = Maxpasitos;

                   BestMinpasitos = Minpasitos;

                   
               
           }
        }       
    }

  

    //Regresa el Indice del Apartamento recomendado
    return BestIndex;

}






/**
 * @brief Obtener resultados de apartamentos con puntuaciones similares al recomendado
 *
 * Esta función busca en el mapa de apartamentos aquellos que tengan puntuaciones similares
 * a la del apartamento recomendado, identificado por su índice BestIndex. Compara las puntuaciones
 * del apartamento recomendado con las de los demás apartamentos en el mapa y devuelve una lista de
 * índices de los apartamentos que tienen puntuaciones iguales.
 *
 * @param Mapa Vector que contiene los apartamentos disponibles para búsqueda.
 * @param BestIndex Índice del apartamento recomendado en el mapa.
 * @return Una lista de índices de apartamentos que tienen puntuaciones iguales a la del apartamento
 *         recomendado. Si no se recomienda ningún apartamento (BestIndex == -1), se devuelve una lista vacía.
 */
list<int> Resultados(vector<Apartment>& Mapa, int BestIndex)
{
    // Lista para almacenar los índices de los apartamentos que tienen puntuaciones iguales a la del recomendado
    list<int> Coincidencias;

    // Verifica si no se recomendó ningún apartamento
    if (BestIndex == -1)
    {
        return Coincidencias; // Retorna la lista vacía
    }

    // Recorre el mapa de apartamentos para comparar las puntuaciones
    for (int i = 0; i < Mapa.size(); i++)
    {
        // Compara las puntuaciones del apartamento recomendado con las del apartamento actual
        if (Equals(Mapa[BestIndex].getPuntaje(), Mapa[i].getPuntaje()))
        {
            // Si las puntuaciones son iguales, agrega el índice del apartamento actual a la lista de coincidencias
            Coincidencias.push_back(i);
        }
    }

    // Retorna la lista de índices de apartamentos con puntuaciones iguales
    return Coincidencias;
}







template<typename T>

    void EmptyVector(vector<T> &vector )
    {
        vector.clear();
    }




int main()
{ 
    //Inicializaciónd de variables de ruta de archivo
    string ruta;
    bool open = false;
    ifstream file;
    ofstream Archivo;
    string ruta2;

    //Bucle While que impide el avance del programa, hasta que no se haya completado la lectura del archivo JSON Line
    do
    {
        cout << "Ingrese la ruta de archivo del archivo JSON Line (sin comillas)" << endl;

        cin >> ruta;

        //Lee el Json Line
        file.open(ruta,ios::in);

        cin.clear();

        system("cls");

        cout << "Error al abrir archivo" << endl;
        
    } while (!file.is_open());

    system("cls");

    do
    {
        
        cout << "Ingrese la direccion donde desea exportar los apartamentos recomendados (sin comillas)" << endl;
        cin >> ruta2;

        Archivo.open(ruta2 + "/Output.txt");

       
        cin.clear();

        system("cls");

        cerr << "No se pudo generar el Archivo.text" << endl;

    } while (Archivo.fail());

    system("cls");

	// Crea un lector de JSON
	Json::Reader reader;
	Json::Value json;

    //String que representa cada linea del archivo
    string line;


    // Lee el archivo línea por línea
    while (getline(file, line))
    {
   
        // Parsea la línea JSON
        bool parsed = reader.parse(line, json, false);

        //Valida si se pudo parsear la línea JSON
        if (!parsed) {
            cerr << "Error al analizar la línea JSON: " << reader.getFormattedErrorMessages() << endl;
            return 1;
        }


        //Separa la linea JSON en dos inputs
        const Json::Value input1Array = json["input1"];
        const Json::Value input2Array = json["input2"];


        //Inicializa el vector de Apartamentos y de parámetros
        vector<Apartment> Map;

        vector<string> input2;

        list<int> resultado;

        //Recorre cada elemento del Array: Input 1
        for (const auto& item : input1Array) 
        {  
            //Crea una lista temporal de negocios
            list<string> negocios;
       
            //Recorre el listado de nombres del elemento 
            for(const auto& itemB : item.getMemberNames())
            {

                if(item[itemB].asBool())//Verifica que el negocio se encuentre en el apartamento
                {
                    //Si se encuentra, agrega el negocio al listado 
                    negocios.push_back(itemB);

                }
            }
            
            //Crea una instancia de la clase Apartment,teniendo la lista temporal de negocios como parámetro
            Apartment apartment(negocios);

            //Añade el apartamento al mapa de apartamentos
            Map.push_back(apartment);
            
        }

        //Recorre cada elemento del input 2, y lo añade al vector de parámetros
        for (const auto& item : input2Array) {
            
            input2.push_back(item.asString());
        }
            
        //Declara una variable con el resultado del índice del apartamento "Recomendado"
        resultado = Resultados(Map,Recomendacion(Map, input2));

      
  
            Archivo << "[";
            cout << "[";

            if(!resultado.empty())
            {
                auto iter = resultado.begin();

                Archivo << *iter;
                cout << *iter;
                ++iter;

                for(; iter != resultado.end(); ++iter)
                {
                    cout << "," << *iter;   
                    Archivo << "," << *iter;
                }
                resultado.pop_front();
            }

            Archivo << "]" << endl;
            cout <<  "]" << endl;
        
        
        //Vacia los vectores 
        EmptyVector(Map);

        EmptyVector(input2);
                    
       
    }

    // Cerrar el archivo
    file.close();
    Archivo.close();
}

