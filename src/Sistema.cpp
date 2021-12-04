#include "Sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

#include "Sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

/* COMANDOS */
string Sistema::quit() {
  return "Finalizando o Concordo";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
	//procurando se o usuário já existe
	for (auto it = usuarios.begin(); it != usuarios.end(); it++)
		if(email == (*it)->get_email())
			return "Usuário já existe!";

	//criando novo usuário (caso não exista)
	if(idsUsuDel.size()) //caso exista ID livre de um usuário deletado
	{
		usuarios.push_back(new Usuario(idsUsuDel[0], nome, email, senha));
		idsUsuDel.erase(idsUsuDel.begin());
	}
	else //criando usuário com ID novo
	{
		usuarios.push_back(new Usuario(proxId, nome, email, senha));
		proxId++;
	}
	
	return "Usuário criado";
}

std::string Sistema::delete_user (const std::string email, const std::string senha){
	//procurando usuário na lista de usuários
	for (auto itUsu = usuarios.begin(); itUsu != usuarios.end(); itUsu++)
		if(email == (*itUsu)->get_email()) //achar usuário pelo email
		{
			//verificar se está logado (retorna erro caso esteja logado)
			if(usuariosLogados.count((*itUsu)->get_id())) return "O usuário está logado no sistema.";

			//verificar senha
			if(senha != (*itUsu)->get_senha()) return "Senha ou usuário inválidos!";

			//removendo o usuário de todos os servidores e o deixando anônimo
			for (auto& iSer: servidores)
			{
				//verificar se é dono dos canais para deixar anônimo
				for (auto& iCha: *iSer.get_canaisTexto())
				{
					//deixar as mensagens do usuário anônimas
					for (auto& iMen: *iCha.get_mensagens())
						if((*itUsu)->get_id() == iMen.get_enviadaPor()->get_id()) //se for dono: deixar anônimo
							iMen.set_enviadaPor(usuarios[0]); //setando usuário anônimo (deletado) como dono
					
					//verificar se é dono do canal
					if((*itUsu)->get_id() == iCha.get_dono()->get_id()) //se for o dono: deixar anônimo
						iCha.set_dono(usuarios[0]); //setando usuário anônimo (deletado) como dono
				}

				if(iSer.get_dono()->get_email() == email) //se for o dono: deixar anônimo
					iSer.set_dono(usuarios[0]); //setando usuário anônimo (deletado) como dono

				//remover do servidor (e de todos os canais)
				leave_server((*itUsu)->get_id(), iSer.get_nome());
			}

			//removendo usuário
			idsUsuDel.push_back((*itUsu)->get_id()); //armazenando ID deletado
			delete (*itUsu); //desalocando
			usuarios.erase(itUsu); //removendo do vetor

			return "Usuário removido";
		}

	return "Usuário não cadastrado!";
}

string Sistema::login(const string email, const string senha) {
	//procurando usuário por email na lista de usuários
	for (auto& iUsu: usuarios)
		if(iUsu->get_email() == email)
		{
			if(iUsu->get_senha() == senha) //verificando senha
			{
				//logando usuário (sem estar visualizando servidor)
				usuariosLogados[iUsu->get_id()] = {0, 0};
				return "Logado como "+iUsu->get_email();
			}
			else //se a senha for incorreta
				return "Senha ou usuário inválidos!";
		}
	
	//caso não encontre o usuário
	return "Senha ou usuário inválidos!";
}

string Sistema::disconnect(int id) {
	if(usuariosLogados.count(id)) //se o usuário estivar logado
	{
		usuariosLogados.erase(id); //removendo do mapa (deslogando)

		for (auto& iUsu: usuarios)
			if(iUsu->get_id() == id)
				return "Desconectando usuário "+iUsu->get_email();
		
	}

	//se não estiver logado
	return "Não está conectado";
}

string Sistema::create_server(int id, const string nome) {
	return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
	return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
	return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
	return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
	//usar leave_channel em todos os canais desse server (remover o usuário de todos os canais)
	return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
	return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
	return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
	return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::remove_channel(int id, const string nome) {
	return "remove_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
	return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
	return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
	return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
	return "list_messages NÃO IMPLEMENTADO";
}

Sistema::Sistema()
{
	usuarios.push_back(new Usuario(0, "Usuário Deletado", "", "SeNhA_iMpOsSiVeL"));
}

Sistema::~Sistema()
{
	//desalocando todos os usuários
	for (auto it = usuarios.begin(); it != usuarios.end(); it++)
		delete *it; //desalocando usuário
}
