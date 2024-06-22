#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>

#include "ImageLoaderVTF.h"

using namespace godot;

static Ref<ImageLoaderVTF> g_imageLoaderVTF;

extern "C" [[maybe_unused]] GDExtensionBool GDE_EXPORT vtf_init(GDExtensionInterfaceGetProcAddress getProcAddress, GDExtensionClassLibraryPtr library, GDExtensionInitialization* initialization) {
	GDExtensionBinding::InitObject init_obj{getProcAddress, library, initialization};

	init_obj.register_initializer([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}

		ClassDB::register_internal_class<ImageLoaderVTF>();

		g_imageLoaderVTF.instantiate();
		g_imageLoaderVTF->add_format_loader();
	});

	init_obj.register_terminator([](ModuleInitializationLevel level) {
		if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
			return;
		}

		if (g_imageLoaderVTF.is_null()) {
			return;
		}
		g_imageLoaderVTF->remove_format_loader();
		g_imageLoaderVTF.unref();
	});

	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
