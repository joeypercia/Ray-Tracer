#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    
    //From T Jank https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
    Hit intersection;
    intersection.object = NULL;
    intersection.dist = NULL;
    vec3 ray_center = ray.endpoint - center;

    float a = dot(ray.direction, ray.direction);
    float b = dot(ray_center, ray.direction)*2;
    float c = dot(ray_center, ray_center) - radius * radius;

    float d = b * b - 4 * a * c;

    if (d < 0)
    {
        intersection.object = NULL;
        return intersection;
    }
    else {
        float n = -b - sqrt(d);
        if (n > 0) {
            intersection.object = this;
            intersection.dist = n / (2 * a);
            return intersection;
        }

        n = -b + sqrt(d);
        if (n > 0)
        {
            intersection.object = this;
            intersection.dist = n / (2 * a);
            return intersection;
        }
        else {
            intersection.object = NULL;
            return intersection;
        }
    }
    
    //TODO;
    return intersection;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; // compute the normal direction
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
