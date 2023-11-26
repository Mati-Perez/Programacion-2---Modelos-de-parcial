#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include "parcial2.h"

void punto1();
void punto2();

//************
void mostrarSocios(){
    Socio reg;
    ArchivoSocios archi("socios.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
        cout<<endl<<endl;
    }
}

void mostrarTurnosPosta(){
    Turno reg;
    ArchivoTurnos archi("turnos.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
        cout<<endl<<endl;
    }
}

void cargarSocios(){
    Socio reg;
    ArchivoSocios archi("socios.dat");
    reg.Cargar();
    archi.grabarRegistro(reg);
}

void cargarTurnos(){
    Turno reg;
    ArchivoTurnos archi("turnos.dat");
    reg.Cargar();
    archi.grabarRegistro(reg);}





//*************
int main()
{
    //********
    int opc;
    while(true){
            system("cls");
        cout<<"MENU"<<endl;
        cout<<"1) PUNTO 1"<<endl;
        cout<<"2) PUNTO 2"<<endl;
        cout<<"3) MOSTRAR SOCIOS"<<endl;
        cout<<"4) MOSTRAR TURNOS"<<endl;
        cout<<"5) CARGAR SOCIOS"<<endl;
        cout<<"6) CARGAR TURNOS"<<endl;
        cout<<"0) SALIR"<<endl;
        cout<<"ingrese una opcion: "<<endl;
        cin>>opc;
        system("cls");
        switch(opc){
        case 1:
            punto1();
            break;
        case 2:
            punto2();
            break;
        case 3:
            mostrarSocios();
            break;
        case 4:
            mostrarTurnosPosta();
            break;
        case 5:
            cargarSocios();
            break;
        case 6:
            cargarTurnos();
            break;
        case 0:
            return false;
        default:
            cout<<"OPCION INCORRECTA"<<endl;
            break;
        }
        system("pause");



    }

    /*
    punto1();
    punto2();*/
    cout<<endl;
    return 0;
}

///PUNTO 1 ***************
///CLASE
class Punto1{
private:
    char codigoSocio[5];
    char nombre[30];
    Fecha Fturno;
    bool estado;
public:

    ///SOBRECARGA DE OPERADOR-------------------------------------
    bool operator==(Turno t){
        if(strcmp(codigoSocio,t.getCodigoSocio())==0) return true;
        return false;
    }
    ///----------------------------------------------------------

    void Mostrar(){
        cout<<"CODIGO DE SOCIO: "<<codigoSocio<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"FECHA DE TURNO: "<<endl;
        Fturno.Mostrar();
        cout<<endl<<endl;
    }


    void setCodigoSocio(const char *cs){strcpy(codigoSocio,cs);}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setEstado(bool a){estado=a;}
    void setTurno(Fecha f){Fturno=f;}

    const char *getCodigoSocio(){return codigoSocio;}
    const char *getNombre(){return nombre;}
    bool getEstado(){return estado;}
    Fecha getTurno(){return Fturno;}

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
        reg.setEstado(0);
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

Fecha buscarTurno(Punto1 p){
    Turno reg;
    ArchivoTurnos archi("turnos.dat");
    Fecha fechita;
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if (reg.getEstado() && p==reg && reg.getImporte()<15000){
            return reg.getFechaTurno();
        }
    }
    fechita.setDia(0);
    return fechita;
}

void nuevoRegistro(Punto1 reg){
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
    Socio reg;
    ArchivoSocios archi("socios.dat");
    int tam=archi.contarRegistros();

    Punto1 pun;
    ArchivoPunto1 archiP("punto1.dat");

    Fecha aux;
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg.getEstado()){
            pun.setCodigoSocio(reg.getCodigoSocio());
            pun.setNombre(reg.getNombre());
            aux=buscarTurno(pun);
            if(aux.getDia()!=0){
                pun.setTurno(aux);
                nuevoRegistro(pun);
            }
        }
    }
    cout<<"***** PUNTO 1 ******"<<endl;
    mostrarRegistro();
    system("pause");
}

///**************************************
/// PUNTO 2

int contarTurnos(int a){
    Turno reg;
    ArchivoTurnos archi("turnos.dat");
    int cantTurnos=archi.contarRegistros();
    int tam=0;
    for(int i=0;i<cantTurnos;i++){
        reg=archi.leerRegistro(i);
        if(reg.getFechaTurno().getAnio()==a && reg.getEstado()){
            tam++;
        }
    }
    return tam;
}

void cargarTurnos(Turno *v, int a){
    Turno reg;
    ArchivoTurnos archi("turnos.dat");
    int cantTurnos=archi.contarRegistros();
    int j=0;
    for(int i=0;i<cantTurnos;i++){
        reg=archi.leerRegistro(i);
        if(reg.getFechaTurno().getAnio()==a && reg.getEstado()){
            v[j]=reg;
            j++;
        }

    }

}


void mostrarTurnos(Turno *v,int tam){

    for(int i=0;i<tam;i++){
        cout<<"NUMERO DE TURNO: "<<v[i].getNumeroTurno()<<endl;
        cout<<"CODIGO DE SOCIO: "<<v[i].getCodigoSocio()<<endl;
        cout<<"CODIGO DE ESPECIALIDAD: "<<v[i].getCodigoEspecialidad()<<endl;
        cout<<"ID PERSONAL: "<<v[i].getIDpersonal()<<endl;
        cout<<"IMPORTE: "<<v[i].getImporte()<<endl;
        cout<<"FECHA DEL TURNO: "<<endl;
        v[i].getFechaTurno().Mostrar();
        cout<<endl<<endl;
    }

}


void punto2(){
    int anio;
    cout<<"******* PUNTO 2 *******"<<endl;
    cout<<"INGRESE UN AÑO: ";
    cin>>anio;
    int tam=contarTurnos(anio);

    if(tam==0){
        cout<<"No hay registro de turnos para este anio!"<<endl;
        return;
    }

    Turno *v;

    v=new Turno[tam];
    if(v==nullptr){
        cout<<"ERROR AL RESERVAR MEMORIA PARA EL VECTOR"<<endl;
        return;
    }
    cargarTurnos(v,anio);
    cout<<"TURNOS PARA EL ANIO "<<anio<<": "<<endl;
    mostrarTurnos(v, tam);
    delete[] v;
}
