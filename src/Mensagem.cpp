#include "Mensagem.hpp"

using namespace std;

Mensagem::Mensagem(unsigned int id, std::string dataHora, Usuario* enviadaPor, std::string conteudo)
{
    this->id = id;
    this->dataHora = dataHora;
    this->enviadaPor = enviadaPor;
    this->conteudo = conteudo;
}

string Mensagem::get_dataHora()
{
    return dataHora;
}

Usuario* Mensagem::get_enviadaPor()
{
    return enviadaPor;
}

string Mensagem::get_conteudo()
{
    return conteudo;
}

void Mensagem::set_enviadaPor(Usuario* enviadaPor)
{
    this->enviadaPor = enviadaPor;
}
