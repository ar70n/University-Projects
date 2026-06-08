package com.aim.project.obr.hyperheuristics;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

/**
 * @author Antonio Moroño
 * @since 28/03/2026 
 * 	
 * 		  Inspired by:
 *        https://people.cs.nott.ac.uk/pszeo/docs/publications/CF_GD_LA.pdf#:~:text=selection%20hyper-heuristic%20is%20a%20high%20level%20search%20methodology,is%20then%20accepted%20or%20rejected%20at%20each%20step.
 * 
 *        This class implements the choice function described in the paper above
 *        with some additional modifications: 
 * 		  -We use an annealing epsilon-greedy strategy for exploration, instead of a pure greedy one.
 *        -We normalize the f1 and f2 scores to avoid issues with different
 *        scales between them and f3.
 */
public class ChoiceFunctionSelection {
	// Parameters to tune
	private double epsilon = 0.15;
	private final double epsilonMin = 0.01;
	private final double epsilonDecay = 0.999;

	private double phi[];

	private int iNumberOfHeuristics;
	private double max_f1;
	private double[] f1_scores;
	private double[] f1_counts;

	private double[] max_f2;
	private double[][] f2_scores;
	private double[][] f2_counts;
	private int last_iHeuristicId;

	private int[] actual_ids; // Used to convert between heuristic ids and their index in the arrays

	private long[] f3_times;

	private double[] choiceFunctionValues;

	private Random rng;

	ChoiceFunctionSelection(int[] ids, long timeStart, Random random) {
		rng = random;

		actual_ids = ids;
		iNumberOfHeuristics = ids.length;
		phi = new double[iNumberOfHeuristics];
		Arrays.fill(phi, 0.5);

		max_f1 = 1e-9;
		f1_scores = new double[iNumberOfHeuristics];
		f1_counts = new double[iNumberOfHeuristics];
		Arrays.fill(f1_scores, 0);
		Arrays.fill(f1_counts, 1);

		max_f2 = new double[iNumberOfHeuristics + 1];
		Arrays.fill(max_f2, 1e-9);
		f2_scores = new double[iNumberOfHeuristics + 1][iNumberOfHeuristics];
		f2_counts = new double[iNumberOfHeuristics + 1][iNumberOfHeuristics];
		for (int i = 0; i <= iNumberOfHeuristics; i++) {
			Arrays.fill(f2_scores[i], 0);
			Arrays.fill(f2_counts[i], 1);
		}
		last_iHeuristicId = iNumberOfHeuristics;

		f3_times = new long[iNumberOfHeuristics];
		Arrays.fill(f3_times, timeStart);

		choiceFunctionValues = new double[iNumberOfHeuristics];
		Arrays.fill(choiceFunctionValues, 0);

	}

	public double[] getChoiceFunctionValues() {
		return choiceFunctionValues;
	}

	//Calculates the scores and updates phi as described in the paper
	public void updateChoiceFunctionValues(int iHeuristicId, double dImprovement, long tttr, long ElapsedTime) {
		iHeuristicId = indexOf(iHeuristicId);
		if (dImprovement > 0) {
			this.phi[iHeuristicId] = 0.99;
		} else {
			this.phi[iHeuristicId] = Math.max(0.01, phi[iHeuristicId] - 0.001);
		}
		double qualityPerMs = dImprovement / Math.max(1L, tttr) * 1_000_000d;

		f1_scores[iHeuristicId] = qualityPerMs * f1_counts[iHeuristicId] + f1_scores[iHeuristicId];
		f1_counts[iHeuristicId] = f1_counts[iHeuristicId] * phi[iHeuristicId];
		max_f1 = Math.max(max_f1, Math.abs(f1_scores[iHeuristicId]));

		f2_scores[last_iHeuristicId][iHeuristicId] = qualityPerMs * f2_counts[last_iHeuristicId][iHeuristicId]
				+ f2_scores[last_iHeuristicId][iHeuristicId];
		f2_counts[last_iHeuristicId][iHeuristicId] = f2_counts[last_iHeuristicId][iHeuristicId] * phi[iHeuristicId];
		max_f2[last_iHeuristicId] = Math.max(max_f2[last_iHeuristicId],
				Math.abs(f2_scores[last_iHeuristicId][iHeuristicId]));

		f3_times[iHeuristicId] = ElapsedTime;

		//We normalize the scores with the maximum absolute values. (we dont want negative division or zero division)
		for (int i = 0; i < this.iNumberOfHeuristics; i++) {
			double normF1 = f1_scores[i] / max_f1;
			double normF2 = f2_scores[last_iHeuristicId][i] / max_f2[last_iHeuristicId];
			double normF3 = (double) (ElapsedTime + 1 - f3_times[i]) / (ElapsedTime + 1); // +1 to avoid 0 division

			choiceFunctionValues[i] = phi[i] * normF1 + phi[i] * normF2 + (1 - phi[i]) * normF3;
		}
		last_iHeuristicId = iHeuristicId;

	}

	private int indexOf(int iHeuristicId) {
		for (int i = 0; i < this.iNumberOfHeuristics; i++) {
			if (this.actual_ids[i] == iHeuristicId) {
				return i;
			}
		}
		return -1;
	}

	//Implements the epsilon-greedy strategy for heuristic selection based on the choice function values.
	public int chooseHeuristic() {
		if (rng.nextDouble() < epsilon) {
			int randomId = rng.nextInt(this.iNumberOfHeuristics);
			epsilon = Math.max(epsilonMin, epsilon * epsilonDecay);
			return actual_ids[randomId];
		}

		int index = 0;
		ArrayList<Integer> indexes = new ArrayList<>();
		for (int id = 0; id < this.iNumberOfHeuristics; id++) {
			if (this.choiceFunctionValues[id] > this.choiceFunctionValues[index]) {
				indexes.clear();
				indexes.add(id);
				index = id;
			} else if (this.choiceFunctionValues[id] == this.choiceFunctionValues[index]) {

				indexes.add(id);
			}
		}
		epsilon = Math.max(epsilonMin, epsilon * epsilonDecay);
		return actual_ids[indexes.get(this.rng.nextInt(indexes.size()))];
	}

}
