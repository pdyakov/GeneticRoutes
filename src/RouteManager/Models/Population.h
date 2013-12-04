/*
 * Population.h
 *
 *  Created on: 20 Oct 2013
 *      Author: pavlik
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Chromosome.h"

class Population {
public:
	Population() { };
	Population(std::vector<Target> targets, std::vector<Drone> drones);
	virtual ~Population() { };

	Chromosome *getChromosomeAtIndex(const int index);

	void setChromosome(const Chromosome& chromosome);
	void changeChromosomeAtIndex(int index, const Chromosome& replacementChromosome);
	void removeChromosomeAtIndex(const unsigned int index);
	unsigned int getSize() const;
	float getSuitabilitySum() const;
	void sort();

private:
	std::vector<Chromosome> _chromosomes;
};

#endif /* POPULATION_H_ */
