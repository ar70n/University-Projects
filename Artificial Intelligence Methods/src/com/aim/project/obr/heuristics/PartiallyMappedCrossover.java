package com.aim.project.obr.heuristics;

import java.util.Random;

import com.aim.project.obr.interfaces.ObjectiveFunctionInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.CrossoverHeuristicInterface;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class PartiallyMappedCrossover implements CrossoverHeuristicInterface {

	private final Random m_oRandom;

    private ObjectiveFunctionInterface m_oObjectiveFunction;

	public PartiallyMappedCrossover(Random oRandom) {
		
		this.m_oRandom = oRandom;
	}

	@Override
	public int apply(OBRSolutionInterface oSolution, double dDepthOfSearch, double dIntensityOfMutation) {

        return oSolution.getObjectiveFunctionValue();
	}

	@Override
	public int apply(OBRSolutionInterface oParent1, OBRSolutionInterface oParent2, OBRSolutionInterface oChild, double dDepthOfSearch, double dIntensityOfMutation) {

		int size = oParent1.getNumberOfLocations() - 1;
		
		int[] parent1 = oParent1.getSolutionRepresentation().getSolutionRepresentation();
		int[] parent2 = oParent2.getSolutionRepresentation().getSolutionRepresentation();

		int[] child1 = parent1.clone();
		int[] child2 = parent2.clone();

		int pA = this.m_oRandom.nextInt(size);
		int pB = pA;
		while (pB == pA) {
			pB = this.m_oRandom.nextInt(size);
		}
		
		int start = Math.min(pA, pB);
	    int end = Math.max(pA, pB);
	    
	    for (int i = start; i < end; i++) {
	        int target1 = parent2[i];
	        int index1 = indexOf(child1, target1);
	        swap(child1, i, index1);
	        
	        int target2 = parent1[i];
	        int index2 = indexOf(child2, target2);
	        swap(child2, i, index2);
	    }
	    
		int[] child = this.m_oRandom.nextBoolean() ? child1 : child2;
		oChild.getSolutionRepresentation().setSolutionRepresentation(child);
		
		int value = this.m_oObjectiveFunction.getObjectiveFunctionValue(oChild.getSolutionRepresentation());
		oChild.setObjectiveFunctionValue(value);
		return value;
	}

	@Override
	public void setObjectiveFunction(ObjectiveFunctionInterface oObjectiveFunction) {

        this.m_oObjectiveFunction = oObjectiveFunction;
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
	
	//Metodo mio
	private int indexOf(int[] arr, int target) {
	    for (int i = 0; i < arr.length; i++) {
	        if (arr[i] == target) return i;
	    }
	    return -1;
	}

	//Metodo mio
	private void swap(int[] arr, int i, int j) {
	    int temp = arr[i];
	    arr[i] = arr[j];
	    arr[j] = temp;
	}
}
