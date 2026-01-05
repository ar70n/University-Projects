package stateMachine.tests;

import stateMachine.Registration;
import stateMachine.RegistrationKind;

/**
 * Clase de prueba para el segundo apartado de la práctica.
 * 
 * @author EPS
 */
public class TesterRepeatedObjects extends TesterStateChanges {
	/**
	 * Constructor por defecto.
	 */
	public TesterRepeatedObjects() {
		super();
	}

	/**
	 * Método principal de la clase.
	 * 
	 * @param args Argumentos de la línea de comandos.
	 */
	public static void main(String[] args) {
		TesterRepeatedObjects tsc = new TesterRepeatedObjects();
		tsc.createRegistrations();
		tsc.regState.addObjects(new Registration("Ann Smith", RegistrationKind.STUDENT)); // Discarded, since repeated
		System.out.println(tsc.regState);
	}
}