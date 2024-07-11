#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>

#include "KeyValues.h"

using namespace godot;

extern "C" [[maybe_unused]] GDExtensionBool GDE_EXPORT kv_init(GDExtensionInterfaceGetProcAddress getProcAddress, GDExtensionClassLibraryPtr library, GDExtensionInitialization* initialization) {
	GDExtensionBinding::InitObject binding{getProcAddress, library, initialization};

	binding.register_initializer([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}

		ClassDB::register_class<KeyValuesElement>();
		ClassDB::register_class<KeyValuesRoot>();
	});

	binding.register_terminator([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}
	});

	binding.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return binding.init();
}
