#include "Servidor.hpp"

using namespace std;

Servidor::Servidor(unsigned int id, Usuario* dono, string nome)
{
    this->id = id;
    this->dono = dono;
    this->nome = nome;
    participantes.push_back(dono); //adicionando o dono aos participantes do servidor
}

unsigned int Servidor::get_id()
{
    return id;
}

Usuario* Servidor::get_dono()
{
    return dono;
}

string Servidor::get_nome()
{
    return nome;
}

void Servidor::set_descricao(string descricao)
{
    this->descricao = descricao;
}

void Servidor::set_codigoConvite(std::string codigo)
{
    codigoConvite = codigo;
}

vector<CanalTexto>* Servidor::get_canaisTexto()
{
    return &canaisTexto;
}

void Servidor::set_dono(Usuario* dono)
{
    this->dono = dono;
}
