// RayTracingInOneWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
    This program follows the instructions of Peter Shirley's book "Ray Tracing in One Weekend".
    Outputs the rendering result to the file "out.ppm".
*/

#include "vec3.h"
#include "ray.h"

#include <iostream>
#include <fstream>
#include <string>

vec3 color(const ray& r)
{
    vec3 unit_direction = vec3::unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    std::cout << "Starting renderer" << std::endl;

    std::ofstream out("out.ppm");
    std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!


    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::cout.rdbuf(coutbuf); //reset to standard output again
    std::cout << "Render Complete!" << std::endl;
}