@tool
extends EditorImportPlugin


enum Presets {
	DEFAULT,
}


func _get_priority() -> float:
	return 1.0


func _get_import_order() -> int:
	return ResourceImporter.IMPORT_ORDER_DEFAULT


func _get_importer_name() -> String:
	return "godotsource.vmt"


func _get_visible_name() -> String:
	return "Source Engine VMT"


func _get_recognized_extensions() -> PackedStringArray:
	return ["vmt"]


func _get_save_extension() -> String:
	return "material"


func _get_resource_type() -> String:
	return "ShaderMaterial"


func _get_preset_count() -> int:
	return Presets.size()


func _get_preset_name(preset_index) -> String:
	match preset_index:
		Presets.DEFAULT:
			return "Default"
		_:
			return "Unknown"


func _get_import_options(_path: String, preset_index: int) -> Array[Dictionary]:
	match preset_index:
		Presets.DEFAULT:
			return []
		_:
			return []


func _get_option_visibility(_path: String, _option_name: StringName, _options: Dictionary) -> bool:
	return true


func find_shader(name: String) -> Shader:
	name = name.to_lower()
	if FileAccess.file_exists("res://shaders/" + name + ".gdshader"):
		return load("res://shaders/" + name + ".gdshader")
	elif FileAccess.file_exists("res://addons/godotsource/shaders/" + name + ".gdshader"):
		return load("res://addons/godotsource/shaders/" + name + ".gdshader")
	return preload("res://addons/godotsource/shaders/unknown.gdshader")


func get_shader_uniform_names(shader: Shader) -> PackedStringArray:
	var array := PackedStringArray()
	for info in shader.get_shader_uniform_list():
		array.append(info["name"])
	return array


func set_shader_texture2D(material: ShaderMaterial, key: String, value: String) -> void:
	material.set_shader_parameter(key, load("res://materials/" + value.replace('\\', '/') + ".vtf"))
	material.set_shader_parameter(key + "_enabled", true)


func set_shader_int(material: ShaderMaterial, key: String, value: String) -> void:
	material.set_shader_parameter(key, value.strip_edges().to_int())


func set_shader_float(material: ShaderMaterial, key: String, value: String) -> void:
	material.set_shader_parameter(key, value.strip_edges().to_float())


func set_shader_boolean(material: ShaderMaterial, key: String, value: String) -> void:
	material.set_shader_parameter(key, value.strip_edges() != '0')


func _import(in_path: String, out_path: String, _options: Dictionary, _platform_variants: Array[String], _gen_files: Array[String]) -> Error:
	var SET_SHADER_UNIFORM_MAP := {
		"texture2D": Callable(self, "set_shader_texture2D"),
		"int":       Callable(self, "set_shader_int"),
		"float":     Callable(self, "set_shader_float"),
		"boolean":   Callable(self, "set_shader_boolean"),
	}
	
	var PARAMETER_MAP := {
		"basetexture":   "texture2D",
		"translucent":   "boolean",
		"bumpmap":       "texture2D",
		"halflambert":   "boolean",
		"selfillum":     "boolean",
		"phong":         "boolean",
		"phongexponent": "int",
		"phongboost":    "float",
	}
	
	var vmt := KeyValuesRoot.new()
	vmt.load_file(in_path)
	
	if vmt.get_child_count() == 0:
		return ERR_PARSE_ERROR
	
	var material := ShaderMaterial.new()
	material.shader = find_shader(vmt.at_n(0).get_key())
	var shaderUniforms := get_shader_uniform_names(material.shader)
	
	var parameters: Array = vmt.at_n(0).get_children()
	for parameter in parameters:
		var paramName: String = parameter.get_key()
		if not paramName.begins_with('$'):
			continue
		paramName = paramName.substr(1)
		
		var paramValue: String = parameter.get_value()
		if paramName in PARAMETER_MAP and paramName in shaderUniforms:
			SET_SHADER_UNIFORM_MAP[PARAMETER_MAP[paramName]].call(material, paramName, paramValue)
	
	var filename = out_path + "." + _get_save_extension()
	return ResourceSaver.save(material, filename)
