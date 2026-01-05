package stateMachine;

/**
 * Clase que representa una inscripción en un evento.
 * 
 * @author EPS, Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public class Registration {
	/**
	 * Nombre del inscrito y afiliación.
	 */
	private String name, affiliation;

	/**
	 * Tipo de inscripción.
	 */
	private RegistrationKind kind;

	/**
	 * Cantidad de dinero pagada.
	 */
	private int amountPayed;

	/**
	 * Indica si la inscripción ha sido validada.
	 */
	private boolean validated;

	/**
	 * Observador de la clase.
	 */
	private static IObserver<Registration> tracker;

	/**
	 * Constructor de la clase.
	 * 
	 * @param name Nombre del inscrito.
	 * @param kind Tipo de inscripción.
	 */
	public Registration(String name, RegistrationKind kind) {
		this.kind = kind;
		this.name = name;
	}

	/**
	 * Método que permite pagar una cantidad de dinero para la inscripción.
	 * 
	 * @param amount Cantidad de dinero a pagar.
	 */
	public void pay(double amount) {
		this.amountPayed += amount;
		if (Registration.tracker != null) {
			Registration.tracker.updateStates();
		}
	}

	/**
	 * Devuelve la cantidad de dinero pagada.
	 * 
	 * @return Cantidad de dinero pagada.
	 */
	public double getAmountPayed() {
		return this.amountPayed;
	}

	/**
	 * Devuelve la cantidad total a pagar por la inscripción.
	 * 
	 * @return Cantidad total a pagar.
	 */
	public double getTotalAmount() {
		return this.kind.getPrice();
	}

	/**
	 * Devuelve al afiliación del inscrito.
	 * 
	 * @return Afiliación del inscrito.
	 */
	public String getAffiliation() {	
		return this.affiliation;
	}

	/**
	 * Establece la afiliación del inscrito.
	 * 
	 * @param aff Afiliación del inscrito.
	 */
	public void setAffiliation(String aff) {
		this.affiliation = aff;
		if (Registration.tracker != null) {
			Registration.tracker.updateStates();
		}
	}

	/**
	 * Devuelve la validez de la inscripción.
	 * 
	 * @return Validez de la inscripción.
	 */
	public boolean getValidated() {
		return this.validated;
	}

	/**
	 * Imprime la información de la inscripción.
	 * 
	 * @return Información de la inscripción.
	 */
	public String toString() {
		return "Reg. of: " + this.name;
	}

	/**
	 * Establece la validez de la inscripción.
	 * 
	 * @param b Validez de la inscripción.
	 */
	public void setValidated(boolean b) {
		this.validated = b;
		if (Registration.tracker != null) {
			Registration.tracker.updateStates();
		}
	}

	/**
	 * Sobrescribe el método equals para comparar inscripciones.
	 * 
	 * @param obj Objeto a comparar.
	 * @return True si son iguales, false en caso contrario.
	 */
	@Override
	public boolean equals(Object obj) {
		if (obj instanceof Registration) {
			Registration reg = (Registration) obj;
			return reg.name.equals(this.name);
		}
		return false;
	}

	/**
	 * Sobrescribe el método hashCode para comparar inscripciones.
	 * 
	 * @return Código hash de la inscripción.
	 */
	@Override
	public int hashCode() {
		return this.name.hashCode();
	}

	/**
	 * Establece el observador de la clase.
	 * 
	 * @param obj Observador de la clase.
	 */
	public static void withTracker(IObserver<Registration> obj) {
		Registration.tracker = obj;
	}
}
