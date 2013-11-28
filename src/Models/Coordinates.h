/*
 * Coordinates.h
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef COORDINATES_H_
#define COORDINATES_H_

class Coordinates {
public:
	Coordinates();
	Coordinates(float xPoint, float yPoint);
	virtual ~Coordinates() { };

	float getPointX() const;
	float getPointY() const;

	void setPointX(float xPoint);
	void setPointY(float yPoint);

private:
	float _xPoint;
	float _yPoint;
};


#endif /* COORDINATES_H_ */
