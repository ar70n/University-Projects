package galeria.obra;

/**
 * La clase Escultura representa una obra de arte escultórica en la galería.
 * Hereda de la clase Fisica y agrega el atributo material.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Escultura extends Fisica {
	private static final long serialVersionUID = 1L;
	private String material;

	/**
	 * Crea una nueva instancia de la clase Escultura con los valores especificados.
	 * 
	 * @param nombre         el nombre de la escultura
	 * @param autor          el autor de la escultura
	 * @param ano            el año de creación de la escultura
	 * @param descripcion    la descripción de la escultura
	 * @param seguroCuantia  la cuantía del seguro de la escultura
	 * @param seguroPoliza   la póliza del seguro de la escultura
	 * @param enPropiedad    indica si la escultura está en propiedad de la galería
	 * @param temperaturaMin la temperatura mínima recomendada para la escultura
	 * @param temperaturaMax la temperatura máxima recomendada para la escultura
	 * @param humedadMin     la humedad mínima recomendada para la escultura
	 * @param humedadMax     la humedad máxima recomendada para la escultura
	 * @param requiereTemp   indica si la escultura requiere control de temperatura
	 * @param requiereHum    indica si la escultura requiere control de humedad
	 * @param ancho          el ancho de la escultura
	 * @param alto           el alto de la escultura
	 * @param largo          el largo de la escultura
	 * @param material       el material de la escultura
	 */
	public Escultura(String nombre, String autor, int ano, String descripcion, double seguroCuantia,
			String seguroPoliza, boolean enPropiedad, double temperaturaMin, double temperaturaMax,
			double humedadMin, double humedadMax, boolean requiereTemp, boolean requiereHum, double ancho, double alto,
			double largo, String material) {
		super(nombre, autor, ano, descripcion, seguroCuantia, seguroPoliza, enPropiedad, temperaturaMin,
				temperaturaMax, humedadMin, humedadMax, requiereTemp, requiereHum, ancho, alto, largo);
		this.material = material;
	}

	/**
	 * Crea una nueva instancia de la clase Escultura con los valores especificados.
	 * 
	 * @param ancho          el ancho de la escultura
	 * @param alto           el alto de la escultura
	 * @param largo          el largo de la escultura
	 * @param temperaturaMin la temperatura mínima recomendada para la escultura
	 * @param temperaturaMax la temperatura máxima recomendada para la escultura
	 * @param humedadMin     la humedad mínima recomendada para la escultura
	 * @param humedadMax     la humedad máxima recomendada para la escultura
	 * @param requiereTemp   indica si la escultura requiere control de temperatura
	 * @param requiereHum    indica si la escultura requiere control de humedad
	 * 
	 * @throws IllegalArgumentException si se proporcionan valores inválidos para
	 *                                  los parámetros
	 */
	public Escultura(double ancho, double alto, double largo, double temperaturaMin,
			double temperaturaMax, double humedadMin, double humedadMax, boolean requiereTemp, boolean requiereHum) {
		super(ancho, alto, largo, temperaturaMin, temperaturaMax, humedadMin, humedadMax, requiereTemp, requiereHum);
	}

	/**
	 * Crea una nueva instancia de la clase Escultura con el nombre especificado.
	 * 
	 * @param nombre el nombre de la escultura
	 */
	public Escultura(String nombre) {
		super(nombre);
	}

	/**
	 * Crea una nueva instancia de la clase Escultura con el nombre y las
	 * dimensiones especificados.
	 * 
	 * @param nombre el nombre de la escultura
	 * @param ancho  el ancho de la escultura
	 * @param alto   el alto de la escultura
	 * @param largo  el largo de la escultura
	 */
	public Escultura(String nombre, double ancho, double alto, double largo) {
		super(nombre, ancho, alto, largo);
	}

	/**
	 * Obtiene el tipo de la escultura.
	 * 
	 * @return el tipo de la escultura
	 */
	public String getTipo() {
		return "Escultura";
	}

	/**
	 * Devuelve una representación en forma de cadena de la escultura.
	 * 
	 * @return una cadena que representa la escultura
	 */
	@Override
	public String toString() {
		return super.toString() + "Material: " + material + "\n";
	}
}