// RayTracingInOneWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
    This program follows the instructions of Peter Shirley's book "Ray Tracing in One Weekend".
    Outputs the rendering result to the file "out.ppm".
*/

#include "float.h"

#include "vec3.h"
#include "ray.h"

#include "camera.h"

#include "random.h"

#include "hittable_list.h"
#include "hittables/sphere.h"

#include <iostream>
#include <fstream>
#include <string>


vec3 color(const ray& r, hittable* world)
{
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec))
    {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    std::cout << "Starting renderer" << std::endl;

    std::ofstream out("out.ppm");
    std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!


    int nx = 200;
    int ny = 100;
    int ns = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    hittable* list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hittable* world = new hittable_list(list, 2);

    camera cam;

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                ray r = cam.get_ray(u, v);
                col = col + color(r, world);
            }
            col = col / float(ns);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::cout.rdbuf(coutbuf); //reset to standard output again
    std::cout << "Render Complete!" << std::endl;
}