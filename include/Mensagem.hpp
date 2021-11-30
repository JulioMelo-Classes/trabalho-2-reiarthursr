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

};

#endif
