package com.aim.project.obr.heuristics;

import java.util.Random;

import com.aim.project.obr.interfaces.HeuristicInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class AdjacentSwap extends HeuristicOperators implements HeuristicInterface {

	public AdjacentSwap(Random oRandom) {

		super(oRandom);
	}

    /**
     * TODO - delta evaluation
     *
     * @param oSolution The solution to which the heuristic is applied. This solution may be modified during the method execution.
     * @param dDepthOfSearch The parameter controlling the extent or depth of exploration performed during the heuristic's application.
     * @param dIntensityOfMutation The parameter controlling the extent or intensity of changes introduced by the heuristic.
     * @return
     */
	@Override
	public int apply(OBRSolutionInterface oSolution, double dDepthOfSearch, double dIntensityOfMutation) {

		int n_swaps;
		if (0 <= dIntensityOfMutation && dIntensityOfMutation < 0.2) n_swaps = 1;
		else if(dIntensityOfMutation < 0.4) n_swaps = 2;
		else if(dIntensityOfMutation < 0.6) n_swaps = 4;
		else if(dIntensityOfMutation < 0.8) n_swaps = 8;
		else if(dIntensityOfMutation < 1) n_swaps = 16;
		else if(dIntensityOfMutation == 1) n_swaps = 32;
		else return Integer.MAX_VALUE;
		
		SolutionRepresentationInterface rep = oSolution.getSolutionRepresentation();
		int[] sol = rep.getSolutionRepresentation();
		
		for(int i = 0; i < n_swaps; i++) {
			int index = this.m_oRandom.nextInt(sol.length);
			this.swap(sol, index, (index + 1) % sol.length);
		}
		int value = this.calculateObjectiveValue(rep);
		oSolution.setObjectiveFunctionValue(value);
		return value;
	}

	@Override
	public boolean isCrossover() {

		return false;
	}

	@Override
	public boolean usesIntensityOfMutation() {

		return true;
	}

	@Override
	public boolean usesDepthOfSearch() {

		return false;
	}

}
