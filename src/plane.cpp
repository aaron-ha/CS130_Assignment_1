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
    double t = -(dot(this->normal,(u - x1))/(intersects));

    Hit hit1 = {this, t, true};

    if (t >= 0){ 
	    hits.push_back(hit1);
	    return true;
    }
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
