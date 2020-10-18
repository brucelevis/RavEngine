#pragma once
#include "Material.hpp"
#include "Uniform.hpp"
#include <array>

namespace RavEngine {
	class DefaultMaterial : public Material {
	public:
		DefaultMaterial() : Material("cubes") {}
	};
	class DefaultMaterialInstance : public MaterialInstance<DefaultMaterial> {
	public:
		DefaultMaterialInstance(Ref<DefaultMaterial> m) : MaterialInstance(m) { };
	};

	class DebugMaterial : public Material{
	public:
		DebugMaterial() : Material("debug"){};
	};

	class DebugMaterialInstance : public MaterialInstance<DebugMaterial>{
	public:
		DebugMaterialInstance(Ref<DebugMaterial> m ) : MaterialInstance(m){};
		void SetColor(const std::array<float,4>& color){
			drawcolor.SetValues(&color[0],4);
		}
	protected:
		Uniform drawcolor = Uniform("u_debugcolor",Uniform::Type::Vec4,4);
	};
}
