package galeria.exposicion; //Faltan terminar funciones

import galeria.sala.*;
import galeria.obra.*;
import descuento.*;
import entrada.*;
import sistema.Sistema;
import java.time.LocalDateTime;
import java.util.List;
import java.util.ArrayList;
import java.time.temporal.ChronoUnit;
import usuario.*;

import java.io.Serializable;

/**
 * Clase abstracta que representa una exposición.
 * Esta clase define los atributos y métodos comunes a todas las exposiciones.
 * Las exposiciones concretas deben extender esta clase y proporcionar
 * implementaciones para los métodos abstractos.
 *
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public abstract class Exposicion implements Serializable {
	/**
	 * Nombre de la exposición.
	 */
	private String nombre;

	/**
	 * Descripción de la exposición.
	 */
	private String descripcion;

	/**
	 * Fecha y hora de apertura de la exposición.
	 */
	private LocalDateTime apertura;

	/**
	 * Precio de la entrada a la exposición.
	 */
	private double precio = 0.0;

	/**
	 * Estado de la exposición.
	 */
	protected EstadoExp estado;

	/**
	 * Número de versión para la serialización.
	 */
	private static final long serialVersionUID = 1L;

	// referencias
	protected List<Visita> visitas = new ArrayList<Visita>();
	private List<Descuento> descuentos = new ArrayList<Descuento>();
	protected List<Sala> salas = new ArrayList<Sala>();

	// Constructores

	/**
	 * Constructor de la clase Exposicion.
	 *
	 * @param nombre      El nombre de la exposición.
	 * @param descripcion La descripción de la exposición.
	 * @param apertura    La fecha y hora de apertura de la exposición.
	 * @throws IllegalArgumentException Si alguno de los campos es nulo.
	 */
	public Exposicion(String nombre, String descripcion, LocalDateTime apertura) throws IllegalArgumentException {
		if (nombre == null || descripcion == null || apertura == null) {
			throw new IllegalArgumentException("Los campos no pueden ser nulos");
		}
		this.nombre = nombre;
		this.descripcion = descripcion;
		this.apertura = apertura;
		this.estado = EstadoExp.ENCREACION;
	}

	/**
	 * Constructor vacío utilizado para pruebas.
	 */
	public Exposicion() {
	}

	/**
	 * Obtiene el aforo total de la exposición.
	 *
	 * @return El aforo total de la exposición.
	 */
	public int getAforo() {
		int aforo = 0;
		try {
			for (Sala s : salas) {
				aforo += s.getAforo();
			}
		} catch (Exception e) {
			System.out.println("Error en getAforo: ");
		}

		return aforo;
	}

	/**
	 * Obtiene todas las obras de arte de la exposición.
	 *
	 * @return Una lista con todas las obras de arte de la exposición.
	 */
	public List<Obra> getObras() {
		List<Obra> obras = new ArrayList<Obra>();
		System.out.println("Salas: " + salas.size());

		for (Sala s : salas) {
			obras.addAll(s.getObras());
			System.out.println("Obras: " + s.getObras());
		}

		return obras;
	}

	/**
	 * Publica la exposición.
	 *
	 * @throws IllegalArgumentException Si la exposición no está en estado de
	 *                                  creación, no tiene salas o el precio de la
	 *                                  entrada es negativo.
	 */
	public void publicar() throws IllegalArgumentException {
		EstadoExp estadoActual = getEstado();

		if (estadoActual != EstadoExp.ENCREACION) {
			System.out.println("Solo se puede publicar una exposición en creación");
			throw new IllegalArgumentException("Solo se puede publicar una exposición en creación");
		}
		if (salas.size() <= 0) {
			System.out.println("La exposición debe tener al menos una sala");
			throw new IllegalArgumentException("La exposición debe tener al menos una sala");
		}
		if (precio < 0) {
			System.out.println("El precio de la entrada debe ser 0 o mayor");
			throw new IllegalArgumentException("El precio de la entrada debe ser 0 o mayor");
		}

		estado = EstadoExp.PUBLICADA;
		for (UsuarioRegistrado u : Sistema.getUsuarios()) {
			if (u.getTipoUsuario().equals("Cliente")) {
				Sistema.enviarMensaje("Nueva Exposición",
						"Se ha publicado la exposición " + nombre + " con fecha de apertura "
								+ apertura + " y precio de entrada " + precio + "€",
						u);
			}

			for (Descuento descuento : descuentos) {
				Sistema.enviarMensaje("Nuevo Descuento",
						"Se ha añadido a la exposición " + nombre + " el descuento " + descuento.getMensaje(), u);
			}
		}
	}

	/**
	 * Elimina la exposición.
	 *
	 * @throws IllegalArgumentException Si la exposición no está en estado de
	 *                                  creación, o si está a menos de 7 días de su
	 *                                  apertura.
	 */
	public void eliminarExp() throws IllegalArgumentException {
		if (estado == EstadoExp.ENCREACION) {
			Sistema.eliminarExp(this);
		} else if (estado == EstadoExp.PUBLICADA) {
			if (ChronoUnit.DAYS.between(LocalDateTime.now(), apertura) > 7) {
				devolverDinero(this);
				// eliminar de estadísticas
				Sistema.eliminarExp(this);
			} else {
				throw new IllegalArgumentException(
						"No se puede eliminar la exposición a menos de 7 días de su apertura");
			}
		} else {
			throw new IllegalArgumentException("No se puede eliminar una exposición que ya ha comenzado o terminado");
		}
	}

	/**
	 * Devuelve el dinero de las entradas vendidas para la exposición.
	 *
	 * @param ex La exposición de la que se devolverá el dinero.
	 */
	private void devolverDinero(Exposicion ex) {
		for (Visita v : ex.visitas) {
			for (Entrada en : v.getEntradas()) {
				if (en.getCardNumber() == null || en.getCliente() == null) {
					continue;
				}
				Cliente cliente = en.getCliente();
				cliente.pagar(precio, en.getCardNumber());
			}
		}
	}

	/**
	 * Añade una sala a la exposición.
	 *
	 * @param s La sala a añadir.
	 * @throws IllegalArgumentException Si la sala no es una sala hija.
	 */
	public void addSala(Sala s) throws IllegalArgumentException {
		if (s.getSubsalas().size() > 0) {
			throw new IllegalArgumentException("Solo puedes salas hija");
		}

		try {
			s.setExposicion(this);
		} catch (Exception e) {
			throw new IllegalArgumentException("La sala no es hoja");
		}

		salas.add(s);
	}

	/**
	 * Obtiene la lista de visitas de la exposición.
	 *
	 * @return La lista de visitas de la exposición.
	 */
	public List<Visita> getVisitas() {
		return visitas;
	}

	/**
	 * Añade una visita a la exposición.
	 *
	 * @param v La visita a añadir.
	 */
	public void addVisita(Visita v) {
		visitas.add(v);
	}

	/**
	 * Añade un descuento a la exposición.
	 *
	 * @param d El descuento a añadir.
	 */
	public void addDescuento(Descuento d) {
		descuentos.add(d);
	}


	/**
	 * Obtiene el precio de la entrada a la exposición.
	 *
	 * @return El precio de la entrada a la exposición.
	 */
	public double getPrecioEntrada() {
		return precio;
	}

	/**
	 * Obtiene la lista de descuentos de la exposición.
	 *
	 * @return La lista de descuentos de la exposición.
	 */
	public List<Descuento> getDescuentos() {
		return descuentos;
	}

	/**
	 * Obtiene la fecha y hora de inicio de la exposición.
	 *
	 * @return La fecha y hora de inicio de la exposición.
	 */
	public LocalDateTime getFechaInicio() {
		return apertura;
	}

	/**
	 * Obtiene el estado actual de la exposición.
	 *
	 * @return El estado actual de la exposición.
	 */
	public EstadoExp getEstado() {
		if (estado == EstadoExp.PUBLICADA) {
			if (LocalDateTime.now().isAfter(apertura) || LocalDateTime.now().isEqual(apertura)) {
				estado = EstadoExp.COMENZADA;
			}
		}

		return estado;
	}

	// Setters

	/**
	 * Establece el nombre de la exposición.
	 *
	 * @param nombre El nuevo nombre de la exposición.
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	/**
	 * Establece el precio de la entrada a la exposición.
	 *
	 * @param precio El nuevo precio de la entrada.
	 * @throws IllegalArgumentException Si la exposición no está en estado de
	 *                                  creación.
	 */
	public void setPrecioEntrada(double precio) throws IllegalArgumentException {
		if (this.getEstado() != EstadoExp.ENCREACION) {
			throw new IllegalArgumentException("No puedes cambiar el precio si la exposicion no esta EnCreación");
		}
		this.precio = precio;
	}

	/**
	 * Establece la lista de descuentos de la exposición.
	 *
	 * @param descuentos La nueva lista de descuentos.
	 */
	public void setDescuentos(List<Descuento> descuentos) {
		this.descuentos = descuentos;
	}

	/**
	 * Establece la fecha y hora de apertura de la exposición.
	 *
	 * @param apertura La nueva fecha y hora de apertura.
	 */
	public void setApertura(LocalDateTime apertura) {
		this.apertura = apertura;
	}

	/**
	 * Establece el estado de la exposición.
	 *
	 * @param estado El nuevo estado de la exposición.
	 */
	public void setEstado(EstadoExp estado) {
		this.estado = estado;
	}

	/**
	 * Obtiene la descripción de la exposición.
	 *
	 * @return La descripción de la exposición.
	 */
	public String getDescripcion() {
		return descripcion;
	}

	/**
	 * Obtiene el nombre de la exposición.
	 *
	 * @return El nombre de la exposición.
	 */
	public String getNombre() {
		return nombre;
	}

	/**
	 * Verifica si la exposición es permanente.
	 *
	 * @return true si la exposición es permanente, false de lo contrario.
	 */
	public abstract boolean esPermanente();

	/**
	 * Verifica si se pueden añadir obras a la exposición.
	 *
	 * @param propiedad Indica si las obras son propiedad de la exposición.
	 * @return true si se pueden añadir obras, false de lo contrario.
	 */
	public abstract boolean addObraCheck(boolean propiedad);

	/**
	 * Verifica si se pueden quitar obras de la exposición.
	 *
	 * @return true si se pueden quitar obras, false de lo contrario.
	 */
	public abstract boolean removeObraCheck();

	/**
	 * Verifica si se puede restaurar una obra de la exposición.
	 *
	 * @return true si se puede restaurar la obra, false de lo contrario.
	 */
	public abstract boolean restaurarObraCheck();

	/**
	 * Devuelve una representación en cadena de la exposición.
	 *
	 * @return Una representación en cadena de la exposición.
	 */
	@Override
	public String toString() {
		return "Exposicion{" + "nombre='" + nombre + '\'' + ", descripción='" + descripcion + '\'' + ", apertura="
				+ apertura + ", precio=" + precio + ", estado=" + estado + ", visitas=" + visitas + ", descuentos="
				+ descuentos + ", salas=" + salas + '}';
	}
}