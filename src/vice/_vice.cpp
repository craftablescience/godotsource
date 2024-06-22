#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>

#include "VICE.h"

using namespace godot;

extern "C" [[maybe_unused]] GDExtensionBool GDE_EXPORT vice_init(GDExtensionInterfaceGetProcAddress getProcAddress, GDExtensionClassLibraryPtr library, GDExtensionInitialization* initialization) {
	GDExtensionBinding::InitObject init_obj{getProcAddress, library, initialization};

	init_obj.register_initializer([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}

		ClassDB::register_class<VICE>();
	});

	init_obj.register_terminator([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}
	});

	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
