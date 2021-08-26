#include "usuario.h"

usuario::usuario()
{

}
void usuario:: metodo2(char *binario,int semilla,string nombre_de_salida){
    char bloques_bits[20]={};
    char codificado [50000]={};
    int k=0;
    string salida2="../practica3parte2/BD/"+nombre_de_salida;
    char *p=binario;
    while (*(p++)!='\0')k++;	//k es la longitud de la cadena

    char temporal;
    for (int i=0;i<k;i=i+semilla) {//recorremos el binario sin codificar con saltos del valor de la semilla
        for (int e=i,a=0;e<i+semilla;e++,a++) {//Para ir separando los bloques y guardarlos en bloques_bits
            *(bloques_bits+a)=*(binario+e);
        }
        for (int b=semilla-1;b>0;b--) {//Para mover una posicion a la derecha cada bit y el ultimo quede a la izquierda del bloque
            if(*(bloques_bits+b)!='\0'){//Si un valor del bloque es '\0' no cambie posiciones
                temporal=*(bloques_bits+b); //bit que va ir en la primera posicion
                *(bloques_bits+b)=*(bloques_bits+b-1);
                *(bloques_bits+b-1)=temporal;// se guarda el bit temporal en la primera posicion
            }
        }
        for (int a=i,b=0;a<i+semilla;a++,b++) {//Iremos guardando los bloques codificados en el arreglo codificado
            *(codificado+a)=*(bloques_bits+b);
        }
    }

    ofstream escribir;
    escribir.open(salida2);
    escribir<<codificado;
    escribir.close();
  //  cout<<"archivo original:              ";for(int i=0;i<k;i++) cout<<*(binario+i);
   // cout<<endl;
    //cout<<"archivo binario codificado:    ";for(int i=0;i<k;i++) cout<<*(codificado+i);
    //cout<<endl;

}
void  usuario::deco_metodo2(int semilla,string nombre_de_entrada){
    string codificado;
    string bloques, nombre;
    string prueba="../practica3parte2/BD/";
    string auxprueba=prueba;
    prueba+=nombre_de_entrada;
    ifstream leer;
    leer.open(prueba);
    if(leer.is_open()){
        getline(leer,codificado);
    }
    else {
        cout<<"el archivo no existe"<<endl;
        }
   leer.close();

   string decodificado=codificado;
   int size=codificado.length();
   char chartem;

   for (int i=0;i<=size-semilla;i=i+semilla) {
       bloques=codificado.substr(i,semilla);//Extrae del string codificado los #semilla primeros caracteres desde la posicion i
       for (int b=0;b < semilla-1;b++){//El primer valor del bloque queda al final y los otros se corren a la izquierda
           chartem=bloques[b];
           bloques[b]=bloques[b+1];
           bloques[b+1]=chartem;
       }
       for (int b=i,c=0;b < i+semilla;c++,b++) {
           decodificado[b]=bloques[c];
       }
   }

   //Vamos a cambiar de binario a ascii

   string texto=decodificado;//Creo otro string donde se guardara los caracteres

   for (int i=0,a=0;i<size;i=i+8,a++) {
       bloques=decodificado.substr(i,8);
       int expdos=1,sum=0;
       for (int e=7;e>=0;e--) {
           if(bloques[e]=='1'){
               sum=sum+expdos;
           }
           expdos=expdos*2;
       }
       texto[a]=sum;
   }

   texto.resize(size/8);//Redefinimos el tamaño del texto donde me quede solo los caracteres ya que hay size/8 caracteres

   ofstream escribir;//Enviamos lo decodificado al archivo fuente2.txt
   //prueba+="decodificado.txt";
   escribir.open("../practica3parte2/BD/usando");
   escribir<<texto;
   escribir.close();

}
string  usuario::recogerunalinea(int linea, string a){//retorna una linea en especifico del archivo a
    string cadena,contrasenaverdadera;
    int contador=0;
    ifstream leer;
    leer.open(a);
    if(leer.is_open()){
        while(getline(leer,cadena)){
            if (contador==linea){ //guardo la linea que quiero retornar
                contrasenaverdadera=cadena;

            }
            contador++;
        }
    }
    return contrasenaverdadera;
}
bool usuario::ingresarcomousuario(string a){// en esta funcion es donde se verificara el inreso del usuario y se sumara o restara dinero
    // se recive el nombre del usuario que desee ingresar al cajero
    string contrasena;
    string contrasenaverdadera;
    string auxa=a;
    bool con=true;

    while(con==true){
        a=auxa;
        deco_metodo2(4,a);// decodifico el archivo  del usuario que desee ingresar, si no existe saldra de la funcion y se le preguntara si desea ingresar al sistema
        a="../practica3parte2/BD/"+a;
        ifstream leer;
            leer.open(a);
            if(leer.is_open()){
                leer.close();
               contrasenaverdadera=recogerunalinea(0,"../practica3parte2/BD/usando");//recogo la linea que tiene las contraseñas para compararlas
               remove("../practica3parte2/BD/usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo
                cout<<"ingrese contrasena"<<endl;
                cin>>contrasena;

                if (contrasena==contrasenaverdadera){
                    cout<<"sesion iniciada"<<endl;
                    return true;
                    con=false;
                }
                else{
                    cout<<"contrasena incorrecta"<<endl;
                }
            }
            else{
                cout<<"usuaio no encontrado"<<endl;
                return false;
                con=false;
            }
    }
}
void usuario:: leer_archivo(char *contenido,string nombre_de_entrada){
string nombre_arch="../practica3parte2/BD/" + nombre_de_entrada;
char linea[10000]={};
int posicion=0;

ifstream leer;
         leer.open(nombre_arch);
         if(leer.is_open()){
             while(!leer.eof()){ //si llega a fin del archivo me retorna false
             int sizelinea=0;
             leer.getline(linea,100);//Solo me esta leyendo la ultima linea
             while (*(linea+sizelinea)!='\0') sizelinea++;
             for (int i=posicion, b=0;i<posicion+sizelinea;i++,b++) {
                 *(contenido+i)=*(linea+b);                  //concactenamos liea por linea en el chart
             }
             *(contenido+posicion+sizelinea)='\n';
             posicion+=sizelinea+1;
             }
         }
         else {
             cout<<"el archivo no existe."<<endl;
         }
        leer.close();
}
void usuario:: convertircadena(int *entero,char *contenido){
   int k=0;
   char *p=contenido;
   while (*(p++)!='\0')k++;	//longitud de la cadena
   for (int i=0;i<k;i++){
       *(entero+i)=*(contenido+i);	//conversion a entero
   }
}
void usuario:: siste_binario(char *binario,int *entero){
    int dividendo=0, resto=0, divisor = 2,i=7,k=0,aux=0,iaux=7;
    int *p=entero;
    while (*(p++)!='\0')k++;	//longitud de la cadena
    for (int j=0;j<k;j++){
        dividendo = entero[j];
        aux=dividendo;
        while(dividendo >= divisor){ //Mientras el dividendo sea mayor o igual que el divisor, es decir, mayor o igual que 2.
            resto = dividendo % 2;
            if(resto == 1){
                 *(binario+i)= 49; //Si el resto es igual a 1 concatenamos 1 a la variable char llamada binario
            }
            else{
                *(binario+i)= 48; // Sino concatemanos 0
            }

              dividendo = dividendo/divisor; // Actualizamos el valor del dividendo dividiendolo entre 2.
              i--;
        }
             if(dividendo == 1){
              *(binario+i)= 49; // Por último sí el valor final del dividendo es 1 concatenamos 1 sino concatenamos 0.
             }
             else {
              *(binario+i)= 48;
             }
             for(int c=0;c<8;c++){
                 if(aux<pow(2,c)){
                     i--;           //primero cambio la posicion para poder agregar los ceros faltantes
                     aux=0;
                     *(binario+i)= 48;    //for para agregar los primeros ceros en binario de cada caracter
                 }
             }
             iaux+=8; // variable auxiliar para conservar el valor inicial de i
             i=iaux;// varaiable que inicia des de primera posicion del numero binario
   }
}
void usuario::versaldo(string usuario){// funcion que  le muestra al usuario su saldo actual con los -1000 por la revision
    // recive como entrada el nombre del usuario para que el pueda ver su saldo actual
    // se recalcara que cuando un usuario ingresa se llevaran todos los datos a un archivo llamado usando donde se realizaran los cambios
    // y despues se codificaran dichos cambios y se llevaran codificados al archivo del usuario que esta viendo su saldo
    string saldo,guardarpasword,auxusuario;
    deco_metodo2(4,usuario);
    saldo=recogerunalinea(2,"../practica3parte2/BD/usando");//abre el archivo y como la linea 3 de los archivos es donde esta el saldo se debe de ingresar 2
    //por que dicho archivo se sobreescreibira
    long int x=stoi(saldo,nullptr,10);//funcion que me ayuda a llevar de string a enteros
    x=x-1000;
    if(x<0){
        x=0;
    }
    cout<<"su saldo es : "<<x<<endl;
    guardarpasword=recogerunalinea(0,"../practica3parte2/BD/usando");// como reescribire el archivo usando se necesita guardar la contraseña dle usuario para que no se pierda
    //se codificara el archivo
    ofstream escribir;
    auxusuario=usuario;
    usuario="../practica3parte2/BD/"+usuario;
    escribir.open(usuario);// el resto de lafuncion lo que hace es guardar los cambios y los codifica
    // se sobreescrive usando con los nuevos cambios
    escribir<<guardarpasword;
    escribir<<"\nsaldo:";
    escribir<<"\n";
    escribir<<x;
    escribir.close();
    usuario=auxusuario;
    char contenido[10000]={};
    int entero[10000]={};
    char binario[80000]={};
    leer_archivo(contenido,usuario);// se leera el archivo usando y se llevara todo su contenido a contenido
    convertircadena(entero,contenido);// convierte todos lo caracteres que hay en contenido a su valor en ascii y los guarda en entero
    siste_binario(binario,entero);// funcion que convierte todo lo que hay en enterno a numeros binarios
    metodo2(binario,4,usuario);
    remove("../practica3parte/usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo

}

void usuario::retirardinero(string usuario){
    //recive el nombre del archivo del usuario que desee retirar el dinero
    string lo_que_tiene,guardarpasword,auxusuario;
    long int lo_que_desea_retirar;

    deco_metodo2(4,usuario);
    //decodificara os datos del usuario y los llevara al archivo usando
    lo_que_tiene=recogerunalinea(2,"../practica3parte2/BD/usando");// recogo la tercer linea del archivo usando que es donde estara el saldo del usuario que desee retirar dinero
    cout<<endl<<endl<<"su saldo actual es :"<<lo_que_tiene<<endl;
    long int x=stoi(lo_que_tiene,nullptr,10);//convierte el saldo que esta en string a int
    cout<<"ingrese la cantidad que desea retirar"<<endl;cin>>lo_que_desea_retirar;
    while(lo_que_desea_retirar>=x){
        cout<<"senor usted no tiene tanto dinero vuelva e ingrese una cantidad"<<endl;cin>>lo_que_desea_retirar;
    }
    x=x-lo_que_desea_retirar-1000;
    cout<<endl<<endl<<"retiro exitoso su nuevo saldo es:"<<x<<endl;
    guardarpasword=recogerunalinea(0,"../practica3parte2/BD/usando");// recoge la linea donde esta contraseña
    ofstream escribir;
    auxusuario=usuario;
    usuario="../practica3parte2/BD/"+usuario;
    escribir.open(usuario);// el resto de lafuncion lo que hace es guardar los cambios
    // reescribo el archivo usando  con los cambios que se hicieron al usuario al retirar dinero

    escribir<<guardarpasword;
    escribir<<"\nsaldo:";
    escribir<<"\n";
    escribir<<x;
    escribir.close();
    usuario=auxusuario;
    char contenido[10000]={};
    int entero[10000]={};
    char binario[80000]={};
    // encripto los cambios de usando y los guardo en el archivo del usuario que esta retirando dinero y borro el archivo usando
    leer_archivo(contenido,usuario);
    convertircadena(entero,contenido);
    siste_binario(binario,entero);
    metodo2(binario,4,usuario);
    remove("../practica3parte2/BD/usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo

}
