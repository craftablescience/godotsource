#include "VICE.h"

#include <godot_cpp/core/class_db.hpp>
#include <vicepp/vicepp.h>

#include <Conversion.h>

using namespace godot;

PackedByteArray VICE::encrypt(const String& data, const String& code) {
	return Conversion::bufferToByteArray(vicepp::encrypt(Conversion::byteArrayToBuffer(data.to_utf8_buffer()), Conversion::stringToStd(code)));
}

PackedByteArray VICE::decrypt(const PackedByteArray& data, const String& code) {
	return Conversion::bufferToByteArray(vicepp::decrypt(Conversion::byteArrayToBuffer(data), Conversion::stringToStd(code)));
}

void VICE::_bind_methods() {
	ClassDB::bind_static_method(get_class_static(), D_METHOD("encrypt", "data", "code"), &VICE::encrypt);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("decrypt", "data", "code"), &VICE::decrypt);
}
