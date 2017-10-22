/*      TYPES.H: arquivo contendo as bibliotecas e definições de tipos        */



/*      BIBLIOTECAS     */

#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <string> // std::string
#include <sstream> // std::stringstream
#include <algorithm> // ::toupper



/*      DECLARAÇÕES DOS TIPOS       */

struct Instr;
struct Dir;
struct Label;
struct Macro;



/*      DEFINIÇÕES DOS TIPOS        */

// Instr: armazena uma instrucao e suas caracteristicas
struct Instr {
    // membros
    std::string name; // nome da instrucao
    int opcode, // opcode da instrucao
        numArg; // numero de argumentos da instrucao
    // metodos
    // constroi a estrutura sem nada
    Instr () {};
    // constroi a estrutura a partir de uma string, um opcode e o numero de argumentos
    Instr (std::string nm, int op, int na): name(nm), opcode(op), numArg(na) {};
};



// Dir: armazena uma diretiva e suas caracteristicas
struct Dir {
    // membros
    std::string name; // nome da diretiva
    // metodos
    Dir () {};
    Dir (std::string nm): name(nm) {};  
};



// Label: armazena um rotulo e suas caracteristicas
struct Label {
    // membros
    std::string name; // nome do rotulo
    std::string equ; // definicao vinda de um equ
    int value; // definicao do rotulo (um endereço)
    int isDefined; // se o rotulo ja foi ou nao definido
    std::vector<int> pendList; // lista de pendencias
    std::vector<int> auxInfoList; // lista de informacoes auxiliares
    int isConst; // se é um const ou não (0: nao eh const, 1: eh const, 2: é const = 0)
    int vectSize; // tamanho do vetor, para o caso de ser um space. 0 indica que o rótulo é da área de texto
    // metodos
    Label () {};
    Label (std::string nm, std::string eq): name(nm), equ(eq) {};
};



// Macro: armazena uma macro e suas caracteristcas
struct Macro {
    // membros
    std::string name; // nome da macro
    std::string definition; // definicao da macro
    int initLine; // linha inicial da macro
    int numLines; // quantas linhas tem a macro
    // metodos
    Macro () {};
    Macro (std::string nm, std::string df, int ln, int nl): name(nm), definition(df), initLine(ln), numLines(nl) {};
};