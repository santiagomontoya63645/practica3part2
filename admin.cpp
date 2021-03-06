#include "admin.h"

Admin::Admin()
{

}
void Admin:: leer_archivo(char *contenido,string nombre_de_entrada){
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
void Admin:: convertircadena(int *entero,char *contenido){
   int k=0;
   char *p=contenido;
   while (*(p++)!='\0')k++;	//longitud de la cadena
   for (int i=0;i<k;i++){
       *(entero+i)=*(contenido+i);	//conversion a entero
   }
}
void Admin:: siste_binario(char *binario,int *entero){
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
              *(binario+i)= 49; // Por ??ltimo s?? el valor final del dividendo es 1 concatenamos 1 sino concatenamos 0.
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
void Admin:: metodo2(char *binario,int semilla,string nombre_de_salida){
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
    //cout<<"archivo original:              ";for(int i=0;i<k;i++) cout<<*(binario+i);
    //cout<<endl;
    //cout<<"archivo binario codificado:    ";for(int i=0;i<k;i++) cout<<*(codificado+i);
    //cout<<endl;

}
void Admin:: deco_metodo2(int semilla,string nombre_de_entrada){
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

   texto.resize(size/8);//Redefinimos el tama??o del texto donde me quede solo los caracteres ya que hay size/8 caracteres

   ofstream escribir;//Enviamos lo decodificado al archivo fuente2.txt
   //prueba+="decodificado.txt";
   escribir.open("../practica3parte2/BD/usando");
   escribir<<texto;
   escribir.close();

}
string Admin:: recogerunalinea(int linea, string a){//retorna una linea en especifico del archivo a
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
bool Admin:: verificador(string clave,string clavedecod){ //verificador de claves

    if (clave==clavedecod){
        return true;
    }
    else{
        return false;
    }
}
void Admin::crearusuario(){
    // como su nombre lo dice crea usuarios y codifica la contrase??a y saldo de los usuaios creados
    // no necesite ningun dato de entrada, lo que hace es crear una carpeta que tiene de nombre el nombre del usuario que deseas crear
    // en b:se ingresa si para crear si ingresa no sale de esta funcion, si ingresa otro caracter volvera a preguntar
    string a,b,auxb,z,saldoinicial;
    while (true){
        cout<<"desea crear usuario?(ingrese si para crear o no para salir de esta opcion)"<<endl;cin>>a;
        if (a=="no"){
            break;
        }
        else if (a=="si"){
            cout<<"ingrese el nombre del usuario"<<endl;cin>>b;
            auxb=b;
            b="../practica3parte2/BD/"+b;
            ofstream escribir;
            escribir.open(b);
            cout<<"ingrese contrasena"<<endl;cin>>z;
            escribir<<z;
            escribir<<"\n";
            escribir<<"saldo:\n";
            cout<<"ingrese saldo inicial"<<endl;cin>>saldoinicial;
            escribir<<saldoinicial;
            escribir.close();
            b=auxb;
            char contenido[10000]={};//variables necesarias para la codificacion
            int entero[10000]={};//
            char binario[80000]={};
            leer_archivo(contenido,b);//ya fue explicado al inicio del archivo
            convertircadena(entero,contenido);
            siste_binario(binario,entero);
            metodo2(binario,4,b);
        }
    }
}
void Admin::modificardinero(string descision){//aca se decide si se va a recargar o retirar
    // si el que ingresa esel administrador solamente es para aumentar su dinero

    string prueba="../practica3parte2/BD/";

    if (descision=="admin"){// caso en que se va a recargar dinero
        cout<<"ingrese usuario que va a recargar"<<endl;cin>>descision;
        string auxdescision=descision;

        deco_metodo2(4,descision);
        descision=prueba+descision;
        ifstream leer;
            leer.open(descision);
            if(leer.is_open()){
                leer.close();
                descision=auxdescision;
               aumentardinero(descision);
            }
            else{
                cout<<"usuario no encontrado"<<endl;

            }

    }
}


void Admin::aumentardinero(string usuario){//solo el admin puede aumentar el dinero si el usuario quiere recargar que vaya alas oficinas de los admins
    // recive d eentrada el nombre del archivo del usuario que senecesita decodificar, aumentar sus aldo y despues codificar
    long int lo_que_desea_recargar;
    string lo_que_tiene,guardarpasword;
    cout<<"cuanto va a recargar?"<<endl;cin>>lo_que_desea_recargar;
    deco_metodo2(4,usuario);
    lo_que_tiene=recogerunalinea(2,"../practica3parte2/BD/usando");// recoge la linea del saldo que posteriormente se convertia a enetero para poder modificar el saldo
    long int x=stoi(lo_que_tiene,nullptr,10);
    x+=lo_que_desea_recargar;
    cout<<"recarga exiosa"<<endl<<" su nuevo saldo es :"<<x<<endl;
    guardarpasword=recogerunalinea(0,"../practica3parte2/BD/usando");
    ofstream escribir;
    escribir.open("../practica3parte2/BD/"+usuario);// el resto de lafuncion lo que hace es guardar los cambios
    escribir<<guardarpasword;
    escribir<<"\nsaldo:";
    escribir<<"\n";
    escribir<<x;
    escribir.close();
    char contenido[10000]={};//guarda el contenido del archivo que desea modificar en este casoo el usuario
    int entero[10000]={};// se guardara cada caracter de contenido pero en ascii (convertircadena)
    char binario[80000]={};// todo lo que haya en entero se llevara a binario
    leer_archivo(contenido,usuario);
    convertircadena(entero,contenido);
    siste_binario(binario,entero);
    metodo2(binario,4,usuario);
    remove("../practica3parte2/BD/usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo
}
