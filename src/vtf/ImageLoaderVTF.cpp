#include "ImageLoaderVTF.h"

#include <Conversion.h>

using namespace godot;
using namespace vtfpp;

PackedStringArray ImageLoaderVTF::_get_recognized_extensions() const {
	return {"vtf"};
}

Error ImageLoaderVTF::_load_image(const Ref<Image>& image, const Ref<FileAccess>& fileAccess, BitField<ImageFormatLoader::LoaderFlags> flags, double scale) {
	// todo: FLAG_CONVERT_COLORS
	// todo: apply scale

	const auto len = static_cast<int64_t>(fileAccess->get_length() - fileAccess->get_position());
	std::vector<std::byte> buffer;
	buffer.resize(len);
	fileAccess->get_buffer(reinterpret_cast<uint8_t*>(buffer.data()), buffer.size());

	// Parse VTF here
	VTF vtf{buffer};
	if (!vtf) {
		return ERR_INVALID_DATA;
	}

	const auto targetFormat = getVTFTargetFormat(vtf.getFormat());
	auto data = vtf.getImageDataAs(targetFormat.first);
	if (data.empty()) {
		return ERR_INVALID_DATA;
	}
	image->set_data(vtf.getWidth(), vtf.getHeight(), false, targetFormat.second, Conversion::bufferToByteArray(data));

	if (image->is_empty()) {
		return ERR_INVALID_DATA;
	}

	if (vtf.getFlags() & VTF::FLAG_SRGB || flags & FLAG_FORCE_LINEAR) {
		image->srgb_to_linear();
	}
	return OK;
}

void ImageLoaderVTF::_bind_methods() {}

std::pair<ImageFormat, Image::Format> ImageLoaderVTF::getVTFTargetFormat(ImageFormat vtfFormat) {
	switch (vtfFormat) {
		case ImageFormat::DXT1_ONE_BIT_ALPHA:
		case ImageFormat::RGBA16161616:
		case ImageFormat::RGBA8888:
		case ImageFormat::ARGB8888:
		case ImageFormat::BGRA8888:
		case ImageFormat::BGRA4444:
		case ImageFormat::BGRA5551:
		case ImageFormat::ABGR8888:
		case ImageFormat::UVWQ8888:
		case ImageFormat::UVLX8888:           return {ImageFormat::RGBA8888,      Image::FORMAT_RGBA8};
		case ImageFormat::RGB888:
		case ImageFormat::BGRX8888:
		case ImageFormat::BGRX5551:
		case ImageFormat::BGR888:             return {ImageFormat::RGB888,        Image::FORMAT_RGB8};
		case ImageFormat::BGR565:
		case ImageFormat::RGB565:             return {ImageFormat::RGB565,        Image::FORMAT_RGB565};
		case ImageFormat::I8:                 return {ImageFormat::I8,            Image::FORMAT_L8};
		case ImageFormat::IA88:               return {ImageFormat::IA88,          Image::FORMAT_LA8};
		case ImageFormat::P8:
		case ImageFormat::A8:                 return {ImageFormat::A8,            Image::FORMAT_R8};
		case ImageFormat::RGB888_BLUESCREEN:
		case ImageFormat::BGR888_BLUESCREEN:  return {ImageFormat::RGB888,        Image::FORMAT_RGB8};
		case ImageFormat::DXT1:               return {ImageFormat::DXT1,          Image::FORMAT_DXT1};
		case ImageFormat::DXT3:               return {ImageFormat::DXT3,          Image::FORMAT_DXT3};
		case ImageFormat::ATI1N:
		case ImageFormat::ATI2N:
		case ImageFormat::BC7:
		case ImageFormat::DXT5:               return {ImageFormat::DXT5,          Image::FORMAT_DXT5};
		case ImageFormat::UV88:               return {ImageFormat::UV88,          Image::FORMAT_RG8};
		case ImageFormat::BC6H:
		case ImageFormat::RGBA16161616F:      return {ImageFormat::RGBA16161616F, Image::FORMAT_RGBAH};
		case ImageFormat::R32F:               return {ImageFormat::R32F,          Image::FORMAT_RF};
		case ImageFormat::RGB323232F:         return {ImageFormat::RGB323232F,    Image::FORMAT_RGBF};
		case ImageFormat::RGBA32323232F:      return {ImageFormat::RGBA32323232F, Image::FORMAT_RGBAF};
		case ImageFormat::EMPTY:              break;
	}
	return {ImageFormat::EMPTY, Image::FORMAT_MAX};
}
