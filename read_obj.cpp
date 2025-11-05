#include "read_obj.h"
#include "Qvector"
#include <fstream>
#include <sstream>
#include <iostream>
#include "QFileInfo"
#include "qdebug.h"

int read_obj::parser(const std::string token){
    size_t slash = token.find('/');
    std::string substring = token.substr(0, slash);
    return std::stoi(substring);
}

Minha_Face *read_obj::loadObj(const QString& filename){

    std::string std_filename = filename.toStdString();
    std::vector<Meu_Ponto> vertices;
    std::ifstream file(std_filename);
    if(!file.is_open()){
        m_error = "Erro: Nao foi possivel abrir" + std_filename;
        return nullptr;
    }
    QFileInfo fileInfo(filename);
    std::string objectName = fileInfo.baseName().toStdString();

    Minha_Face *objetoUnico = new Minha_Face(objectName);

    std::string line;

    vertices.emplace_back("", 0, 0, 0);
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if(prefix=="v"){
            double x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back("", x, y, z);
        }else if(prefix == "f"){
            std::vector<int> faceIdx;
            std::string token;
            while (iss >> token){
                int idx = parser(token);
                faceIdx.push_back(idx);
            }
            for(size_t i = 0; i < faceIdx.size(); ++i){
                int idx1 = faceIdx[i];
                int idx2 = faceIdx[(i + 1) % faceIdx.size()];

                const auto& v1 = vertices[idx1];

                const auto& v2 = vertices[idx2];

                objetoUnico->addLinha(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
            }
        }else{

        }
    }
    file.close();
    return objetoUnico;
}






