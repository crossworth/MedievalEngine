#include "MedievalEngine.h"

using namespace ME;

MedievalEngine* MedievalEngine::mInstance = nullptr;

MedievalEngine* MedievalEngine::getInstance(int argc, char **argv) {
    if (!mInstance) {
        mInstance = new MedievalEngine(argc, argv);
    }
    return mInstance;
}

MedievalEngine::MedievalEngine(int argc, char** argv) : mAssetsManager(nullptr) {
    // handle argc and argv

    mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);

    WindowInfo mWindowInfo;

    std::string tmpBitsPerPixel, tmpHeight, tmpWidth, tmpFullScreen, tmpWindowName;

    tmpBitsPerPixel = mConfigurations.getKey("bits_per_pixel");
    tmpHeight       = mConfigurations.getKey("height");
    tmpWidth        = mConfigurations.getKey("width");
    tmpFullScreen   = mConfigurations.getKey("fullscreen");
    tmpWindowName   = mConfigurations.getKey("engine_name");


    if(tmpBitsPerPixel != "") {
        mWindowInfo.bitsPerPixel = Data2::str_to_int(tmpBitsPerPixel);
    }

    if(tmpHeight != "") {
        mWindowInfo.height = Data2::str_to_int(tmpHeight);
    }

    if(tmpWidth != "") {
        mWindowInfo.width = Data2::str_to_int(tmpWidth);
    }

    if(tmpFullScreen != "") {
        mWindowInfo.fullScreen = Data2::str_to_bool(tmpFullScreen);
    }

    if (tmpWindowName != "") {
        mWindowInfo.windowName = tmpWindowName;
    }

    // parse info from file
    // handle argc and argv

    mWindow.create(mWindowInfo);
    mAssetsManager = AssetsManager::getInstance();

}

void MedievalEngine::init() {





        // Verifica as informações do arquivo de configuração
        // e cria a janela com base nelas ou com base nas defaults
}

void MedievalEngine::run() {
    while(mWindow.isOpen()) {
        mWindow.clear();

        mWindow.display();
    }
}

void MedievalEngine::close() {
    mWindow.close();
    mWindow.~Window();
    mAssetsManager->~AssetsManager();
}

Window* MedievalEngine::getWindow() {
    return &mWindow;
}

AssetsManager* MedievalEngine::getAssetsManager() {
    return mAssetsManager;
}
