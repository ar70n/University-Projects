package com.aim.project.obr.solution;

import com.aim.project.obr.interfaces.SolutionRepresentationInterface;

/**
 * @author Warren G Jackson
 * @since 1.0.0 (15/03/2026)
 */
public class SolutionRepresentation implements SolutionRepresentationInterface {

	private int[] aiRepresentation;
	
	public SolutionRepresentation(int[] aiRepresentation) {

		this.aiRepresentation = aiRepresentation;
	}

	@Override
	public int[] getSolutionRepresentation() {

        return this.aiRepresentation;
	}

	@Override
	public void setSolutionRepresentation(int[] aiSolutionRepresentation) {

        this.aiRepresentation = aiSolutionRepresentation;
	}

	@Override
	public int getTotalNumberOfLocations() {

        return this.aiRepresentation.length + 1;
	}

	@Override
	public SolutionRepresentationInterface clone() {

        return new SolutionRepresentation(this.aiRepresentation.clone());
	}
}
