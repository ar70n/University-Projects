package galeria.obra;

/**
 * Esta clase representa una fotografía en la galería de arte.
 * Extiende la clase Fisica y hereda sus atributos y métodos.
 */
public class Fotografia extends Fisica {
	private static final long serialVersionUID = 1L;
	private boolean color;

	/**
	 * Crea una nueva instancia de la clase Fotografia.
	 *
	 * @param nombre         el nombre de la fotografía
	 * @param autor          el autor de la fotografía
	 * @param ano            el año de creación de la fotografía
	 * @param descripcion    la descripción de la fotografía
	 * @param seguroCuantia  la cuantía del seguro de la fotografía
	 * @param seguroPoliza   el número de póliza del seguro de la fotografía
	 * @param enPropiedad    indica si la fotografía está en propiedad de la galería
	 * @param temperaturaMin la temperatura mínima recomendada para la conservación
	 *                       de la fotografía
	 * @param temperaturaMax la temperatura máxima recomendada para la conservación
	 *                       de la fotografía
	 * @param humedadMin     la humedad mínima recomendada para la conservación de
	 *                       la fotografía
	 * @param humedadMax     la humedad máxima recomendada para la conservación de
	 *                       la fotografía
	 * @param requiereTemp   indica si la fotografía requiere control de temperatura
	 * @param requiereHum    indica si la fotografía requiere control de humedad
	 * @param ancho          el ancho de la fotografía en centímetros
	 * @param alto           el alto de la fotografía en centímetros
	 * @param largo          el largo de la fotografía en centímetros
	 * @param color          indica si la fotografía es a color
	 */
	public Fotografia(String nombre, String autor, int ano, String descripcion, double seguroCuantia,
			String seguroPoliza, boolean enPropiedad, double temperaturaMin,
			double temperaturaMax, double humedadMin, double humedadMax, boolean requiereTemp,
			boolean requiereHum, double ancho, double alto, double largo, boolean color) {
		super(nombre, autor, ano, descripcion, seguroCuantia, seguroPoliza, enPropiedad, temperaturaMin,
				temperaturaMax, humedadMin, humedadMax, requiereTemp, requiereHum, ancho, alto, largo);
		this.color = color;
	}

	/**
	 * Obtiene el tipo de la obra, que en este caso es "Fotografia".
	 *
	 * @return el tipo de la obra
	 */
	public String getTipo() {
		return "Fotografia";
	}

	/**
	 * Devuelve una representación en forma de cadena de la fotografía.
	 *
	 * @return una cadena que representa la fotografía
	 */
	@Override
	public String toString() {
		return super.toString() + "Color: " + color + "\n";
	}

}