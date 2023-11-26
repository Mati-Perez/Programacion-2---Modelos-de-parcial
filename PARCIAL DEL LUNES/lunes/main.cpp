#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include "parcial2.h"


///GENERAR UN ARCHIVO CON LOS CLIENTES QUE HAYAN REALIZADO UNA COMPRA POR UN IMPORTE SUP A 15000
///CADA REGISTRO DEBE TENER EL CODIGO DE CLIENTE. EL NOMBRE DEL CLIENTE Y LA FECHA DEL TOUR.
///EN CASO DE QUE HAYA MAS DE UNA CMPRA CN ESAS CARACTERISTICAS SE DEBE REGISTRAR LA FECHA DE
///LA PRIMERA

void punto1();
void punto2();
/// punto 4

void mostrarClientes(){
    Cliente reg;
    ArchivoClientes archi("clientes.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
    }
}

void mostrarGuias(){
    Guia reg;
    ArchivoGuias archi("guias.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
    }
}

void mostrarTour(){
    Tour reg;
    ArchivoTours archi("Tours.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
    }
}

void mostrarVentas(){
    Venta reg;
    ArchivoVentas archi("Ventas.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
    }

}

int main()
{
    int opc;
    while(true){
        system("cls");
        cout<<"PARCIAL LUNES"<<endl;
        cout<<"======================="<<endl;
        cout<<"1) PUNTO 1"<<endl;
        cout<<"2) PUNTO 2"<<endl;
        cout<<"6) MOSTRAR CLIENTES"<<endl;
        cout<<"7) MOSTRAR GUIAS"<<endl;
        cout<<"8) MOSTRAR TOUR"<<endl;
        cout<<"9) MOSTRAR VENTAS"<<endl;
        cout<<"======================="<<endl;
        cout<<"0) SALIR"<<endl;
        cout<<"INGRESE UNA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
        case 1:
            punto1();
            break;
        case 2:
            punto2();
            break;
        case 6:
            mostrarClientes();
            break;
        case 7:
            mostrarGuias();
            break;
        case 8:
            mostrarTour();
            break;
        case 9:
            mostrarVentas();
            break;
        case 0:
            return false;
        default:
            cout<<"OPCION INCORRECTA!"<<endl;
            break;
        }
       system("pause");

    }

    return 0;
}


class Punto1{
private:
    char codigoCliente[5];
    char nombre[30];

    Fecha tour;
    bool estado;
public:
    bool operator==(Venta &v){
        if(strcmp(codigoCliente,v.getNumeroDeCliente())==0) return true;
        else return false;
    }

    void Mostrar(){
        cout<<"CODIGO DE CLIENTE: "<<codigoCliente<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"FECHA DEL TOUR: "<<endl;
        tour.Mostrar();
    }


    void setCodigoCliente(const char *cc){strcpy(codigoCliente,cc);}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setEstado(bool a){estado=a;}
    void setTour(Fecha f){tour=f;}

    const char *getCodigoCliente(){return codigoCliente;}
    const char *getNombre(){return nombre;}
    bool getEstado(){return estado;}
    Fecha getTour(){return tour;}
};

class ArchivoPunto1{
private:
    char nombre[30];
public:
    ArchivoPunto1(const char *n){
        strcpy(nombre, n);
    }
    Punto1 leerRegistro(int pos){
        Punto1 reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof reg*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
    int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Punto1);
    }
    bool grabarRegistro(Punto1 reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

Fecha buscarCompra(Punto1 p){
    Venta reg;
    ArchivoVentas archi("Ventas.dat");
    Fecha aux;
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(p==reg && reg.getEstado()){
            if(reg.getImporte()>15000){
                return reg.getFechaVenta();
            }

    }
    aux.setDia(0);
    return aux;

}}

void grabarRegistro(Punto1 reg){
    ArchivoPunto1 archi("punto1.dat");
    archi.grabarRegistro(reg);
}

void mostrarRegistro(){
    Punto1 reg;
    ArchivoPunto1 archi("punto1.dat");
    int tam=archi.contarRegistros();

    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
    }
}

void punto1(){
    Cliente reg;
    ArchivoClientes archi("clientes.dat");

    Punto1 p;

    int tam=archi.contarRegistros();
    Fecha fechita;
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        p.setCodigoCliente(reg.getCodigoCliente());
        p.setNombre(reg.getNombre());
        p.setEstado(true);
        fechita=buscarCompra(p);
        if(fechita.getDia()!=0 && reg.getEstado()){
            p.setTour(fechita);
            grabarRegistro(p);
        }
    }
    mostrarRegistro();
    return;

}











void cargarVector(Punto1 *v){
    Punto1 reg;
    ArchivoPunto1 archi("punto1.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        v[i]=reg;
    }

}

void mostrarVector(Punto1 *v,int tam){
    cout<<"VECTOR DINAMICO PARA PUNTO 2: "<<endl;
    for(int i=0;i<tam;i++){
        v[i].Mostrar();
    }

}



void punto2(){
    Punto1 reg;
    ArchivoPunto1 archi("punto1.dat");
    int tam=archi.contarRegistros();
    if(tam==0){
        cout<<"NO HAY REGISTROS"<<endl;
        return;
    }
    Punto1 *v;
    v=new Punto1[tam];
    if(v==nullptr){
        cout<<"ERROR AL RESERVAR MEMORIA PARA EL VECTOR"<<endl;
        return;
    }
    cargarVector(v);
    mostrarVector(v,tam);

    delete[] v;
    return;
}
