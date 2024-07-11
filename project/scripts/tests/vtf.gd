extends Node


func test_load() -> bool:
	var vtf := preload("res://test_assets/vtf/image.vtf")
	return vtf.get_height() == 256 && vtf.get_width() == 256
