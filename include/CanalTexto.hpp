#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include "Usuario.hpp"
#include "Mensagem.hpp"
#include <string>

// Canal de Texto
class CanalTexto {
  private:
    /**
     * @brief Um identificador único para o este canal
     * 
     */
    unsigned int id;

    /**
     * @brief O nome do canal, conforme o comando create-channel
     * 
     */
    std::string nome;
    
    /**
     * @brief Referência para o usuário que criou este canal
     * 
     */
    Usuario* dono;
    
    /**
     * @brief Um vector com mensagens que foram enviadas neste canal
     * 
     */
    std::vector<Mensagem> mensagens;

  public:

};

#endif
