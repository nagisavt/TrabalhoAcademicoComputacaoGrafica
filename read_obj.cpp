#include "read_obj.h"
#include "Qvector"
#include <fstream>
#include <sstream>
#include <iostream>
#include "QFileInfo"

Minha_Face* read_obj::load(const QString& filename){
    m_error.clear();

    std::string std_filename = filename.toStdString();

    std::vector<Meu_Ponto> temp_vertices;
    std::ifstream file(std_filename);
    if(!file.is_open()){
        m_error = "Erro: Nao foi possivel abrir" + std_filename;
        return nullptr;
    }
    QFileInfo fileInfo(filename);
    std::string objectName = fileInfo.baseName().toStdString();

    Minha_Face* objetoUnico = new Minha_Face(objectName);

    std::string line;
    int lineNumber = 0;

    while(std::getline(file, line)){
        lineNumber++;
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if(prefix=="v"){
            double x, y, z;
            if(!(iss >> x >> y >> z)){
                m_error = "Erro na linha" + std::to_string(lineNumber) + "Linha 'v' mal formatada";
                file.close();
                delete objetoUnico;
                return nullptr;
            }
            temp_vertices.emplace_back("v_temp", x, y, z);
        }else if(prefix == "f"){
            std::vector<int> face_v_indices;
            std::string token;
            while (iss >> token){
                int v_idx = parseIndexF(token);
                if(v_idx < 0 || v_idx >= temp_vertices.size()){
                    m_error = "Erro na linha" + std::to_string(lineNumber) + ": Indice de vertice invalido";
                    file.close();
                    delete objetoUnico;
                    return nullptr;
                }
                face_v_indices.push_back(v_idx);
            }
            if(face_v_indices.size() < 3) continue;
            for(size_t i = 0; i < face_v_indices.size(); ++i){
                int idx1 = face_v_indices[i];
                int idx2 = face_v_indices[i];

                const auto& v1 = temp_vertices[idx1];
                const auto& v2 = temp_vertices[idx2];

                objetoUnico->addLinha(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);
            }
        }
    }
    return objetoUnico;
}

int read_obj::parseIndexF(const std::string& token){
    try{
        size_t first_slash = token.find('/');
        std::string v_str = token.substr(0, first_slash);
        return std::stoi(v_str) -1;
    }catch(const std::exception& e){
        (void)e;
        return -1;
    }
}






