package com.aim.project.obr.heuristics;

import java.util.Arrays;
import java.util.Random;

import com.aim.project.obr.interfaces.HeuristicInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

/**
 * @author Antonio Moroño
 * @since (15/04/2026)
 * This mutation heuristic extracts 4 random segments of the solution and reconnects them in a different order.
 * Allows to generate different solutions preserving some structure instead of just doing random swaps.
 * Inspired by: Martin, O., Otto, S. W., Felten, E. W. (1991). Large-step Markov chains for the traveling salesman problem. Complex Systems, 5, 299-326.
 */
public class DoubleBridgeKick extends HeuristicOperators implements HeuristicInterface {

    public DoubleBridgeKick(Random oRandom) {
        super(oRandom);
    }

    @Override
    public int apply(OBRSolutionInterface oSolution, double dDepthOfSearch, double dIntensityOfMutation) {

        int nKicks;
        if (dIntensityOfMutation >= 0.0 && dIntensityOfMutation < 0.2) nKicks = 1;
        else if (dIntensityOfMutation < 0.4) nKicks = 2;
        else if (dIntensityOfMutation < 0.6) nKicks = 4;
        else if (dIntensityOfMutation < 0.8) nKicks = 8;
        else if (dIntensityOfMutation < 1.0) nKicks = 16;
        else if (dIntensityOfMutation == 1.0) nKicks = 32;
        else return Integer.MAX_VALUE;

        SolutionRepresentationInterface rep = oSolution.getSolutionRepresentation();
        int[] sol = rep.getSolutionRepresentation();
        int n = sol.length;

        //With less than 8 locations, we can't do a proper double bridge, so we just do random swaps instead.
        if (n < 8) {
            for (int k = 0; k < nKicks; k++) {
                int i = m_oRandom.nextInt(n);
                int j = i;
                while (j == i) j = m_oRandom.nextInt(n);
                swap(sol, i, j);
            }
            int value = calculateObjectiveValue(rep);
            oSolution.setObjectiveFunctionValue(value);
            return value;
        }

        for (int k = 0; k < nKicks; k++) {

            //We choose 4 random breakpoint, ensuring no overlap and at least one element in each segment
            int c1 = 1 + m_oRandom.nextInt(n - 6);          // [1 .. n-6]
            int c2 = c1 + 1 + m_oRandom.nextInt(n - c1 - 5);
            int c3 = c2 + 1 + m_oRandom.nextInt(n - c2 - 4);
            int c4 = c3 + 1 + m_oRandom.nextInt(n - c3 - 3);

            // Segments:
            // S0 = [0, c1)
            // S1 = [c1, c2)
            // S2 = [c2, c3)
            // S3 = [c3, c4)
            // S4 = [c4, n)

            int[] copy = Arrays.copyOf(sol, n);
            int p = 0;

            //We mix the segments in a fixed way to create the new solution.
            p = copySegment(copy, 0,  c1, sol, p);  // S0
            p = copySegment(copy, c3, c4, sol, p);  // S3
            p = copySegment(copy, c2, c3, sol, p);  // S2
            p = copySegment(copy, c1, c2, sol, p);  // S1
            p = copySegment(copy, c4, n,  sol, p);  // S4
        }

        int value = calculateObjectiveValue(rep);
        oSolution.setObjectiveFunctionValue(value);
        return value;
    }

    // Helper method to copy a segment of the solution array
    // Returns the next position to copy to in the destination array
    private int copySegment(int[] src, int from, int to, int[] dst, int pos) {
        for (int i = from; i < to; i++) {
            dst[pos++] = src[i];
        }
        return pos;
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