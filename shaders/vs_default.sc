$input a_position, a_normal
$output v_normal

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

void main()
{
	v_normal = a_normal;
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );;
}
