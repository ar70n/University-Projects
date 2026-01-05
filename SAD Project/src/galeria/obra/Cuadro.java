package galeria.obra;

/**
 * La clase Cuadro representa una obra de arte en forma de cuadro.
 * Hereda de la clase Fisica y agrega el atributo tecnica.
 * 
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Cuadro extends Fisica {
	private static final long serialVersionUID = 1L;
	private String tecnica;

	/**
	 * Crea una instancia de la clase Cuadro con los parámetros especificados.
	 * 
	 * @param nombre         el nombre del cuadro
	 * @param autor          el autor del cuadro
	 * @param ano            el año de creación del cuadro
	 * @param descripcion    la descripción del cuadro
	 * @param seguroCuantia  la cuantía del seguro del cuadro
	 * @param seguroPoliza   la póliza del seguro del cuadro
	 * @param enPropiedad    indica si el cuadro está en propiedad
	 * @param temperaturaMin la temperatura mínima recomendada para el cuadro
	 * @param temperaturaMax la temperatura máxima recomendada para el cuadro
	 * @param humedadMin     la humedad mínima recomendada para el cuadro
	 * @param humedadMax     la humedad máxima recomendada para el cuadro
	 * @param requiereTemp   indica si el cuadro requiere control de temperatura
	 * @param requiereHum    indica si el cuadro requiere control de humedad
	 * @param ancho          el ancho del cuadro
	 * @param alto           el alto del cuadro
	 * @param largo          el largo del cuadro
	 * @param tecnica        la técnica utilizada en el cuadro
	 * 
	 * @throws IllegalArgumentException si alguno de los parámetros no es válido
	 */
	public Cuadro(String nombre, String autor, int ano, String descripcion, double seguroCuantia,
			String seguroPoliza, boolean enPropiedad, double temperaturaMin,
			double temperaturaMax, double humedadMin, double humedadMax, boolean requiereTemp, boolean requiereHum,
			double ancho, double alto, double largo, String tecnica) {
		super(nombre, autor, ano, descripcion, seguroCuantia, seguroPoliza, enPropiedad, temperaturaMin,
				temperaturaMax, humedadMin, humedadMax, requiereTemp, requiereHum, ancho, alto, largo);
		this.tecnica = tecnica;
	}

	/**
	 * Obtiene el tipo de la obra, que en este caso es "Cuadro".
	 * 
	 * @return el tipo de la obra
	 */
	public String getTipo() {
		return "Cuadro";
	}

	/**
	 * Obtiene la técnica utilizada en el cuadro.
	 * 
	 * @return la técnica utilizada en el cuadro
	 */
	public String getTecnica() {
		return tecnica;
	}

	/**
	 * Devuelve una representación en forma de cadena de la instancia de la clase
	 * Cuadro.
	 * 
	 * @return una representación en forma de cadena de la instancia de la clase
	 *         Cuadro
	 */
	@Override
	public String toString() {
		return super.toString() + "Tecnica: " + tecnica + "\n";
	}
}
