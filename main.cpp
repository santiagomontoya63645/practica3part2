// para ingresar como administrador debes darle en la opcion  ingresar al a sistema y cuando te pida el usuario ingresar administrador, luego te pide la clave que es 1234
//la clave de administrador es 1234 y la cuenta de administrador es administrador
//pd el archivo usando es un archivo temporal donde se realizaran cambios de las demas cuentas y posteriormente se guardaran en dichas cuentas
//se esta encryptando y desencryptando con el metodo 2 con semilla 4
// muchas de las funciones se explican solas con el nombre
//este archivo debe eestar en una una carpeta llamada practica3parte2
// el dinero debe ser representado hasta con un maximo de 8 bits
//todos los archivos cuando se crean cuando se modifica el dinero se realizan los cambios y luego se procede a encryptarlos
//la unica manera de verificar los cambios es atravez del cmd cuando se aumenta o se disminuye el dinero
//todos los aarchivos de los ususarios estan encryptados
//todo estara guardado en una carpeta de base de datos llamada BD que debes crearla dentro de la carpeta de practica 3 parte 2
#include <iostream>
#include "admin.h"
#include "usuario.h"
using namespace std;

int main()
{
    Admin admin;
    usuario Usuario;
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
                      remove("../practica3parte2/BD/usando");
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
                      opcion=0;

                      claveverif=false;//poner despues de esto si se desea sali del sistema

              }
          }
              else{

                  usuario=Usuario.ingresarcomousuario(a);//poner los cassos de mirar saldo o retirar saldoo errar seccion
                  opcion3=0;
                  if (usuario==true){
                      while(opcion3!=3){
                          cout<<"ingrese 1 si desea ver su saldo"<<endl<<"ingrese 2 si desea retirar dinero"<<endl<<"ingrese 3 para cerrar seccion"<<endl;
                          cin>>opcion3;
                          cout<<endl<<endl<<endl<<endl<<endl;
                          switch (opcion3) {//aca el usuario escoge que desea hacer
                            case 1:
                              Usuario.versaldo(a);
                              break;
                            case 2:
                              Usuario.retirardinero(a);
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
