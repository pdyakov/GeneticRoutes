/*
 * Coordinates.cpp
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "Coordinates.h"

Coordinates::Coordinates() : _xPoint(0), _yPoint(0) {

}

Coordinates::Coordinates(float xPoint, float yPoint) : _xPoint(xPoint), _yPoint(yPoint) {

}

float Coordinates::getPointX() const {
	return _xPoint;
}

float Coordinates::getPointY() const {
	return _yPoint;
}

void Coordinates::setPointX(float xPoint) {
	_xPoint = xPoint;
}

void Coordinates::setPointY(float yPoint) {
	_yPoint = yPoint;
}
