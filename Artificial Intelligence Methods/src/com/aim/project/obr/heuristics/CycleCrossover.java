package com.aim.project.obr.heuristics;

import java.util.Random;

import com.aim.project.obr.interfaces.CrossoverHeuristicInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.ObjectiveFunctionInterface;

/**
 * This crossover type heuristic should take two parent solutions and create a single child
 * (chosen randomly) according to the explanation of OX from the lectures (see lecture 6).
 * When selecting the two cut points, you should ensure that it is not possible that all
 * sightseeing locations are within the segment to be copied. There is no requirement to
 * use either of the intensity of mutation or depth of search settings for this
 * implementation.
 *
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class CycleCrossover implements CrossoverHeuristicInterface {
	
	private final Random m_oRandom;
	
	private ObjectiveFunctionInterface m_oObjectiveFunction;

	public CycleCrossover(Random oRandom) {
		
		this.m_oRandom = oRandom;
	}

	@Override
	public int apply(OBRSolutionInterface oSolution, double dDepthOfSearch, double dIntensityOfMutation) {

        return oSolution.getObjectiveFunctionValue();
	}

	@Override
	public int apply(OBRSolutionInterface oParent1, OBRSolutionInterface oParent2,
                        OBRSolutionInterface oChild, double dDepthOfSearch, double dIntensityOfMutation) {


		int size = oParent1.getNumberOfLocations() - 1;
		
		int[] parent1 = oParent1.getSolutionRepresentation().getSolutionRepresentation();
		int[] parent2 = oParent2.getSolutionRepresentation().getSolutionRepresentation();

		int[] child1 = parent1.clone();
		int[] child2 = parent2.clone();
		

		int pA = this.m_oRandom.nextInt(size);
		boolean[] inCycle = new boolean[size];
        int currentIndex = pA;
		

        while (!inCycle[currentIndex]) {
            
            inCycle[currentIndex] = true;
            currentIndex = indexOf(parent1, parent2[currentIndex]);
        }
		
		for (int i = 0; i < size; i++) {
			if (!inCycle[i]) {
				child1[i] = parent2[i];
                child2[i] = parent1[i]; 
			}
		}
	    
	    
		int[] child = this.m_oRandom.nextBoolean() ? child1 : child2;
		oChild.getSolutionRepresentation().setSolutionRepresentation(child);
		
		int value = this.m_oObjectiveFunction.getObjectiveFunctionValue(oChild.getSolutionRepresentation());
		oChild.setObjectiveFunctionValue(value);
		return value;
	}


	@Override
	public boolean isCrossover() {

		return true;
	}

	@Override
	public boolean usesIntensityOfMutation() {

		return false;
	}

	@Override
	public boolean usesDepthOfSearch() {

		return false;
	}

	@Override
	public void setObjectiveFunction(ObjectiveFunctionInterface oObjectiveFunction) {
		
		this.m_oObjectiveFunction = oObjectiveFunction;
	}
	
	//Metodo mio
	private int indexOf(int[] arr, int target) {
	    for (int i = 0; i < arr.length; i++) {
	        if (arr[i] == target) return i;
	    }
	    return -1;
	}
}
