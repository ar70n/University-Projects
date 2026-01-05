package galeria.obra;

import galeria.sala.Sala;

/**
 * Clase que representa una obra audiovisual.
 * Extiende de la clase Obra.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Audiovisual extends Obra {

	private int duracion; // Duración en minutos
	private String idioma; // Idioma de la obra
	private static final long serialVersionUID = 1L;

	/**
	 * Constructor de la clase Audiovisual.
	 * 
	 * @param nombre        Nombre de la obra.
	 * @param autor         Autor de la obra.
	 * @param ano           Año de creación de la obra.
	 * @param descripcion   Descripción de la obra.
	 * @param seguroCuantia Cuantía del seguro de la obra.
	 * @param seguroPoliza  Póliza del seguro de la obra.
	 * @param enPropiedad   Indica si la obra está en propiedad.
	 * @param duracion      Duración en minutos de la obra audiovisual.
	 * @param idioma        Idioma de la obra audiovisual.
	 */
	public Audiovisual(String nombre, String autor, int ano, String descripcion, double seguroCuantia,
			String seguroPoliza, boolean enPropiedad, int duracion, String idioma) {
		super(nombre, autor, ano, descripcion, seguroCuantia, seguroPoliza, enPropiedad);
		this.duracion = duracion;
		this.idioma = idioma;
	}

	/**
	 * Constructor de la clase Audiovisual.
	 * 
	 * @param nombre        Nombre de la obra.
	 * @param autor         Autor de la obra.
	 * @param ano           Año de creación de la obra.
	 * @param descripcion   Descripción de la obra.
	 * @param seguroCuantia Cuantía del seguro de la obra.
	 * @param seguroPoliza  Póliza del seguro de la obra.
	 * @param enPropiedad   Indica si la obra está en propiedad.
	 */
	public Audiovisual(String nombre, String autor, int ano, String descripcion, double seguroCuantia,
			String seguroPoliza, boolean enPropiedad) {
		super(nombre, autor, ano, descripcion, seguroCuantia, seguroPoliza, enPropiedad);
	}

	/**
	 * Constructor de la clase Audiovisual.
	 * 
	 * @param nobmre Nombre de la obra.
	 */
	public Audiovisual(String nobmre) {
		super(nobmre);
	}

	/**
	 * Constructor de la clase Audiovisual utilizado para pruebas.
	 * No se debe utilizar para otra cosa.
	 * 
	 * @param estado Estado de la obra.
	 */
	public Audiovisual(EstadoObra estado) {
		this.estado = estado;
	}

	/**
	 * Constructor por defecto de la clase Audiovisual.
	 */
	public Audiovisual() {
		super();
	}

	/**
	 * Obtiene el tipo de la obra.
	 * 
	 * @return El tipo de la obra.
	 */
	public String getTipo() {
		return "Audiovisual";
	}

	/**
	 * Verifica si la humedad está en rango para la obra audiovisual.
	 * 
	 * @param humedad Humedad a verificar.
	 * @return true si la humedad está en rango, false en caso contrario.
	 */
	public boolean humedadEnRango(double humedad) {
		return true;
	}

	/**
	 * Verifica si la temperatura está en rango para la obra audiovisual.
	 * 
	 * @param temperatura Temperatura a verificar.
	 * @return true si la temperatura está en rango, false en caso contrario.
	 */
	public boolean temperaturaEnRango(double temperatura) {
		return true;
	}

	/**
	 * Expone la obra audiovisual en una sala.
	 * 
	 * @param sala Sala en la que se va a exponer la obra.
	 * @throws InvalidStateTransition Si ocurre una transición de estado inválida.
	 * @throws InvalidConditions      Si las condiciones para exponer la obra no son
	 *                                válidas.
	 */
	@Override
	public void exponerEn(Sala sala) throws InvalidStateTransition, InvalidConditions {
		if (sala.getEnchufes() > 0) { // El método getEnchufes tiene que devolver solo los enchufes libres no todos
										// los enchufes de la sala
			super.exponerEn(sala);
		} else {
			throw new InvalidEnchufesConditions();
		}
	}

	/**
	 * Devuelve una representación en forma de cadena de la obra audiovisual.
	 * 
	 * @return Representación en forma de cadena de la obra audiovisual.
	 */
	public String toString() {
		return super.toString() + "Duracion: " + duracion + " minutos\nIdioma: " + idioma + "\n";
	}
}