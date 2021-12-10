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

string Servidor::get_codigoConvite()
{
    return codigoConvite;
}

vector<CanalTexto>* Servidor::get_canaisTexto()
{
    return &canaisTexto;
}

void Servidor::set_dono(Usuario* dono)
{
    this->dono = dono;
}

void Servidor::add_participantes(Usuario* usuario)
{
    //verificar se já está nele
    for (auto& iPar: participantes)
        if(usuario->get_id() == iPar->get_id()) //se os IDs forem iguais (se ele já estiver)
            return;

    //adicionando usuário ao servidor
    participantes.push_back(usuario);
}

void Servidor::rem_participante(Usuario* usuario)
{
    //procurando usuário pelo ID
    for (auto itPar = participantes.begin(); itPar != participantes.end(); itPar++)
        if((*itPar)->get_id() == usuario->get_id())
        {
            participantes.erase(itPar); //removendo usuário
            break;
        }
}

string Servidor::list_participantes()
{
    string lista; //lista que contem todos os participantes
    
    for (size_t i = 0; i < participantes.size(); i++)
    {
		if(i>0) //adicionando quebra de linha
			lista += '\n';
		
		lista += participantes[i]->get_nome(); //adicionando nome do participante
	}

    return lista;
}

string Servidor::list_canaisTexto()
{
    string lista = "#canais de texto\n"; //lista que contem todos os canais de texto
    
    for (size_t i = 0; i < canaisTexto.size(); i++)
    {
		if(i>0) //adicionando quebra de linha
			lista += '\n';
		
		lista += canaisTexto[i].get_nome(); //adicionando nome do canal de texto
	}

    return lista;
}

unsigned int Servidor::prox_id_canal()
{
    proxIdCan++;

    return proxIdCan;
}

bool Servidor::canal_existe(string nome)
{
    for (auto& iCan: canaisTexto)
        if(iCan.get_nome() == nome)
            return true;
    
    return false;
}
