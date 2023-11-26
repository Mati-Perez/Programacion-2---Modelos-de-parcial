///Ejercicio: Parcial 2 de Programaci�n II
///Autor:DEK
///Fecha:
///Comentario:

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}


class Fecha{
private:
    int dia,mes, anio;
public:
    void Cargar(){
        cin>>dia;
        cin>>mes;
        cin>>anio;
    }
    void Mostrar(){
        cout<<dia<<"/";
        cout<<mes<<"/";
        cout<<anio<<endl;
    }
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}

    void setDia(int d){dia=d;}
    void setMes(int m){mes=m;}
    void setAnio(int a){anio=a;}

};




class Socio{
private:
    char codigoSocio[5];
    int categoria;
    char nombre[30];
    char direccion[30];
    char telefono[30];
    char email[30];
    Fecha inscripcion;
    bool estado;
public:
    void Cargar(){
        cout<<"CODIGO SOCIO: "<<endl;
        cargarCadena(codigoSocio,5);
        cout<<"CATEGORIA: "<<endl;
        cin>>categoria;
        cout<<"NOMBRE: "<<endl;
        cargarCadena(nombre,29);
        cout<<"DIRECCION: "<<endl;
        cargarCadena(direccion,29);
        cout<<"TELEFONO: "<<endl;
        cargarCadena(telefono,29);
        cout<<"EMAIL: "<<endl;
        cargarCadena(email,29);
        cout<<"ISNCRIPCION: "<<endl;
        inscripcion.Cargar();
        estado=true;
    }
    void Mostrar(){
        cout<<"CODIGO SOCIO: "<<codigoSocio<<endl;
        cout<<"CATEGORIA: "<<categoria<<endl;
        cout<<"NOMBRE: "<<nombre<<endl;
        cout<<"DIRECCION: "<<direccion<<endl;
        cout<<"TELEFONO: "<<telefono<<endl;
        cout<<"EMAIL: "<<email<<endl;
        cout<<"FECHA DE INSCRIPCION: "<<endl;
        inscripcion.Mostrar();
        if(!estado) cout<<"ESTA BORRADO"<<endl<<endl;
    }


    void setCodigoSocio(const char *cs){strcpy(codigoSocio,cs);}
    void setCategoria(int c){categoria=c;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setTelefono(const char *n){strcpy(telefono,n);}
    void setDireccion(const char *n){strcpy(direccion,n);}
    void setEstado(bool a){estado=a;}
    void setInscripcion(Fecha f){inscripcion=f;}

    const char *getCodigoSocio(){return codigoSocio;}
    int getCategoria(){return categoria;}
    const char *getNombre(){return nombre;}
    const char *getTelefono(){return telefono;}
    const char *getDireccion(){return direccion;}
    bool getEstado(){return estado;}
    Fecha getInscripcion(){return inscripcion;}
};

class ArchivoSocios{
private:
    char nombre[30];
public:
    ArchivoSocios(const char *n){
        strcpy(nombre, n);
    }
    Socio leerRegistro(int pos){
        Socio reg;
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
        return tam/sizeof(Socio);
    }
    bool grabarRegistro(Socio reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

class Medico{
private:
    int IDpersonal;
    char nombre[30];
    char telefono[30];
    char email[30];
    char direccion[30];
    bool estado;
public:
    void Cargar(){
        cin>>IDpersonal;
        cargarCadena(nombre,29);
        cargarCadena(telefono,29);
        cargarCadena(email,29);
        cargarCadena(direccion,29);
        estado=true;
    }
    void Mostrar(){
        cout<<IDpersonal<<endl;
        cout<<nombre<<endl;
        cout<<telefono<<endl;
        cout<<email<<endl;
        cout<<direccion<<endl;
        if(!estado) cout<<"ESTA BORRADO"<<endl<<endl;
    }


    void setIDpersonal(int id){IDpersonal=id;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setTelefono(const char *n){strcpy(telefono,n);}
    void setDireccion(const char *n){strcpy(direccion,n);}
    void setEstado(bool a){estado=a;}
    void setEmail(const char *e){strcpy(email,e);}

    int getIDpersonal(){return IDpersonal;}
    const char *getNombre(){return nombre;}
    const char *getTelefono(){return telefono;}
    const char *getDireccion(){return direccion;}
    bool getEstado(){return estado;}
    const char *getEmail(){return email;}

};

class ArchivoMedicos{
private:
    char nombre[30];
public:
    ArchivoMedicos(const char *n){
        strcpy(nombre, n);
    }
    Medico leerRegistro(int pos){
        Medico reg;
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
        return tam/sizeof(Medico);
    }
    bool grabarRegistro(Medico reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};


class Especialidad{
private:
    int codigoEspecialidad, tipo;
    char nombre[30];
    bool estado;
public:
    void Cargar(){
        cin>>codigoEspecialidad;
        cargarCadena(nombre, 29);
        cin>>tipo;
        estado=true;
    }
    void Mostrar(){
        cout<<codigoEspecialidad<<endl;
        cout<<nombre<<endl;
        cout<<tipo<<endl;
        if(estado==false) cout<<"BORRADO"<<endl;
    }

    void setCodigoEspecialidad(int ce){codigoEspecialidad=ce;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setTipo(int t){tipo=t;}
    void setEstado(bool e){estado=e;}

    int getCodigoEspecialidad(){return codigoEspecialidad;}
    const char *getNombre(){return nombre;}
    int getTipo(){return tipo;}
    bool getEstado(){return estado;}
};


class ArchivoEspecialidades{
private:
    char nombre[30];
public:
    ArchivoEspecialidades(const char *n){
        strcpy(nombre, n);
    }
    Especialidad leerRegistro(int pos){
        Especialidad reg;
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
        return tam/sizeof(Especialidad);
    }
    bool grabarRegistro(Especialidad reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

class Turno{
private:
    int numeroTurno;
    char codigoSocio[5];
    int codigoEspecialidad;
    int IDpersonal;
    float importe;
    Fecha fechaTurno;
    bool estado;
public:
    void Cargar(){
        cout<<"NUMERO DE TURNO: ";
        cin>>numeroTurno;
        cout<<"CODIGO DE SOCIO: ";
        cin>>codigoSocio;
        cout<<"CODIGO DE ESPECIALIDAD: ";
        cin>>codigoEspecialidad;
        cout<<"ID PERSONAL: ";
        cin>>IDpersonal;
        cout<<"IMPORTE: ";
        cin>>importe;
        cout<<"FECHA DE TURNO: ";
        fechaTurno.Cargar();
        estado=true;
    }
    void Mostrar(){
        cout<<"NUMERO DE TURNO: "<<numeroTurno<<endl;
        cout<<"CODIGO DE SOCIO: "<<codigoSocio<<endl;
        cout<<"CODIGO DE ESPECIALIDAD: "<<codigoEspecialidad<<endl;
        cout<<"ID PERSONAL: "<<IDpersonal<<endl;
        cout<<"IMPORTE: "<<importe<<endl;
        cout<<"FECHA DE TURNO: "<<endl;
        fechaTurno.Mostrar();
        if(estado==false) cout<<"BORRADO"<<endl;
    }

    void setNumeroTurno(int nt){numeroTurno=nt;}
    void setCodigoSocio(const char *cs){strcpy(codigoSocio,cs);}
    void setCodigoEspecialidad(int ce){codigoEspecialidad=ce;}
    void setIDpersonal(int id){IDpersonal=id;}
    void setImporte(float im){importe=im;}
    void setFechaTurno(Fecha t){fechaTurno=t;};
    void setEstado(bool e){estado=e;}

    int getNumeroTurno(){return numeroTurno;}
    const char *getCodigoSocio(){return codigoSocio;}
    int getCodigoEspecialidad(){return codigoEspecialidad;}
    int getIDpersonal(){return IDpersonal;}
    float getImporte(){return importe;}
    Fecha getFechaTurno(){return fechaTurno;};
    bool getEstado(){return estado;}
};

class ArchivoTurnos{
private:
    char nombre[30];
public:
    ArchivoTurnos(const char *n){
        strcpy(nombre, n);
    }
    Turno leerRegistro(int pos){
        Turno reg;
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
        return tam/sizeof(Turno);
    }
    bool grabarRegistro(Turno reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};
