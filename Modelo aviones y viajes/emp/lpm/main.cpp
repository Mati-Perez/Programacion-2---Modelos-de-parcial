#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include "parcial2.h"

class Punto6{
private:
    int codigo;
    char nombre[30];
    int cantidad;

public:
    void setCodigo(int cod){codigo=cod;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setCantidad(int cant){cantidad=cant;}

    int getCodigo(){return codigo;}
    const char *getNombre(){return nombre;}
    int getCantidad(){return cantidad;}

    void Mostrar(){
        cout<<"CODIGO: "<<codigo<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"CANTIDAD: "<<cantidad<<endl<<endl;
    }
};

class ArchivoPunto6{
private:
    char nombre[30];
public:
    ArchivoPunto6(){strcpy(nombre, "punto6.dat");}
    ///--------------------------------------------
    Punto6 leerRegistro(int pos){
        Punto6 reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof(Punto6)*pos,0);
        fread(&reg, sizeof reg,1, p);
        fclose(p);
        return reg;
    }
    ///-----------------------------------------------
    int contarRegistros(){
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return -1;
        fseek(p, 0,2);
        int tam=ftell(p);
        fclose(p);
        return tam/sizeof(Punto6);
    }
    ///****************************
    bool listarArchivo(){
        Punto6 reg;
        FILE *p;
        p = fopen(nombre, "rb");
        if (p == NULL){
        cout << "No se pudo abrir " << endl;
        return false;
        }
        while (fread(&reg, sizeof reg, 1, p)==1 ){
        reg.Mostrar();
        cout << endl;
        }
        fclose(p);
        return true;
        }

    ///ESCRIBIR-------------------------------------------------
    bool escribirRegistro(Punto6 reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }

};



void punto5();
void punto6();
void punto7();
void punto9();

bool Avion::operator ==(const char *c){
    if(strcmp(marca,c)==0) return true;
    else return false;
}

class Punto1{

private:
    int numeroPasajero;
    char nombre[30];
    char telefono[30];
    char direccion[30];
    int provincia;
    bool activo;
public:
    void Mostrar(){
        cout<<numeroPasajero<<"     "<<nombre<<"     "<<telefono<<"     "<<direccion<<"     "<<provincia;
    }

    int getNumeroPasajero(){return numeroPasajero;}
    int getProvincia(){return provincia;}
    const char *getNombre(){return nombre;}
    const char *getTelefono(){return telefono;}
    const char *getDireccion(){return direccion;}
    bool getActivo(){return activo;}

    void setNumeroPasajero(int np){numeroPasajero=np;}
    void setProvincia(int np){provincia=np;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setTelefono(const char *n){strcpy(telefono,n);}
    void setDireccion(const char *n){strcpy(direccion,n);}
    void setActivo(bool a){activo=a;}

};


class ArchivoPunto1{
private:
    char nombre[30];
public:
    ArchivoPunto1(const char *n){
        strcpy(nombre,n);
    }

        ///****************************
    bool listarArchivo(){
        Punto1 reg;
        FILE *p;
        p = fopen(nombre, "rb");
        if (p == NULL){
        cout << "No se pudo abrir " << endl;
        return false;
        }
        while (fread(&reg, sizeof reg, 1, p)==1 ){
        reg.Mostrar();
        cout << endl;
        }
        fclose(p);
        return true;
        }

    ///ESCRIBIR-------------------------------------------------
    bool escribirRegistro(Punto1 reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }

};


void punto1();
bool punto2();
void punto3();
void punto8();


void mostrarPasajes(){
    ArchivoPasajes archi;
    archi.listarArchivo();

}

void mostrarPasajeros(){
    ArchivoPasajeros archi("pasajeros.dat");
    archi.listarArchivo();
}

void mostrarAviones(){
    ArchivoAvion archi;
    archi.listarArchivo();
}
void mostrarV(){
    ArchivoVuelo archi;

    archi.listarArchivo();
}


int main()
{
    int opc;
    while(true){
    system("cls");
    cout<<"************** MODELO PARCIAL **************"<<endl;
    cout<<"*********************************************"<<endl;
    cout<<"1) PUNTO 1"<<endl;
    cout<<"2) PUNTO 2"<<endl;
    cout<<"3) PUNTO 3"<<endl;
    cout<<"4) PUNTO 4"<<endl;
    cout<<"5) PUNTO 5"<<endl;
    cout<<"6) PUNTO 6"<<endl;
    cout<<"7) PUNTO 7"<<endl;
    cout<<"8) PUNTO 8"<<endl;
    cout<<"9) PUNTO 9"<<endl;
    cout<<"10) PUNTO 10"<<endl;
    cout<<"11) PUNTO 11"<<endl;
    cout<<"12) MOSTRAR PASAJES"<<endl;
    cout<<"13) MOSTRAR PASAJEROS"<<endl;
    cout<<"14) MOSTRAR AVIONES"<<endl;
    cout<<"15) MOSTRAR VUELOS"<<endl;

    cout<<"*******************************************"<<endl;
    cout<<"0) SALIR"<<endl<<endl;
    cout<<"SELECCIONE UNA OPCION: ";
    cin>>opc;
    system("cls");
    switch(opc){
    case 1:
        punto1();
        break;
    case 2:
        if(punto2()) cout<<"cambios guardado!";
        else cout<<"error al cambiar la cantidad de asientos"<<endl;
        break;
    case 3:
        punto3();
        break;
    case 5:
        punto5();
        break;
    case 6:
        punto6();
        break;
    case 7:
        punto7();
        break;
    case 8:
        punto8();
        break;
    case 9:
        punto9();
        break;
    case 12:
        mostrarPasajes();
        break;
    case 13:
        mostrarPasajeros();
        break;
    case 14:
        mostrarAviones();
        break;
    case 15:
        mostrarV();
        break;
    case 0:
        return false;
    default:
        cout<<"OPCION INCORRECTA"<<endl;
        break;
    }
    system("pause");}
    return 0;
}


void punto1(){
    bool hayPasaje=false;

    Pasaje ticket;
    ArchivoPasajes archiTicket;
    int cantPasajes=archiTicket.contarRegistros();

    Pasajero persona;
    ArchivoPasajeros archiPersona("pasajeros.dat");
    int cantPasajeros= archiPersona.contarRegistros();

    Punto1 sinPasaje;
    ArchivoPunto1 archiSinPasaje("punto1.dat");

    for(int i=0;i<cantPasajeros;i++){
        hayPasaje=false;
        persona=archiPersona.leerRegistro(i);
        for(int j=0;j<cantPasajes;j++){
            ticket=archiTicket.leerRegistro(j);
            if(persona.getNumeroPasajero()==ticket.getNumeroPasajero() &&persona.getActivo()&&ticket.getActivo()){
                if(ticket.getFechaCompra().getAnio()==2023){
                    hayPasaje=true;
                }
            }
        }
    if(!hayPasaje){
        sinPasaje.setNumeroPasajero(persona.getNumeroPasajero());
        sinPasaje.setNombre(persona.getNombre());
        sinPasaje.setTelefono(persona.getTelefono());
        sinPasaje.setDireccion(persona.getDireccion());
        sinPasaje.setProvincia(persona.getProvincia());
        sinPasaje.setActivo(true);
        archiSinPasaje.escribirRegistro(sinPasaje);
    }
    }

    cout<<"PASAJEROS SIN PASAJES EN 2023:"<<endl;
    archiSinPasaje.listarArchivo();

}

bool punto2(){
    Avion reg;
    ArchivoAvion archi;
    int tam=archi.contarRegistros();
    FILE *p=fopen("aviones.dat","rb+");
    if(p==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }

    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg=="Boeing"){
            reg.setCantidadAsientos(reg.getCantidadAsientos()*0.95);
            fseek(p,sizeof(Avion)*i,0);
            fwrite(&reg,sizeof reg,1,p);
        }
    }
    fclose(p);
    return true;
}

void punto3(){
    Avion reg;
    ArchivoAvion archi;
    int tam=archi.contarRegistros();
    int cont=0;
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg.getTipo()==1){
            cont++;
        }
    }
    if(cont==0){
        cout<<"NO HAY AVIONES PROPIOS"<<endl;
        return;
    }
    Avion *v;
    v=new Avion[cont];
    if(v==nullptr){
        cout<<"ERROR AL RESERVAR MEMORIA EN EL ARCHIVO"<<endl;
        return;
    }
    int aux=0;
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg.getTipo()==1){
            v[aux]=reg;
            aux++;
        }
    }

    cout<<"AVIONES DE TIPO PROPIO: "<<endl;
    for(int i=0;i<cont;i++){
        cout<<"Codigo de avion: "<<v[i].getCodigoAvion()<<endl;
        cout<<"Nombre: "<<v[i].getNombre()<<endl;
        cout<<"Marca: "<<v[i].getMarca()<<endl<<endl;
    }
        delete[] v;

        return;

}


///PUNTO 5

void grabarPasajero(Pasajero pas){
    Pasajero reg;
    ArchivoPasajeros archi("punto5.dat");
    archi.escribirRegistro(pas);
}

void buscarPasajero(int num){
    Pasajero reg;
    ArchivoPasajeros archi("pasajeros.dat");
    int cant=archi.contarRegistros();
    for(int i=0;i<cant;i++){
        reg=archi.leerRegistro(i);
        if(reg.getNumeroPasajero()==num){
            grabarPasajero(reg);
        }
    }

}

void mostrarPasajeros2023(){
    Pasajero reg;
    ArchivoPasajeros archi("punto5.dat");
    cout<<"PASAJEROS CON PASAJES PARA EL PRESENTE ANIO: "<<endl;
    archi.listarArchivo();

}


void punto5(){
    Pasaje reg;
    ArchivoPasajes archi;
    int tam=archi.contarRegistros();
    bool existen=false;

    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg.getFechaCompra().getAnio()==2022){
            buscarPasajero(reg.getNumeroPasajero());
            existen=true;
        }

    }
    if(existen) mostrarPasajeros2023();
    else cout<<"NO EXISTEN PASAJEROS CON PASAJES PARA EL PRESENTE ANIO"<<endl;


}


///PUNTO 6

int buscar(int cod){
    Pasaje reg;
    ArchivoPasajes archi;
    int tam=archi.contarRegistros();
    int v=0;
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(cod==reg.getCodigoAvion()){
                v++;}

    }
return v;
}


void grabarRegistro(Avion av,int vuelos){
    Punto6 reg;
    ArchivoPunto6 archi;
    reg.setCodigo(av.getCodigoAvion());
    reg.setNombre(av.getNombre());
    reg.setCantidad(vuelos);
    archi.escribirRegistro(reg);
}

void mostrarVuelos(){
    Punto6 reg;
    ArchivoPunto6 archi;
    cout<<"CANTIDAD DE VUELOS POR AVIONES: "<<endl;
    archi.listarArchivo();

}


void punto6(){
    Avion reg;
    ArchivoAvion archi;
    int tam=archi.contarRegistros();
    int vuelos;

    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        vuelos=buscar(reg.getCodigoAvion());

        grabarRegistro(reg,vuelos);
    }

    mostrarVuelos();

}



void punto7(){
    Punto6 reg;
    ArchivoPunto6 archi;
    int tam=archi.contarRegistros();
    Punto6 *v;
    v=new Punto6[tam];
    if(v==nullptr){
        cout<<"ERROR AL RESERVAR MEMORIA PARA EL VECTOR"<<endl;
        return;
    }
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        v[i]=reg;
    }

    for(int i=0;i<tam;i++){
        cout<<"VECTOR "<<i+1<<": "<<endl;
        v[i].Mostrar();
    }
delete[] v;
}


///PUNTOS DEL PARCIAL

class Punto8{
private:
    char codigoVuelo[5];
    char nombre[30];
    int pasajeros;
public:

    void Mostrar(){
        cout<<"CODIGO DE VUELO: "<<codigoVuelo<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"CANTIDAD DE PASAJEROS: "<<pasajeros<<endl<<endl;
    }

    const char* getCodigoVuelo(){return codigoVuelo;}
    const char* getNombre(){return nombre;}
    int getPasajeros(){return pasajeros;}


    void setCodigoVuelo(const char *cv){strcpy(codigoVuelo, cv);}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setPasajeros(int d){pasajeros=d;}
};

class ArchivoPunto8{
private:
    char nombre[30];
public:
    ArchivoPunto8(){strcpy(nombre,"punto8.dat");}
    ///-----------------------------------------
    Punto8 leerRegistro(int pos){
        Punto8 reg;
        FILE *p;
        p=fopen(nombre, "rb");
        if(p==NULL) return reg;
        fseek(p, sizeof(Punto8)*pos,0);
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
        return tam/sizeof(Punto8);
    }
        ///****************************
    bool listarArchivo(){
        Punto8 reg;
        FILE *p;
        p = fopen(nombre, "rb");
        if (p == NULL){
        cout << "No se pudo abrir " << endl;
        return false;
        }
        while (fread(&reg, sizeof reg, 1, p)==1 ){
        reg.Mostrar();
        cout << endl;
        }
        fclose(p);
        return true;
        }

    ///ESCRIBIR-------------------------------------------------
    bool escribirRegistro(Punto8 reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }


};

bool buscar2(int cod){
    Avion reg;
    ArchivoAvion archi;
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(cod==reg.getCodigoAvion()){
            if(strcmp(reg.getMarca(),"Embraer")){
                return true;
            }
        }
    }
return false;
}

bool empraer(const char* cod){
    Pasaje reg;
    ArchivoPasajes archi;
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(strcmp(reg.getCodigoVuelo(),cod)){
            return(buscar2(reg.getCodigoAvion()));
        }
    }
return false;
}

int buscarCantidad(const char* c){
    Pasaje reg;
    int cont=0;
    ArchivoPasajes archi;
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(strcmp(reg.getCodigoVuelo(),c)==0){
            cont++;
        }
    }
return cont;
}

void grabarPunto8(Vuelo v){
    Punto8 reg;
    ArchivoPunto8 archi;
    int cant=buscarCantidad(v.getCodigoVuelo());
    reg.setCodigoVuelo(v.getCodigoVuelo());
    reg.setNombre(v.getNombre());
    reg.setPasajeros(cant);
    archi.escribirRegistro(reg);
}

void mostrarPunto8(){
    ArchivoPunto8 archi;
    cout<<"AVIONES EMBRAER QUE HAYAN TENIDO VUELOS CHARTER: "<<endl;
    archi.listarArchivo();

}

void punto8(){
    Vuelo reg;
    ArchivoVuelo archi;
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg.getTipoViaje()==2){
            if(empraer(reg.getCodigoVuelo())){
                grabarPunto8(reg);
            }
        }
    }
    mostrarPunto8();

}

///DAR DE BAJA A TODOS LOS VUELOS DE TIPO PROMOCION 4

bool modificarRegistro(int pos, Vuelo reg){

    FILE *p=fopen("vuelos.dat","rb+");
    if(p==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }


    fseek(p,sizeof(Avion)*pos,0);
    bool escribio=fwrite(&reg,sizeof reg,1,p);
    fclose(p);
    return escribio;
}

void punto9(){
    Vuelo reg;
    ArchivoVuelo archi;
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg.getTipoViaje()==4){
            reg.setActivo(false);
            modificarRegistro(i,reg);
        }

    }

cout<<"CAMBIOS REALIZADOS!"<<endl;
}
