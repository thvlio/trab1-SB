/*      COMMON.H: arquivo contendo as definições das funções comuns     */



/*      DECLARAÇÕES DAS FUNÇÕES     */
int errorCheck (int, char**, std::string, std::string);
std::string o2pre (std::string);
std::string o2mcr (std::string);
std::vector<Instr> getInstrList (std::string);
std::vector<Dir> getDirList (std::string);
int integerCheck (std::string, int&);
void reportError (std::string, std::string, int, std::string);
int labelCheck (std::string, std::vector<Instr>&, std::vector<Dir>&, int&);
bool operator< (const Error&, const Error&);


/*      DEFINIÇÕES DAS FUNÇÕES     */

/*
errorCheck: verifica se ha algum erro nos argumentos de entrada do programa ou no arquivo do codigo de entrada
entrada: argc e argv recebidos pela funcao main()
saida: um inteiro indicando se houve erro (0 se nao, -1 se sim)
*/
int errorCheck (int argc, char *argv[], std::string instrFileName, std::string dirFileName) {
    
    // verifica o numero de argumentos dados
    if (argc != 4) {
        std::cout << "Número inválido de argumentos: " << argc-1 << " (3 esperados)" << "\n";
        return -1;
    }
    
    // guarda os argumentos em strings
    std::string operation (*(argv+1)),
        inFileName (*(argv+2)),
        outFileName (*(argv+3));
    
    // verifica se a operacao eh valida
    if (operation != "-p" && operation != "-m" && operation != "-o") {
        std::cout << "Operação inválida: " << operation << "\n";
        return -1;
    }
    
    // verifica se as extensao do arquivo de entrada eh .asm
    if (inFileName.size() < 5) {
        std::cout << "Extensão do arquivo de entrada não suportada (somente .asm)" << "\n";
        return -1;
    } else {
        std::string inExt = inFileName.substr(inFileName.size() - 4);
        if (inExt != ".asm") {
            std::cout << "Extensão do arquivo de entrada não suportada (somente .asm)" << "\n";
            return -1;
        }
    }
    
    // verifica se as extensao do arquivo de saida eh .o
    if (outFileName.size() < 3) {
        std::cout << "Extensão do arquivo de saída não suportada (somente .o)" << "\n";
        return -1;
    } else {
        std::string outExt = outFileName.substr(outFileName.size() - 2);
        if (outExt != ".o") {
            std::cout << "Extensão do arquivo de saída não suportada (somente .o)" << "\n";
            return -1;
        }
    }
    
    // verifica se o arquivo de entrada existe
    std::ifstream asmFile (inFileName);
    if (!asmFile.is_open()) {
        std::cout << "Erro ao abrir o arquivo de entrada: " << inFileName << "\n";
        return -1;
    } else
        asmFile.close();
        
    // verifica se o arquivo com a lista de instrucoes existe
    std::ifstream instrFile (instrFileName);
    if (!instrFile.is_open()) {
        std::cout << "Erro ao abrir a tabela de instruções: " << instrFileName << "\n";
        return -1;
    } else
        instrFile.close();
    
    // verifica se o arquivo com a lista de diretivas existe
    std::ifstream dirFile (dirFileName);
    if (!dirFile.is_open()) {
        std::cout << "Erro ao abrir a tabela de diretivas: " << dirFileName << "\n";
        return -1;
    } else
        dirFile.close();
    
    return 0;
}



/*
o2pre: passa uma string com extensao '.o' para extensao '.pre'
entrada: string com o nome original com a extensao '.o'
saida: string com o nome alterado com a extensao '.pre'
*/
std::string o2pre (std::string original) {
    
    std::string altered (original);
    
    altered.pop_back();
    altered.append("pre");
    
    return altered;
}



/*
o2mcr: passa uma string com extensao '.o' para extensao '.mcr'
entrada: string com o nome original com a extensao '.o'
saida: string com o nome alterado com a extensao '.mcr'
*/
std::string o2mcr (std::string original) {
    
    std::string altered (original);
    
    altered.pop_back();
    altered.append("mcr");
    
    return altered;
}



/*
getInstrList: constroi a tabela de instrucoes num vetor 
entrada: nome do arquivo que contem a tabela
saida: vetor com a lista de instrucoes
*/
std::vector<Instr> getInstrList (std::string instrFileName) {
    
    // abre o arquivo
    std::ifstream instrFile (instrFileName);
    
    // cria uma lista de instrucoes
    std::vector<Instr> instrList;
    
    while (!instrFile.eof()) {
        
        std::string name; // nome da instrucao
        int opcode, // opcode
            numArg; // num de operandos
        
        // le o nome da instrucao
        instrFile >> name;
        
        // '#' serve para indicar "comentarios" 
        if (name != "#") {
            
            // le o num de operandos e o opcode
            instrFile >> numArg;
            instrFile >> opcode;
            
            // cria uma instrucao com essas caracteristicas e salva no vetor
            Instr instr (name, opcode, numArg);
            instrList.push_back(instr);
            
        } else {
            // le o resto da linha e ignora
            getline(instrFile, name);
        }
            
    }
    
    instrFile.close();
    return instrList;
}



/*
getDirList: constroi a tabela de diretivas num vetor 
entrada: nome do arquivo que contem a tabela
saida: vetor com a lista de diretivas
*/
std::vector<Dir> getDirList (std::string dirFileName) {
    
    // abre o arquivo e cria uma lista de diretivas vazia
    std::ifstream dirFile (dirFileName);
    std::vector<Dir> dirList;
    
    while (!dirFile.eof()) {
        
        std::string name;
        dirFile >> name;
        
        // novamente, '#' indica "comentarios"
        if (name != "#") {
            // cria uma diretiva e salva no vetor
            Dir dir (name);
            dirList.push_back(dir);
        } else
            getline(dirFile, name); // le o resto da linha e ignora
    
    }
    
    dirFile.close();
    return dirList;
}



/*
integerCheck: checa se a string pode ser convertida em um numero sem erros
entrada: string a ser convertida e inteiro que armazenará o resultado
saida: inteiro que determina se houve ou não erro na conversão (1 ok, 0 erro)
*/
int integerCheck (std::string value, int &conv) {
    
    char *ptr = nullptr; // ponteiro para um caracter
    const char *cValue = value.c_str(); // array de caracteres equivalente à string
    conv = strtol(cValue, &ptr, 10); // converte o array para um numero e altera ptr para o ultimo caracter lido
    
    // se o ultimo caracter lido foi um '\0', entao a string foi convertida em um numero sem nenhum problema
    return (*ptr == '\0'); 
    
}



/*
labelCheck: verifica se o rotulo eh valido
entrada: rotulo a ser verificado
saida: inteiro indicando se rotulo é válido
*/
int labelCheck (std::string label, std::vector<Instr> &instrList, std::vector<Dir> &dirList, int &pos) {
    
    // checa se o rótulo está vazio
    if (label.empty())
        return -5;
    
    // checa o tamanho da string
    if (label.size() > 100) {
        pos = label.size()-1;
        return -1;
    }
    
    // checa se o primeiro caracter é um número
    if (label.front() >= '0' && label.front() <= '9')
        return -2;
    
    // verifica se só existem números, caracteres ou _ na string
    for (unsigned int i = 0; i < label.size(); ++i) {
        if ((label[i] < 'A' || label[i] > 'Z') && (label[i] < '0' || label[i] > '9') && (label[i] != '_')) {
            pos = i;
            return -3; 
        }
    }
    
    // verifica se o rótulo tem o nome de uma instrução
    for (unsigned int i = 0; i < instrList.size(); ++i) {
        if (label == instrList[i].name)
            return -4;
    }
    
    // verifica se o rótulo tem o nome de uma diretiva
    for (unsigned int i = 0; i < dirList.size(); ++i) {
        if (label == dirList[i].name)
            return -4;
    }
        
    return 0;
}



/*
reportList: reporta todos os erros, na ordem das linhas. mostra no terminal a mensagem de erro passada pelo programa, junto com o tipo de erro e a linha
entrada: lista de erros
saida: nenhuma (erros no terminal)
*/
void reportList (std::vector<Error> &errorList) {
    
    // configura algumas cores
    std::string escRed = "\033[31;1m",
    escGreen = "\033[32;1m",
    escYellow = "\033[33;1m",
    escBlue = "\033[34;1m",
    escReset = "\033[0m";
    
    // mostra os erros
    for (unsigned int i = 0; i < errorList.size(); ++i) {
        
        // erro atual
        Error error = errorList[i];
        
        // offset para ajustar o apontador de erro na linha
        std::string offset;
        for (int i = 0; i < error.pos; ++i)
            offset.push_back(' ');
        
        // para o caso de não ter linha específica
        if (error.lineNum == -1) {
            std::cout << escRed << "Erro" << escReset << " no arquivo de entrada: " << escYellow << error.message << escReset << " (erro " << error.type << ")" << "\n\n";
        
        // quando tem linha específica
        } else {
            std::cout << escRed << "Erro" << escReset << " na linha " << escRed << error.lineNum << escReset << " do arquivo de entrada: " << escYellow << error.message << escReset << " (erro " << error.type << ")" << "\n";
            std::cout << "\t" << escBlue << error.line << escReset << "\n";
            std::cout << "\t" << offset << escGreen << "^" << escReset << "\n\n";
        }
        
    }
    
}



/*
operator<: overload do operator < para poder usar std::sort
entrada: duas structs do tipo Error
saida: se a primeira é menor que a segunda (compara o num de linhas)
*/
bool operator< (const Error &A, const Error &B) {
    return (A.lineNum < B.lineNum);
}