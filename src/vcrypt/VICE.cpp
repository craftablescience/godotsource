#include "VICE.h"

#include <godot_cpp/core/class_db.hpp>
#include <vcryptpp/VICE.h>

#include <Convert.h>

using namespace godot;

PackedByteArray VICE::encrypt(const String& data, const String& code) {
	return Convert::bufferToByteArray(vcryptpp::VICE::encrypt(Convert::byteArrayToBuffer(data.to_utf8_buffer()), Convert::stringToStd(code)));
}

PackedByteArray VICE::decrypt(const PackedByteArray& data, const String& code) {
	return Convert::bufferToByteArray(vcryptpp::VICE::decrypt(Convert::byteArrayToBuffer(data), Convert::stringToStd(code)));
}

void VICE::_bind_methods() {
	ClassDB::bind_static_method(get_class_static(), D_METHOD("encrypt", "data", "code"), &VICE::encrypt);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("decrypt", "data", "code"), &VICE::decrypt);
}
