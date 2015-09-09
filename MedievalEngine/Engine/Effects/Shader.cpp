#include "Shader.h"

using namespace ME;

Shader::Shader(const std::string& fileName, const Shader::Type& type) : mIsShaderEnable(false) {
    mType = Effect::SHADER;

    // TODO(Pedro): Log here if the shader is not enable
    // and not on the isShaderEnable
    if (isShaderEnable()) {

        std::string shaderLocation = ME::ENGINE_DEFAULTS::SHADER_PATH + fileName;

        //TODO(Pedro): Set a variable if we could not load a shader and
        // on the update method we just verify if we loaded the shader first
        // no pointer updating something that it's not doing nothing
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

// TODO(Pedro): Could we remove one of theses?
// Make a private loader maybe or something different
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
    if (isShaderEnable()) {
        mShader.setParameter(paramenter, static_cast<float>(data));
    }
}

sf::RenderStates* Shader::update(Drawable* object) {
    // TODO(Pedro): Make an if we have loaded the shader without problems and if the shader is available

    // set the texture if we need work with on the GLSL land
    mShader.setParameter("texture", sf::Shader::CurrentTexture);
    mRenderStates->shader = &mShader;
    // Return an sf::RenderStates with the shader
    return mRenderStates;
}

bool Shader::isShaderEnable() {
    if (sf::Shader::isAvailable()) {
        mIsShaderEnable = true;
    } else {
        mIsShaderEnable = false;

        // We call setDone so we can remove our-selves from the object
        setDone();
    }
    return mIsShaderEnable;
}
