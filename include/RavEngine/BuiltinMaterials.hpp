#pragma once
#include "Material.hpp"
#include "Uniform.hpp"
#include "Texture.hpp"
#include "Common3D.hpp"

namespace RavEngine {
    /**
     PBR material surface shader.
     Subclass this material to make custom surface shaders
     */
	class PBRMaterial : public Material {
	public:
		PBRMaterial() : Material("pbrmaterial") {}
        friend class PBRMaterialInstance;
    protected:
        SamplerUniform albedoTxUniform = SamplerUniform("s_albedoTex");
        Vector4Uniform albedoColorUniform = Vector4Uniform("albedoColor");
	};

    /**
     Allows attaching a PBR material to an object.
     Subclass to expose additional fields in a custom shader
     */
	class PBRMaterialInstance : public MaterialInstance<PBRMaterial> {
	public:
		PBRMaterialInstance(Ref<PBRMaterial> m) : MaterialInstance(m) { };

		inline void SetAlbedoTexture(Ref<Texture> texture) {
			albedo = texture;
		}
       inline void SetAlbedoColor(const ColorRGBA& c){
            color = c;
        }

        void DrawHook() override;
	protected:
		Ref<Texture> albedo = TextureManager::defaultTexture;
		ColorRGBA color{1,1,1,1};
	};

    /**
     Used internally for debug primitives
     */
	class DebugMaterial : public Material{
	public:
		DebugMaterial() : Material("debug"){};
	};
    /**
     Used internally for debug primitives
     */
	class DebugMaterialInstance : public MaterialInstance<DebugMaterial>{
	public:
		DebugMaterialInstance(Ref<DebugMaterial> m ) : MaterialInstance(m){};		
	};

    class DeferredBlitShader : public Material{
    public:
        DeferredBlitShader() : Material("deferred_blit"){}
    };
}
