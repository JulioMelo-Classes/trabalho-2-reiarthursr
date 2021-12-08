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
		usuarios.push_back(new Usuario(proxIdUsu, nome, email, senha));
		proxIdUsu++;
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
	//se o usuário não estivar logado
	if(!usuariosLogados.count(id)) return "Não está conectado";
	
	usuariosLogados.erase(id); //removendo do mapa (deslogando)

	for (auto& iUsu: usuarios)
		if(iUsu->get_id() == id)
			return "Desconectando usuário "+iUsu->get_email();

	return "Erro ao desconectar";
}

string Sistema::create_server(int id, const string nome) {
	//se o usuário não estivar logado
	if(!usuariosLogados.count(id)) return "Não está conectado";

	//se o servidor já existir
	for (auto& iSer: servidores)
		if(iSer.get_nome() == nome) return "Servidor com esse nome já existe";
	
	//criando servidor (e adicionando na lista de servidores)
	for (auto& iUsu: usuarios) //procurando usuário pelo ID
		if(iUsu->get_id() == id)
		{
			servidores.push_back(Servidor(proxIdSer, iUsu, nome));

			proxIdSer++; //aumentando proxIdSer após ser usado

			return "Servidor criado";
		}
	
	return "Erro ao criar servidor";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
	//se o usuário não estivar logado
	if(!usuariosLogados.count(id)) return "Não está conectado";

	for (auto& iSer: servidores) //procurando servidor pelo nome
		if(iSer.get_nome() == nome)
		{
			if(iSer.get_dono()->get_id() != id) //verificar se o usuário é dono
				return "Você não pode alterar a descrição de um servidor que não foi criado por você";

			iSer.set_descricao(descricao); //setando descrição ao servidor

			return "Descrição do servidor ‘"+nome+"’ modificada!";
		}
	
	return "Servidor ‘"+nome+"’ não existe";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	//se o usuário não estivar logado
	if(!usuariosLogados.count(id)) return "Não está conectado";

	for (auto& iSer: servidores) //procurando servidor pelo nome
		if(iSer.get_nome() == nome)
		{
			if(iSer.get_dono()->get_id() != id) //verificar se o usuário é dono
				return "Você não pode alterar o código de convite de um servidor que não foi criado por você";

			iSer.set_descricao(codigo); //setando descrição ao servidor

			if(codigo == "") //se o código for removido
				return "Código de convite do servidor '"+nome+"' removido!";
			return "Código de convite do servidor '"+nome+"' modificada!";
		}
	
	return "Servidor '"+nome+"' não existe";
}

string Sistema::list_servers(int id) {
	//se o usuário não estivar logado
	if(!usuariosLogados.count(id)) return "Não está conectado";

	string retorno; //a lista dos servers a ser retornado

	//armazenando os nomes dos servidores na variável "retorno"
	for (size_t i = 0; i < servidores.size(); i++)
	{
		if(i>0) //adicionando quebra de linha
			retorno += '\n';
		
		retorno += servidores[i].get_nome(); //adicionando nome do servidor
	}
	
	return retorno;
}

string Sistema::remove_server(int id, const string nome) {
	//se o usuário não estivar logado
	if(!usuariosLogados.count(id)) return "Não está conectado";

	for (auto iSer = servidores.begin(); iSer != servidores.end(); iSer++) //procurando servidor pelo nome
		if(iSer->get_nome() == nome)
		{
			if(iSer->get_dono()->get_id() != id) //verificar se o usuário é dono
				return "Você não é o dono do servidor ‘"+nome+"’";

			//fazer usuários não visualizarem o servidor
			for (auto& iULog: usuariosLogados)
				if(iULog.second.first == iSer->get_id()) //se o usuário estiver visualizando o servidor
				{
					iULog.second.first = 0; //parar de visualizar servidor
					iULog.second.second = 0; //parar de visualizar canal
				}

			servidores.erase(iSer); //removendo servidor

			return "Servidor ‘"+nome+"’ removido";
		}

	return "Servidor ‘"+nome+"’ não encontrado";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	//se o usuário não estivar logado
	if(!usuariosLogados.count(id)) return "Não está conectado";

	for (auto& iSer: servidores) //encontrando servidor pelo nome
		if(iSer.get_nome() == nome)
		{
			//verificar código de convite e se o usuário é o dono
			if(codigo != iSer.get_codigoConvite() && codigo != "" && id != iSer.get_dono()->get_id())
				return "Servidor requer código de convite";

			//encontrar usuário pelo ID
			for (auto& iUsu: usuarios)
				if(iUsu->get_id() == id)
				{
					iSer.add_participantes(iUsu); //adicionando aos participantes

					//fazer o usuário visualizar o servidor
					for (auto& iULog: usuariosLogados)
						if(iULog.first == iUsu->get_id()) //procurando usuário pelo ID
							iULog.second.first = iSer.get_id(); //fazer visualizar servidor
				}

			return "Entrou no servidor com sucesso";
		}

	return "Servidor não encontrado";
}

string Sistema::leave_server(int id, const string nome) {
	/*for (auto& iSer: servidores) //procurando servidor pelo nome
		if(iSer.get_nome() == nome)
			for (auto& iULog: usuariosLogados) //se o usuário não estivar conectado ao servidor
				if(iULog.first == id) //procurando usuário logado pelo ID
				{
					if(iULog.second.first == iSer.get_id()) //se o usuário está no servidor
					{
						//fazendo o usuário não visualizar mais
						iULog.second.first = 0;
						iULog.second.second = 0;
						
						for (auto& iUsu: usuarios) //procurando usuário pelo ID
							if(iUsu->get_id() == id)
								iSer.rem_participante(iUsu); //removendo usuário do servidor
						
						return "Saindo do servidor ‘"+nome+"’";
					}
					else //se não estiver
						return "Não está conectado no servidor";
				}*/

	return "Servidor não encontrado";
}

string Sistema::list_participants(int id) {
	for (auto& iULog: usuariosLogados) //procurando usuário logado pelo ID
		if(iULog.first == id)
			for (auto& iSer: servidores) //procurando servidores pelo ID
				if(iSer.get_id() == iULog.second.first)
					return iSer.list_participantes(); //retornando lista de participantes
	
	return "Não está conectado a um servidor";
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
