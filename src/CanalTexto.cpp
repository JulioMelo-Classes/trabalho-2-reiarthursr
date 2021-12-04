#include "CanalTexto.hpp"

using namespace std;

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
