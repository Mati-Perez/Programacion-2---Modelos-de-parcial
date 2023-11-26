#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include "parcial2.h"

class Tonelada {
private:
    char codigo[6];
    char nombre[30];
    float cantidad;
    bool estado;

public:

    void Mostrar() {
        cout << "Codigo de empresa: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Cantidad: " << cantidad << endl;
    }

    const char* getCodigo() { return codigo; }
    const char* getNombre() { return nombre; }
    float getCantidad() { return cantidad; }
    bool getEstado() { return estado; }

    void setCodigo(const char* c) { strcpy(codigo, c); }
    void setNombre(const char* n) { strcpy(nombre, n); }
    void setCantidad(float t) { cantidad = t; }
    bool setEstado(bool e){estado=e;}
};

class ArchivoTonelada{
private:
    char nombre[30];

public:
    ArchivoTonelada(const char *t) {
        strcpy(nombre,t);
    }

    Tonelada leerRegistro(int pos) {
        Tonelada reg;
        FILE* p;
        p = fopen(nombre, "rb");
        if (p == NULL) return reg;
        fseek(p, sizeof(Tonelada) * pos, 0);
        fread(&reg, sizeof reg, 1, p);
        fclose(p);
        return reg;
    }

    int contarRegistros() {
        FILE* p;
        p = fopen(nombre, "rb");
        if (p == NULL) return -1;
        fseek(p, 0, 2);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Tonelada);
    }
    ///********************************************************
    bool listarArchivo(){
        Tonelada reg;
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

    bool escribirRegistro(Tonelada reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }
    ///*********************************************************
};


void punto1(){
    Tonelada ton;
    ArchivoTonelada archiT("Tonelada.dat");

    Empresa emp;
    ArchivoEmpresa archiE("Empresa.dat");
    int cantEmp=archiE.contarRegistros();

    Cosecha cos;
    ArchivoCosecha archiC("Cosecha.dat");
    int cantCos=archiC.contarRegistros();

    int cantidad;

    for(int i=0;i<cantEmp;i++){
        cantidad=0;
        emp=archiE.leerRegistro(i);
        for(int j=0;j<cantCos;j++){
            cos=archiC.leerRegistro(j);
            if(strcmp(emp.getCodigoEmpresa(),cos.getCodigoEmpresa())==1){
                cantidad=cantidad+cos.getToneladasCosechadas();
            }
        }
        ton.setCodigo(emp.getCodigoEmpresa());
        ton.setNombre(emp.getNombre());
        ton.setCantidad(cantidad);
        ton.setEstado(true);
        archiT.escribirRegistro(ton);
    }
    system("cls");
    cout<<"NUEVO ARCHIVO GENERADO: "<<endl;
    archiT.listarArchivo();


}

void mostrarEmpresas(){
    Empresa reg;
    ArchivoEmpresa archi("empresa.dat");
    cout<<"EMPRESAS: "<<endl;
    archi.listarArchivo();
}


void mostrarCosechas(){
    Cosecha reg;
    ArchivoCosecha archi("cosecha.dat");
    cout<<"COSECHAS: "<<endl;
    archi.listarArchivo();

}

void punto2(){
    Cosecha reg;
    ArchivoCosecha archi("cosecha.dat");
    int tam=archi.contarRegistros();
    int meses[12]={0};

    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        if(reg.getCodigoCereal()==10){
        meses[reg.getFecha().getMes()-1]=meses[reg.getFecha().getMes()-1]+reg.getToneladasCosechadas();
    }}
    int mayor=meses[0];
    int mes=0;
    for(int i=0;i<12;i++){
        if(mayor<meses[i]){
            mayor=meses[i];
            mes=i;
        }
    }
    cout<<"EL MES CON MAYOR CNTIDAD DE TONELADAS COSECHADAS DE CEREAL TIPO 10 ES EL MES "<<mes+1<<endl<<endl;

}

void punto3(){
    Tonelada ton;
    ArchivoTonelada archiT("Tonelada.dat");

    Empresa emp;
    ArchivoEmpresa archiE("Empresa.dat");
    int cantEmp=archiE.contarRegistros();

    Cosecha cos;
    ArchivoCosecha archiC("Cosecha.dat");
    int cantCos=archiC.contarRegistros();

    int cantidad;



    Tonelada *v;
    int tam = archiE.contarRegistros();
    if(tam==0){
        cout<<"NO HAY REGISTROS DE EMPRESAS EN EL ARCHIVO"<<endl;
        return;
    }
    v=new Tonelada[tam];
    if(v==nullptr){
        cout<<"ERROR AL RESERVAR MEMORIA PARA EL VECTOR"<<endl;
        return;
    }

    for(int i=0;i<tam;i++){
        cantidad=0;
        emp=archiE.leerRegistro(i);
        for(int j=0;j<cantCos;j++){
            cos=archiC.leerRegistro(j);
            if(strcmp(emp.getCodigoEmpresa(),cos.getCodigoEmpresa())==1){
                cantidad=cantidad+cos.getToneladasCosechadas();
            }
        }
        v[i].setCodigo(emp.getCodigoEmpresa());
        v[i].setNombre(emp.getNombre());
        v[i].setCantidad(cantidad);
        v[i].setEstado(true);
        archiT.escribirRegistro(ton);
    }
    system("cls");
    cout<<"NUEVO ARCHIVO GENERADO: "<<endl;
    for(int i=0;i<tam;i++){
        v[i].Mostrar();
        cout<<endl<<endl;
    }
    delete[] v;
}

bool modificarRegistro(Cosecha reg, int pos){
    FILE *p=fopen("cosecha.dat","rb+");
    if(p==NULL){
        cout<<"ERROR DE ARCHIVO"<<endl;
        return false;
    }


    fseek(p,sizeof(Cosecha)*pos,0);
    bool escribio=fwrite(&reg,sizeof reg,1,p);
    fclose(p);
    return escribio;
}

void punto4(){
    Cosecha reg;
    ArchivoCosecha archi("cosecha.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.setToneladasCosechadas(reg.getToneladasCosechadas()*1000);
        modificarRegistro(reg,i);
    }
}


int main()
{

    int opc;

    while(true){
        system("cls");
        cout<<"MENU"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"1) PUNTO 1"<<endl;
        cout<<"2) MOSTRAR EMPRESAS"<<endl;
        cout<<"3) MOSTRAR COSECHAS"<<endl;
        cout<<"4) PUNTO 2"<<endl;
        cout<<"5) PUNTO 3"<<endl;
        cout<<"6) punto 4"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"0) SALIR"<<endl;
        cout<<endl;
        cout<<"INGRESE UNA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
        case 1:
            punto1();
            break;
        case 2:
            mostrarEmpresas();
            break;
        case 3:
            mostrarCosechas();
            break;
        case 4:
            punto2();
            break;
        case 5:
            punto3();
            break;
        case 6:
            punto4();
            break;
        case 0:
            return false;
        default:
            cout<<"OPCION INCORRECTA"<<endl;
            break;
        }
        system("pause");
    }
    return 0;
}

//bool Empresa::operator ==(Cosecha c){
//    if(strcmp(codigoEmpresa,c.getCodigoEmpresa())) return true;
//    else return false;
//}
