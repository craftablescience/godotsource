#include "Steam.h"

#include <godot_cpp/core/class_db.hpp>
#include <sourcepp/string/String.h>

#include <Convert.h>

using namespace godot;
using namespace sourcepp;

namespace {

const steampp::Steam& getSteam() {
	static steampp::Steam steam;
	return steam;
}

} // namespace

bool Steam::is_found() {
	return static_cast<bool>(::getSteam());
}

String Steam::get_install_dir() {
	std::string dir{::getSteam().getInstallDir()};
#ifdef _WIN32
	string::normalizeSlashes(dir);
#endif
	return Convert::stringToGodot(dir);
}

PackedStringArray Steam::get_library_dirs() {
#if _WIN32
	PackedStringArray array;
	auto dirs = ::getSteam().getLibraryDirs();
	for (auto& dir : dirs) {
		string::normalizeSlashes(dir);
		array.push_back(Convert::stringToGodot(dir));
	}
	return array;
#else
	return Convert::stringArrayToGodot(::getSteam().getLibraryDirs());
#endif
}

String Steam::get_sourcemod_dir() {
	std::string dir{::getSteam().getSourceModDir()};
#ifdef _WIN32
	string::normalizeSlashes(dir);
#endif
	return Convert::stringToGodot(dir);
}

PackedInt64Array Steam::get_installed_apps() {
	PackedInt64Array array;
	auto apps = ::getSteam().getInstalledApps();
	for (auto app : apps) {
		array.push_back(app);
	}
	return array;
}

bool Steam::is_app_installed(steampp::AppID appID) {
	return ::getSteam().isAppInstalled(appID);
}

String Steam::get_app_name(steampp::AppID appID) {
	return Convert::stringToGodot(::getSteam().getAppName(appID));
}

String Steam::get_app_install_dir(steampp::AppID appID) {
	std::string dir{::getSteam().getAppInstallDir(appID)};
#ifdef _WIN32
	string::normalizeSlashes(dir);
#endif
	return Convert::stringToGodot(dir);
}

String Steam::get_app_icon_path(steampp::AppID appID) {
	std::string path{::getSteam().getAppIconPath(appID)};
#ifdef _WIN32
	string::normalizeSlashes(path);
#endif
	return Convert::stringToGodot(path);
}

String Steam::get_app_logo_path(steampp::AppID appID) {
	std::string path{::getSteam().getAppLogoPath(appID)};
#ifdef _WIN32
	string::normalizeSlashes(path);
#endif
	return Convert::stringToGodot(path);
}

String Steam::get_app_box_art_path(steampp::AppID appID) {
	std::string path{::getSteam().getAppBoxArtPath(appID)};
#ifdef _WIN32
	string::normalizeSlashes(path);
#endif
	return Convert::stringToGodot(path);
}

String Steam::get_app_store_art_path(steampp::AppID appID) {
	std::string path{::getSteam().getAppStoreArtPath(appID)};
#ifdef _WIN32
	string::normalizeSlashes(path);
#endif
	return Convert::stringToGodot(path);
}

bool Steam::is_app_using_source_engine(steampp::AppID appID) {
	return ::getSteam().isAppUsingSourceEngine(appID);
}

bool Steam::is_app_using_source_2_engine(steampp::AppID appID) {
	return ::getSteam().isAppUsingSource2Engine(appID);
}

void Steam::_bind_methods() {
	ClassDB::bind_static_method(get_class_static(), D_METHOD("is_found"), &Steam::is_found);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_install_dir"), &Steam::get_install_dir);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_library_dirs"), &Steam::get_library_dirs);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_sourcemod_dir"), &Steam::get_sourcemod_dir);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_installed_apps"), &Steam::get_installed_apps);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("is_app_installed", "appID"), &Steam::is_app_installed);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_app_name", "appID"), &Steam::get_app_name);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_app_install_dir", "appID"), &Steam::get_app_install_dir);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_app_icon_path", "appID"), &Steam::get_app_icon_path);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_app_logo_path", "appID"), &Steam::get_app_logo_path);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_app_box_art_path", "appID"), &Steam::get_app_box_art_path);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("get_app_store_art_path", "appID"), &Steam::get_app_store_art_path);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("is_app_using_source_engine", "appID"), &Steam::is_app_using_source_engine);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("is_app_using_source_2_engine", "appID"), &Steam::is_app_using_source_2_engine);
}
