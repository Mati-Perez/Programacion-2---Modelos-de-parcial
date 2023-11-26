#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include "parcial2.h"

void punto1();
void punto2();
void punto3();
void mostrarCompras();
void mostrarMateriales();
void mostrarProveedores();
void punto1F();





class ProveedorSinCompras{
private:
    int numeroProveedor;
    char nombre[30];
    int provincia;
    bool activo;
public:
    void Cargar(){
        cin>>numeroProveedor;
        cargarCadena(nombre,29);
        cin>>provincia;
        activo=true;
    }
    void Mostrar(){
        cout<<"NUMERO DE PROVEEDOR: "<<numeroProveedor<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"PROVINCIA: "<<provincia<<endl;
    }

    int getNumeroProveedor(){return numeroProveedor;}
    int getProvincia(){return provincia;}
    const char *getNombre(){return nombre;}
    bool getActivo(){return activo;}

    void setNumeroProveedor(int np){numeroProveedor=np;}
    void setProvincia(int np){provincia=np;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setActivo(bool a){activo=a;}
};


class ArchivoProveedoresSinCompras{
    private:
        char nombre[30];
    public:
        ArchivoProveedoresSinCompras(const char *n){
            strcpy(nombre, n);
        }
        ProveedorSinCompras leerRegistro(int pos){
            ProveedorSinCompras reg;
            FILE *p=fopen(nombre,"rb");
            if(p==NULL){
                return reg;
            }
            fseek(p, pos * sizeof reg, 0);
            fread(&reg, sizeof reg, 1, p);
            fclose(p);
            return reg;
        }
        int contarRegistros(){
            FILE *p=fopen(nombre,"rb");
            if(p==NULL){
                return -1;
            }
            fseek(p, 0, 2);
            int cant=ftell(p)/sizeof(ProveedorSinCompras);
            fclose(p);
            return cant;
        }
        bool grabarRegistro(ProveedorSinCompras reg){
            FILE *p;
            p=fopen(nombre, "ab");
            if(p==NULL) return false;
            int escribio=fwrite(&reg, sizeof reg,1, p);
            fclose(p);
            return escribio;
        }
};


int main()
{
    int opc;
    while(true){
        system("cls");
        cout<<"====+ MODELO SEGUNDO PARCIAL +===="<<endl;
        cout<<"1) PUNTO 1"<<endl;
        cout<<"2) PUNTO 2"<<endl;
        cout<<"3) PUNTO 3"<<endl;
        cout<<"4) MOSTRAR ARCHIVO COMPRAS GRRR"<<endl;
        cout<<"5) MOSTRAR ARCHIVO MATERIALES GRRR"<<endl;
        cout<<"6) MOSTRAR PROVEEDORES"<<endl;
        cout<<"7) PUNTO 1 DE FRANCO"<<endl;
        cout<<"0) salir"<<endl;
        cout<<"================================"<<endl;
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
                punto3();
                break;
            case 4:
                mostrarCompras();
                break;
            case 5:
                mostrarMateriales();
                break;
            case 6:
                mostrarProveedores();
                break;
            case 7:
                punto1F();
                break;
            case 0:
                return false;
                break;
            default:
                cout<<"OPCION INCORRECTA!"<<endl;
                break;
        }
        system("pause");
    }
    return 0;
}

///PUNTO 1----------------------------------

bool sinCompras(int num){

    int cantCompras;
    Compra reg;
    ArchivoCompras archi("compras.dat");
    cantCompras = archi.contarRegistros();

    for(int i=0;i<cantCompras;i++){
        reg=archi.leerRegistro(i);
        if(reg.getNumeroproveedor()==num && reg.getActivo()){
            if(reg.getFechaCompra().getAnio()==2023){
                return false;
            }
        }
    }
    return true;
}


void agregarRegistro(Proveedor r){
    ArchivoProveedoresSinCompras archi("ProveedoresSinCompras.dat");
    ProveedorSinCompras reg;

    reg.setNumeroProveedor(r.getNumeroProveedor());
    reg.setNombre(r.getNombre());
    reg.setProvincia(r.getProvincia());
    reg.setActivo(true);

    reg.Mostrar();

    archi.grabarRegistro(reg);
}

void punto1(){

    Proveedor reg;
    ArchivoProveedores archi("proveedores.dat");
    int cantProv=archi.contarRegistros();
    int num;
    for(int i=0;i<cantProv;i++){
        reg=archi.leerRegistro(i);
        if(reg.getActivo()){
            num=reg.getNumeroProveedor();

            if(sinCompras(num)){
                agregarRegistro(reg);
                cout<<endl;
            };
        }
}}





///PUNTO 2----------------------------------

void mostrarMenor(int *t,int tam){
    int menor=-1;

    for(int i=0;i<tam;i++){
        if(menor==-1 && t[i]!=0){
            menor=t[i];
        } else if(menor>t[i] && t[i]!=0){
            menor=t[i];
        }
    }

    cout<<"TIPO DE MATERIAL CON MENOR CANTIDAD: ("<<menor<<") :"<<endl;
    for(int i=0;i<tam;i++){
        if(t[i]==menor){
            cout<<"MATERIAL TIPO "<<i+1<<endl<<endl;
        }
    }

}


void punto2(){
    Material reg;
    int tipos[6]={0};
    ArchivoMateriales archi("materiales.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        tipos[reg.getTipo()-1]=tipos[reg.getTipo()-1]+1;
    }

    mostrarMenor(tipos,6);
}

///PUNTO 3------------------------------------

void cargarMateriales(Material *m, int tam){

    Material reg;
    ArchivoMateriales archi("materiales.dat");

    int pos=0;
    for(int i=0; i<tam; i++){
        reg=archi.leerRegistro(i);
        m[pos]=reg;
        pos++;
    }
}
void mostrarVector(Material *m,int tam){
    int tipo;
    cout<<"INGRESE UN TIPO DE MATERIAL: ";
    cin>>tipo;

    for(int i=0; i<tam; i++){
        if(m[i].getTipo()==tipo){
            m[i].Mostrar();
            cout<<endl<<endl;
        }
    }
}


void punto3(){
    Material *m;
    ArchivoMateriales archi("materiales.dat");
    int tam=archi.contarRegistros();

    m=new Material[tam];
    if(m==nullptr){
        cout<<"ERROR AL RESERVAR MEMORIA PARA EL VECTOR"<<endl;
        return;
    }
    cargarMateriales(m,tam);

    mostrarVector(m, tam);
    delete[] m;

}




///PUNTO 4----------------------------------------------------

//bool Obra::operator ==(float sup){
//        if(superficie==sup) return true;
//        return false;}

void mostrarCompras(){
    Compra reg;
    ArchivoCompras archi("compras.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
    cout<<endl<<endl;
    }
}

void mostrarMateriales(){
    Material reg;
    ArchivoMateriales archi("materiales.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
        cout<<endl<<endl;
    }


}

void mostrarProveedores(){
    Proveedor reg;
    ArchivoProveedores archi("proveedores.dat");
    int tam=archi.contarRegistros();
    for(int i=0;i<tam;i++){
        reg=archi.leerRegistro(i);
        reg.Mostrar();
        cout<<endl<<endl;
    }



}



bool nocompras2023(int numproveedor){
ArchivoCompras archicomp("compras.dat");
int cant=archicomp.contarRegistros();
Compra regcompra;

for(int i=0;i<cant;i++){
    regcompra=archicomp.leerRegistro(i);
    cout<<"MOSTRAME EL NUMERO DE PROVEEDOR DE LAS COMPRAS:!!!!!!!!!!! "<<regcompra.getNumeroproveedor();
    if((numproveedor==regcompra.getNumeroproveedor())&&(regcompra.getFechaCompra().getAnio()!=2023)){
        return true;
    }
    else{
        return false;
    }
}

}




void punto1F(){
///   el número de proveedor, el nombre del proveedor y la provincia del proveedor.
ArchivoProveedores archip("proveedores.dat");
Proveedor reg;
bool x=false;
int cant=archip.contarRegistros();
ArchivoProveedoresSinCompras archip1("proveedoresSinComprasF.dat");
ProveedorSinCompras aux;
///


for(int i=0;i<cant;i++){
    reg=archip.leerRegistro(i);
    cout<<"NUMERO DE PROVEEDOR: "<<reg.getNumeroProveedor()<<endl<<endl;
   x=nocompras2023(reg.getNumeroProveedor());
   if(x==true){
    aux.setNumeroProveedor(reg.getNumeroProveedor());
    aux.setNombre(reg.getNombre());
    aux.setProvincia(reg.getProvincia());
    aux.Mostrar();
    archip1.grabarRegistro(aux);
   }
}

///archip1.listar();
}



