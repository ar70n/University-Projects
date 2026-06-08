package com.aim.project.obr.solution;

import com.aim.project.obr.interfaces.OBRSolutionInterface;
import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class OBRSolution implements OBRSolutionInterface {

	private SolutionRepresentationInterface oRepresentation;
	private int iObjectiveFunctionValue;
	
	public OBRSolution(SolutionRepresentationInterface oRepresentation, int iObjectiveFunctionValue) {

		this.oRepresentation = oRepresentation;
		this.iObjectiveFunctionValue = iObjectiveFunctionValue;
	}

	@Override
	public int getObjectiveFunctionValue() {

        return iObjectiveFunctionValue;
	}

	@Override
	public void setObjectiveFunctionValue(int iObjectiveFunctionValue) {

		this.iObjectiveFunctionValue = iObjectiveFunctionValue;
	}

	@Override
	public SolutionRepresentationInterface getSolutionRepresentation() {

        return this.oRepresentation;
	}
	
	@Override
	public OBRSolutionInterface clone() {

		return new OBRSolution(oRepresentation.clone(), iObjectiveFunctionValue);
	}

	@Override
	public int getNumberOfLocations() {

        return this.oRepresentation.getTotalNumberOfLocations();
	}
}
