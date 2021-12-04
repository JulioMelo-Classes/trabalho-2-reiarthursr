#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include "Usuario.hpp"
#include "Mensagem.hpp"
#include <string>
#include <vector>

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
   * @param dono O dono a ser setado para o canal.
   */
  void set_dono(Usuario* dono);

  /**
   * @brief Get the mensagens object
   * 
   * @return std::vector<Mensagem>* mensagens (apenas uma referência para o vetor "mensagens")
   */
  std::vector<Mensagem>* get_mensagens();

};

#endif
