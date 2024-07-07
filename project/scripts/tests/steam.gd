extends Node


func test_apps() -> bool:
	if OS.get_environment("NO_STEAM") == "1":
		return true

	# Going to assume the runner has *something* installed
	if not Steam.is_found():
	    return false

	var app_list := Steam.get_installed_apps()
	return not app_list.is_empty()
