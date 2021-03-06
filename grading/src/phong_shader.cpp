#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
	const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
    // TODO: determine the color
    // Ambient
	vec3 color;
	color = world.ambient_color * world.ambient_intensity * this->color_ambient;   

	for(unsigned int i = 0; i < world.lights.size(); i++){
		vec3 l, n, lightColor, lightVector;	
		lightVector = (world.lights[i]->position - intersection_point).normalized();
		
		Hit hitShadow;
		Ray rayShadow;
		if(world.enable_shadows) {
			rayShadow.endpoint = intersection_point;
			rayShadow.direction = lightVector;
			if (world.Closest_Intersection(rayShadow, hitShadow) && ((world.lights[i]->position - intersection_point).magnitude() > hitShadow.t)) continue;
		}
			//Diffuse
	        //I_d = R_d*L_d*max(0,l*n)
	        //max(x,y)
			n = same_side_normal;
			l = world.lights.at(i)->position - intersection_point;
			lightColor = world.lights.at(i)->Emitted_Light(rayShadow) / l.magnitude_squared();

			double maxY = dot(n, l.normalized());

			color += this->color_diffuse * lightColor * fmax(0, maxY);

			//Specular
	       	//I_s = R_s*L_s*max(0,cos(phi))^alpha
			//R = (2*dot(L,N)*N-L) : reflected direction
			//alpha = specular power
			//** L and R must be normalized!!
			vec3 r = (2 * dot(n, l.normalized()) * n - l.normalized()).normalized();
			color += this->color_specular * lightColor *
			         pow(fmax(0,dot(r, (ray.direction.normalized()*-1.0).normalized())), specular_power);
	}

	return color;
}
