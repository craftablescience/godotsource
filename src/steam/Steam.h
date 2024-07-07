#pragma once

#include <godot_cpp/core/object.hpp>
#include <steampp/steampp.h>

namespace godot {

class Steam : public Object {
	GDCLASS(Steam, Object) // NOLINT(*-default-arguments, *-use-auto)

public:
	Steam() = default;

	static bool is_found();

	static String get_install_dir();

	static PackedStringArray get_library_dirs();

	static String get_sourcemod_dir();

	static PackedInt64Array get_installed_apps();

	static bool is_app_installed(steampp::AppID appID);

	static String get_app_name(steampp::AppID appID);

	static String get_app_install_dir(steampp::AppID appID);

	static String get_app_icon_path(steampp::AppID appID);

	static String get_app_logo_path(steampp::AppID appID);

	static String get_app_box_art_path(steampp::AppID appID);

	static String get_app_store_art_path(steampp::AppID appID);

	static bool is_app_using_source_engine(steampp::AppID appID);

	static bool is_app_using_source_2_engine(steampp::AppID appID);

protected:
	static void _bind_methods();
};

} // namespace godot
