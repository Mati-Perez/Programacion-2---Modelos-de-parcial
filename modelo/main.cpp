#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

class ObraSinCompras{
private:
    char codigoObra[5];
    char direccion[30];
    int provincia;
    bool activo;
public:
    void Cargar(){
        cargarCadena(codigoObra,4);
        cargarCadena(direccion,29);
        cin>>provincia;
        activo=true;
    }

    void Mostrar(){
        cout<<codigoObra<<endl;
        cout<<direccion<<endl;
        cout<<provincia<<endl;
    }

    const char* getCodigoObra(){return codigoObra;}
    const char* getDireccion(){return direccion;}
    int getProvincia(){return provincia;}
    bool getActivo(){return activo;}

    void setCodigoObra(const char *co){strcpy(codigoObra, co);}
    void setDireccion(const char *d){strcpy(direccion,d);}
    void setProvincia(int p){provincia=p;}
    void setActivo(bool a){activo=a;}
};

class ArchivoObrasSinCompras{
    private:
        char nombre[30];
    public:
        ArchivoObrasSinCompras(const char *n){
            strcpy(nombre,n);
        }
        Obra leerRegistro(int pos){
            Obra reg;
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
            int cant=ftell(p)/sizeof(Obra);
            fclose(p);
            return cant;
        }
        bool grabarRegistro(Obra reg){
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

    punto1();
    return 0;
}

void punto1(){


    grabarRegistro();

}

bool grabarRegistro(){

    int contarObras;
    Obra reg;
    ArchivoObras archi("obras.dat");
    contarObras=archi.contarRegistros();

    for(int i=0;i<contarObras;i++){
        if(reg[i].getEstadoEjecucion()==3 && reg[i].getActivo()){
            verificarCompras(reg[i].getCodigoObra());

        }
    }


    Alumno reg;
    ArchivoAlumnos archiAlu("alumnos.dat");
    cout<<"INGRESAR LOS VALORES DEL REGISTRO "<<endl;
    reg.Cargar();
    bool escribio=archiAlu.grabarRegistro(reg);
    return escribio;


}

