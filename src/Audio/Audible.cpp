#include "Audible.h"

using namespace ME;

// Initialize the value with the engine default's
float Audible::GLOBAL_VOLUME  = ME::ENGINE_DEFAULTS::DEFAULT_VOLUME;
float Audible::VOICE_VOLUME   = ME::ENGINE_DEFAULTS::VOICE_VOLUME;
float Audible::MUSIC_VOLUME   = ME::ENGINE_DEFAULTS::MUSIC_VOLUME;
float Audible::AMBIENT_VOLUME = ME::ENGINE_DEFAULTS::AMBIENT_VOLUME;

bool Audible::mIsFunctionsExported = false;


Audible::Audible() {
	if (!mIsFunctionsExported) {
		exportFunctions();
	}
}

void Audible::exportFunctions() {
	mIsFunctionsExported = true;

    LuaAPI::state.set_function("audio_get_global_volume", []() -> float {
    	return Audible::GLOBAL_VOLUME;
    });
    LuaExportAPI::exports("audio_get_global_volume", "", "float", LuaExportType::FUNCTION,
                        	"get the engine global audio volume");

    LuaAPI::state.set_function("audio_get_voice_volume", []() -> float {
    	return Audible::VOICE_VOLUME;
    });
    LuaExportAPI::exports("audio_get_voice_volume", "", "float", LuaExportType::FUNCTION,
                        	"get the engine voice audio volume");

    LuaAPI::state.set_function("audio_get_music_volume", []() -> float {
    	return Audible::MUSIC_VOLUME;
    });
    LuaExportAPI::exports("audio_get_music_volume", "", "float", LuaExportType::FUNCTION,
                        	"get the engine music audio volume");

    LuaAPI::state.set_function("audio_get_ambient_volume", []() -> float {
    	return Audible::AMBIENT_VOLUME;
    });
    LuaExportAPI::exports("audio_get_ambient_volume", "", "float", LuaExportType::FUNCTION,
                        	"get the engine ambient audio volume");

	LuaAPI::state.set_function("audio_set_global_volume", [this](float volume) {
    	Audible::GLOBAL_VOLUME = volume;
		// TODO(Pedro): set a flag to update the volume, insted of tring to update on the objects, maybe register this functions outside this class as well
    	updateVolume();
    });
    LuaExportAPI::exports("audio_set_global_volume", "", "float", LuaExportType::FUNCTION,
                        	"set the engine global audio volume");

    LuaAPI::state.set_function("audio_set_voice_volume", [this](float volume) {
    	Audible::VOICE_VOLUME = volume;
    	updateVolume();
    });
    LuaExportAPI::exports("audio_set_voice_volume", "", "float", LuaExportType::FUNCTION,
                        	"set the engine voice audio volume");

    LuaAPI::state.set_function("audio_set_music_volume", [this](float volume) {
    	Audible::MUSIC_VOLUME = volume;
    	updateVolume();
    });
    LuaExportAPI::exports("audio_set_music_volume", "", "float", LuaExportType::FUNCTION,
                        	"set the engine music audio volume");

    LuaAPI::state.set_function("audio_set_ambient_volume", [this](float volume) {
    	Audible::AMBIENT_VOLUME = volume;
    	updateVolume();
    });
    LuaExportAPI::exports("audio_set_ambient_volume", "", "float", LuaExportType::FUNCTION,
                        	"set the engine ambient audio volume");


}

Audio::AudioType Audible::getType() {
    return mAudioType;
}

void Audible::setType(const Audio::AudioType& type) {
    mAudioType = type;
}
