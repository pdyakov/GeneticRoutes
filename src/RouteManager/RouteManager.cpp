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

	// start algorithm
	while(!routesResolved(_populations.back())) {

		nextGeneration(_populations.back());

		calculateSuitabilityScoreForPopulation(_populations.back());

		selection(_populations.back());

	}

	Population resultPopulation = _populations.back();


	for (unsigned int i = 0; i < drones.size(); i++) {
		results.push_back(Route(*resultPopulation.getChromosomeAtIndex(0), drones.at(i)));
	}

	return results;
}

// initial selection. Chromosomes that can't exist are removed.
void RouteManager::selection(Population& population) {

	std::vector<Drone> drones = DataRepository::getInstance().getDrones();

	for (unsigned int i = 0; i < population.getSize(); i++) {
		for (unsigned int j = 0; j < drones.size(); j++) {
			Drone drone = drones.at(j);
			Route route = Route(*population.getChromosomeAtIndex(i), drone);
			float routeDistance = route.getRouteDistance();
			if ((routeDistance / drone.getDroneSpeed()) > drone.getRemainingFlightTime()) {
				population.removeChromosomeAtIndex(i);
				break;
			}
		}
	}
}

// calculate suitability for each chromosome. Higher score - better;
void RouteManager::calculateSuitabilityScoreForPopulation(Population& population) {
	std::vector<Drone> drones = DataRepository::getInstance().getDrones();

	for (unsigned int i = 0; i < population.getSize(); i++) {
		Chromosome *chromosome = population.getChromosomeAtIndex(i);
		float suitability = 0;
		float suitabilitySum = 0;

		// Calculating suitability for first drone
		Drone drone = drones.at(0);
		Route route = Route(*chromosome, drone);
		suitability = route.getRouteDistance() / drone.getDroneSpeed();
		suitabilitySum += suitability;
		//Calculating max suitability for chromosome. It will be total flight time.
		float maxSuit = suitability;
		for (unsigned int j = 1; j < drones.size(); j++) {
			Drone drone = drones.at(j);
			Route route = Route(*chromosome, drone);
			suitability = route.getRouteDistance() / drone.getDroneSpeed();
			suitabilitySum += suitability;
			if (suitability > maxSuit)
				maxSuit = suitability;
		}

		//Set minimal suitability as total suitability for chromosome.
		chromosome->setSuitability(100 / (suitabilitySum + (maxSuit * 6)));
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
	float suitSum = population.getSuitabilitySum();
	float chanses[population.getSize() + 1];

	// calculate chances to be a parent.
	chanses[0] = 0;
	for (unsigned int i = 0; i < population.getSize(); i++) {
		chanses[i + 1] = ((population.getChromosomeAtIndex(i)->getSuitability() * 100.0) / suitSum) + chanses[i];
	}
	chanses[population.getSize()] = 100; // max chance must be int and exactly 100

	// Generate family population.
	Population familyPopulation = Population();

	for (int i = 0; i < Constants::getPopulationCount(); i++) {
		int chance = rand() % 100 + 1;
		for (unsigned int j = 0; j < population.getSize(); j++) {
			if (chance > chanses[j] && chance <= chanses[j + 1]) {
				familyPopulation.setChromosome(*population.getChromosomeAtIndex(j));
				break;
			}
		}
	}

	Population nextPopulation = crossing(familyPopulation);
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
			Gene tGene = chromosome1.getGeneAtIndex(i);
			chromosome1.ChangeGeneAtIndex(i, chromosome2.getGeneAtIndex(i));
			chromosome2.ChangeGeneAtIndex(i, tGene);
		}

		int mutateChance = rand() % 500 + 1;

		if (mutateChance == 8) {
			chromosome1.MutateGene();
		}



		nextPopulation.setChromosome(chromosome1);
		nextPopulation.setChromosome(chromosome2);
	}

	return nextPopulation;
}






