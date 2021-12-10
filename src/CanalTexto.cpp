#include "CanalTexto.hpp"

using namespace std;

CanalTexto::CanalTexto(unsigned int id, std::string nome, Usuario* dono)
{
    this->id = id;
    this->nome = nome;
    this->dono = dono;
}

string CanalTexto::get_nome()
{
    return nome;
}

Usuario* CanalTexto::get_dono()
{
    return dono;
}

void CanalTexto::set_dono(Usuario* dono)
{
    this->dono = dono;
}

vector<Mensagem>* CanalTexto::get_mensagens()
{
    return &mensagens;
}
