#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    double min_t = std::numeric_limits<double>::max();
    Hit closesthit, previoushit;
    closesthit.object = NULL;
    closesthit.dist = NULL;
    
    for (unsigned i = 0; i < objects.size(); ++i)
    {
        previoushit = objects.at(i)->Intersection(ray, 0);

          if ((closesthit.object == NULL && previoushit.dist > small_t && previoushit.dist < min_t)
              || (closesthit.dist > previoushit.dist &&
                  previoushit.dist >= small_t && previoushit.dist < min_t))
          {
              closesthit = previoushit;
          }

    }
        return closesthit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    //Ray ray(camera.position, camera.World_Position(pixel_index));
    Ray ray(camera.position, (camera.World_Position(pixel_index) - camera.position).normalized());
    vec3 color=Cast_Ray(ray, 0);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
  
        vec3 color;
        Hit closest_hit = Closest_Intersection(ray);
        //vec3 normal = closest_hit.object->Normal(ray.Point(closest_hit.dist), 0);
        //vec3 intersection_point = ray.Point(closest_hit.dist);
        if (recursion_depth < recursion_depth_limit)
        {
            if (closest_hit.object != NULL)
            {
                color = closest_hit.object->material_shader->Shade_Surface(ray, ray.Point(closest_hit.dist), closest_hit.object->Normal(ray.Point(closest_hit.dist), closest_hit.part), recursion_depth);//material_shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
            }
            else
            {
                color = background_shader->Shade_Surface(ray, vec3(0, 0, 0), vec3(0, 0, 0), recursion_depth + 1);
            }
        }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    //TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.
    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
