package com.aim.project.obr.instance;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

import com.aim.project.obr.OBRObjectiveFunction;
import com.aim.project.obr.interfaces.ObjectiveFunctionInterface;
import com.aim.project.obr.interfaces.OBRInstanceInterface;
import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.solution.OBRSolution;
import com.aim.project.obr.solution.SolutionRepresentation;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class OpenTopBusRoutingInstance implements OBRInstanceInterface {

    private final int m_iNumberOfLocations;
    private final Location[] m_aoLocations;
    private final Location m_oBusDepotLocation;
    private final Random m_oRandom;
    private final ObjectiveFunctionInterface m_oObjectiveFunction;

    public OpenTopBusRoutingInstance(int iNumberOfLocations, Location[] aoLocations, Location oBusDepotLocation, Random oRandom) {

        this.m_iNumberOfLocations = iNumberOfLocations;
        this.m_aoLocations = aoLocations;
        this.m_oBusDepotLocation = oBusDepotLocation;
        this.m_oRandom = oRandom;
        this.m_oObjectiveFunction = new OBRObjectiveFunction(this);
    }

	@Override
	public OBRSolution createSolution(InitialisationMode oMode) {
		SolutionRepresentation rep = null;
		switch(oMode) {
		case InitialisationMode.RANDOM:
			//We shuffle first and get the ids after because its easier than dealing with Integer/int types
			List<Location> locations = new ArrayList<>(Arrays.asList(this.m_aoLocations));
			Collections.shuffle(locations, m_oRandom);
			
			int[] random_sol = locations.stream().sequential().mapToInt(loc->loc.iLocationId()).toArray();

			rep = new SolutionRepresentation(random_sol);
			return new OBRSolution(rep, this.m_oObjectiveFunction.getObjectiveFunctionValue(rep));

			
		case InitialisationMode.CONSTRUCTIVE:
			// nearest neighbour greedy algorithm
			int[] constructive_sol = new int[m_iNumberOfLocations - 1];
			
			//We get a list with ids and an array with distances with relation id[i]<->distance[i]
			List<Integer> loc_ids = new ArrayList<>(Arrays.stream(m_aoLocations).sequential().mapToInt(loc->loc.iLocationId()).boxed().toList());
			int[] distances = loc_ids.stream().sequential().mapToInt(loc->this.m_oObjectiveFunction.getDistanceBetweenBusDepotAndPoI(loc)).toArray();
			//ArrayList<Integer> mins_index = new ArrayList<>();
			
			int min = 0;
			for(int i = 0; i < distances.length; i++) {
				if (distances[i] < distances[min]) {
				//	mins_index.clear();
				//	mins_index.add(i);
					min = i;
				}
				//else if (distances[i] == distances[min]) {
				//	mins_index.add(i);
				//}
			}
			//Integer final_index = mins_index.get(m_oRandom.nextInt(mins_index.size()));
			Integer final_index = min;
			constructive_sol[0] = loc_ids.get(final_index);
			loc_ids.remove(final_index.intValue());
			//mins_index.clear();
			
			for (int j = 1; j < constructive_sol.length; j++) {
				int aux = j; //Compiler complains because of lambda expression if not
				distances = loc_ids.stream().sequential().mapToInt(loc->this.m_oObjectiveFunction.getCost(constructive_sol[aux - 1], loc)).toArray();
				min = 0;
				for(int i = 0; i < distances.length; i++) {
					if (distances[i] < distances[min]) {
						//mins_index.clear();
						//mins_index.add(i);
						min = i;
					}
					//else if (distances[i] == distances[min]) {
					//	mins_index.add(i);
					//}
				}
				
				//final_index = mins_index.get(m_oRandom.nextInt(mins_index.size()));
				final_index = min;
				constructive_sol[j] = loc_ids.get(final_index);
				loc_ids.remove(final_index.intValue());
				//mins_index.clear();
			}
			rep = new SolutionRepresentation(constructive_sol);
			return new OBRSolution(rep, this.m_oObjectiveFunction.getObjectiveFunctionValue(rep));

		default:
			return null;
		}
    }

    @Override
	public ObjectiveFunctionInterface getOBRObjectiveFunction() {

		return this.m_oObjectiveFunction;
	}

	@Override
	public int getNumberOfLocations() {

        return this.m_iNumberOfLocations;
	}

	@Override
	public Location getLocationForPoI(int iPointOfInterestId) {

		for (Location l : m_aoLocations) {
			if (l.iLocationId() == iPointOfInterestId){
				return l;
			}
		}
		return null;
	}

	@Override
	public Location getLocationOfBusDepot() {

        return this.m_oBusDepotLocation;
	}

	@Override
	public ArrayList<Location> getSolutionAsListOfLocations(OBRSolutionInterface oSolution) {

		ArrayList<Location> list = new ArrayList<>(this.m_iNumberOfLocations);
		list.add(m_oBusDepotLocation);
		
		//We take the array of ints which are the ids of the locations so we map them to get a list of locations en we add them to the list (which only contained the bus depot)
		list.addAll((Arrays.stream(oSolution.getSolutionRepresentation().getSolutionRepresentation()).sequential().mapToObj((id->getLocationForPoI(id))).toList()));
        return list;
    }
}
