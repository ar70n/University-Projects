package stateMachine;

/**
 * Enumerado con los estados de la inscripción posibles.
 * 
 * @author EPS
 * @version 1.0
 */
public enum RegistrationState {
	/**
	 * Inscripción iniciada.
	 */
	STARTED,

	/**
	 * Inscripción rellenada.
	 */
	FILLED,

	/**
	 * Inscripción validada.
	 */
	VALIDATED,

	/**
	 * Inscripción pagada.
	 */
	PAYED,

	/**
	 * Inscripción finalizada.
	 */
	FINISHED,

	/**
	 * Inscripción rechazada.
	 */
	REJECTED;
}
