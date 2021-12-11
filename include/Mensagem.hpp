#ifndef MENSAGEM_H
#define MENSAGEM_H
#include "Usuario.hpp"
#include <string>

// Mensagem
class Mensagem {
  private:
    /**
     * @brief Um identificador único para o esta mensagem
     * 
     */
    unsigned int id;

    /**
     * @brief Um texto representando um timestamp com a data e hora
     * em que a mensagem foi enviada no formato <DD/MM/AAAA - HH:MM>, exemplo: <08/03/2021 - 11:53>
     * 
     */
    std::string dataHora;

    /**
     * @brief Referência do usuário que enviou a mensagem
     * 
     */
    Usuario* enviadaPor;
    
    /**
     * @brief Conteúdo da mensagem
     * 
     */
    std::string conteudo;

  public:
  /**
   * @brief Construct a new Mensagem object
   * 
   * @param id ID da mensagem a ser setado.
   * @param dataHora Data/hora da mensagem a ser setado.
   * @param enviadaPor Usuário que enviou a mensagem.
   * @param conteudo Conteúdo da mensagem.
   */
  Mensagem(unsigned int id, std::string dataHora, Usuario* enviadaPor, std::string conteudo);

  /**
   * @brief Get the dataHora object
   * 
   * @return std::string Data/hora do envio da mensagem.
   */
  std::string get_dataHora();

  /**
   * @brief Get the enviadaPor object
   * 
   * @return Usuario* enviadaPor
   */
  Usuario* get_enviadaPor();

  /**
   * @brief Get the conteudo object
   * 
   * @return std::string Conteúdo da mensagem.
   */
  std::string get_conteudo();

  /**
   * @brief Set the enviadaPor object
   * Serve para deixar o Usuário anônimo após ser deletado.
   * 
   * @param enviadaPor Usuário que enviou a mensagem a ser setado.
   */
  void set_enviadaPor(Usuario* enviadaPor);

};

#endif
