# 3D Ray Tracer

## 3D Ray Tracer renders a scene represented in json format and saves in bmp data format.

### Getting started

1. Compile code in your favourite c compiler.

2. Create your own scene json representation by example in directory. Supports rendering of spheres and planes.

3. Run compiled c code with following parameters: 
* scene json file name 
* file name for saving traced scene in bmp data format
* width of traced image
* height of traced image
* num bounces
* num samples rays per pixel

```
    ./main scene.json traced.bmp 1000 1000 10 2
```
