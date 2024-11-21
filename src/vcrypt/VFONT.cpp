#include "VFONT.h"

#include <godot_cpp/core/class_db.hpp>
#include <vcryptpp/VFONT.h>

#include <Convert.h>

using namespace godot;

PackedByteArray VFONT::decrypt(const PackedByteArray& data, const String& code) {
	return Convert::bufferToByteArray(vcryptpp::VFONT::decrypt(Convert::byteArrayToBuffer(data)));
}

void VFONT::_bind_methods() {
	ClassDB::bind_static_method(get_class_static(), D_METHOD("decrypt", "data"), &VFONT::decrypt);
}
