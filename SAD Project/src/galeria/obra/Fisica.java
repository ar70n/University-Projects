package galeria.obra;

import galeria.sala.*;
import galeria.*;

/**
 * Clase abstracta que representa una obra física en la galería.
 * Extiende de la clase Obra.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public abstract class Fisica extends Obra {
	private static final long serialVersionUID = 1L;
	protected double temperaturaMin;
	protected double temperaturaMax;
	protected double humedadMin;
	protected double humedadMax;
	protected boolean requiereTemp;
	protected boolean requiereHum;
	protected Vector3 dimensiones = new Vector3();

	/**
	 * Constructor de la clase Fisica.
	 * 
	 * @param nombre         El nombre de la obra.
	 * @param autor          El autor de la obra.
	 * @param fecha          La fecha de la obra.
	 * @param descripcion    La descripción de la obra.
	 * @param seguroCuantia  La cuantía del seguro de la obra.
	 * @param seguroPoliza   La póliza del seguro de la obra.
	 * @param enPropiedad    Indica si la obra está en propiedad.
	 * @param temperaturaMin La temperatura mínima requerida para la obra.
	 * @param temperaturaMax La temperatura máxima requerida para la obra.
	 * @param humedadMin     La humedad mínima requerida para la obra.
	 * @param humedadMax     La humedad máxima requerida para la obra.
	 * @param requiereTemp   Indica si la obra requiere control de temperatura.
	 * @param requiereHum    Indica si la obra requiere control de humedad.
	 * @param ancho          El ancho de la obra.
	 * @param alto           El alto de la obra.
	 * @param largo          El largo de la obra.
	 */
	public Fisica(String nombre, String autor, int fecha, String descripcion, double seguroCuantia,
			String seguroPoliza, boolean enPropiedad, double temperaturaMin, double temperaturaMax,
			double humedadMin, double humedadMax, boolean requiereTemp, boolean requiereHum, double ancho, double alto,
			double largo) {
		super(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza, enPropiedad);
		this.temperaturaMin = temperaturaMin;
		this.temperaturaMax = temperaturaMax;
		this.humedadMin = humedadMin;
		this.humedadMax = humedadMax;
		this.requiereTemp = requiereTemp;
		this.requiereHum = requiereHum;
		this.dimensiones.setDimensiones(ancho, alto, largo);
	}

	/**
	 * Constructor para los test.
	 * 
	 * @param ancho          El ancho de la obra.
	 * @param alto           El alto de la obra.
	 * @param largo          El largo de la obra.
	 * @param temperaturaMin La temperatura mínima requerida para la obra.
	 * @param temperaturaMax La temperatura máxima requerida para la obra.
	 * @param humedadMin     La humedad mínima requerida para la obra.
	 * @param humedadMax     La humedad máxima requerida para la obra.
	 * @param requiereTemp   Indica si la obra requiere control de temperatura.
	 * @param requiereHum    Indica si la obra requiere control de humedad.
	 * @throws IllegalArgumentException Si se proporcionan argumentos inválidos.
	 */
	public Fisica(double ancho, double alto, double largo, double temperaturaMin, double temperaturaMax,
			double humedadMin, double humedadMax, boolean requiereTemp, boolean requiereHum) {
		super();
		this.dimensiones.setDimensiones(ancho, alto, largo);
		this.requiereHum = true;
		this.temperaturaMin = temperaturaMin;
		this.temperaturaMax = temperaturaMax;
		this.humedadMin = humedadMin;
		this.humedadMax = humedadMax;
		this.requiereTemp = requiereTemp;
		this.requiereHum = requiereHum;
	}

	/**
	 * Constructor con nombre
	 * 
	 * @param nombre El nombre de la obra.
	 */
	public Fisica(String nombre) {
		super(nombre);
	}

	/**
	 * Constructor con nombre y dimensiones.
	 * 
	 * @param nombre El nombre de la obra.
	 * @param ancho  El ancho de la obra.
	 * @param alto   El alto de la obra.
	 * @param largo  El largo de la obra.
	 */
	public Fisica(String nombre, double ancho, double alto, double largo) {
		super(nombre);
		this.dimensiones.setDimensiones(ancho, alto, largo);
	}

	/**
	 * Obtiene el tipo de la obra física.
	 * 
	 * @return El tipo de la obra física.
	 */
	public abstract String getTipo();

	/**
	 * Obtiene las dimensiones de la obra física.
	 * 
	 * @return Las dimensiones de la obra física.
	 */
	@Override
	public Vector3 getDimensiones() {
		return this.dimensiones;
	}

	/**
	 * Obtiene la temperatura mínima requerida para la obra.
	 * 
	 * @return La temperatura mínima requerida para la obra.
	 */
	public double getTemperaturaMin() {
		return temperaturaMin;
	}

	/**
	 * Obtiene la temperatura máxima requerida para la obra.
	 * 
	 * @return La temperatura máxima requerida para la obra.
	 */
	public double getTemperaturaMax() {
		return temperaturaMax;
	}

	/**
	 * Obtiene la humedad mínima requerida para la obra.
	 * 
	 * @return La humedad mínima requerida para la obra.
	 */
	public double getHumedadMin() {
		return humedadMin;
	}

	/**
	 * Obtiene la humedad máxima requerida para la obra.
	 * 
	 * @return La humedad máxima requerida para la obra.
	 */
	public double getHumedadMax() {
		return humedadMax;
	}

	/**
	 * Obtiene si una obra rquiere temperatura.
	 * @return true si requiere temperatura
	 */
	public boolean isRequiereTemp() {
		return requiereTemp;
	}

	/**
	 * Obtiene si una obra rquiere humedad.
	 * @return true si requiere humedad
	 */
	public boolean isRequiereHum() {
		return requiereHum;
	}

	/**
	 * Comprueba si la humedad está dentro del rango requerido.
	 * 
	 * @param humedad La humedad a comprobar.
	 * @return true si la humedad está dentro del rango, false de lo contrario.
	 */
	public boolean humedadEnRango(double humedad) {
		return humedad >= this.humedadMin && humedad <= this.humedadMax;
	}

	/**
	 * Comprueba si la temperatura está dentro del rango requerido.
	 * 
	 * @param temperatura La temperatura a comprobar.
	 * @return true si la temperatura está dentro del rango, false de lo contrario.
	 */
	public boolean temperaturaEnRango(double temperatura) {
		return temperatura >= this.temperaturaMin && temperatura <= this.temperaturaMax;
	}

	/**
	 * Comprueba si la obra física cabe en una sala.
	 * 
	 * @param sala La sala en la que se quiere comprobar si cabe la obra física.
	 * @return true si la obra física cabe en la sala, false de lo contrario.
	 */
	public boolean cabeEn(Sala sala) {
		if (this.getDimensiones().getX() < sala.getDimensiones().getX()
				&& this.getDimensiones().getY() < sala.getDimensiones().getY()
				&& this.getDimensiones().getZ() < sala.getDimensiones().getZ()
				&& this.getDimensiones().volumen() < sala.getDimensiones().volumen()) {
			return true;
		}
		return false;
	}

	/**
	 * Expone la obra física en una sala.
	 * 
	 * @param s La sala en la que se quiere exponer la obra física.
	 * @throws InvalidStateTransition Si se produce una transición de estado
	 *                                inválida.
	 * @throws InvalidConditions      Si las condiciones requeridas no se cumplen.
	 */
	@Override
	public void exponerEn(Sala s) throws InvalidStateTransition, InvalidConditions {
		if (this.requiereHum && !humedadEnRango(s.getHumedad())) {
			throw new InvalidHumidityConditions(s.getHumedad(), this.humedadMin, this.humedadMax);
		}
		if (this.requiereTemp && !temperaturaEnRango(s.getTemperatura())) {
			throw new InvalidTemperatureConditions(s.getTemperatura(), this.temperaturaMin, this.temperaturaMax);
		}
		if (!this.cabeEn(s)) {
			throw new InvalidDimensionConditions(s.getDimensiones(), this.dimensiones);
		}

		super.exponerEn(s);
	}

	/**
	 * Obtiene una representación en forma de cadena de la obra física.
	 * 
	 * @return La representación en forma de cadena de la obra física.
	 */
	@Override
	public String toString() {
		return super.toString() + "Dimensiones: " + this.dimensiones.toString() + "\n";
	}
}