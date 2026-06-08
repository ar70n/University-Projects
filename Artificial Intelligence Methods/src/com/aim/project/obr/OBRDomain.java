package com.aim.project.obr;

import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

import com.aim.project.obr.heuristics.AdjacentSwap;
import com.aim.project.obr.heuristics.CandidateListGuided;
import com.aim.project.obr.heuristics.CycleCrossover;
import com.aim.project.obr.heuristics.DavissHillClimbing;
import com.aim.project.obr.heuristics.DoubleBridgeKick;
import com.aim.project.obr.heuristics.Inversion;
import com.aim.project.obr.heuristics.NextDescent;
import com.aim.project.obr.heuristics.OrderCrossover;
import com.aim.project.obr.heuristics.PartiallyMappedCrossover;
import com.aim.project.obr.heuristics.Reinsertion;
import com.aim.project.obr.heuristics.SteepestDescent;
import com.aim.project.obr.heuristics.TwoOpt;
import com.aim.project.obr.instance.InitialisationMode;
import com.aim.project.obr.instance.Location;
import com.aim.project.obr.instance.reader.OBRInstanceReader;
import com.aim.project.obr.interfaces.*;

import AbstractClasses.ProblemDomain;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class OBRDomain extends ProblemDomain implements Visualisable, InLabPracticalExamInterface {
	
	private final String[] INSTANCE_FILES = {
		    "square.obr",              // ID 0
		    "libraries-15.obr",        // ID 1
		    "carparks-40.obr",         // ID 2
		    "tramstops-85.obr",        // ID 3
		    "grid.obr",                // ID 4
		    "clustered-pois.obr",      // ID 5
		    "chatgpt-instance-100-PoIs.obr", // ID 6
		    "my-nightmare.obr",		   // ID 7
		    "chaos.obr"				   // ID 8
		};
	private OBRInstanceReaderInterface instanceReader;
	private OBRInstanceInterface instance;
	
	private int[] ls_ids = null, mut_ids = null, xo_ids = null;
    private final int num_heuristics = 12;
    private HeuristicInterface[] heuristics;

    //Mutation heuristics
    private final int id_AdjacentSwap = 0;
    private final int id_Reinsertion = 1;
	private final int id_Inversion = 2;
	private final int id_DoubleBridgeKick = 3;

    //Local Search heuristics
    private final int id_DavissHillClimbing = 4;
    private final int id_NextDescent = 5;
    private final int id_SteepestDescent = 6;
    private final int id_CandidateListGuided = 7;
    private final int id_TwoOpt = 8;

    //Crossover heuristics
    private final int id_PartiallyMappedCrossover = 9;
    private final int id_OrderCrossover = 10;
    private final int id_CycleCrossover = 11;
    
    
    
    private OBRSolutionInterface[] solutions;
    private double best_value = Double.MAX_VALUE;
    private OBRSolutionInterface best_solution;
    private OBRSolutionInterface initial_solution = null;
    
	public OBRDomain(long lSeed) {

		super(lSeed);

        //  recommend to create the heuristics here
		heuristics = new HeuristicInterface[num_heuristics];
		heuristics[id_AdjacentSwap] = new AdjacentSwap(rng);
		heuristics[id_Reinsertion] = new Reinsertion(rng);
		heuristics[id_Inversion] = new Inversion(rng);
		heuristics[id_DoubleBridgeKick] = new DoubleBridgeKick(rng);
		heuristics[id_DavissHillClimbing] = new DavissHillClimbing(rng);
		heuristics[id_NextDescent] = new NextDescent(rng);
		heuristics[id_SteepestDescent] = new SteepestDescent(rng);
		heuristics[id_CandidateListGuided] = new CandidateListGuided(rng);
		heuristics[id_TwoOpt] = new TwoOpt(rng);
		heuristics[id_PartiallyMappedCrossover] = new PartiallyMappedCrossover(rng);
		heuristics[id_OrderCrossover] = new OrderCrossover(rng);
		heuristics[id_CycleCrossover] = new CycleCrossover(rng);
		
		
		ArrayList<Integer> ls = new ArrayList<>();
		ArrayList<Integer> mut = new ArrayList<>();
		ArrayList<Integer> xo = new ArrayList<>();
		for(int i = 0; i < num_heuristics; i++) {
			if (heuristics[i].usesDepthOfSearch()) ls.add(i);
			if (heuristics[i].usesIntensityOfMutation()) mut.add(i);
			if (heuristics[i].isCrossover()) xo.add(i);
			
		}
		this.ls_ids = ls.stream().sequential().mapToInt(i -> i).toArray();
		this.mut_ids = mut.stream().sequential().mapToInt(i -> i).toArray();
		this.xo_ids = xo.stream().sequential().mapToInt(i -> i).toArray();
        
		this.instanceReader = new OBRInstanceReader();
		
	}
	
	//Tengo una duda y es que no se si esta implementacion es correcta porque apply devuelve el objective value de la nueva solucion
	//Y nosotros justo despues hacemos getFunctionValue para ver si es la bestSolution pero no se
	@Override
	public double applyHeuristic(int iHeuristicIndex, int iCurrentSolutionIndex, int iCandidateSolutionIndex) {
	    
		copySolution(iCurrentSolutionIndex, iCandidateSolutionIndex);
		heuristics[iHeuristicIndex].apply(this.solutions[iCandidateSolutionIndex], this.depthOfSearch, this.intensityOfMutation);
		
		return getFunctionValue(iCandidateSolutionIndex);
	}

	@Override
	public double applyHeuristic(int iHeuristicIndex, int iParent1Index, int iParent2Index, int iCandidateIndex) {

		if (heuristics[iHeuristicIndex].isCrossover()) {
			CrossoverHeuristicInterface h = (CrossoverHeuristicInterface) heuristics[iHeuristicIndex];
			h.apply(this.solutions[iParent1Index], this.solutions[iParent2Index], this.solutions[iCandidateIndex], this.depthOfSearch, this.intensityOfMutation);
			
			return getFunctionValue(iCandidateIndex);
		}
		throw new IllegalArgumentException("Heuristic at index " + iHeuristicIndex + " is not a crossover heuristic.");
	}

	@Override
	public String bestSolutionToString() {
	
	    return Arrays.toString(this.getBestSolutionRepresentation());
	}

	@Override
	public boolean compareSolutions(int iSolutionIndexA, int iSolutionIndexB) {

		return Arrays.equals(this.solutions[iSolutionIndexA].getSolutionRepresentation().getSolutionRepresentation(),
				this.solutions[iSolutionIndexB].getSolutionRepresentation().getSolutionRepresentation());
	}

	@Override
	public void copySolution(int iSolutionIndexFrom, int iSolutionIndexTo) {

        //  this should create a deep copy of the solution
		solutions[iSolutionIndexTo] = solutions[iSolutionIndexFrom].clone();
	}

	@Override
	public double getBestSolutionValue() {
		return this.best_value;
	}
	
	@Override
	public double getFunctionValue(int iSolutionIndex) {

        double fitness = this.solutions[iSolutionIndex].getObjectiveFunctionValue();
		if (fitness < this.best_value) {
			this.best_value = fitness;
			this.updateBestSolution(iSolutionIndex);
		}
		return fitness;
	}

	@Override
	public int[] getHeuristicsOfType(HeuristicType oHeuristicType) {

		switch(oHeuristicType) {	
		case HeuristicType.LOCAL_SEARCH:
			return getHeuristicsThatUseDepthOfSearch();
		case HeuristicType.MUTATION:
			return getHeuristicsThatUseIntensityOfMutation();
		case HeuristicType.CROSSOVER:
			return this.xo_ids;
		default:
			break;
		}
        return new int[0];
	}

	@Override
	public int[] getHeuristicsThatUseDepthOfSearch() {
		return this.ls_ids;
	}

	@Override
	public int[] getHeuristicsThatUseIntensityOfMutation() {	
        return this.mut_ids;
    }
	
	@Override
	public int getNumberOfHeuristics() {

        //  Note needs hard coding due to the design of HyFlex.
        //  The ProblemDomain class calls this method upon initialisation.
		return num_heuristics;
	}

	@Override
	public int getNumberOfInstances() {

		return this.INSTANCE_FILES.length;
	}

	@Override
	public void initialiseSolution(int iSolutionIndex) {
		
        //  don't forget this might be the best solution found so far!
		OBRSolutionInterface new_sol = this.instance.createSolution(InitialisationMode.RANDOM);
		if (this.initial_solution == null) {
			this.initial_solution = new_sol.clone();
		}
		this.solutions[iSolutionIndex] =  new_sol;
		this.getFunctionValue(iSolutionIndex);
    }

	@Override
	public void loadInstance(int iInstanceId) {

        //  I recommend using <code>public URL getResource(String name)</code> and tag the folder with the
        //  instance files as a resource to help with project portability.
		URL url = getClass().getResource("/instances/obr/" + this.INSTANCE_FILES[iInstanceId]);
		try {
			this.instance = instanceReader.readOBRInstanceFile(Paths.get(url.toURI()), rng);
			for (HeuristicInterface h : this.heuristics) {
				h.setObjectiveFunction(instance.getOBRObjectiveFunction());
			}
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}		
	}

	@Override
	public void setMemorySize(int iNewMemorySize) {

		OBRSolutionInterface[] newSolutions = new OBRSolutionInterface[iNewMemorySize];
		if (this.solutions != null) {
			for (int i = 0; i < Math.min(this.solutions.length, iNewMemorySize); i++) {
	            newSolutions[i] = this.solutions[i]; 
	        }
		}
		this.solutions = newSolutions;
	}

	@Override
	public String solutionToString(int iSolutionIndex) {

	    return Arrays.toString(this.solutions[iSolutionIndex].getSolutionRepresentation().getSolutionRepresentation());
	}

	@Override
	public String toString() {

		return "Open-top Bus Routing";
	}
	
	private void updateBestSolution(int iSolutionIndex) {

		//  be careful that the reference is not saved otherwise we may modify it accidentally elsewhere in the code.
		this.best_solution = this.solutions[iSolutionIndex].clone();
	}
	
	@Override
	public OBRInstanceInterface getLoadedInstance() {

		return this.instance;
	}

	/**
	 * @return The integer array representing the ordering of the best solution.
	 */
	@Override
	public int[] getBestSolutionRepresentation() {

		return this.best_solution.getSolutionRepresentation().getSolutionRepresentation();
	}

	@Override
	public Location[] getRouteOrderedByPoIs() {

		int n_locs = this.instance.getNumberOfLocations() - 1;
		Location[] route = new Location[n_locs];
		
		int i = 0;
		for (int id : this.best_solution.getSolutionRepresentation().getSolutionRepresentation()) {
			route[i] = this.instance.getLocationForPoI(id);
			i++;
		}
		return route;
		
	}

	public OBRSolutionInterface getBestSolution() {

        return this.best_solution;
	}

    /**
     * Should print the best solution found in the form:
     * (d_x,d_y) - (l_x0,l_y0) - ... - (l_x{n-1},l_y{n-1}) - (d_x,d_y)
     * where:
     * `d` is the (bus) depot
     * `l_xi` is the x-coordinate of the location in the i^th index in the solution.
     * `l_yi` is the y-coordinate of the location in the i^th index in the solution.
     * <p>
     * For example:
     * (0,0) - (1,1) - (2,2) - (3,3) - (4,4) - (0,0)
     */
    @Override
    public void printBestSolutionFound() {

    	OBRSolutionInterface sol = this.getBestSolution();
    	ArrayList<Location> loRouteLocations = this.instance.getSolutionAsListOfLocations(sol);
    	
    	Iterator<Location> oLocationIterator = loRouteLocations.iterator();
		Location oLocation;

		StringBuilder sb = new StringBuilder();

		if(oLocationIterator.hasNext()) {

			oLocation = oLocationIterator.next();
			sb.append("(").append(oLocation.x()).append(",").append(oLocation.y()).append(")");
		}

		while(oLocationIterator.hasNext()) {

			oLocation = oLocationIterator.next();
			sb.append(" - ").append("(").append(oLocation.x()).append(",").append(oLocation.y()).append(")");

		}
		
		System.out.println(sb);
    }

    /**
     * Prints the objective value of the best solution found.
     */
    @Override
    public void printObjectiveValueOfTheBestSolutionFound() {

        System.out.println(this.getBestSolutionValue());
    }

    /**
     * Should print the initial solution:
     * (d_x,d_y) - (l_x0,l_y0) - ... - (l_x{n-1},l_y{n-1}) - (d_x,d_y)
     * where:
     * `d` is the (bus) depot
     * `l_xi` is the x-coordinate of the location in the i^th index in the solution.
     * `l_yi` is the y-coordinate of the location in the i^th index in the solution.
     * <p>
     * For example:
     * (0,0) - (2,2) - (1,1) - (3,3) - (4,4) - (0,0)
     */
    @Override
    public void printInitialSolution() {

    	OBRSolutionInterface sol = this.initial_solution;
    	ArrayList<Location> loRouteLocations = this.instance.getSolutionAsListOfLocations(sol);
    	
    	Iterator<Location> oLocationIterator = loRouteLocations.iterator();
		Location oLocation;

		StringBuilder sb = new StringBuilder();

		if(oLocationIterator.hasNext()) {

			oLocation = oLocationIterator.next();
			sb.append("(").append(oLocation.x()).append(",").append(oLocation.y()).append(")");
		}

		while(oLocationIterator.hasNext()) {

			oLocation = oLocationIterator.next();
			sb.append(" - ").append("(").append(oLocation.x()).append(",").append(oLocation.y()).append(")");
		}
		
		System.out.println(sb);
    }

    
}
