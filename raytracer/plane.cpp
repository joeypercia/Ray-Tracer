#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    Hit intersection;
    intersection.dist = NULL;
    intersection.object = NULL;
    float d = dot(ray.direction, normal);
    vec3 plane = this->x1;
    //if (abs(d) > small_t)
    //{
        float t = dot(plane - ray.endpoint, normal) / dot(ray.direction, normal);
        if (t > small_t)
        {
            intersection.dist = t;
            intersection.object = this;
        }
    //}

    return intersection;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
