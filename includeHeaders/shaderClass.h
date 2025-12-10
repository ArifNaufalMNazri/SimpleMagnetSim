#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <fstream>
#include <string>

std::string getFileContents(const char* filename);

class Shader
{
  public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate(GLuint program);
    void Delete();

};

#endif