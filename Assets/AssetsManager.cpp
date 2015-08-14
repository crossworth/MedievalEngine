//#include "AssetsManager.h"

//using namespace ME;

//AssetsManager::AssetsManager() {
//    dbg = Debugger::getInstance();
//    dbg->log(VERBOSE, 1,"[AssetsManager::AssetsManager] AssetsManager created");

//    ASSETS_PATH = GLOBAL_PATH + "data/assets/";
//}

//MEid AssetsManager::loadTexture(const std::string &fileName) {
//    sf::Texture* tmpTexture;

//    if (tmpTexture->loadFromFile(ASSETS_PATH + fileName)) {
//        dbg->log(VERBOSE, 1, ("[AssetsManager::loadTexture] Erro while opening texture: " + ASSETS_PATH + fileName).c_str());
//    }

//    MEid textureID = ID::get();

//    mAssets.insert(textureID, tmpTexture);
//    return textureID;
//}
