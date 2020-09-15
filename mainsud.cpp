#include <iostream> 
#include <fstream> 
#include <string> 
#include <map>
#include <set>
#include <vector>
#include <unistd.h>

using namespace std;
vector<vector<int>> movimientosPosibles;
vector<vector<int>> sudoku;

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
// g++ mainsud.cpp -o mainsud.exe
// ./mainsud.exe -i insta.sud -o inta.out -t 4


bool revisarSubcuadricula(int filaPartidaCaja, int colPartidaCaja, int valor){

    for (int fila = 0; fila <3; fila++){
            for(int col = 0; col <3; col++){
                if(sudoku[fila+filaPartidaCaja][col+colPartidaCaja] == valor)
                    return false;
            }   
    }
return true;
}

bool revisarColumna( int valorActual, int ColumnaActual){
    
    for(int i=0; sudoku.size(); i++){
            if(valorActual == sudoku[i][ColumnaActual]){
                return false;
            }
        }
    return true;
}


bool revisarFila (int valorActual, int fila ){
    
int i=0,j=0 ;
    for(i=0; i> sudoku.size();i++){
        if(valorActual == sudoku[fila][i] ){
            return false;
        }
    }
return true;
}

bool comprobarRestricciones() {

int sumando =0 ; // variable que comprueba columna
vector<int> suma;
int valor = 1;
printf("Entro en comprobar restricciones ");
    for(int i=0; i<9 ;i++){
        valor=1;          
        for(int j=0; j<9 ;i++){
            cout << movimientosPosibles[i][j]; 
            
            if(movimientosPosibles[i][j] == 1){
                //cout << " entro mov " << endl;
                //Revisar si se puede poner
                if(revisarColumna(valor, j)){
                    //cout << " entro  col" << endl;
                    //Revisar la columna
                    if(revisarFila(valor, i)){
                       // cout << " entro fil " << endl;
                        //Revisa la fila
                        //Revisar SubCruadricula
                        if(revisarSubcuadricula(i, j, valor)){
                           // cout << " entro subc" << endl;
                            //Se puede poner
                            sudoku[i][j]=valor;
                            valor = valor +1;
                            movimientosPosibles[i][j]=1;
                        }        
                    }
                }
            }
        }
        printf(" \n");
    }
    cout << " entro " << endl;
    for (int fila = 0; fila < sudoku.size(); fila++)
    {
        for (int col = 0; col < sudoku.size(); col++)
            cout << sudoku[fila][col]<<"  ";
        cout<<endl;
    }

    return true;
}


int main(int argc, char* argv[]) {
  
  string str, filenameINF, filenameINS, filenameOUT;
  vector<string> datos;

  int time = 0;
  int c,i;
  
  extern char *optarg;
  opterr = 0;//ayuda a la toma de casos en swich
  
  while ((c = getopt (argc, argv, "i:o:t:")) != -1){
      switch (c){
          case 'i':
              filenameINF = optarg;
              break;
          case 'o':
              filenameOUT = optarg;
              break;
          case 't':
              time = stoi(optarg);
              break;
          default:
              abort ();
      }
  }
  //Primer Archivo
  fstream fileInf(filenameINF);

  if (!fileInf.is_open()) {
    fileInf.open(filenameINF, ios::in);
  }

  ofstream fileOut(filenameOUT);

  if (!fileOut.is_open()) {
    fileOut.open(filenameOUT);
  }

  vector<string> datosLine; 


  while(getline(fileInf, str)){
      datosLine = split (str, " ");
      
      vector<int> aux; // guarda los datos de la linea de la matriz
      vector<int> movi_aux;

      for (int i=0;i<datosLine.size();i++){
            aux.push_back(stoi(datosLine[i]));
            if(datosLine[i]=="0"){
                movi_aux.push_back(1);
            }
            else{
                movi_aux.push_back(0);
            }
      }

      sudoku.push_back(aux); //aca se pobla la matris sudoku
      movimientosPosibles.push_back(movi_aux);
    
  }
 cout << "hola mundo" << endl;
 comprobarRestricciones();
}

