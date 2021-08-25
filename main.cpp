#include <iostream>
#include "admin.h"
using namespace std;

int main()
{
    Admin admin;
    string clave;
    string a,clavedecod,salida;
    int opcion=0,opcion2=0,opcion3=0;
    bool claveverif=false,f=true,usuario=false;
    while(f==true){
        while(opcion2!=2){//opcion 2 determinara si se apaga el sistema o si desea ingresar usuario
          cout<<"ingrese 1 si desea ingresar al sistema"<<endl<<"2 si desea salir"<<endl;cin>>opcion2;
          switch (opcion2) {
          case 2:
              return 0;
          case 1:
              cout<<"ingrese usuario "<<endl;cin>>a;//ingrese administrador si quieres entrar como tal
              if(a=="administrador"){
                  claveverif=false;
                  while(claveverif==false){
                      a="sudo";
                      cout<<"ingrese clave de admin"<<endl;cin>>clave;
                      admin.deco_metodo2(4,a);
                      clavedecod=admin.recogerunalinea(0,"usando");
                      claveverif=admin.verificador(clave,clavedecod);
                      if(claveverif==false){//cave d eadministrador que ingreso esta incorrecta
                          cout<<"clave incorrecta"<<endl;
                      }
                      else{
                          cout<<"puto"<<endl;
                      }
                  }
              }
          }
        }
    }
    return 0;
}
