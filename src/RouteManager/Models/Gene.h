/*
 * Gene.h
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef GENE_H_
#define GENE_H_

#include "../../Models/Drone.h"
#include "../../Models/Target.h"

class Gene {
public:
	Gene();
	Gene(const Target& target, const Drone& drone);
	virtual ~Gene() { };

	Drone* getDrone();
	Target* getTarget();

	void setDrone(const Drone& drone);
	void setTarget(const Target& target);

private:
	Target _target;
	Drone _drone;
};


#endif /* GENE_H_ */
