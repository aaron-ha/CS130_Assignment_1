#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 x1 = this->x1;
    vec3 u = ray.endpoint;
    vec3 w = ray.direction;
    
    double intersects = dot(this->normal, w);
    double t = dot(this->normal,(x1 - u)/(intersects));

    Hit hit1;
     
    if(intersects == 0){
	hit1 = {this, 0, true};
	hits.push_back(hit1);
	return true;
    }
    else if (t > 0){ 
        hit1 = {this, t, true};	
	hits.push_back(hit1);
	return true;
    }
    else{
	return false;
    }
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
