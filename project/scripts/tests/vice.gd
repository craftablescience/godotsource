extends Node


func test_decrypt() -> bool:
	var decrypted := VICE.decrypt(Test.read_file_bytes("res://test_assets/vice/encrypted.enc"), "x9Ke0BY7").get_string_from_utf8()
	var expected := Test.read_file_str("res://test_assets/vice/decrypted.dec")
	return decrypted == expected


func test_encrypt() -> bool:
	var encrypted := VICE.encrypt(Test.read_file_str("res://test_assets/vice/decrypted.dec"), "x9Ke0BY7")
	var expected := Test.read_file_bytes("res://test_assets/vice/encrypted.enc")
	return encrypted == expected
