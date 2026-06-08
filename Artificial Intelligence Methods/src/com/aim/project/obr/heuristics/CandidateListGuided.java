package com.aim.project.obr.heuristics;

import java.util.Arrays;
import java.util.Random;

import com.aim.project.obr.interfaces.HeuristicInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

/**
 * @author Antonio Moroño
 * @since (15/04/2026)
 * It is basically like a NextDescent but instead of exploring adjacent swaps, it explores the k-closest locations to the current position, where k is determined as a function of the depth of search and the number of locations.
 * The candidate list is built based on the distance between the current position and any other position.
 */
public class CandidateListGuided extends HeuristicOperators implements HeuristicInterface {

    public CandidateListGuided(Random oRandom) {
        super(oRandom);
    }

    @Override
    public int apply(OBRSolutionInterface oSolution, double dDepthOfSearch, double dIntensityOfMutation) {

        int nIterations;
        if (dDepthOfSearch >= 0.0 && dDepthOfSearch < 0.2) nIterations = 1;
        else if (dDepthOfSearch < 0.4) nIterations = 2;
        else if (dDepthOfSearch < 0.6) nIterations = 3;
        else if (dDepthOfSearch < 0.8) nIterations = 4;
        else if (dDepthOfSearch <= 1.0) nIterations = 5;
        else return Integer.MAX_VALUE;

        SolutionRepresentationInterface rep = oSolution.getSolutionRepresentation();
        int[] sol = rep.getSolutionRepresentation();
        int n = sol.length;

        int currentEval = oSolution.getObjectiveFunctionValue();

        //The number of candidate positions k is determined as a function of the depth of search and the number of locations.
        //k = 5 for depth of search 0, and k = 20 for depth of search 1
        int k = Math.max(5, (int) Math.round((0.05 + 0.15 * dDepthOfSearch) * n));
        k = Math.min(k, Math.max(1, n - 1)); // Ensure k is between 1 and n-1

        for (int it = 0; it < nIterations; it++) {

            boolean improved = false; //First improvement

            int start = this.m_oRandom.nextInt(n);

            for (int offset = 0; offset < n; offset++) {
                int iPos = (start + offset) % n;

                int[] candidatePositions = getNearestCandidatePositions(sol, iPos, k);

                int bestJPos = -1;
                int bestEvalForI = currentEval;

                //We want the best swap for all the candidate positions.
                for (int idx = 0; idx < candidatePositions.length; idx++) {
                    int jPos = candidatePositions[idx];

                    this.swap(sol, iPos, jPos);
                    int tmpEval = this.calculateObjectiveValue(rep);
                    this.swap(sol, iPos, jPos);

                    if (tmpEval < bestEvalForI) {
                        bestEvalForI = tmpEval;
                        bestJPos = jPos;
                    }
                }

                //If the best swap in the current position's candidate list improves the solution, we apply it and exit. (first improvement)
                if (bestJPos != -1) {
                    this.swap(sol, iPos, bestJPos);
                    currentEval = bestEvalForI;
                    improved = true;
                    break;
                }
            }

            //If after going through all the positions, we haven't found any improvement
            //we ignore the depth of search and exit (local optimum reached)
            if (!improved) {
                break;
            }
        }

        oSolution.setObjectiveFunctionValue(currentEval);
        return currentEval;
    }

    /**
     * Returns the k closest positions to iPos
     */
    private int[] getNearestCandidatePositions(int[] sol, int iPos, int k) {

        final int n = sol.length;
        final int poiI = sol[iPos];

        int[] bestPos = new int[k];
        int[] bestCost = new int[k];

        Arrays.fill(bestPos, -1);
        Arrays.fill(bestCost, Integer.MAX_VALUE);

        for (int jPos = 0; jPos < n; jPos++) {
            if (jPos == iPos) continue;

            int cost = this.m_oObjectiveFunction.getCost(poiI, sol[jPos]);

            //If the current cost is better than any in the array,
            //we shift up the costs (losing the reference of the one on top of the array which is the farest candidate)
            //and insert the current cost in the free position, keeping the array sorted
            //Closest candidate is at the beginning of the array
            for (int i = 0; i < k; i++) {
                if (cost < bestCost[i]) {
                    for (int j = k - 1; j > i; j--) {
                        bestCost[j] = bestCost[j - 1];
                        bestPos[j] = bestPos[j - 1];
                    }
                    bestCost[i] = cost;
                    bestPos[i] = jPos;
                    break;
                }
            }
        }

        return bestPos;
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