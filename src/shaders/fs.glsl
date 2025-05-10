#version 410 core 

in vec2 vs_uv;

uniform float height;
uniform int n_squares;
uniform float wind_direction;
uniform float wind_curve;
uniform float wind_force;
uniform float wind_speed;
uniform float time;

out vec4 fs_color;

/* Copyright (c)2014 David Hoskins */
float hash12(vec2 p)
{
	vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

vec2 uv_wind()
{
	return vs_uv +
		vec2(cos(wind_direction), sin(wind_direction))*
		wind_force*
		pow(height, wind_curve)*
		(sin(time*wind_speed)/2. + .5);
}

// Avoids any tall border grass appearing
bool grass_root_outside(vec2 uv)
{
	return uv != clamp(uv, vec2(0.), vec2(1.));
}

// Returns the x&y coordinates of the square
// 0<=x<n_squares; 0<=y<n_squares
vec2 square_coordinates(vec2 uv)
{
	return floor(uv*n_squares);
}

// uv in the square section
vec2 uv_in_square(vec2 uv)
{
	return fract(uv*n_squares) - .5;
}

void main()
{
	vec2 skewed = uv_wind();
	vec2 uv = uv_in_square(skewed);
	float threshold = hash12(square_coordinates(skewed));

	if(
			height > threshold ||
			length(uv) > threshold-height/threshold || // Makes grass thin on top
			grass_root_outside(skewed)
			) discard;

	fs_color = vec4(0., .1+height, 0., 1.);
}
