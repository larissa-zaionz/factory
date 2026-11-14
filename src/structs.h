#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Item {
    int id;
    std::string nome;
    std::string tipo; 
    double valor;    
};

struct Maquina {
    int id;
    std::string nome;
    int produtividade;  
    double custoEnergia;   
    double lucroPorTurno;  
};

struct Receita {
    int id; 
    std::string nome;
    std::string materiaPrima; 
    std::string produtoFinal;
    int custoEnergetico;
};

#endif