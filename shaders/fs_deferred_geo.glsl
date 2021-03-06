$input v_normal, v_texcoord0, v_worldpos

#include "common.sh"
#include <bgfx_shader.sh>
#include "pbr_fs.glsl"

SAMPLER2D(s_albedoTex,0);
uniform vec4 albedoColor;

void main()
{
	PBR material = make_mat();
	material.color = texture2D(s_albedoTex, v_texcoord0) * albedoColor;
	material.normal = v_normal;
	material.position = v_worldpos;
	
	store(material);
}

