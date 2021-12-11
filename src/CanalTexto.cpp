#include "CanalTexto.hpp"
#include <iostream>

using namespace std;

unsigned int CanalTexto::get_id()
{
    return id;
}

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

unsigned int CanalTexto::prox_id_mensagem()
{
    proxIdMen++;

    return proxIdMen;
}

string CanalTexto::exibir_mensagens()
{
    if(!mensagens.size()) //se não houver mensagens
        return "Sem mensagens para exibir";

    //armazenando mensagens na variável retorno, para retornar depois
    string retorno;
    for (size_t i = 0; i < mensagens.size(); i++)
    {
		if(i>0) //adicionando quebra de linha
			retorno += '\n';

        retorno += mensagens[i].get_enviadaPor()->get_nome(); //adicionando nome de quem enviou
        retorno += mensagens[i].get_dataHora()+": "; //adicionando data e hora do envio
        retorno += mensagens[i].get_conteudo(); //adicionando conteúdo da mensagem
	}

    return retorno;
}
