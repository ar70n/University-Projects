package stateMachine.tests;

import java.util.List;

import stateMachine.Registration;

/**
 * Clase de prueba para el tercer apartado de la práctica.
 * 
 * @author EPS
 */
public class TesterTrajectories extends TesterStateChanges {
	/**
	 * Constructor por defecto.
	 */
	public TesterTrajectories() {
		super();
	}

	/**
	 * Método principal de la clase.
	 * 
	 * @param args Argumentos de la línea de comandos.
	 */
	public static void main(String[] args) {
		TesterTrajectories tsc = new TesterTrajectories();
		tsc.createRegistrations();
		tsc.changeRegistrations();
		tsc.displayTrajectories();
	}

	/**
	 * Método que cambia los estados de las inscripciones.
	 */
	@Override
	protected void changeRegistrations() {
		super.changeRegistrations();
		this.johnDoe.setValidated(true);
		this.lisaMartin.setAffiliation("Arkham College");
		this.regState.updateStates();
	}

	/**
	 * Método que muestra las trayectorias de las inscripciones.
	 */
	protected void displayTrajectories() {
		for (Registration r : List.of(annSmith, johnDoe, lisaMartin))
			System.out.println(r + ": " + this.regState.trajectory(r));
	}
}