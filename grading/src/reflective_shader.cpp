#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    vec3 color;
    
   /* Muzo's notes in class:
    * Ray reflected_ray;
    * reflected_ray.endpoint = ...;
    * reflected_ray.direction = r;
    * recursion_depth++;
    * reflected_color = world.Cast_Ray(reflected_ray, recursion_depth++);*/

    vec3 r, e, n;
	n = same_side_normal;
	// Use ray direction instead of light direction
	// Ray_dir * 2 * dot(Ray_dir, N) * N
	e = intersection_point;
	r = ray.direction + (-2.0 * dot(ray.direction, n) * n);

	Ray reflectedRay(e, r);

	recursion_depth++;

	vec3 reflected_color, shader_color;
	reflected_color = shader->world.Cast_Ray(reflectedRay, recursion_depth);
	shader_color = shader->Shade_Surface(ray, e, n, recursion_depth, is_exiting);
	
    // TODO: determine the color
	// from the notes : (reflectivity * reflected_color + (1 - reflectivity) * shader_color).
	color = (reflectivity * reflected_color + (1 - reflectivity) * shader_color);
    return color;
}
