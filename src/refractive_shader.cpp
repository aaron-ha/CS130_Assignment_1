#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
        //TODO (Test 27+): Compute the refraction_color:
        // - Check if it is total internal reflection. 
        //      If so update the reflectance_ratio for total internal refraction
        //
        //      else, follow the instructions below
        //
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        //
	vec3 n = same_side_normal;
	double air_index, n_i, n_r;
	air_index = 1;
	//make sure that n_i & n_r are properly set -> if the ray is not exiting but entering
	//then n_r should be the object's refractive index, while n_i should be air's|vice-versa
	//n_i = (is_exiting) ? refractive_index : air_index;
	//n_r = (is_exiting) ? air_index : refractive_index;
	if(is_exiting){
		n_i = refractive_index;
		n_r = air_index;
		n*= -1.0;
	}
	else {
		n_i = air_index;
		n_r = refractive_index;
	}

	//if cos0_r is negative: reflectance ratio = 1
	//cos0_r = [1-(n_i/n_r)^2 * (1 - cos^2 0_i)]^1/2
	double ni_nr_sqr	 = pow((n_i/n_r), 2);
	double cos_i		 = dot(n,-1.0 * ray.direction) / ray.direction.magnitude();
	double cos_r 		 = pow(1 - ni_nr_sqr * (1 - pow(cos_i, 2)),0.5);
	double cos_r_sqr	 = 1 - ni_nr_sqr * (1 - pow(cos_i, 2));

	if(cos_r_sqr < 0) { //check for total internal reflection
		reflectance_ratio = 1;
	}
	else {
		vec3 r, e, T;
		e = intersection_point;
		r = ray.direction - dot(ray.direction, n) * n;
		//T = n_i/n_r * (d - dot(d, n) * n) - cos_r*N
		T = (n_i/n_r) * r - cos_r * n;
		Ray refractedRay(e, T);
		refraction_color = world.Cast_Ray(refractedRay, recursion_depth+1);

		double r_parallel, r_perpendicular;

		r_parallel = pow((n_r * cos_i - n_i * cos_r) / (n_r * cos_i + n_i * cos_r),2);
		r_perpendicular = pow((n_i * cos_i - n_r * cos_r) / (n_i * cos_i + n_r * cos_r),2);
		reflectance_ratio = (r_parallel + r_perpendicular) / 2;
	}
    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        // Copied over from reflective_shader.cpp
	
	vec3 r, e, n;
	n = same_side_normal;
	e = intersection_point;
	r = ray.direction + (-2.0 * dot(ray.direction, n) * n);
	
	Ray reflectedRay(e, r);
	reflection_color = shader->world.Cast_Ray(reflectedRay, recursion_depth + 1);
    }

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    // Notes:  color=reflectance_ratio * reflection_color + (1 - reflectance_ratio) * refraction_color).
    color = reflectance_ratio * reflection_color + (1 - reflectance_ratio) * refraction_color;
    
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}

