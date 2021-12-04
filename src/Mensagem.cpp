#include "Mensagem.hpp"

using namespace std;

Usuario* Mensagem::get_enviadaPor()
{
    return enviadaPor;
}

void Mensagem::set_enviadaPor(Usuario* enviadaPor)
{
    this->enviadaPor = enviadaPor;
}
