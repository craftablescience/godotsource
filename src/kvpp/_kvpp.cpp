#include "KeyValues.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

extern "C" [[maybe_unused]] GDExtensionBool GDE_EXPORT kvpp_gd_init(GDExtensionInterfaceGetProcAddress getProcAddress, GDExtensionClassLibraryPtr library, GDExtensionInitialization* initialization) {
	GDExtensionBinding::InitObject init_obj{getProcAddress, library, initialization};

	init_obj.register_initializer([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}

		ClassDB::register_internal_class<KeyValuesElement>();
		ClassDB::register_class<KeyValues>();
	});

	init_obj.register_terminator([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}
	});

	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
