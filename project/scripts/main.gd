extends Node


func _ready():
	var all_passed := Test.run_tests()
	await get_tree().create_timer(0.25).timeout
	get_tree().quit(0 if all_passed else 1)
