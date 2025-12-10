#ifndef DRAWMAGNET_CLASS_H
#define DRAWMAGNET_CLASS_H

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <iostream>


class Magnet{
  public: 
    GLuint red, blue, line, Circle;
    std::vector<float> verticesRed;
    std::vector<float> verticesBlue;
    glm::vec2 rightEnd, leftEnd;
    float radiusField;
    float mass;
    glm::vec2 distanceVector, origin;
    std::vector<GLuint> order;
    
    Magnet(const char* vertexFile, const char* fragmentFileRed, const char* fragmentFileBlue, const char* fragmentLine, const char* fragmentCircle);

    void getVertices(float originX, float originY, float length, float width);

    void drawMagnet();

    std::vector<GLfloat> getField(int segments, float wide);

    void drawField(int segments, std::vector<GLfloat> field);

    std::vector<GLfloat> getCircle(float radius, GLfloat centerX, GLfloat centerY);

    void drawCircle(float radius, GLfloat centerX, GLfloat centerY);

    ~Magnet();
};

#endif