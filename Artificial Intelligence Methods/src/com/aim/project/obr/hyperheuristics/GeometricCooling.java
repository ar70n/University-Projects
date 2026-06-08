package com.aim.project.obr.hyperheuristics;


/**
 * 
 * @author Warren G. Jackson
 *
 */
public class GeometricCooling  {
	
	/**
	 * Maintain the state of the current temperature
	 */
	private double m_dCurrentTemperature;
	
	/**
	 * The $\alpha$ parameter of the cooling schedule.
	 * Recall from the lectures what a "reasonable" setting should be but be prepared to experiment to find a "good" value!
	 */
	private final double m_dAlpha;
	
	/**
	 * 
	 * @param dInitialSolutionFitness The objective value of the initial solution.
	 */
	public GeometricCooling(double dInitialSolutionFitness) {
			
		this.m_dCurrentTemperature = dInitialSolutionFitness;
		
		// TODO You will need to find a suitable value for alpha 
		//      through prior knowledge and experimentation!
		this.m_dAlpha = 0.999925d; //0.9999225dd;
	}

	
	public double getCurrentTemperature() {
		
		return this.m_dCurrentTemperature;
	}

	/**
	 * DEFINITION: T_{i + 1} = alpha * T_i
	 */
	
	public void advanceTemperature() {
		
		// TODO update the value of the current temperature, 'm_dCurrentTemperature'
		this.m_dCurrentTemperature = this.m_dAlpha * this.m_dCurrentTemperature;
	}
	
	public String toString() {
		
		return "Geometric Cooling (α = " + this.m_dAlpha + ")";
	}
}
