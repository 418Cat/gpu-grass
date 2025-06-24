#version 330 core 

layout (location=0) in vec3 in_pos;
layout (location=1) in vec2 in_uv;

uniform float total_height;
uniform int n_shells;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec2 vs_uv;
out float height;

void main()
{
	vs_uv = in_uv;
	// Set the normalized height based on the shell instance index
	height = float(gl_InstanceID)/float(n_shells);

	vec4 pos = vec4(in_pos, 1.);

	// Multiply normalized height by total_height to get real world height
	pos.y += height*total_height;

	gl_Position = projection * view * model * pos;
}
