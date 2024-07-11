@tool
extends EditorPlugin


var VMT_IMPORT_PLUGIN: EditorImportPlugin = null


func _enter_tree():
	VMT_IMPORT_PLUGIN = preload("res://addons/godotsource/scripts/vmt.gd").new()
	add_import_plugin(VMT_IMPORT_PLUGIN)


func _exit_tree():
	remove_import_plugin(VMT_IMPORT_PLUGIN)
	VMT_IMPORT_PLUGIN = null
