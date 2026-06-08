package com.aim.project.obr;

import com.aim.project.obr.interfaces.ObjectiveFunctionInterface;
import com.aim.project.obr.interfaces.OBRInstanceInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class OBRObjectiveFunction implements ObjectiveFunctionInterface {

    private final OBRInstanceInterface m_oInstance;
	private int m_iDistanceCache[][] = null;
	private int m_iDistanceCacheBusDepot[] = null;

	public OBRObjectiveFunction(OBRInstanceInterface oInstance) {

        this.m_oInstance = oInstance;
		int n_locs = this.m_oInstance.getNumberOfLocations() - 1;
		this.m_iDistanceCache = new int[n_locs][n_locs];
		for (int i = 0; i < n_locs; i++) {
			for (int j = 0; j < n_locs; j++) {
				this.m_iDistanceCache[i][j] = this.getCostRaw(i, j);
			}
		}
		this.m_iDistanceCacheBusDepot = new int[n_locs];
		for (int i = 0; i < n_locs; i++) {
			this.m_iDistanceCacheBusDepot[i] = this.getDistanceBetweenBusDepotAndPoIRaw(i);
		}
	}

	@Override
	public int getObjectiveFunctionValue(SolutionRepresentationInterface oSolution) {

		int[] sol = oSolution.getSolutionRepresentation();
		int total = getDistanceBetweenBusDepotAndPoI(sol[0]);
		for(int i = 0; i < oSolution.getTotalNumberOfLocations() - 2; i++) {
			total+=getCost(sol[i], sol[i+1]);
		}
		total+=getDistanceBetweenBusDepotAndPoI(sol[oSolution.getTotalNumberOfLocations() - 2]);
		return total;
	}

	@Override
	public int getCost(int iLocationA, int iLocationB) {

        return this.m_iDistanceCache[iLocationA][iLocationB];	
	}

	@Override
	public int getDistanceBetweenBusDepotAndPoI(int iLocation) {

        return this.m_iDistanceCacheBusDepot[iLocation];
	}

	//Metodo mio
	private int getCostRaw(int iLocationA, int iLocationB) {
	
	    return (int) Math.ceil(Math.sqrt(
        		Math.pow(m_oInstance.getLocationForPoI(iLocationA).x() - m_oInstance.getLocationForPoI(iLocationB).x(),2) + 
        		Math.pow(m_oInstance.getLocationForPoI(iLocationA).y() - m_oInstance.getLocationForPoI(iLocationB).y(), 2)));
	}

	//Metodo mio
	public int getDistanceBetweenBusDepotAndPoIRaw(int iLocation) {

        return (int) Math.ceil(Math.sqrt(
        		Math.pow(m_oInstance.getLocationOfBusDepot().x() - m_oInstance.getLocationForPoI(iLocation).x(),2) + 
        		Math.pow(m_oInstance.getLocationOfBusDepot().y() - m_oInstance.getLocationForPoI(iLocation).y(), 2)));
	}
}
