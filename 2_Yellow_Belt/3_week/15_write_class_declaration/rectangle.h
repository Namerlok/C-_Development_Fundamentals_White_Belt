/*
 * rectangle.h
 *
 *  Created on: 16 июл. 2020 г.
 *      Author: Zarka
 */
#pragma once

#ifndef RECTANGLE_H_
#define RECTANGLE_H_


class Rectangle {
public:
    Rectangle(int width, int height);

    int GetArea() const;

    int GetPerimeter() const;

    int GetWidth() const;
    int GetHeight() const;

private:
    int width_, height_;
};



#endif /* RECTANGLE_H_ */

