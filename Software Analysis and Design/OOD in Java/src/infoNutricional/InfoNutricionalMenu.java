package infoNutricional;

/**
 * Esta clase representa la información nutricional de un menú.
 * Extiende la clase InfoNutricionalConjunto.
 * @author Antonio Moroño y Pedro Ismael Haddou
 */
public class InfoNutricionalMenu extends InfoNutricionalConjunto {

	/**
	 * Devuelve una representación en cadena de caracteres de la información nutricional del menú.
	 * @return La información nutricional del menú.
	 */
	@Override
	public String toString() {
		return "INFORMACION NUTRICIONAL DEL MENU  " + super.toString();
	}

	/**
	 * Devuelve una representación en cadena de caracteres del tipo de información (menú).
	 * @return El tipo de información (menú).
	 */
	public String printInfo() {
		return "MENU";
	}

}