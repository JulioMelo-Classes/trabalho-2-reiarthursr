#include "Usuario.hpp"

using namespace std;
Usuario::Usuario(unsigned int id, string nome, string email, string senha)
{
    this->id = id;

    nome.erase(nome.size()-1); //removendo caracter bugado
    this->nome = nome;

    this->email = email;
    this->senha = senha;
}

unsigned int Usuario::get_id()
{
    return id;
}

string Usuario::get_nome()
{
    return nome;
}

string Usuario::get_email()
{
    return email;
}

std::string Usuario::get_senha()
{
    return senha;
}
