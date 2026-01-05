package stateMachine.tests;

import stateMachine.*;
import stateMachine.Process;

/**
 * Clase de prueba para el cuarto apartado de la práctica.
 * 
 * @author EPS
 * @version 1.0
 */
public class TesterProcess extends TesterTrajectories {
	/**
	 * Constructor por defecto.
	 */
	public TesterProcess() {
		super();
	}

	/**
	 * Método principal de la clase.
	 * 
	 * @param args Argumentos de la línea de comandos.
	 */
	public static void main(String[] args) {
		TesterProcess tsc = new TesterProcess();
		tsc.createRegistrations();
		tsc.changeRegistrations();
		tsc.displayTrajectories();
		tsc.buildProcess();
	}

	/**
	 * Método que cambia los estados de las inscripciones.
	 */
	@Override
	protected void changeRegistrations() {
		super.changeRegistrations();
		this.lisaMartin.setValidated(true);
		this.regState.updateStates();
		this.lisaMartin.pay(RegistrationKind.MEMBER.getPrice());
		this.regState.updateStates();
	}

	/**
	 * Método que construye el proceso de las inscripciones.
	 */
	protected void buildProcess() {
		Process<RegistrationState> regProcess = new Process<>(RegistrationState.values());
		for (Registration r : this.regState) // iterates on all Registrations
			regProcess.add(this.regState.trajectory(r));
		System.out.println(regProcess);
	}
}