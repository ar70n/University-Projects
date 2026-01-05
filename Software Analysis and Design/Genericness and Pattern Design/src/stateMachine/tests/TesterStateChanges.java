package stateMachine.tests;

import stateMachine.*;
import stateMachine.IllegalStateException;

import static stateMachine.RegistrationState.*;
import static stateMachine.RegistrationKind.*;

/**
 * Clase de prueba para el primer apartado de la práctica.
 * 
 * @author EPS
 * @version 1.0
 */
public class TesterStateChanges {
	/**
	 * Tracker de estados de las inscripciones.
	 */
	protected ObjectStateTracker<Registration, RegistrationState> regState;

	/**
	 * Inscripciones de prueba.
	 */
	protected Registration annSmith, johnDoe, lisaMartin;

	/**
	 * Constructor por defecto.
	 */
	public TesterStateChanges() {
	}

	/**
	 * Método principal de la clase.
	 * 
	 * @param args Argumentos de la línea de comandos.
	 */
	public static void main(String[] args) {
		TesterStateChanges tsc = new TesterStateChanges();
		tsc.createRegistrations();
		System.out.println(tsc.regState);
		tsc.changeRegistrations();
		System.out.println(tsc.regState);
	}

	/**
	 * Método que cambia los estados de las inscripciones.
	 */
	protected void changeRegistrations() {
		this.annSmith.setAffiliation("University of Miskatonic"); // now it is filled
		this.johnDoe.pay(STUDENT.getPrice()); // becomes payed
		this.regState.updateStates();
	}

	/**
	 * Método que crea las inscripciones de prueba.
	 */
	protected void createRegistrations() {
		this.regState = new ObjectStateTracker<>(RegistrationState.values());
		try {
			regState.withState(PAYED, r -> r.getAmountPayed() == r.getTotalAmount() && !r.getValidated())
					.withState(STARTED, r -> r.getAffiliation() == null && !r.getValidated())
					.withState(FILLED, r -> r.getAffiliation() != null && !r.getValidated())
					.withState(VALIDATED, r -> r.getAmountPayed() == 0 && r.getValidated())
					.withState(FINISHED, r -> r.getAmountPayed() == r.getTotalAmount() && r.getValidated())
					.elseState(REJECTED);
		} catch (IllegalStateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		this.annSmith = new Registration("Ann Smith", FULL);
		this.johnDoe = new Registration("John Doe", STUDENT);
		this.lisaMartin = new Registration("Lisa Martin", MEMBER);
		this.regState.addObjects(annSmith, johnDoe, lisaMartin);
	}
}