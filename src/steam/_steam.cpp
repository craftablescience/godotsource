#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>

#include "Steam.h"

using namespace godot;

extern "C" [[maybe_unused]] GDExtensionBool GDE_EXPORT steam_init(GDExtensionInterfaceGetProcAddress getProcAddress, GDExtensionClassLibraryPtr library, GDExtensionInitialization* initialization) {
	GDExtensionBinding::InitObject binding{getProcAddress, library, initialization};

	binding.register_initializer([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}

		ClassDB::register_class<Steam>();
	});

	binding.register_terminator([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}
	});

	binding.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return binding.init();
}
