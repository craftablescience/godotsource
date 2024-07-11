extends Node


func test_read_empty() -> bool:
	var kv1 := KeyValuesRoot.new()
	kv1.load_str("")
	return kv1.get_child_count() == 0


func test_read_block() -> bool:
	var kv1 := KeyValuesRoot.new()
	kv1.load_str("""
"block"
{
}
""")
	return kv1.get_child_count() == 1 and \
		   kv1.at_n(0).get_key() == "block" and \
		   kv1.at_n(0).get_value() == "" and \
		   kv1.at_n(0).get_child_count() == 0


func test_read_blocks() -> bool:
	var kv1 := KeyValuesRoot.new()
	kv1.load_str("""
"block1"
{
}
"block2"
{
}
""")
	return kv1.get_child_count() == 2 and \
		   kv1.at_n(0).get_key() == "block1" and \
		   kv1.at_n(0).get_value() == "" and \
		   kv1.at_n(0).get_child_count() == 0 and \
		   kv1.at_n(1).get_key() == "block2" and \
		   kv1.at_n(1).get_value() == "" and \
		   kv1.at_n(1).get_child_count() == 0


func test_read_keys() -> bool:
	var kv1 := KeyValuesRoot.new()
	kv1.load_str("""
"keys"
{
	"test"   "1"
	"test 2"  0
}
""")
	return kv1.get_child_count() == 1 and \
		   kv1.at_n(0).get_key() == "keys" and \
		   kv1.at_k("keys").get_value() == "" and \
		   kv1.at_k("keys").get_child_count() == 2 and \
		   kv1.at_k("keys").at_n(0).get_key() == "test" and \
		   kv1.at_k("keys").at_k("test").get_value() == "1" and \
		   kv1.at_k("keys").at_k("test").get_child_count() == 0 and \
		   kv1.at_k("keys").at_n(1).get_key() == "test 2" and \
		   kv1.at_k("keys").at_k("test 2").get_value() == "0" and \
		   kv1.at_k("keys").at_k("test 2").get_child_count() == 0


func test_read_escaped() -> bool:
	var kv1 := KeyValuesRoot.new()
	kv1.load_str_escaped("""
"\\"keys\\""
{
	"te\\"st"  "\\1\\in"
	"test\\t2"  0\\n
}
""")
	return kv1.get_child_count() == 1 and \
		   kv1.at_n(0).get_key() == "\"keys\"" and \
		   kv1.at_k("\"keys\"").get_value() == "" and \
		   kv1.at_k("\"keys\"").get_child_count() == 2 and \
		   kv1.at_k("\"keys\"").at_n(0).get_key() == "te\"st" and \
		   kv1.at_k("\"keys\"").at_k("te\"st").get_value() == "\\1\\in" and \
		   kv1.at_k("\"keys\"").at_k("te\"st").get_child_count() == 0 and \
		   kv1.at_k("\"keys\"").at_n(1).get_key() == "test\t2" and \
		   kv1.at_k("\"keys\"").at_k("test\t2").get_value() == "0\n" and \
		   kv1.at_k("\"keys\"").at_k("test\t2").get_child_count() == 0


func test_read_comments() -> bool:
	var kv1 := KeyValuesRoot.new()
	kv1.load_str("""
"keys"
{   // cool
	"test"   "1" // so nice
	"test 2"  0  // here's another one
}
// Wowie
""")
	return kv1.get_child_count() == 1 and \
		   kv1.at_n(0).get_key() == "keys" and \
		   kv1.at_k("keys").get_value() == "" and \
		   kv1.at_k("keys").get_child_count() == 2 and \
		   kv1.at_k("keys").at_n(0).get_key() == "test" and \
		   kv1.at_k("keys").at_k("test").get_value() == "1" and \
		   kv1.at_k("keys").at_k("test").get_child_count() == 0 and \
		   kv1.at_k("keys").at_n(1).get_key() == "test 2" and \
		   kv1.at_k("keys").at_k("test 2").get_value() == "0" and \
		   kv1.at_k("keys").at_k("test 2").get_child_count() == 0


func test_read_children() -> bool:
	var kv1 := KeyValuesRoot.new()
	kv1.load_str("""
"keys"
{
	"test"   "1"
	"test 2"  0
}
""")
	if kv1.at_k("keys").get_children().is_empty():
		return false
	for element in kv1.at_k("keys").get_children():
		if not element.get_key().begins_with("test"):
			return false
	return true
