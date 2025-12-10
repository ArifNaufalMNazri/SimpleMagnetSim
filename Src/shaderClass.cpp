#include "shaderClass.h"

std::string getFileContents(const char* filename){
  std::ifstream in(filename, std::ios::binary);
  
  //Check if file found
  if(!in){
    std::cerr<<"ERROR: '"<<filename<<"' not found!\n";
    throw("File not found");
  }
  else{
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile){

  std::string vertexCode = getFileContents(vertexFile);
  std::string fragmentCode= getFileContents(fragmentFile);

  const char* vertexSource= vertexCode.c_str();
  const char* fragmentSource= fragmentCode.c_str();

  GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  
  //Check Vertex Shader
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR: Vertex Shader failed to compile\n" << infoLog << std::endl;
  }
  
  GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  //Check Fragment Shader
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr<<"ERROR: Fragment Shader failed to compile\n"<<infoLog<<std::endl;
  }
  
  //Attach Shaders to Program
  ID=glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cerr<<"ERROR: Program failed to link Shaders"<<infoLog<<std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

}

void Shader::Activate(GLuint program){
  glUseProgram(program);
}

void Shader::Delete(){
  glDeleteProgram(ID);
}