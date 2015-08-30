#ifndef SHADER_H
#define SHADER_H
#include "Effects/Effect.h"

namespace ME {

class Shader : public Effect {
public:
    enum Type {VERTEX, FRAGMENT};
public:
    Shader(const std::string& fileName, const Shader::Type& type);
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    void setParameter(const std::string& parameter, const double& data);
    void update(Drawable* object);
private:
    bool isShaderEnable();
    Shader();
    sf::Shader mShader;
    bool mIsShaderEnable;
};

}

#endif // SHADER_H
