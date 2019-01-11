#include "glimac/Moon.hpp"
#include <math.h>
#include <iostream>

namespace glimac{

    void Moon::initTexture(){
        glGenTextures(1,&_textureMoon);
        glBindTexture(GL_TEXTURE_2D, _textureMoon);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgMoon->getWidth(),_imgMoon->getHeight(),0,GL_RGBA,GL_FLOAT,_imgMoon->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    
    void Moon::drawMoon(float planetDiameter, glm::mat4 ProjMatrix, float nb_vertex, float t, GLuint vao, Camera* camera){
        _ellipse.draw(planetDiameter, camera);
        
        float scaleValue = _diameter/planetDiameter;
        float scaleMajorAxis = (_aphelion+_perihelion)/2.0f/planetDiameter;
        float Sin = sin(_inclination);
        float Cos = cos(_inclination);
        
        _programMoon.m_Program.use();
        glUniform1i(_programMoon.uMoonTexture, 0);
        glBindTexture(GL_TEXTURE_2D,_textureMoon);
        
        glm::mat4 viewMatrix = camera->getViewMatrix();
        
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f),glm::vec3(0,0,-5))* viewMatrix; // Translation
        MVMatrix = glm::rotate(MVMatrix, t, glm::vec3(0, Cos, -Sin));
        MVMatrix = glm::translate(MVMatrix, glm::vec3(scaleMajorAxis, 0, 0)); // Translation * Rotation * Translation
        MVMatrix = glm::scale(MVMatrix, glm::vec3(scaleValue, scaleValue, scaleValue)); // Translation * Rotation * Translation * Scale
        
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix))* viewMatrix;
        glm::mat4 MVPMatrix = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(_programMoon.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(_programMoon.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(_programMoon.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0, 8*nb_vertex);

        glBindTexture(GL_TEXTURE_2D,0);
    }
    
    std::string Moon::getName(){
        return _name;
    }
    
    void Moon::deleteTextures(){
        glDeleteTextures(1,&_textureMoon);
    }
}
