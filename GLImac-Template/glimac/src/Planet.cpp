#include "glimac/Planet.hpp"

namespace glimac{
    void Planet::initTexture(){
        glGenTextures(1,&_texturePlanet);
        glBindTexture(GL_TEXTURE_2D, _texturePlanet);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgPlanet->getWidth(),_imgPlanet->getHeight(),0,GL_RGBA,GL_FLOAT,_imgPlanet->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Planet::initTextureExtra(){
        glGenTextures(1,&_textureExtra);
        glBindTexture(GL_TEXTURE_2D, _textureExtra);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_imgExtra->getWidth(),_imgExtra->getHeight(),0,GL_RGBA,GL_FLOAT,_imgExtra->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void Planet::drawPlanet(float sunDiameter, float sunRotation){
    
    }
    
    void Planet::deleteTextures(){
        glDeleteTextures(1,&_texturePlanet);
        if(_extra)
            glDeleteTextures(1,&_textureExtra);
        for(Moon & moon : _moons)
            moon.deleteTextures();
    }
}
