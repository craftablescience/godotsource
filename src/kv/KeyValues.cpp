#include "KeyValues.h"

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <memory>

#include <Convert.h>

using namespace godot;
using namespace kvpp;

constexpr const char* KV1_ELEMENT_DATA_NOT_LOADED = "KV1 element has no data!";
constexpr const char* KV1_ROOT_DATA_ALREADY_LOADED = "KV1 data has already been loaded! This new data will be ignored.";
constexpr const char* KV1_ROOT_DATA_NOT_LOADED = "KV1 data has not been loaded yet!";

String KeyValuesElement::get_key() const {
	ERR_FAIL_COND_V_EDMSG(!this->data, "", KV1_ELEMENT_DATA_NOT_LOADED);
	return Convert::stringToGodot(this->data->element.getKey());
}

String KeyValuesElement::get_value() const {
	ERR_FAIL_COND_V_EDMSG(!this->data, "", KV1_ELEMENT_DATA_NOT_LOADED);
	return Convert::stringToGodot(this->data->element.getValue());
}

String KeyValuesElement::get_conditional() const {
	ERR_FAIL_COND_V_EDMSG(!this->data, "", KV1_ELEMENT_DATA_NOT_LOADED);
	return Convert::stringToGodot(this->data->element.getConditional());
}

bool KeyValuesElement::has_child(const String& childKey) const {
	ERR_FAIL_COND_V_EDMSG(!this->data, false, KV1_ELEMENT_DATA_NOT_LOADED);
	return this->data->element.hasChild(Convert::stringToStd(childKey));
}

uint64_t KeyValuesElement::get_child_count() const {
	ERR_FAIL_COND_V_EDMSG(!this->data, 0, KV1_ELEMENT_DATA_NOT_LOADED);
	return this->data->element.getChildCount();
}

uint64_t KeyValuesElement::get_child_count_with_key(const String& childKey) const {
	ERR_FAIL_COND_V_EDMSG(!this->data, 0, KV1_ELEMENT_DATA_NOT_LOADED);
	return this->data->element.getChildCount(Convert::stringToStd(childKey));
}

Array KeyValuesElement::get_children() const {
	ERR_FAIL_COND_V_EDMSG(!this->data, {}, KV1_ELEMENT_DATA_NOT_LOADED);
	Array array;
	for (const auto& child : this->data->element.getChildren()) {
		Ref<KeyValuesElement> kvElem;
		kvElem.instantiate();
		kvElem->data = std::make_unique<KeyValuesElementData>(KeyValuesElementData{child});
		array.push_back(kvElem);
	}
	return array;
}

Ref<KeyValuesElement> KeyValuesElement::at_n(unsigned int index) const {
	ERR_FAIL_COND_V_EDMSG(!this->data, {}, KV1_ELEMENT_DATA_NOT_LOADED);
	Ref<KeyValuesElement> kvElem;
	kvElem.instantiate();
	kvElem->data = std::make_unique<KeyValuesElementData>(KeyValuesElementData{this->data->element[index]});
	return kvElem;
}

Ref<KeyValuesElement> KeyValuesElement::at_k(const String& childKey) const {
	ERR_FAIL_COND_V_EDMSG(!this->data, {}, KV1_ELEMENT_DATA_NOT_LOADED);
	Ref<KeyValuesElement> kvElem;
	kvElem.instantiate();
	kvElem->data = std::make_unique<KeyValuesElementData>(KeyValuesElementData{this->data->element[Convert::stringToStd(childKey)]});
	return kvElem;
}

Ref<KeyValuesElement> KeyValuesElement::at_kn(const String& childKey, unsigned int n) const {
	ERR_FAIL_COND_V_EDMSG(!this->data, {}, KV1_ELEMENT_DATA_NOT_LOADED);
	Ref<KeyValuesElement> kvElem;
	kvElem.instantiate();
	kvElem->data = std::make_unique<KeyValuesElementData>(KeyValuesElementData{this->data->element(Convert::stringToStd(childKey), n)});
	return kvElem;
}

bool KeyValuesElement::is_invalid() const {
	ERR_FAIL_COND_V_EDMSG(!this->data, true, KV1_ELEMENT_DATA_NOT_LOADED);
	return this->data->element.isInvalid();
}

void KeyValuesElement::setData(const KeyValuesElementData& newData) {
	this->data = std::make_unique<KeyValuesElementData>(newData);
}

void KeyValuesElement::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_key"), &KeyValuesElement::get_key);
	ClassDB::bind_method(D_METHOD("get_value"), &KeyValuesElement::get_value);
	ClassDB::bind_method(D_METHOD("get_conditional"), &KeyValuesElement::get_conditional);
	ClassDB::bind_method(D_METHOD("has_child", "childKey"), &KeyValuesElement::has_child);
	ClassDB::bind_method(D_METHOD("get_child_count"), &KeyValuesElement::get_child_count);
	ClassDB::bind_method(D_METHOD("get_child_count_with_key", "childKey"), &KeyValuesElement::get_child_count_with_key);
	ClassDB::bind_method(D_METHOD("get_children"), &KeyValuesElement::get_children);
	ClassDB::bind_method(D_METHOD("at_n", "index"), &KeyValuesElement::at_n);
	ClassDB::bind_method(D_METHOD("at_k", "childKey"), &KeyValuesElement::at_k);
	ClassDB::bind_method(D_METHOD("at_kn", "childKey", "n"), &KeyValuesElement::at_kn);
	ClassDB::bind_method(D_METHOD("is_invalid"), &KeyValuesElement::is_invalid);
}

void KeyValuesRoot::load_file(const String& kvPath) {
	auto file = FileAccess::open(kvPath, FileAccess::READ);
	if (!file.is_null() && file->is_open()) {
		this->load_str(file->get_as_text());
	}
}

void KeyValuesRoot::load_file_escaped(const String& kvPath) {
	auto file = FileAccess::open(kvPath, FileAccess::READ);
	if (!file.is_null() && file->is_open()) {
		this->load_str_escaped(file->get_as_text());
	}
}

void KeyValuesRoot::load_str(const String& kvData) {
	ERR_FAIL_COND_EDMSG(this->kv, KV1_ROOT_DATA_ALREADY_LOADED);
	this->kv = std::make_unique<KV1>(Convert::stringToStd(kvData));
}

void KeyValuesRoot::load_str_escaped(const String& kvData) {
	ERR_FAIL_COND_EDMSG(this->kv, KV1_ROOT_DATA_ALREADY_LOADED);
	this->kv = std::make_unique<KV1>(Convert::stringToStd(kvData), true);
}

bool KeyValuesRoot::has_child(const String& childKey) const {
	ERR_FAIL_COND_V_EDMSG(!this->kv, false, KV1_ROOT_DATA_NOT_LOADED);
	return this->kv->hasChild(Convert::stringToStd(childKey));
}

uint64_t KeyValuesRoot::get_child_count() const {
	ERR_FAIL_COND_V_EDMSG(!this->kv, 0, KV1_ROOT_DATA_NOT_LOADED);
	return this->kv->getChildCount();
}

uint64_t KeyValuesRoot::get_child_count_with_key(const String& childKey) const {
	ERR_FAIL_COND_V_EDMSG(!this->kv, 0, KV1_ROOT_DATA_NOT_LOADED);
	return this->kv->getChildCount(Convert::stringToStd(childKey));
}

Array KeyValuesRoot::get_children() {
	ERR_FAIL_COND_V_EDMSG(!this->kv, {}, KV1_ROOT_DATA_NOT_LOADED);
	Array array;
	for (const auto& child : this->kv->getChildren()) {
		Ref<KeyValuesElement> kvElem;
		kvElem.instantiate();
		kvElem->setData({child});
		array.push_back(kvElem);
	}
	return array;
}

Ref<KeyValuesElement> KeyValuesRoot::at_n(unsigned int index) {
	ERR_FAIL_COND_V_EDMSG(!this->kv, {}, KV1_ROOT_DATA_NOT_LOADED);
	Ref<KeyValuesElement> kvElem;
	kvElem.instantiate();
	kvElem->setData({(*this->kv)[index]});
	return kvElem;
}

Ref<KeyValuesElement> KeyValuesRoot::at_k(const String& childKey) {
	ERR_FAIL_COND_V_EDMSG(!this->kv, {}, KV1_ROOT_DATA_NOT_LOADED);
	Ref<KeyValuesElement> kvElem;
	kvElem.instantiate();
	kvElem->setData({(*this->kv)[Convert::stringToStd(childKey)]});
	return kvElem;
}

Ref<KeyValuesElement> KeyValuesRoot::at_kn(const String& childKey, unsigned int n) {
	ERR_FAIL_COND_V_EDMSG(!this->kv, {}, KV1_ROOT_DATA_NOT_LOADED);
	Ref<KeyValuesElement> kvElem;
	kvElem.instantiate();
	kvElem->setData({(*this->kv)(Convert::stringToStd(childKey), n)});
	return kvElem;
}

bool KeyValuesRoot::is_invalid() const {
	ERR_FAIL_COND_V_EDMSG(!this->kv, true, KV1_ROOT_DATA_NOT_LOADED);
	return this->kv->isInvalid();
}

void KeyValuesRoot::_bind_methods() {
	ClassDB::bind_method(D_METHOD("load_file", "kvPath"), &KeyValuesRoot::load_file);
	ClassDB::bind_method(D_METHOD("load_file_escaped", "kvPath"), &KeyValuesRoot::load_file_escaped);
	ClassDB::bind_method(D_METHOD("load_str", "kvData"), &KeyValuesRoot::load_str);
	ClassDB::bind_method(D_METHOD("load_str_escaped", "kvData"), &KeyValuesRoot::load_str_escaped);
	ClassDB::bind_method(D_METHOD("has_child", "childKey"), &KeyValuesRoot::has_child);
	ClassDB::bind_method(D_METHOD("get_child_count"), &KeyValuesRoot::get_child_count);
	ClassDB::bind_method(D_METHOD("get_child_count_with_key", "childKey"), &KeyValuesRoot::get_child_count_with_key);
	ClassDB::bind_method(D_METHOD("get_children"), &KeyValuesRoot::get_children);
	ClassDB::bind_method(D_METHOD("at_n", "index"), &KeyValuesRoot::at_n);
	ClassDB::bind_method(D_METHOD("at_k", "childKey"), &KeyValuesRoot::at_k);
	ClassDB::bind_method(D_METHOD("at_kn", "childKey", "n"), &KeyValuesRoot::at_kn);
	ClassDB::bind_method(D_METHOD("is_invalid"), &KeyValuesRoot::is_invalid);
}
