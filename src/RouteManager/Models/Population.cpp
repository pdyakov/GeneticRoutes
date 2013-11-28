/*
 * Population.cpp
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "Population.h"
#include <stdlib.h>
#include "../../DataAccess/Constants.h"

// Generate random population of POPULATION_COUNT chromosomes
Population::Population(std::vector<Target> targets, std::vector<Drone> drones) {
	int targetCount = targets.size();
	int droneCount = drones.size();
	for (int i = 0; i < Constants::getPopulationCount(); i++) {
		Chromosome chromosome = Chromosome();
		for (int j = 0; j < targetCount; j++) {
			Gene gene = Gene(targets.at(j), drones.at(rand() % droneCount));
			chromosome.AddGene(gene);
		}
		setChromosome(chromosome);
	}
}

Chromosome *Population::getChromosomeAtIndex(const int index) {
	return &(*(_chromosomes.begin() + index));
}

void Population::setChromosome(const Chromosome& chromosome) {
	_chromosomes.push_back(chromosome);
}

void Population::changeChromosomeAtIndex(int index, const Chromosome& replacementChromosome) {
	_chromosomes.assign(index, replacementChromosome);
}

void Population::removeChromosomeAtIndex(const unsigned int index) {
	_chromosomes.erase(_chromosomes.begin() + index);
}

unsigned int Population::getSize() const {
	return _chromosomes.size();
}

float Population::getSuitabilitySum() const {
	float sum = 0;
	for (unsigned int i = 0; i < _chromosomes.size(); i++) {
		sum += _chromosomes.at(i).getSuitability();
	}
	return sum;
}


