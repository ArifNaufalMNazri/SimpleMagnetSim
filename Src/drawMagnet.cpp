#include "drawMagnet.h"

Magnet::Magnet(const char* vertexFile, const char* fragmentFileRed, const char* fragmentFileBlue, const char* fragmentLine, const char* fragmentCircle){
  Shader shaderProgramRed(vertexFile, fragmentFileRed);
  Shader shaderProgramBlue(vertexFile, fragmentFileBlue);
  Shader shaderProgramLine(vertexFile, fragmentLine);
  Shader shaderProgramCircle(vertexFile, fragmentCircle);

  red=shaderProgramRed.ID;
  blue=shaderProgramBlue.ID;
  line=shaderProgramLine.ID;
  Circle=shaderProgramCircle.ID;

  order={
    1,3,2,
    1,0,2
  };

  std::cout<<"Creating Magnet...\n";
}

void Magnet::getVertices(float originX, float originY, float length, float width){
  origin={originX, originY};

  //Get values for lengths and width
  GLfloat redLength=originX+(length/2);
  GLfloat blueLength=originX-(length/2);
  GLfloat upWidth=originY+(width/2);
  GLfloat downWidth=originY-(width/2);
  
  rightEnd={redLength-0.01f, originY};
  leftEnd={blueLength+0.01f, originY};
   
  glm::vec2 distance=rightEnd - leftEnd;
  radiusField= (glm::length(distance)/2);
  
  //Push values into verticesRed
  verticesRed.push_back(redLength);
  verticesRed.push_back(upWidth);
  verticesRed.push_back(0.0f);
  
  verticesRed.push_back(originX);
  verticesRed.push_back(upWidth);
  verticesRed.push_back(0.0f);

  verticesRed.push_back(redLength);
  verticesRed.push_back(downWidth);
  verticesRed.push_back(0.0f);

  verticesRed.push_back(originX);
  verticesRed.push_back(downWidth);
  verticesRed.push_back(0.0f);
  
  //Push values into verticesBlue
  verticesBlue.push_back(blueLength);
  verticesBlue.push_back(upWidth);
  verticesBlue.push_back(0.0f);

  verticesBlue.push_back(originX);
  verticesBlue.push_back(upWidth);
  verticesBlue.push_back(0.0f);

  verticesBlue.push_back(blueLength);
  verticesBlue.push_back(downWidth);
  verticesBlue.push_back(0.0f);

  verticesBlue.push_back(originX);
  verticesBlue.push_back(downWidth);
  verticesBlue.push_back(0.0f);

}

void Magnet::drawMagnet(){
  //Create and bind VAOred object
  VAO VAOred;
  VAOred.Bind();
  
  //Create VBOred and EBOred objects
  VBO VBOred(verticesRed.data(), verticesRed.size()*sizeof(float));
  EBO EBOred(order.data(), order.size()*sizeof(GLuint));
  
  VAOred.LinkVBO(VBOred, 0);
  VAOred.Unbind();//Only unbind VAO after linking
  
  //Create and bind VAOblue object
  VAO VAOblue;
  VAOblue.Bind();

  //Create VBOblue and EBOblue objects
  VBO VBOblue(verticesBlue.data(), verticesBlue.size()*sizeof(float));
  EBO EBOblue(order.data(), order.size()*sizeof(float));

  VAOblue.LinkVBO(VBOblue, 0);
  VAOblue.Unbind();
  
  glUseProgram(red);

  VAOred.Bind();//Bind the VAO

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//Draw the six orders in the order[] array

  glUseProgram(blue);

  VAOblue.Bind();

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

std::vector<GLfloat> Magnet::getField(int segments, float wide){
  std::vector<GLfloat> field;
  float r=radiusField*wide + 0.1f;

  for(int i=0; i<segments; i++){
    float angle=(2*3.14159*i)/segments;

    GLfloat Xcenter=(rightEnd.x + leftEnd.x)/2;
    GLfloat Ycenter=(rightEnd.y + leftEnd.y)/2;

    float x=Xcenter+r*cos(angle);
    float y=Ycenter+r*sin(angle);

    field.push_back(x);
    field.push_back(y);

  }

  return field;
}

void Magnet::drawField(int segments, std::vector<GLfloat> field){
  GLuint VAO, VBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, field.size()*sizeof(float), field.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glUseProgram(line);

  glDrawArrays(GL_LINE_LOOP, 0, field.size()/2);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

std::vector<GLfloat> Magnet::getCircle(float radius, GLfloat centerX, GLfloat centerY){
  std::vector<GLfloat> vertices;

  vertices.push_back(centerX);
  vertices.push_back(centerY);
  vertices.push_back(0.0f);

  for(int i=0; i<=300; i++){
    float angle=(2*3.14159*i)/300;

    float x=centerX+radius*cos(angle);
    float y=centerY+radius*sin(angle);

    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0f);

  }  

  return vertices;
}

void Magnet::drawCircle(float radius, GLfloat centerX, GLfloat centerY){
  std::vector<GLfloat> circle=getCircle(radius, centerX, centerY);

  VAO VAO;
  VAO.Bind();

  VBO VBO(circle.data(), circle.size()*sizeof(float));

  VAO.LinkVBO(VBO, 0);
  VAO.Unbind();

  glUseProgram(Circle);

  VAO.Bind();

  glDrawArrays(GL_TRIANGLE_FAN, 0, 302);
  
}


Magnet::~Magnet(){
  glDeleteProgram(red);
  glDeleteProgram(blue);
  glDeleteProgram(line);

  std::cout<<"Magnet Destroyed!\n";
}