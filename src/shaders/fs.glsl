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

vec2 wind()
{
	return
		vec2(cos(wind_direction), sin(wind_direction))*
		wind_force*
		pow(height, wind_curve)*      // Higher grass are more pushed by wind
		(sin(time*wind_speed)/2.+.5); // Oscillating wind force (from 0 to 1)
}

// Avoids any tall grass appearing on the edge of the plane because of wind
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
	vec2 skewed = vs_uv + wind();
	vec2 uv = uv_in_square(skewed); // Uv in current grass strand square
	float threshold = hash12(square_coordinates(skewed)); // Max height for square

	if(
			height > threshold || // Stop drawing if pixel higher than grass
			length(uv) > (threshold-height)/threshold * .5 || // Taller grass thin
			grass_root_outside(skewed) // Don't draw grass from thin air at the edge
			)
	{
		// Dirt color
		if(height == 0.)
		{
			fs_color = vec4(40./255., 30./255., 0., 1.);
			return;
		}

		discard;
	}

	// Green shading, guesswork to get something that looks good
	fs_color = vec4(0., .1+height/1.3, 0., 1.);

}
