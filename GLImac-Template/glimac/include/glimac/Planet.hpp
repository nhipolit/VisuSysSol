#pragma once
#include "Moon.hpp"
#include "PlanetProgram.hpp"
#include <list>

namespace glimac {
    class Planet{
        private:
            GLuint _texturePlanet;
            GLuint _textureExtra;
            PlanetProgram _programPlanet;
            std::unique_ptr<Image> _imgPlanet;
            std::unique_ptr<Image> _imgExtra;
            std::list<Moon> _moons;
            
            bool _extra;
            float _ellipse;
            float _diameter;
            float _orbitalPeriod;
            float _lengthDays;
            float _orbitalInclination;
            
            void initTexture();
            void initTextureExtra();
            void initMoons(std::list<Moon> moons);
        public:
            Planet(Planet const&);
        
            Planet(std::string pathImg, std::string pathImg2, std::list<Moon> moons, bool extra, float ellipse, float diameter, float orbitalPeriod, float lengthDays, float orbitalInclination, PlanetProgram programPlanet):
            _moons(moons),_ellipse(ellipse), _extra(extra), _diameter(diameter), _orbitalPeriod(orbitalPeriod), _lengthDays(lengthDays), _orbitalInclination(orbitalInclination), _programPlanet(programPlanet){
                _imgPlanet = loadImage(pathImg);
                this->initTexture();
                
                if(_extra){
                    _imgExtra = loadImage(pathImg2);
                    this->initTextureExtra();
                }
            }
    };
}