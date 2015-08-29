#include "Blur.h"

using namespace ME;

Blur::Blur(const double& amount) : mIsShaderEnable(false) {
    mType = Effect::BLUR;

    if (isShaderEnable()) {
        mIsShaderEnable = true;

        std::string shaderLocation = ME::ENGINE_DEFAULTS::ASSETS_PATH + "shaders/blur.frag";

        if(!mShader.loadFromFile(shaderLocation, sf::Shader::Type::Fragment)) {
            LOG << Log::WARNING
                << "[Blur::Blur] Blur Shader not found " + ME::ENGINE_DEFAULTS::ASSETS_PATH + "shaders/blur.vert"
                << std::endl;
        } else {
            setAmount(amount);
        }
    }
}

void Blur::setAmount(const double& amount) {
    if (isShaderEnable()) {
        mAmount = amount;
        mShader.setParameter("blur_radius", static_cast<float>(amount));
    }
}

void Blur::update(Drawable* object) {
    mRenderStates->shader = &mShader;
}


bool Blur::isShaderEnable() {
    if (sf::Shader::isAvailable()) {
        mIsShaderEnable = true;
    } else {
        mIsShaderEnable = false;
        setDone();

        LOG << Log::WARNING
            << "[Blur::isShaderEnable] Shaders are not available" << std::endl;
    }
    return mIsShaderEnable;
}
