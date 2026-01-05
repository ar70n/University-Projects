package galeria.obra;

import galeria.sala.*;
import galeria.Vector3;

import java.io.Serializable;

/**
 * Clase abstracta que representa una obra de arte.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public abstract class Obra implements Serializable {
	protected String nombre;
	protected String autor;
	protected int fecha;
	protected String descripcion;
	protected double seguroCuantia;
	protected String seguroPoliza;
	protected boolean enPropiedad;
	protected EstadoObra estado = EstadoObra.ALMACEN;
	protected Sala sala = null;
	private static final long serialVersionUID = 1L;

	// Constructores

	/**
	 * Constructor de la clase Obra.
	 * 
	 * @param nombre        El nombre de la obra.
	 * @param autor         El autor de la obra.
	 * @param fecha         La fecha de creación de la obra.
	 * @param descripcion   La descripción de la obra.
	 * @param seguroCuantia La cuantía del seguro de la obra.
	 * @param seguroPoliza  La póliza del seguro de la obra.
	 * @param enPropiedad   Indica si la obra está en propiedad.
	 */
	public Obra(String nombre, String autor, int fecha, String descripcion, double seguroCuantia, String seguroPoliza,
			boolean enPropiedad) {
		this.nombre = nombre;
		this.autor = autor;
		this.fecha = fecha;
		this.descripcion = descripcion;
		this.seguroCuantia = seguroCuantia;
		this.seguroPoliza = seguroPoliza;
		this.enPropiedad = enPropiedad;
		this.estado = EstadoObra.ALMACEN;
	}

	/**
	 * Constructor vacío de la clase Obra.
	 * Este constructor se utiliza para pruebas y no debe ser eliminado.
	 */
	public Obra() {
	}

	/**
	 * Constructor de la clase Obra que recibe solo el nombre de la obra.
	 * 
	 * @param nombre El nombre de la obra.
	 */
	public Obra(String nombre) {
		this.nombre = nombre;
	}

	// Getters

	/**
	 * Obtiene el nombre de la obra.
	 * 
	 * @return El nombre de la obra.
	 */
	public String getNombre() {
		return this.nombre;
	}

	/**
	 * Verifica si la obra está en propiedad.
	 * 
	 * @return true si la obra está en propiedad, false de lo contrario.
	 */
	public boolean getPropiedad() {
		return this.enPropiedad;
	}

	/**
	 * Obtiene el estado de la obra.
	 * 
	 * @return El estado de la obra.
	 */
	public EstadoObra getEstado() {
		return this.estado;
	}

	/**
	 * Obtiene la sala en la que se encuentra la obra.
	 * 
	 * @return La sala en la que se encuentra la obra.
	 */
	public Sala getSala() {
		return sala;
	}

	/**
	 * Obtiene el tipo de la obra.
	 * 
	 * @return El tipo de la obra.
	 */
	public abstract String getTipo();

	/**
	 * Obtiene las dimensiones de la obra.
	 * 
	 * @return Las dimensiones de la obra.
	 */
	public Vector3 getDimensiones() {
		return new Vector3(0, 0, 0);
	}

	/**
	 * Obtiene el autor de la obra.
	 * 
	 * @return El autor de la obra.
	 */
	public String getAutor() {
		return autor;
	}

	/**
	 * Obtiene la fecha de creación de la obra.
	 * 
	 * @return La fecha de creación de la obra.
	 */
	public int getFecha() {
		return fecha;
	}

	/**
	 * Obtiene la descripción de la obra.
	 * 
	 * @return La descripción de la obra.
	 */
	public String getDescripcion() {
		return descripcion;
	}

	/**
	 * Obtiene la póliza del seguro de la obra.
	 * 
	 * @return La póliza del seguro de la obra.
	 */
	public double getSeguroCuantia() {
		return seguroCuantia;
	}

	public String getSeguroPoliza() {
		return seguroPoliza;
	}

	// Setters

	/**
	 * Establece el nombre de la obra.
	 * 
	 * @param nombre El nuevo nombre de la obra.
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	/**
	 * Establece el autor de la obra.
	 * 
	 * @param autor El nuevo autor de la obra.
	 */
	public void setAutor(String autor) {
		this.autor = autor;
	}

	/**
	 * Establece la sala en la que se encuentra la obra.
	 * 
	 * @param sala La nueva sala en la que se encuentra la obra.
	 */
	public void setSala(Sala sala) {
		this.sala = sala;
	}

	/**
	 * Este método solo existe para pruebas y no debe ser utilizado.
	 * Se debe utilizar el método cambiarEstado().
	 * 
	 * @param estado El nuevo estado de la obra.
	 */
	protected void setEstado(EstadoObra estado) {
		this.estado = estado;
	}

	// Metodos complejos

	/**
	 * Implementa un cambio de estado elemental sin tener en cuenta condiciones
	 * externas como exposiciones o salas.
	 * 
	 * @param estado El nuevo estado de la obra.
	 * @throws InvalidStateTransition Si la transición de estados no es válida.
	 */
	protected void cambiarEstado(EstadoObra estado) throws InvalidStateTransition {
		if (this.estado == EstadoObra.RETIRADA) {
			throw new InvalidStateTransition(this.estado, estado);
		} else if (this.estado != EstadoObra.ALMACEN && estado != EstadoObra.ALMACEN) {
			throw new InvalidStateTransition(this.estado, estado);
		} else {
			// Solo se cambia de estado si la transicion esta bien definida
			this.estado = estado;
		}
	}

	/**
	 * Este es el método que se debe llamar desde el gestor para exponer una obra en
	 * una sala.
	 * 
	 * @param s La sala en la que se expondrá la obra.
	 * @throws InvalidStateTransition Si la transición de estados no es válida.
	 * @throws InvalidConditions      Si las condiciones de exposición no son
	 *                                válidas.
	 */
	public void exponerEn(Sala s) throws InvalidStateTransition, InvalidConditions {
		cambiarEstado(EstadoObra.EXPOSICION);
		this.sala = s;
	}

	/**
	 * Este método elimina la obra de la sala en la que se encuentra.
	 * 
	 * @throws StateExceptions Si el estado de la obra no es válido para realizar
	 *                         esta acción.
	 */
	public void removeFromSala() throws StateExceptions {
		if (this.estado != EstadoObra.EXPOSICION) {
			throw new ExpectedDifferentState(EstadoObra.EXPOSICION, this.estado);
		}
		if (!this.sala.removeObra(this)) {
			throw new ExpoDeclinedTransition(this.estado, EstadoObra.ALMACEN); // Exposicion rechazo la solicitud de
																				// reitrar la obra
		}
		this.sala = null;
		this.cambiarEstado(EstadoObra.ALMACEN);
	}

	/**
	 * Este método se utiliza para restaurar una obra, ya sea que esté en una
	 * exposición o no.
	 * 
	 * @throws StateExceptions Si el estado de la obra no es válido para realizar
	 *                         esta acción.
	 */
	public void restaurar() throws StateExceptions {
		if (this.estado == EstadoObra.EXPOSICION) {
			if (this.sala.restaurarObra(this)) {
				this.cambiarEstado(EstadoObra.ALMACEN);
			} else {
				throw new ExpoDeclinedTransition(this.estado, EstadoObra.ALMACEN);
			}
		}
		this.cambiarEstado(EstadoObra.RESTAURACION);
	}

	/**
	 * Este método no se debe utilizar para retirar una obra de una exposición o
	 * sala.
	 * Para eso, se debe utilizar el método removeFromSala().
	 * También se plantea la posibilidad de llamar al método removeFromSala() desde
	 * aquí.
	 * 
	 * @throws StateExceptions Si el estado de la obra no es válido para realizar
	 *                         esta acción.
	 */
	public void enviarAlmacen() throws StateExceptions {
		if (this.estado == EstadoObra.EXPOSICION) {
			this.removeFromSala();
		} else {
			this.cambiarEstado(EstadoObra.ALMACEN);
		}
	}

	/**
	 * Este método se utiliza para prestar una obra.
	 * 
	 * @throws StateExceptions Si el estado de la obra no es válido para realizar
	 *                         esta acción.
	 */
	public void prestar() throws StateExceptions {
		if (this.estado == EstadoObra.EXPOSICION) {
			this.removeFromSala();
		}
		this.cambiarEstado(EstadoObra.PRESTAMO);
	}

	/**
	 * Este método se utiliza para retirar una obra.
	 * 
	 * @throws StateExceptions Si el estado de la obra no es válido para realizar
	 *                         esta acción.
	 */
	public void retirar() throws StateExceptions {
		if (this.estado == EstadoObra.EXPOSICION) {
			this.removeFromSala();
		}
		this.cambiarEstado(EstadoObra.RETIRADA);
	}

	// No me gustan estos metodos porque no tienen sentido para audiovisual. Moroño
	public abstract boolean humedadEnRango(double humedad);

	public abstract boolean temperaturaEnRango(double humedad);

	@Override
	public String toString() {
		return "Nombre: " + nombre + "\nAutor: " + autor + "\nFecha: " + fecha + "\nDescripcion: " + descripcion
				+ "\nSeguro cuantia: " + seguroCuantia + "\nSeguro poliza: " + seguroPoliza + "\nEn propiedad: "
				+ enPropiedad + "\nEstado: " + estado + "\nSala: " + sala;
	}
}