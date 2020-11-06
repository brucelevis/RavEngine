#include "Texture.hpp"
#include <bimg/bimg.h>
#include <bx/bx.h>
#include <bx/readerwriter.h>
#include "App.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <fstream>

using namespace std;
using namespace RavEngine;


Texture::Texture(const std::string& name){
	//read from resource
	
	auto data = App::Resources->FileContentsAt(("/textures/" + name).c_str());
	
	int width, height,channels;
	stbi_uc const* datastr = reinterpret_cast<const unsigned char* const>(data.c_str());
	auto size = sizeof(stbi_uc) * data.size();
	
	ofstream out(name, ofstream::binary);

	for(int i = 0; i < size; i++){
		out.put(datastr[i]);
	}

	//out.write(data.c_str(),size);
	out.close();
	
	unsigned char* bytes = stbi_load_from_memory(datastr, size, &width, &height, &channels, 4);
	if (bytes == nullptr){
		throw(runtime_error(stbi_failure_reason()));
	}
	
	bool hasMipMaps = false;
	uint16_t numlayers = 1;
	auto format = bgfx::TextureFormat::RGB8;
	const bgfx::Memory* textureData = bgfx::copy(bytes, size);
	
	int flags = BGFX_TEXTURE_SRGB | BGFX_SAMPLER_POINT;
	
	texture = bgfx::createTexture2D(width,height,hasMipMaps,numlayers,format,flags,textureData);
	
	if(!bgfx::isValid(texture)){
		throw runtime_error("Cannot create texture");
	}
}

void Texture::Bind(int id, const Uniform &uniform){
	bgfx::setTexture(id, uniform, texture);
}
