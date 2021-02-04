#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli) {
    vagas = lot;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
    if (clientes.size() + 1 > numMaximoClientes)
        return false;
    clientes.push_back({nome, false});
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
    int index = posicaoCliente(nome);
    if (index == -1 || clientes.at(index).presente == true)
        return false;
    clientes.erase(clientes.begin() + index);
    return true;
}

bool ParqueEstacionamento::entrar(const string & nome) {
    int index = posicaoCliente(nome);
    if (index == -1 || clientes.at(index).presente == true || vagas == 0)
        return false;
    --vagas;
    clientes.at(index).presente = true;
    return true;
}

bool ParqueEstacionamento::sair(const string & nome) {
    int index = posicaoCliente(nome);
    if (index == -1 || clientes.at(index).presente == false)
        return false;
    ++vagas;
    clientes.at(index).presente = false;
    return true;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
    for (int index = 0; index < clientes.size(); index++)
        if (clientes.at(index).nome == nome)
            return index;
    return -1;
}

unsigned ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}