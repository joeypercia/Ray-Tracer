#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"
//#include "phong_shader.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
    const vec3& normal, int recursion_depth) const
{

    vec3 color;
    //vec3 reflectance; // k

    if (recursion_depth < world.recursion_depth_limit)
    {

        vec3 reflectedRay = -2*(dot(normal, ray.direction.normalized())) * normal + ray.direction.normalized();
       
        Ray reflected_Ray(intersection_point, reflectedRay.normalized());

        color = (1 - reflectivity) * color + reflectivity * world.Cast_Ray(reflected_Ray, ++recursion_depth);
    }

    //TODO; // determine the color
    return color;
}
