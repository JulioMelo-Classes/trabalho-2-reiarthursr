#include "Usuario.hpp"

using namespace std;

Usuario::Usuario(unsigned int id, string nome, string email, string senha)
{
    this->id = id;
    this->nome = nome;
    this->email = email;
    this->senha = senha;
}

string Usuario::get_email()
{
    return email;
}