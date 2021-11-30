#ifndef USUARIO_H
#define USUARIO_H
#include <string>

// Usuário
class Usuario {
  private:
    /**
     * @brief Um identificador único para o usuário
     * 
     */
    unsigned int id;

    /**
     * @brief O nome cadastrado pelo usuário, conforme o comando create-user
     * 
     */
    std::string nome;

    /**
     * @brief O email cadastrado pelo usuário, conforme o comando create-user
     * 
     */
    std::string email;
    
    /**
     * @brief A senha cadastrada pelo usuário, conforme o comando create-user
     * 
     */
    std::string senha;

  public:

};

#endif
