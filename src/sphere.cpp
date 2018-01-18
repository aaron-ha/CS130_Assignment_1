#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
/* Notes from lab:
 * descriminate = u(u*v)^2-u(v*v-r^2) => b^2 - 4ac
 * a = L, b = 2*u*v, c = (v*v)-r^2
 * t1 = (u*v) + sqrt((u*v)^2-(v*v-r^2)) 
 * t1 = (u*v) - sqrt((u*v)^2-(v*v-r^2))
 *
 */
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 t = ray.endpoint, 
	 u = ray.direction;
    vec3 v = u - this->center;

    double rsqr = this->radius*this->radius;
    
    double a = dot(t,t), 
	   b = dot(t,v), 
	   c = dot(v,v) - rsqr;

    double discriminate = (b*b) - c;

    if(discriminate > 0){
         double t1 = (-b + pow(discriminate, 1/2)),
		t2 = (-b - pow(discriminate, 1/2));

	 Hit one = {this, t1, true},
	     two = {this, t2, true};

	 if(t1 >= 0) hits.push_back(one);
	 if(t2 >= 0) hits.push_back(two);
    }

    // return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    normal = (point-this->center).normalized();
   	    
    return normal;
}
