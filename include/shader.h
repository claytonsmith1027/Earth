#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath){
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try{
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream;
                std::stringstream fShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                vShaderFile.close();
                fShaderFile.close();
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch(std::fstream::failure e){
                std::cout << "FAILED READING SHADER FILE" << std::endl;
            }

            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            // compile and link shaders to program
            int success;
            char infoLog[512];
            
            GLuint vertexShader;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vShaderCode, NULL);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR COMPILING VERTEX SHADER\n" << infoLog << std::endl;
            }
            
            GLuint fragmentShader;
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR COMPILING VERTEX SHADER\n" << infoLog << std::endl;
            }
            
            ID = glCreateProgram();
            glAttachShader(ID, vertexShader);    
            glAttachShader(ID, fragmentShader);
            glLinkProgram(ID);
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if(!success){
                glGetProgramInfoLog(ID, 512, NULL, infoLog);
                std::cout << "ERROR LINKING PROGRAM\n" << infoLog << std::endl;
            }
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void use(){
            glUseProgram(ID);
        }

        void setBool(std::string& name, bool value) const{
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
        }
        void setInt(std::string& name, int value) const{
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setFloat(std::string& name, float value) const{
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
};