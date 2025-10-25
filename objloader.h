#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Qstring.h"
#include "QVector"
#include "meu_objeto.h"

class objloader
{
public:
    objloader() = default;

    Minha_Face* load(const std::string& filename);

    const std::vector<Minha_Face>& getFaces()const {return m_faces; };

    const std::string& getError()const {return m_error; };
private:
    std::vector<Minha_Face> m_faces;
    std::string m_error;

    int parseFaceIndex(const std::string& token);
};

#endif // OBJLOADER_H
