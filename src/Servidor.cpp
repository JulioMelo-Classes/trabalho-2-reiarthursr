#include "Servidor.hpp"

using namespace std;

Usuario* Servidor::get_dono()
{
    return dono;
}

string Servidor::get_nome()
{
    return nome;
}

vector<CanalTexto>* Servidor::get_canaisTexto()
{
    return &canaisTexto;
}

void Servidor::set_dono(Usuario* dono)
{
    this->dono = dono;
}
