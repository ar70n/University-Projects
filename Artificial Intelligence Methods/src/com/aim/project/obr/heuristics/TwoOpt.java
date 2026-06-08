package com.aim.project.obr.heuristics;

import java.util.Random;

import com.aim.project.obr.interfaces.HeuristicInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

/**
 * @author Antonio Moroño
 * @since (15/04/2026)
 * The 2-opt heuristic iteratively selects two positions in the solution and reverses the segment between them. 
 * Inspired by: Croes, G. A. (1958). A Method for Solving Traveling-Salesman Problems. Operations Research, 6(6), 791-812.
 */
public class TwoOpt extends HeuristicOperators implements HeuristicInterface {

    public TwoOpt(Random oRandom) {
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
        int n = sol.length;

        int currentEval = oSolution.getObjectiveFunctionValue();
        if (n < 2) {
            return currentEval;
        }

        for (int it = 0; it < n_iterations; it++) {

            int bestI = -1;
            int bestJ = -1;
            int bestDelta = 0; 

            //We explore from left to right all possible pairs of positions.
            for (int i = 0; i < n - 1; i++) {
                for (int j = i + 1; j < n; j++) {

                    //No need to invert the whole route
                    if (i == 0 && j == n - 1) {
                        continue;
                    }

                    int delta = twoOptDelta(sol, i, j); //We look for negative deltas
                    if (delta < bestDelta) {
                        bestDelta = delta;
                        bestI = i;
                        bestJ = j;
                    }
                }
            }

            //If after going through all the positions, we haven't found any improvement
            //we ignore the depth of search and exit (local optimum reached)
            if (bestI == -1) {
                break; 
            }

            //We only reverse the best segment found (steepest descent)
            reverseSegment(sol, bestI, bestJ);
            currentEval += bestDelta; //No need to recalculate the objective function value!
        }

        oSolution.setObjectiveFunctionValue(currentEval);
        return currentEval;
    }

    /**
     * Delta incremental of applying 2-opt over [i..j].
     * We break: (prev, i) y (j, next)
     * We create:  (prev, j) y (i, next)
     * We only calculate the cost!
     */
    private int twoOptDelta(int[] sol, int i, int j) {

        int n = sol.length;
        int a = (i == 0) ? -1 : sol[i - 1];     // -1 represents depot
        int b = sol[i];
        int c = sol[j];
        int d = (j == n - 1) ? -1 : sol[j + 1]; // -1 represents depot

        int oldCost = edgeCost(a, b) + edgeCost(c, d);
        int newCost = edgeCost(a, c) + edgeCost(b, d);

        return newCost - oldCost;
    }

    private int edgeCost(int from, int to) {

        if (from == -1 && to == -1) return 0; // depot to depot, shouldn't happen but just in case
        if (from == -1) return m_oObjectiveFunction.getDistanceBetweenBusDepotAndPoI(to);
        if (to == -1) return m_oObjectiveFunction.getDistanceBetweenBusDepotAndPoI(from);
        return m_oObjectiveFunction.getCost(from, to);
    }

    private void reverseSegment(int[] sol, int i, int j) {
        //Two indexes approach 
        while (i < j) {
            swap(sol, i, j);
            i++;
            j--;
        }
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