package galeria.sala;

/**
 * Esta clase representa una sala raíz en una galería.
 * Extiende la clase Sala e incluye atributos adicionales como la temperatura,
 * humedad y si es regulable.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class SalaRaiz extends Sala {
	private static final long serialVersionUID = 1L;
	private boolean regulable;
	private double temperatura;
	private double humedad;

	/**
	 * Constructor de la clase SalaRaiz.
	 * 
	 * @param ancho       el ancho de la sala
	 * @param alto        el alto de la sala
	 * @param largo       el largo de la sala
	 * @param enchufes    el número de enchufes en la sala
	 * @param aforo       el aforo máximo de la sala
	 * @param regulable   indica si la sala es regulable
	 * @param temperatura la temperatura de la sala
	 * @param humedad     la humedad de la sala
	 */
	public SalaRaiz(double ancho, double alto, double largo, int enchufes, int aforo, boolean regulable,
			double temperatura, double humedad) {
		super(ancho, alto, largo, enchufes, aforo);
		this.regulable = regulable;
		this.temperatura = temperatura;
		this.humedad = humedad;
	}

	/**
	 * Constructor para pruebas de obra/sala.
	 * 
	 * @param ancho       el ancho de la sala
	 * @param alto        el alto de la sala
	 * @param largo       el largo de la sala
	 * @param temperatura la temperatura de la sala
	 * @param humedad     la humedad de la sala
	 * @param regulable   indica si la sala es regulable
	 */
	public SalaRaiz(double ancho, double alto, double largo, double temperatura, double humedad, boolean regulable) {
		super(ancho, alto, largo);
		this.temperatura = temperatura;
		this.humedad = humedad;
		this.regulable = regulable;
	}

	/**
	 * Constructor por defecto de la clase SalaRaiz.
	 */
	public SalaRaiz(double ancho, double alto, double largo) {
		super(ancho, alto, largo);
	}

	/**
	 * Constructor por defecto de la clase SalaRaiz.
	 */
	public SalaRaiz() {
	}

	// Getters

	/**
	 * Obtiene la temperatura de la sala.
	 * 
	 * @return la temperatura de la sala
	 */
	public double getTemperatura() {
		return temperatura;
	}

	/**
	 * Obtiene la humedad de la sala.
	 * 
	 * @return la humedad de la sala
	 */
	public double getHumedad() {
		return humedad;
	}

	/**
	 * Indica si la sala es regulable.
	 * 
	 * @return true si la sala es regulable, false de lo contrario
	 */
	public boolean getRegulable() {
		return regulable;
	}

	/**
	 * Establece si la sala es regulable.
	 * 
	 * @param regulable true si la sala es regulable, false de lo contrario
	 */
	public void setRegulable(boolean regulable) {
		this.regulable = regulable;
	}

	/**
	 * Establece la temperatura de la sala.
	 * 
	 * @param temperatura la temperatura de la sala
	 */
	public void setTemperatura(double temperatura) {
		this.temperatura = temperatura;
	}

	/**
	 * Establece la humedad de la sala.
	 * 
	 * @param humedad la humedad de la sala
	 */
	public void setHumedad(double humedad) {
		this.humedad = humedad;
	}




}