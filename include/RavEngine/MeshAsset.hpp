#pragma once

#include "SharedObject.hpp"
#include <bgfx/bgfx.h>

namespace RavEngine{

class MeshAsset : public SharedObject{
public:
	
	/**
	 Create a MeshAsset
	 @param path the path to the asset in the embedded filesystem
	 */
	MeshAsset(const std::string& path);
	
	const bgfx::VertexBufferHandle& getVertexBuffer(){
		return vertexBuffer;
	}
	const bgfx::IndexBufferHandle& getIndexBuffer(){
		return indexBuffer;
	}
	
	virtual ~MeshAsset(){
		bgfx::destroy(vertexBuffer);
		bgfx::destroy(indexBuffer);
	}
	
protected:
	bgfx::VertexBufferHandle vertexBuffer;
	bgfx::IndexBufferHandle indexBuffer;
};

}
