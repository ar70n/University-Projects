package com.aim.project.obr.heuristics;

import java.util.ArrayList;
import java.util.Random;

import com.aim.project.obr.interfaces.HeuristicInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

import uk.ac.nott.cs.aim.helperfunctions.ArrayMethods;


/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class DavissHillClimbing extends HeuristicOperators implements HeuristicInterface {

	public DavissHillClimbing(Random oRandom) {
	
		super(oRandom);
	}

	@Override
	public int apply(OBRSolutionInterface oSolution, double dDepthOfSearch, double dIntensityOfMutation) {

		int n_iterations;
	    if (dDepthOfSearch >= 0.0 && dDepthOfSearch < 0.2) n_iterations = 1;
	    else if (dDepthOfSearch < 0.4) n_iterations = 2;
	    else if (dDepthOfSearch < 0.6) n_iterations = 3;
	    else if (dDepthOfSearch < 0.8) n_iterations = 4;
	    else if (dDepthOfSearch <= 1.0) n_iterations = 5;
	    else return Integer.MAX_VALUE;
		
		int bestEval = oSolution.getObjectiveFunctionValue();
		SolutionRepresentationInterface rep = oSolution.getSolutionRepresentation();
		int[] sol = rep.getSolutionRepresentation();
		
		for (int i = 0; i < n_iterations; i++) {
			ArrayList<Integer> perm = createRandomPermutation(oSolution.getNumberOfLocations() - 1);
			
			for (int j = 0; j < sol.length; j++) {
	
				this.swap(sol, perm.get(j), (perm.get(j)+ 1) % sol.length);
				int tempEval = this.calculateObjectiveValue(rep);
				
				if(tempEval < bestEval) {
					bestEval = tempEval;
				} else {
					this.swap(sol, perm.get(j), (perm.get(j)+ 1) % sol.length);
				}
				
			}
		}
		oSolution.setObjectiveFunctionValue(bestEval);
		return bestEval;
	}

	@Override
	public boolean isCrossover() {

		return false;
	}

	@Override
	public boolean usesIntensityOfMutation() {

		return false;
	}

	@Override
	public boolean usesDepthOfSearch() {

		return true;
	}
	
	//Metodo mio
    private ArrayList<Integer> createRandomPermutation(int length) {
    	Random r = this.m_oRandom;
    	ArrayList<Integer> perm = new ArrayList<Integer>(length);
    	for (int i = 0; i<length;i++) {
    		perm.add(i);
    	}
    	return ArrayMethods.shuffle(perm, r);
    }

}
