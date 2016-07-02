#ifndef SHADER_H
#define SHADER_H
#include "Effects/Effect.h"

namespace ME {

// TODO(Pedro): Can we have two shader at the same time on the same object?
// Verify sfml exemples to more info about this
// NOTE(Pedro): Yep, we can have more than one shader but we need to draw it to a RenderImage first
// and than apply the second shader to the RenderImage
class Shader : public Effect {
public:
    /**
     * The Shader type
     */
    enum Type {
        VERTEX,  ///< Vertex Shader
        FRAGMENT ///< FRAGMENT Shader
    };
public:
    Shader(const std::string& fileName, const Shader::Type& type);
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    void setParameter(const std::string& parameter, const double& data);
    void update(Drawable* object);
private:
    bool isShaderAvailable();
    bool mLoadedWithoutErros;
    Shader();
    sf::Shader mShader;
    bool mIsShaderEnable;
};

}

#endif // SHADER_H
