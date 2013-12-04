/*
 * RouteManager.cpp
 *
 *  Created on: 27 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "RouteManager.h"
#include "../DataAccess/DataRepository.h"
#include "../DataAccess/Constants.h"
#include <stdlib.h>
#include <algorithm>

std::vector<Route> RouteManager::calculateBestRoutes(const std::vector<Target>& targets) {

	std::vector<Drone> drones = DataRepository::getInstance().getDrones();
	std::vector<Route> results;
	srand(time(NULL));

	// generate first population
	Population firstPopulation = Population(targets, drones);

	_populations.push_back(firstPopulation);

	calculateSuitabilityScoreForPopulation(_populations.back());

	// make selection
	selection(_populations.back());

	int iteration_count = 0;
	// start algorithm
	while(!routesResolved(_populations.back()) && iteration_count < Constants::getPopulationCount()) {

		nextGeneration(_populations.back());

		calculateSuitabilityScoreForPopulation(_populations.back());

		selection(_populations.back());

		iteration_count++;
	}

	Population resultPopulation = _populations.back();

	int bestNumber = 0;
	float bestSuit = resultPopulation.getChromosomeAtIndex(0)->getSuitability();
	for (unsigned int i = 0; i < resultPopulation.getSize(); i++) {
		if (resultPopulation.getChromosomeAtIndex(i)->getSuitability() > bestSuit) {
			bestNumber = i;
		}
	}
	for (unsigned int i = 0; i < drones.size(); i++) {
		results.push_back(Route(*resultPopulation.getChromosomeAtIndex(bestNumber), drones.at(i)));
	}

	return results;
}

// initial selection. Chromosomes that can't exist are removed.
void RouteManager::selection(Population& population) {
	for (unsigned int i = 0; i < population.getSize(); i++) {
		for (unsigned int j = 0; j < DataRepository::getInstance().getDronesCount(); j++) {
			Drone *drone = DataRepository::getInstance().getDroneAtIndex(j);
			Route route = Route(*population.getChromosomeAtIndex(i), *drone);
			float route_distance = route.getRouteDistance();
			if ((route_distance / drone->getDroneSpeed()) > drone->getRemainingFlightTime()) {
				population.removeChromosomeAtIndex(i);
				break;
			}
		}
	}
}

// calculate suitability for each chromosome. Higher score - better;
void RouteManager::calculateSuitabilityScoreForPopulation(Population& population) {
	float suitability;
	float suitability_sum;
	float max_suitability;
	Drone *drone;

	for (unsigned int i = 0; i < population.getSize(); i++) {
		Chromosome *chromosome = population.getChromosomeAtIndex(i);
//		suitability_sum = 0;

		// Calculating suitability for first drone
		drone = DataRepository::getInstance().getDroneAtIndex(0);
		Route route = Route(*chromosome, *drone);
		suitability = route.getRouteDistance() / drone->getDroneSpeed();
//		suitability_sum += suitability;

		//Calculating max suitability for chromosome. It will be total flight time.
		max_suitability = suitability;
		for (unsigned int j = 1; j < DataRepository::getInstance().getDronesCount(); j++) {
			drone = DataRepository::getInstance().getDroneAtIndex(j);
			Route route = Route(*chromosome, *drone);
			suitability = route.getRouteDistance() / drone->getDroneSpeed();
//			suitability_sum += suitability;
			if (suitability > max_suitability)
				max_suitability = suitability;
		}
		chromosome->setSuitability((10 / max_suitability));
	}
}


// Check if routes are resolved. Routes resolved if all chromosomes has same suitability.
bool RouteManager::routesResolved(Population& population) {
	if (population.getSize() < 2)
		return true;

	for (unsigned int i = 1; i < population.getSize(); i++) {

		if (population.getChromosomeAtIndex(i)->getSuitability() !=
				population.getChromosomeAtIndex(i-1)->getSuitability()) {
			return false;
		}
	}

	return true;
}

// Calculate next population.
void RouteManager::nextGeneration(Population& population) {
	float suitability_sum = population.getSuitabilitySum();
	float chanses[population.getSize() + 1];

	// calculate chances to be a parent and find best one.
	chanses[0] = 0;
	int best_index = 0;
	float best_suitability = population.getChromosomeAtIndex(0)->getSuitability();

	for (unsigned int i = 0; i < population.getSize(); i++) {
		float local_suitability = population.getChromosomeAtIndex(i)->getSuitability();
		if (local_suitability > best_suitability) {
			best_index = i;
			best_suitability = local_suitability;
		}
		chanses[i + 1] = ((local_suitability * 100.0) / suitability_sum) + chanses[i];
	}
	chanses[population.getSize()] = 100; // max chance must be int and exactly 100

	Chromosome best_chromosome = *population.getChromosomeAtIndex(best_index);
	population.removeChromosomeAtIndex(best_index);
	int numberOfClones =
			Constants::getPopulationCount() -
			(Constants::getPopulationCount() *
					((suitability_sum / (float)Constants::getPopulationCount())
							/ best_suitability));

	if (numberOfClones > (Constants::getPopulationCount() / 2)) {
		numberOfClones = Constants::getPopulationCount() / 2;
	}

	// Generate family population.
	Population familyPopulation = Population();
	for (int i = 0; i < Constants::getPopulationCount() - numberOfClones; i++) {
		int chance = rand() % 100 + 1;

		for (unsigned int j = 0; j < population.getSize(); j++) {
			if (chance > chanses[j] && chance <= chanses[j + 1]) {
				familyPopulation.setChromosome(*population.getChromosomeAtIndex(j));
				break;
			}
		}
	}

	Population nextPopulation = crossing(familyPopulation);

	//clones

	std::cout << best_chromosome.getSuitability() << std::endl;
	for (int i = nextPopulation.getSize(); i < Constants::getPopulationCount(); i++) {
		nextPopulation.setChromosome(best_chromosome);
	}
	_populations.push_back(nextPopulation);
}

// Crossing between parents.
Population RouteManager::crossing(Population& population) {
	Population nextPopulation = Population();
	while (population.getSize() > 1) {
		int randomNumber = rand() % population.getSize();
		Chromosome chromosome1 = *population.getChromosomeAtIndex(randomNumber);
		population.removeChromosomeAtIndex(randomNumber);
		randomNumber = rand() % population.getSize();
		Chromosome chromosome2 = *population.getChromosomeAtIndex(randomNumber);
		population.removeChromosomeAtIndex(randomNumber);

		randomNumber = rand() % (chromosome1.getSize() - 1) + 1;

		for (int i = 0; i < randomNumber; i++) {
			Gene temp = *chromosome1.getGeneAtIndex(i);
			chromosome1.ChangeGeneAtIndex(i, *chromosome2.getGeneAtIndex(i));
			chromosome2.ChangeGeneAtIndex(i, temp);
		}

		int mutateChance = rand() % 100 + 1;

		if (mutateChance == 8) {
			chromosome1.MutateGene();
		}

		if (mutateChance == 46) {
			chromosome1.MutateGene();
		}

		if (mutateChance == 16) {
			chromosome2.MutateGene();
		}

		nextPopulation.setChromosome(chromosome1);
		nextPopulation.setChromosome(chromosome2);
	}

	return nextPopulation;
}






