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
    vec3 v = t - this->center;
    
    double rsqr = this->radius*this->radius;
    
    double a = 1, 
    b = dot(u,v), 
    c = dot(v,v) - rsqr;

    double discriminate = (b*b) - c;

    Hit one, two;

    one.object = this;
    two.object = this;

    one.ray_exiting = false;
    two.ray_exiting = true;

    if(discriminate > 0)
    {
       double t1 = (-b - pow(discriminate, 0.5)),
       t2 = (-b + pow(discriminate, 0.5));

       if(t1 >= 0)
       {
          one.t = t1;
          hits.push_back(one);
       }
       if(t2 >= 0)
       {
           two.t = t2;
           hits.push_back(two);
       }
       return true;
    }
    return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    normal = (point-this->center).normalized();
    
    return normal;
}

