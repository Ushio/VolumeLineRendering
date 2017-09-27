#version 410

layout(location = 0) in vec3 in_position;
layout(location = 6) in float in_radius;

uniform mat4 u_mvmat;
uniform mat4 u_pmat;

out float inout_radius;

void main()
{
	gl_Position = u_mvmat * vec4(in_position, 1.0);
	inout_radius = in_radius;
}
