package com.aim.project.obr.hyperheuristics;


import com.aim.project.obr.OBRDomain;
import com.aim.project.obr.SolutionPrinter;
import com.aim.project.obr.interfaces.OBRSolutionInterface;

import AbstractClasses.HyperHeuristic;
import AbstractClasses.ProblemDomain;
import AbstractClasses.ProblemDomain.HeuristicType;

import java.util.Arrays;

/**
 * This class extends the HyperHeuristic framework and implements a specific type of hyper-heuristic (MCF_AE_HH).
 * The goal of this hyper-heuristic is to iteratively explore the solution space by applying 
 * a perturbation heursitic (mutation/crossover) followed by a local search heuristic, while maintaining a memory of the best solutions found.
 * The hyper-heuristic uses a choice function to select which heuristics to apply at each step, based on their past performance, and employs an accept-everything move acceptance criterion.
 * The heuristics are selected using a choice function (one for perturbation heuristics and one for local search heuristics).
 *
 * @author Antonio Moroño
 * @since 1.0.0 (28/03/2026)
 */
public class MCF_AE_HH extends HyperHeuristic {

	private static final int BEST_ACCEPTED_INDEX = 2;

	public MCF_AE_HH(long lSeed) {
		
		super(lSeed);
	}

	@Override
	protected void solve(ProblemDomain oProblem) {

		oProblem.setMemorySize(8);

		int iCurrentSolutionIndex = 0;
		int iCandidateSolutionIndex = 1;
		
		//FIFO memory for crossover operators saving solutions that have improved the current solution.
		int[] iFifoMemory = {3, 4, 5, 6, 7}; 
		int mem_index = 0;
		
		//Initialization
		oProblem.initialiseSolution(iCurrentSolutionIndex);
		oProblem.copySolution(iCurrentSolutionIndex, BEST_ACCEPTED_INDEX);
		oProblem.copySolution(iCurrentSolutionIndex, iCandidateSolutionIndex);
		for (int index : iFifoMemory) {
			oProblem.copySolution(iCurrentSolutionIndex, index);
		}
		
		double dCurrentCost = oProblem.getFunctionValue(iCurrentSolutionIndex);
		int iNumberOfHeuristics = oProblem.getNumberOfHeuristics();

		// cache indices of crossover heuristics
		boolean[] abIsCrossover = new boolean[iNumberOfHeuristics];
		Arrays.fill(abIsCrossover, false);

		for(int i : oProblem.getHeuristicsOfType(ProblemDomain.HeuristicType.CROSSOVER)) {
			abIsCrossover[i] = true;
		}
		
		// initialize choice function selectors for perturbation heuristics and local search heuristics
		ChoiceFunctionSelection cfs_ls = new ChoiceFunctionSelection(oProblem.getHeuristicsThatUseDepthOfSearch(), this.getElapsedTime(), rng);
		
		int[] ids = Arrays.copyOf(oProblem.getHeuristicsThatUseIntensityOfMutation(),oProblem.getHeuristicsThatUseIntensityOfMutation().length + oProblem.getHeuristicsOfType(HeuristicType.CROSSOVER).length);
		System.arraycopy(oProblem.getHeuristicsOfType(HeuristicType.CROSSOVER),0, ids, oProblem.getHeuristicsThatUseIntensityOfMutation().length, oProblem.getHeuristicsOfType(HeuristicType.CROSSOVER).length);
		ChoiceFunctionSelection cfs_rest = new ChoiceFunctionSelection(ids, this.getElapsedTime(), rng);
		
		
		oProblem.setIntensityOfMutation(0.6); //0.6-0.8 sweet spot for iom
		oProblem.setDepthOfSearch(0.4); //0.4 sweet spot for dos
		long start1;
		long end1;
		long start2;
		long end2;
		
		// If you want to make the HH more sophisticated you can use annealing for the acceptance criterion.
		// I didnt see benefit in using it
		//GeometricCooling m_oCoolingSchedule = new GeometricCooling(dCurrentCost);

		// main search loop
		double dCandidateCost;
		while(!hasTimeExpired()) {
			
			//We select the perturbation heuristic
			int iHeuristicId = cfs_rest.chooseHeuristic();
			
			start1 = System.nanoTime();
			double afterPert;
			// If the selected heuristic is a crossover, we select the second parent from either the best accepted solution or from the FIFO memory, with a bias towards the best accepted solution.
			if(abIsCrossover[iHeuristicId]) {
				if (rng.nextDouble() < 0.7) {
					afterPert = oProblem.applyHeuristic(iHeuristicId, iCurrentSolutionIndex, BEST_ACCEPTED_INDEX, iCandidateSolutionIndex);
				} else {
					afterPert = oProblem.applyHeuristic(iHeuristicId, iCurrentSolutionIndex, iFifoMemory[rng.nextInt(iFifoMemory.length)], iCandidateSolutionIndex);
				}
			} else {
				afterPert = oProblem.applyHeuristic(iHeuristicId, iCurrentSolutionIndex, iCandidateSolutionIndex);
			}
			end1 = System.nanoTime();

			//We select the local search heuristic			
			int iHeuristicIdls = cfs_ls.chooseHeuristic();
			start2 = System.nanoTime();
			dCandidateCost = oProblem.applyHeuristic(iHeuristicIdls, iCandidateSolutionIndex, iCandidateSolutionIndex);
			end2 = System.nanoTime();
			
			// update the best solution for use with crossover operators
			if (dCandidateCost <= oProblem.getBestSolutionValue()) {
				oProblem.copySolution(iCandidateSolutionIndex, BEST_ACCEPTED_INDEX);
			}
			
			// update the FIFO memory if the candidate solution is better than the current solution.
			if(dCandidateCost < dCurrentCost) {
				oProblem.copySolution(iCandidateSolutionIndex, iFifoMemory[mem_index]);
				mem_index = (mem_index + 1) % iFifoMemory.length;
			}

			// update choice function scores and phi values for both the perturbation heuristic and the local search heuristic based on their performance.
			// notice how we reward the perturbation heuristic based on the improvement after the perturbation and after the local search.
			double lambda = 0.2;
			cfs_rest.updateChoiceFunctionValues(iHeuristicId, lambda*(dCurrentCost - afterPert) + (1 - lambda)*(dCurrentCost - dCandidateCost) , end1 - start1, this.getElapsedTime());
			cfs_ls.updateChoiceFunctionValues(iHeuristicIdls, (afterPert - dCandidateCost), end2 - start2, this.getElapsedTime());

			//Again this commented code implements an annealing acceptance criterion, but I found that accepting all moves worked better for this particular HH.
			//double delta = oProblem.getFunctionValue(iCandidateSolutionIndex) - oProblem.getFunctionValue(iCurrentSolutionIndex);
			//if (delta < 0 || this.rng.nextDouble() < Math.exp(-delta/m_oCoolingSchedule.getCurrentTemperature())) {
				
				//accepts all moves
				dCurrentCost = dCandidateCost;

                // swapping indices saves having to do a deep copy of the solution
				iCurrentSolutionIndex = 1 - iCurrentSolutionIndex;
				iCandidateSolutionIndex = 1 - iCandidateSolutionIndex;
			//}
			//m_oCoolingSchedule.advanceTemperature();
		}

		
		OBRSolutionInterface oSolution = ((OBRDomain) oProblem).getBestSolution();
		SolutionPrinter oSolutionPrinter = new SolutionPrinter("sr-ie-hh-out.csv");
		oSolutionPrinter.printSolution( ((OBRDomain) oProblem).getLoadedInstance().getSolutionAsListOfLocations(oSolution));
	}

	@Override
	public String toString() {

		return "SR_IE_HH";
	}
}
