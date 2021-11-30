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
    /**
     * @brief Construct a new Usuario object
     * 
     * @param id ID do usuário a ser setado.
     * @param nome Nome do usuário a ser setado.
     * @param email E-mail do usuário a ser setado.
     * @param senha Senha do usuário a ser setada.
     */
    Usuario(unsigned int id, std::string nome, std::string email, std::string senha);

    /**
     * @brief Get the id object
     * 
     * @return unsigned int id
     */
    unsigned int get_id();

    /**
     * @brief Get the nome object
     * 
     * @return std::string nome
     */
    std::string get_nome();

    /**
     * @brief Get the email object
     * 
     * @return std::string email
     */
    std::string get_email();

    /**
     * @brief Get the senha object
     * 
     * @return std::string senha
     */
    std::string get_senha();
};

#endif
