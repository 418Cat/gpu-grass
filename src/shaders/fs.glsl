#version 410 core 

in vec2 vs_uv;

uniform float height;
uniform int n_squares;

out vec4 fs_color;

/* Copyright (c)2014 David Hoskins */
float hash12(vec2 p)
{
	vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

// Returns the x&y coordinates of the square
// 0<=x<n_squares; 0<=y<n_squares
vec2 square_coordinates()
{
	return floor(vs_uv*n_squares);
}

// uv in the square
vec2 in_square_uv()
{
	vec2 uv = fract(vs_uv*n_squares) - .5;
	return uv;
}

void main()
{
	vec2 uv = in_square_uv();
	float threshold = hash12(square_coordinates());

	if(
			height > threshold ||
			length(uv) > threshold-height/threshold 
			) discard;


	fs_color = vec4(0., .1+height, 0., 1.);
}
