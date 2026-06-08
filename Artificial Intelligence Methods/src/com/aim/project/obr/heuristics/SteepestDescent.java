package com.aim.project.obr.heuristics;


import java.util.Random;

import com.aim.project.obr.interfaces.HeuristicInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;


/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class SteepestDescent extends HeuristicOperators implements HeuristicInterface {

	public SteepestDescent(Random oRandom) {
	
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
		
	    SolutionRepresentationInterface rep = oSolution.getSolutionRepresentation();
		int[] sol = rep.getSolutionRepresentation();
		int bestEval = oSolution.getObjectiveFunctionValue();
		
	    for (int i = 0; i < n_iterations; i++) {
			int index = this.m_oRandom.nextInt(sol.length);
			int bestIndex = -1;
			boolean improved = false;
			
			for (int j = 0; j < sol.length; j++) {
				this.swap(sol, (index + j) % sol.length, (index + j + 1) % sol.length);
				int tmpEval = this.calculateObjectiveValue(rep);
			
				if (tmpEval < bestEval) {
					bestIndex = j;
					bestEval = tmpEval;
					improved = true;

				} 
				this.swap(sol, (index + j) % sol.length, (index + j + 1) % sol.length);
			}
			
			if (improved) {
				this.swap(sol, (index + bestIndex) % sol.length, (index + bestIndex + 1) % sol.length);
			} else {
				break;
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
}
