#ifndef READ_OBJ_H
#define READ_OBJ_H

#include "Qstring"
#include "meu_objeto.h"

class read_obj
{
public:
    read_obj() =  default;
    int parser(const std::string token);
    Minha_Face *loadObj(const QString& filename);

    const std::string& getError() const { return m_error; }
private:
    std::string m_error;
    int parseIndexF(const std::string& token);

};

#endif // READ_OBJ_H
