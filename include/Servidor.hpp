#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "Usuario.hpp"
#include "CanalTexto.hpp"
#include <string>
#include <vector>

// Canal de Texto
class Servidor {
  private:
    /**
     * @brief Um identificador único para o este servidor
     * 
     */
    unsigned int id;

    /**
     * @brief Referência para o usuário que criou o servidor
     * 
     */
    Usuario* dono;

    /**
     * @brief Nome do servidor, passado no comando create-server
     * 
     */
    std::string nome;

    /**
     * @brief Descrição do servidor passada no comando set-server-desc
     * 
     */
    std::string descricao;

    /**
     * @brief O código de convite do servidor, se houver.
     * Passado no comando set-server-invite-code. Por padrão deve ser uma deve ser uma string vazia.
     * 
     */
    std::string codigoConvite;

    /**
     * @brief Um vetor contendo todos os canais de texto deste servidor
     * 
     */
    std::vector<CanalTexto> canaisTexto;
    
    /**
     * @brief Um vetor contendo referências para todos os participantes deste servidor.
     * Um usuário vira participante de um servidor após usar o comando enter-server.
     * 
     */
    std::vector<Usuario*> participantes;

  public:
    /**
     * @brief Construct a new Servidor object
     * 
     * @param id ID do servidor a ser setado.
     * @param dono Usuário dono do servidor a ser setado.
     * @param nome Nome do servidor a ser setado.
     */
    Servidor(unsigned int id, Usuario* dono, std::string nome);

    /**
     * @brief Get the id object
     * 
     * @return unsigned int id
     */
    unsigned int get_id();

    /**
     * @brief Get the dono object
     * 
     * @return Usuario* dono
     */
    Usuario* get_dono();

    /**
     * @brief Set the dono object
     * Serve para deixar o Usuário anônimo após ser deletado.
     * 
     * @param dono O dono a ser setado para o servidor.
     */
    void set_dono(Usuario* dono);

    /**
     * @brief Get the nome object
     * 
     * @return std::string nome
     */
    std::string get_nome();

    /**
     * @brief Set the descricao object
     * 
     * @param descricao Descrição a ser setada para o servidor.
     */
    void set_descricao(std::string descricao);

    /**
     * @brief Set the codigoConvite object
     * 
     * @param codigo Codigo de convite a ser setado para o servidor.
     */
    void set_codigoConvite(std::string codigo);

    /**
     * @brief Get the canaisTexto object
     * 
     * @return std::vector<CanalTexto>* canaisTexto (apenas a referência do vetor "canaisTexto")
     */
    std::vector<CanalTexto>* get_canaisTexto();

};

#endif
