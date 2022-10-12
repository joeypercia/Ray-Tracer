#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    
   
    vec3 color;

    vec3 ambient = world.ambient_color * color_ambient * world.ambient_intensity;
    
    
    color += ambient;
   
      

   


    for (unsigned i = 0; i < world.lights.size(); ++i)
    {
       
        vec3 lightcolor = world.lights[i]->Emitted_Light(ray.direction);
        vec3 l = world.lights[i]->position - intersection_point;
        vec3 lightintensity = lightcolor / l.magnitude_squared();

        double diffintensity = std::max(dot(normal, l.normalized()), 0.0);
        vec3 diffuse = diffintensity * color_diffuse * lightintensity;

        color += diffuse;

        vec3 r = (2 * dot(l.normalized(), normal) * normal - l.normalized());
        double specintensity = std::pow(std::max(dot(-ray.direction.normalized(), r.normalized()), 0.0), specular_power);  //world.camera.position.normalized()
        vec3 specular = specintensity * color_specular * lightintensity;

        color += specular;
        if (world.enable_shadows == true)
        {
            vec3 shadowDirection = (world.lights[i]->position - intersection_point).normalized();
            Ray shadowRay;
            shadowRay.endpoint = intersection_point;
            shadowRay.direction = shadowDirection;

            Hit shadowHit = world.Closest_Intersection(shadowRay);
            //if (shadowHit.dist <= (world.lights[i]->position - intersection_point).magnitude() || shadowHit.object != NULL)
            if (shadowHit.object != NULL && shadowHit.dist <= (intersection_point - world.lights[i]->position).magnitude()) //(world.lights[i]->position - intersection_point).magnitude() //&& shadowHit.dist <= (world.lights[i]->position - intersection_point).magnitude()
            {
               color -= diffuse;
               color -= specular;
            }
        }
    }


           
        

    //TODO; //determine the color
    //color = ambient + diffuse + specular;
    return color;
}
