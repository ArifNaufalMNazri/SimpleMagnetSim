#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "drawMagnet.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <chrono> 
#include <thread> 

GLFWwindow* createWindow(int width, int height, const char* name){
  GLFWwindow* window=glfwCreateWindow(width, height, name, NULL, NULL);
  if(!window){
    std::cerr<<"ERROR: Window could not be created!\n";
    return nullptr;
  }

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cerr<<"ERROR: Glad could not be loaded!\n";
    return nullptr;
  }

  glViewport(0, 0, width, height);

  return window;
}

float originX, originY, length, magnetStrength, radius;
GLfloat centerX, centerY;

void getInput(){
    while(true){
    std::cout<<"Enter x-origin of magnet: ";
    std::cin>>originX;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Invalid input. Try again\n";
    }
    else{
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
  }

  while(true){
    std::cout<<"Enter y-origin of magnet: ";
    std::cin>>originY;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Invalid input. Try again\n";
    }
    else{
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
  }

  while(true){
    std::cout<<"Enter length of magnet: ";
    std::cin>>length;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Invalid input. Try again\n";
    }
    else{
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
  }
  while(true){
    std::cout<<"Enter strength of magnet(1, 2, 3): ";
    std::cin >>magnetStrength;
    if(magnetStrength!= 1 && magnetStrength != 2 && magnetStrength != 3){
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout<<"Invalid input. Try again\n";
    }
    else{
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
  }

  while(true){
    std::cout<<"Enter radius of circle: ";
    std::cin>>radius;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Invalid input. Try again\n";
    }
    else{
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
  }

  while(true){
    std::cout<<"Enter x-origin of circle: ";
    std::cin>>centerX;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Invalid input. Try again\n";
    }
    else{
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
  }

  while(true){
    std::cout<<"Enter y-origin of circle: ";
    std::cin>>centerY;
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Invalid input. Try again\n";
    }
    else{
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
  }
}

int main(){
  getInput();

  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window=createWindow(600, 600, "magnetSim");

  Magnet magnet("Shaders/default.vert.txt", "Shaders/fragRed.txt", "Shaders/fragBlue.txt", "Shaders/fragWhite.txt", "Shaders/fragCircle.txt");

  magnet.getVertices(originX, originY, length, length/4);

  //Fun fact to put in presentation: Force of magnet on a magnetic object is inversely proportional to distance cubed
  std::vector<GLfloat> outerField, secondField, thirdField, fourthField, fifthField;

  if(magnetStrength==1){
    outerField=magnet.getField(300, magnetStrength);
    secondField=magnet.getField(300, magnetStrength/2);
    thirdField=magnet.getField(300, magnetStrength/4);
  }
  else if(magnetStrength==2){
    outerField=magnet.getField(300, magnetStrength*1.4);
    secondField=magnet.getField(300, magnetStrength*0.85);
    thirdField=magnet.getField(300, magnetStrength/2);
    fourthField=magnet.getField(300, magnetStrength/4);
  }
  else if(magnetStrength==3){
    outerField=magnet.getField(300, magnetStrength*1.1);
    secondField=magnet.getField(300, magnetStrength*0.8);
    thirdField=magnet.getField(300, magnetStrength*0.48);
    fourthField=magnet.getField(300, magnetStrength*0.29);
    fifthField=magnet.getField(300, magnetStrength*0.17);
  }

  std::cout<<"Program Starting...\n";

  glm::vec2 radiusMagneticField={outerField[0] - originX, outerField[1] - originY};
  float radiusDistance=glm::length(radiusMagneticField);

  GLfloat addY, addX;
  glm::vec2 distanceRedPole={magnet.rightEnd.x - centerX, magnet.rightEnd.y - centerY};
  glm::vec2 distanceBluePole={magnet.leftEnd.x - centerX, magnet.leftEnd.y - centerY};

  float redLength=glm::length(distanceRedPole);
  float blueLength=glm::length(distanceBluePole);
  
  bool redLess=true;

  if(redLength<=blueLength){
    if(magnetStrength==1){
      addY=distanceRedPole.y/1000;
      addX=distanceRedPole.x/1000;
    }
    else if(magnetStrength==2){
      addY=distanceRedPole.y/500;
      addX=distanceRedPole.x/500;
    }
    else if(magnetStrength==3){
      addY=distanceRedPole.y/250;
      addX=distanceRedPole.x/250;
    }
  }
  else if(redLength>blueLength){
    if(magnetStrength==1){
      addY=distanceBluePole.y/1000;
      addX=distanceBluePole.x/1000;
    }
    else if(magnetStrength==2){
      addY=distanceBluePole.y/500;
      addX=distanceBluePole.x/500;
    }
    else if(magnetStrength==3){
      addY=distanceBluePole.y/250;
      addX=distanceBluePole.x/250;
    }
    redLess=false;
  }

  std::this_thread::sleep_for(std::chrono::seconds(5));

  GLfloat circleX=centerX;
  GLfloat circleY=centerY;

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    distanceBluePole={magnet.leftEnd.x - centerX, magnet.leftEnd.y - centerY};
    distanceRedPole={magnet.rightEnd.x - centerX, magnet.rightEnd.y - centerY};

    float redLength=glm::length(distanceRedPole);
    float blueLength=glm::length(distanceBluePole);

    magnet.drawMagnet();
    magnet.drawField(300, outerField);
    magnet.drawField(300, secondField);
    magnet.drawField(300, thirdField);
    magnet.drawField(300, fourthField);
    magnet.drawField(300, fifthField);

    magnet.drawCircle(radius, centerX, centerY);
    
    glm::vec2 distanceBallField={originX - centerX, originY - centerY};
    float distanceAB=glm::length(distanceBallField);

    if(distanceAB<=radius + radiusDistance){
      if(redLess){
        if(redLength>radius){
          centerY+=addY;
          centerX+=addX;
        } 
        if(redLength<=radius){
          std::this_thread::sleep_for(std::chrono::seconds(1));
          centerY=circleY;
          centerX=circleX;
        }
      }
      else{
        if(blueLength>radius){
          centerY+=addY;
          centerX+=addX;
        }
        if(blueLength<=radius){
          std::this_thread::sleep_for(std::chrono::seconds(1));
          centerY=circleY;
          centerX=circleX;
        }
      }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  outerField.clear();
  secondField.clear();
  thirdField.clear();
  fourthField.clear();
  fifthField.clear();


  glfwTerminate();
  std::cout<<"Program Ended!\n";
  return 0;
}

//Compile command: g++ main.cpp Src/drawMagnet.cpp Src/shaderClass.cpp Src/EBO.cpp Src/VBO.cpp Src/VAO.cpp glad.c -I"D:/CodeVS/OpenGL/magnetSim/libraries/includeHeaders" -I"D:/CodeVS/OpenGL/magnetSim/libraries/include" -L"D:/CodeVS/OpenGL/magnetSim/libraries/lib-mingw-w64" -lglfw3dll -lopengl32 -lgdi32  -o magnetSim.exe