#include "Shader.h"

using namespace ME;

Shader::Shader(const std::string& fileName, const Shader::Type& type) : mIsShaderEnable(false) {
    mType = Effect::SHADER;

    if (isShaderEnable()) {

        std::string shaderLocation = ME::ENGINE_DEFAULTS::SHADER_PATH + fileName;

        if (type == Shader::Type::VERTEX) {
            if(!mShader.loadFromFile(shaderLocation, sf::Shader::Type::Vertex)) {
                LOG << Log::WARNING
                    << "[Shader::Shader] Vertex Shader not found " + shaderLocation
                    << std::endl;
            } 

        } else {
            if(!mShader.loadFromFile(shaderLocation, sf::Shader::Type::Fragment)) {
                LOG << Log::WARNING
                    << "[Shader::Shader] Fragment Shader not found " + shaderLocation
                    << std::endl;
            } 
        }

    }
}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) {
    mType = Effect::SHADER;

    if (isShaderEnable()) {
        std::string vertShaderLocation = ME::ENGINE_DEFAULTS::SHADER_PATH + vertexShader;
        std::string fragShaderLocation = ME::ENGINE_DEFAULTS::SHADER_PATH + fragmentShader;

        if (!mShader.loadFromFile(vertShaderLocation, fragShaderLocation)) {
                LOG << Log::WARNING
                << "[Shader::Shader] Shaders not found " + vertShaderLocation
                << " " + fragShaderLocation << std::endl;
        }
    }

}

void Shader::setParameter(const std::string& paramenter, const double& data) {
    if (isShaderEnable()) {
        mShader.setParameter(paramenter, static_cast<float>(data));
    }
}

sf::RenderStates* Shader::update(Drawable* object) {
    mRenderStates->shader = &mShader;
    return mRenderStates;
}

bool Shader::isShaderEnable() {
    if (sf::Shader::isAvailable()) {
        mIsShaderEnable = true;
    } else {
        mIsShaderEnable = false;
        setDone();

        LOG << Log::WARNING
            << "[Shader::isShaderEnable] Shaders are not available" << std::endl;
    }
    return mIsShaderEnable;
}
