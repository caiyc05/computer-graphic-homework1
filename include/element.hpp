#pragma once

#include <image.hpp>
#include <algorithm>
#include <queue>
#include <cstdio>

class Element {
public:
    virtual void draw(Image &img) = 0;
    virtual ~Element() = default;
};

class Line : public Element {

public:
    int xA, yA;
    int xB, yB;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Implement Bresenham Algorithm
        int dx = xB - xA;
        int dy = yB - yA;
        bool steep = (abs(dx) >= abs(dy));
        if(!steep){
            //说明斜率绝对值大于1，交换x,y
            int storeA = xA;
            xA = yA;
            yA = storeA;

            int storeB = xB;
            xB = yB;
            yB = storeB;

            dx = xB - xA;
            dy = yB - yA;
        }
        float d = 0;
        int x = xA;
        int y = yA;
        int sx = (xA < xB) ? 1:-1;
        int sy = (yA < yB) ? 1:-1;

        //两种情况：斜率绝对值大于1，斜率绝对值小于等于1,
        //如果斜率小于1那么就按照原先的进行，如果不是，那么先将x,y进行交换,并且最后填充的时候需要换回来
        for(int i=0;i<=abs(dx);i++){
            if(steep){
                img.SetPixel(x,y,color);
            }
            else{
                img.SetPixel(y,x,color);
            }
            x += sx;
            d += dy/dx*sx;
            if(abs(d) >= 0.5){
                y += sy;
                d -= sy;
            }
        }
        printf("Draw a line from (%d, %d) to (%d, %d) using color (%f, %f, %f)\n", xA, yA, xB, yB,
                color.x(), color.y(), color.z());
    }
};

class Circle : public Element {

public:
    int cx, cy;
    int radius;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Implement Algorithm to draw a Circle
        float d = 1.25 - radius;
        int x = cx;
        int y = cy+radius;
        img.SetPixel(x,y,color);
        img.SetPixel(x,-y,color);
        img.SetPixel(-x,y,color);
        img.SetPixel(-x,-y,color);
        while(x <= y){
            if(d<0){
                d += 2*x + 3;
            }
            else{
                d += 2*(x-y) + 5;
                y--;
            }
            x++;
            img.SetPixel(x,y,color);
            img.SetPixel(x,-y,color);
            img.SetPixel(-x,y,color);
            img.SetPixel(-x,-y,color);
        }
        printf("Draw a circle with center (%d, %d) and radius %d using color (%f, %f, %f)\n", cx, cy, radius,
               color.x(), color.y(), color.z());
    }
};

class Fill : public Element {

public:
    int cx, cy;
    Vector3f color;
    void draw(Image &img) override {
        // TODO: Flood fill

        printf("Flood fill source point = (%d, %d) using color (%f, %f, %f)\n", cx, cy,
                color.x(), color.y(), color.z());
    }
};