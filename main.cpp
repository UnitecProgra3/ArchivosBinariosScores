#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
using namespace std;

class Puntaje
{
public:
    string nombre;
    int puntaje;
    Puntaje(string nombre, int puntaje)
    {
        this->nombre = nombre;
        this->puntaje = puntaje;
    }
};

list<Puntaje*> puntajes;

int main()
{
    int opcion;
    do
    {
        cout<<"Menu de puntajes"<<endl;
        cout<<"1 Ingresar"<<endl;
        cout<<"2 Imprimir"<<endl;
        cout<<"3 Guardar todos"<<endl;
        cout<<"4 Guardar uno solo"<<endl;
        cout<<"5 Cargar todos"<<endl;
        cout<<"6 Cargar uno solo"<<endl;
        cout<<"7 Salir"<<endl;
        cout<<"Opcion: "<<endl;
        cin>>opcion;

        switch(opcion)
        {
            case 1://Ingresar
            {
                string nombre;
                int puntaje;
                cout<<"Nombre: ";
                cin>>nombre;
                cout<<"Puntaje: ";
                cin>>puntaje;
                puntajes.push_back(new Puntaje(nombre,puntaje));
                break;
            }
            case 2://Imprimir
            {
                for(list<Puntaje*>::iterator i = puntajes.begin();
                        i!=puntajes.end();
                        i++)
                    cout<<(*i)->nombre<<": "<<(*i)->puntaje<<endl;
                break;
            }
            case 3://Guardar todos
            {
                ofstream out("puntajes.dat");
                for(list<Puntaje*>::iterator i = puntajes.begin();
                        i!=puntajes.end();
                        i++)
                {
                    string nombre = (*i)->nombre;
                    int puntaje = (*i)->puntaje;
                    out.write(nombre.c_str(),15);
                    out.write((char*)&puntaje,4);
                }
                out.close();
                break;
            }
            case 4://Cargar uno solo
            {
                cout<<"Ingrese la posicion en la lista: "<<endl;
                int pos_lista;
                cin>>pos_lista;
                cout<<"Ingrese la posicion en el archivo: "<<endl;
                int pos_archivo;
                cin>>pos_archivo;

                ofstream out("puntajes.dat");
                out.seekp(pos_archivo*19);

                list<Puntaje*>::iterator it = puntajes.begin();
                for(int i=0;i<pos_lista;i++)
                {
                    it++;
                }

                cout<<(*it)->nombre.c_str()<<endl;
                cout<<(*it)->puntaje<<endl;

                out.write((*it)->nombre.c_str(),15);
                out.write((char*)&(*it)->puntaje,4);
            }
            case 5://Cargar todos
            {
                ifstream in("puntajes.dat");
                in.seekg(0,ios::end);
                int tamano = in.tellg();
                in.seekg(0);
                while(in.tellg()<tamano)
                {
                    char* nombre = new char[15];
                    int puntaje;
                    in.read(nombre,15);
                    if(nombre)
                    in.read((char*)&puntaje,4);
                    puntajes.push_back(new Puntaje(nombre,puntaje));
                }
                break;
            }
            case 6:
            {
                cout<<"Posicion: ";
                int pos_cargar;
                cin>>pos_cargar;

                if(pos_cargar<0)
                {
                    cout<<"Posicion invalida"<<endl;
                    break;
                }

                ifstream in("puntajes.dat");

                in.seekg(0,ios::end);
                if(pos_cargar*19>in.tellg())
                {
                    cout<<"Posicion invalida"<<endl;
                    break;
                }

                in.seekg(0);
                in.seekg(pos_cargar*19);

                char* nombre=new char[15];
                int puntaje;

                in.read(nombre,15);
                in.read((char*)&puntaje,4);

                puntajes.push_back(new Puntaje(nombre,puntaje));
            }
        }

    }while(opcion!=7);

    return 0;
}
