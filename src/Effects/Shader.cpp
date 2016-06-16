#include "Shader.h"

using namespace ME;

Shader::Shader(const std::string& fileName, const Shader::Type& type) : mLoadedWithoutErros(true), mIsShaderEnable(false) {
    mType = Effect::SHADER;

    if (isShaderAvailable()) {

        std::string shaderLocation = ME::ENGINE_DEFAULTS::SHADER_PATH + fileName;

        if (type == Shader::Type::VERTEX) {
            if (!mShader.loadFromFile(shaderLocation, sf::Shader::Type::Vertex)) {
                mLoadedWithoutErros = false;
                LOG << Log::WARNING
                    << "[Shader::Shader] Vertex Shader not found " + shaderLocation
                    << std::endl;
            }

        } else {
            if (!mShader.loadFromFile(shaderLocation, sf::Shader::Type::Fragment)) {
                mLoadedWithoutErros = false;
                LOG << Log::WARNING
                    << "[Shader::Shader] Fragment Shader not found " + shaderLocation
                    << std::endl;
            }
        }
    } else {
        LOG << Log::WARNING
            << "[Shader::Shader] The Shader is not available"
            << std::endl;
    }
}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) {
    mType = Effect::SHADER;

    if (isShaderAvailable()) {
        std::string vertShaderLocation = ME::ENGINE_DEFAULTS::SHADER_PATH + vertexShader;
        std::string fragShaderLocation = ME::ENGINE_DEFAULTS::SHADER_PATH + fragmentShader;

        if (!mShader.loadFromFile(vertShaderLocation, fragShaderLocation)) {
            mLoadedWithoutErros = false;
            LOG << Log::WARNING
            << "[Shader::Shader] Shaders not found " + vertShaderLocation
            << " " + fragShaderLocation << std::endl;
        }
    } else {
        LOG << Log::WARNING
            << "[Shader::Shader] Shaders are not available" << std::endl;
    }
}

// TODO(Pedro): Implement all the supported paramenter's types
// 2 floats, sf::Vector2f (GLSL type vec2)
// 3 floats, sf::Vector3f (GLSL type vec3)
// 4 floats (GLSL type vec4)
// sf::Color (GLSL type vec4)
// sf::Transform (GLSL type mat4)
// sf::Texture (GLSL type sampler2D)
void Shader::setParameter(const std::string& paramenter, const double& data) {
    if (isShaderAvailable() && mLoadedWithoutErros) {
        mShader.setParameter(paramenter, static_cast<float>(data));
    }
}

void Shader::update(Drawable* object) {
    if (isShaderAvailable() && mLoadedWithoutErros) {
        mShader.setParameter("texture", sf::Shader::CurrentTexture);
        // NOTE(Pedro): If we use a RenderImage we can add more shaders to the same drawable
        object->getRenderState()->shader = &mShader;
    } else {
        setDone();
    }
}

bool Shader::isShaderAvailable() {
    if (sf::Shader::isAvailable()) {
        mIsShaderEnable = true;
    } else {
        mIsShaderEnable = false;
    }
    
    return mIsShaderEnable;
}
