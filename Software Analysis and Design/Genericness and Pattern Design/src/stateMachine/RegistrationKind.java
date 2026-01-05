package stateMachine;

/**
 * Enumerado con los tipos de inscripción posibles.
 * 
 * @author EPS
 * @version 1.0
 */
public enum RegistrationKind {
	/**
	 * Inscripción completa.
	 */
	FULL(1100),

	/**
	 * Inscripción como miembro.
	 */
	MEMBER(900),

	/**
	 * Inscripción como estudiante.
	 */
	STUDENT(450);

	/**
	 * Precio de la inscripción.
	 */
	private int price;

	/**
	 * Constructor del enumerado.
	 * 
	 * @param price Precio de la inscripción.
	 */
	RegistrationKind(int price) {
		this.price = price;
	}

	/**
	 * Devuelve el precio de la inscripción.
	 * 
	 * @return Precio de la inscripción.
	 */
	public double getPrice() {
		return this.price;
	}
}
