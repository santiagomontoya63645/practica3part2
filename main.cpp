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
                      clavedecod=admin.recogerunalinea(0,"../practica3parte2/BD/usando");
                      claveverif=admin.verificador(clave,clavedecod);
                      if(claveverif==false){//cave d eadministrador que ingreso esta incorrecta
                          cout<<"clave incorrecta"<<endl;
                      }

                  }
                  while (claveverif==true){

                      while(opcion!=3){//opciones del administrador
                          cout<<"ingrese 1 si quiere crear usuarios"<<endl<<"2 si el usuario desea recargar"<<endl<<"3 para cerrar seccion"<<endl;//puedes poner 4 para salir f=false
                          cin>>opcion;
                          switch (opcion) {
                          case 1:
                              admin.crearusuario();// omg que hace esto? solo diosito y chuck norrys lo sabran
                              break;
                          case 2:

                              admin.modificardinero("admin");//se usa para recargar las cuentas
                              break;
                          }

                      }
              }
          }
        }
    }
    }
    return 0;
}
