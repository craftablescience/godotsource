extends Node


func read_file_bytes(path: String) -> PackedByteArray:
	return FileAccess.get_file_as_bytes(path)


func read_file_str(path: String) -> String:
	return FileAccess.get_file_as_string(path)


func run_tests() -> bool:
	var all_passed := true
	
	var base_dir := "res://scripts/tests"
	for script_name in DirAccess.get_files_at(base_dir):
		var test_script: Script = load(base_dir + '/' + script_name)
		var test_node: Node = Node.new()
		test_node.set_script(test_script)
		
		print("Running tests in " + script_name + "...")
		var count_passed := 0
		var count_total := 0
		for method in test_node.get_method_list():
			if method["name"].begins_with("test_"):
				count_total += 1
				var method_name_pretty: String = method["name"].substr(5).replace('_', ' ').capitalize()
				if test_node.call(method["name"]):
					print_rich("\t- " + method_name_pretty + " [color=#00cc00]SUCCESS[/color]")
					count_passed += 1
				else:
					print_rich("\t- " + method_name_pretty + " [color=#ff5555]FAIL[/color]")
		print("Result: " + str(count_passed) + '/' + str(count_total) + " passed\n")
		if count_passed < count_total:
			all_passed = false
		
		test_node.queue_free()
	
	return all_passed
