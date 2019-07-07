#include <stdlib.h>
#include <stdio.h>
#include "material.h"
#include "sphere.h"
#include "plane.h"
#include "cJSON.h"
#include "scene.h"
#include "light.h"

static void add_lights_to_scene(cJSON* lights, Scene* scene);

static void add_spheres_to_scene(cJSON* json, Scene* scene);
static void add_planes_to_scene(cJSON* planes, Scene* scene);

static Material read_material(cJSON* item);
static Vector3 read_vector3(cJSON* item);
static Color read_color(cJSON* item);

static int error_flag = 0;

Scene* scene_from_json(char* json_text){
    cJSON* json = cJSON_Parse(json_text);
    Scene* scene = malloc(sizeof(Scene));
    
    if (json == NULL){
        goto fail;
    }
    
    cJSON* camera = cJSON_GetObjectItemCaseSensitive(json, "camera");
    scene->camera = read_vector3(camera);
    
    if(error_flag){
        goto fail;
    }

    cJSON* image_plane = cJSON_GetObjectItemCaseSensitive(json, "image plane");
    
    if(!cJSON_IsObject(image_plane)){   
        goto fail;
    }    

    cJSON* top_left = cJSON_GetObjectItemCaseSensitive(image_plane, "top left");
    cJSON* top_right = cJSON_GetObjectItemCaseSensitive(image_plane, "top right");
    cJSON* bottom_left = cJSON_GetObjectItemCaseSensitive(image_plane, "bottom left");
    cJSON* bottom_right = cJSON_GetObjectItemCaseSensitive(image_plane, "bottom right");

    scene->image_plane.top_left = read_vector3(top_left);

    if(error_flag){
        goto fail;
    }
    
    scene->image_plane.top_right = read_vector3(top_right);

    if(error_flag){
        goto fail;
    }

    scene->image_plane.bottom_left = read_vector3(bottom_left);

    if(error_flag){
        goto fail;
    }

    scene->image_plane.bottom_right = read_vector3(bottom_right);    
        
    if(error_flag){
        goto fail;
    }

    cJSON* ambient_light = cJSON_GetObjectItemCaseSensitive(json, "ambient light");
    scene->kAmbientLight = read_color(ambient_light);

    if(error_flag){
        goto fail;
    }
    
    cJSON* objects = cJSON_GetObjectItemCaseSensitive(json, "objects");
    
    if(!cJSON_IsObject(objects)){   
        goto fail;
    }

    cJSON* spheres = cJSON_GetObjectItemCaseSensitive(objects, "spheres");
        
    if(!cJSON_IsArray(spheres)){
        goto fail;
    }

    cJSON* planes = cJSON_GetObjectItemCaseSensitive(objects, "planes");
        
    if(!cJSON_IsArray(planes)){
        goto fail;
    }

    scene->objects = array_list_init();
	scene->lights = array_list_init();

    add_spheres_to_scene(spheres, scene);
    
    if(error_flag){
        goto fail1;
    }  

    add_planes_to_scene(planes, scene);

    if(error_flag){
        goto fail1;
    }  
    
    cJSON* lights = cJSON_GetObjectItemCaseSensitive(json, "lights");

    if(!cJSON_IsArray(lights)){
        goto fail1;
    }    
  
    add_lights_to_scene(lights, scene); 

    if(error_flag){
        goto fail1;
    }   
    
    cJSON_Delete(json);
    return scene;

fail:
    cJSON_Delete(json);
    free(scene);
    return NULL;

fail1:
    cJSON_Delete(json);
    scene_free(scene);
    return NULL;
}

void scene_free(Scene* scene){
    int objects_size = array_list_size(scene->objects);
    int lights_size = array_list_size(scene->lights);

    Scene_object* scene_object;

    for(int i = 0 ; i < objects_size; i++){
        scene_object = array_list_get(scene->objects, i);
        scene_object->free(scene_object);
    }

    for(int i = 0; i < lights_size; i++){
        free(array_list_get(scene->lights, i));
    }
       
    array_list_free(scene->objects);

    array_list_free(scene->lights);    

    free(scene);
}

static void add_lights_to_scene(cJSON* lights, Scene* scene){
    cJSON* light = NULL;

    Vector3 position;
    Color intensity_specular;
    Color intensity_diffuse;
    
    cJSON_ArrayForEach(light, lights){
        position = read_vector3(cJSON_GetObjectItemCaseSensitive(light, "position"));
        
        if(error_flag){
            return;
        }

        intensity_specular = read_color(cJSON_GetObjectItemCaseSensitive(light, "intensity specular"));

        if(error_flag){
            return;
        }

        intensity_diffuse = read_color(cJSON_GetObjectItemCaseSensitive(light, "intensity diffuse"));

        if(error_flag){
            return;
        }

        array_list_add(scene->lights, create_light(position, intensity_specular, intensity_diffuse));
    }
}

static void add_planes_to_scene(cJSON* planes, Scene* scene){
    cJSON* plane = NULL; 
    
    Vector3 point;
    Material material;
    Vector3 normal;
    
    cJSON_ArrayForEach(plane, planes){
        point = read_vector3(cJSON_GetObjectItemCaseSensitive(plane, "point"));

        if(error_flag){
            return;        
        }

        normal = read_vector3(cJSON_GetObjectItemCaseSensitive(plane, "normal"));

        if(error_flag){
            return;
        }

        material = read_material(cJSON_GetObjectItemCaseSensitive(plane, "material"));

        if(error_flag){
            return;        
        }
        
        array_list_add(scene->objects, create_plane(normal, point, material));
    }
}

static void add_spheres_to_scene(cJSON* spheres, Scene* scene){
    cJSON* sphere = NULL;
    cJSON* radius = NULL;  
    
    Vector3 center;
    Material material;
    float radius1;
    
    cJSON_ArrayForEach(sphere, spheres){
        center = read_vector3(cJSON_GetObjectItemCaseSensitive(sphere, "center"));

        if(error_flag){
            return;        
        }

        material = read_material(cJSON_GetObjectItemCaseSensitive(sphere, "material"));

        if(error_flag){
            return;        
        }

        radius = cJSON_GetObjectItemCaseSensitive(sphere, "radius");

        if(!cJSON_IsNumber(radius)){
            error_flag = 1;
            return;
        }

        radius1 = radius->valuedouble;
        
        array_list_add(scene->objects, create_sphere(center, material, radius1));
    }
}

static Material read_material(cJSON* item){ 
    Color ambient = read_color(cJSON_GetObjectItemCaseSensitive(item, "ambient"));

    if(error_flag){
        goto fail;        
    }
    
    Color diffuse = read_color(cJSON_GetObjectItemCaseSensitive(item, "diffuse"));

    if(error_flag){
        goto fail;        
    }

    Color specular = read_color(cJSON_GetObjectItemCaseSensitive(item, "specular"));

    if(error_flag){
        goto fail;     
    } 

    Color reflection = read_color(cJSON_GetObjectItemCaseSensitive(item, "reflection"));

    if(error_flag){
        goto fail;     
    } 
    
    cJSON* alpha = cJSON_GetObjectItemCaseSensitive(item, "alpha");
    
    if(!cJSON_IsNumber(alpha)){
        error_flag = 1;
        goto fail;
    }

    int aplha1 = alpha->valuedouble;

    return (Material){ambient, diffuse, specular, reflection, aplha1};
fail:
    return (Material){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},0};
    
}

static Color read_color(cJSON* item){
    Color color;

    if(!cJSON_IsObject(item)){
        error_flag = 1; 
        goto end;
    }

    cJSON* r = cJSON_GetObjectItemCaseSensitive(item, "red");
    cJSON* g = cJSON_GetObjectItemCaseSensitive(item, "green");
    cJSON* b = cJSON_GetObjectItemCaseSensitive(item, "blue");
    
    if(!cJSON_IsNumber(r) || !cJSON_IsNumber(g) || !cJSON_IsNumber(b)){
        error_flag = 1;
        goto end;
    }

    color.r = r->valuedouble;
    color.g = g->valuedouble;
    color.b = b->valuedouble;    

end:
    return color;
}

static Vector3 read_vector3(cJSON* item){
    Vector3 vector;

    if(!cJSON_IsObject(item)){
        error_flag = 1; 
        goto end;
    }

    cJSON* x = cJSON_GetObjectItemCaseSensitive(item, "x");
    cJSON* y = cJSON_GetObjectItemCaseSensitive(item, "y");
    cJSON* z = cJSON_GetObjectItemCaseSensitive(item, "z");
    
    if(!cJSON_IsNumber(x) || !cJSON_IsNumber(y) || !cJSON_IsNumber(z)){
        error_flag = 1;
        goto end;
    }

    vector.x = x->valuedouble;
    vector.y = y->valuedouble;
    vector.z = z->valuedouble;    

end:
    return vector;
}
