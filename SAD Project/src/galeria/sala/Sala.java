
package galeria.sala;

import galeria.*;
import galeria.exposicion.*;
import galeria.obra.*;

import java.util.List;
import java.util.ArrayList;
import java.io.Serializable;

/**
 * Clase abstracta que representa una sala en una galería.
 * Esta clase proporciona métodos y atributos comunes a todas las salas.
 * Las salas pueden contener obras de arte y pueden ser divididas en subsalas.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public abstract class Sala implements Serializable {
	protected Exposicion exposicion = null;
	protected List<Obra> obras = new ArrayList<Obra>();
	protected List<Subsala> subsalas = new ArrayList<Subsala>();
	protected Vector3 dimensiones = new Vector3();
	protected int enchufes;
	protected int aforo;
	private static final long serialVersionUID = 1L;

	// Constructores

	/**
	 * Constructor de Sala que recibe las dimensiones, enchufes y aforo.
	 * 
	 * @param ancho    el ancho de la sala
	 * @param alto     el alto de la sala
	 * @param largo    el largo de la sala
	 * @param enchufes el número de enchufes en la sala
	 * @param aforo    el aforo máximo de la sala
	 */
	protected Sala(double ancho, double alto, double largo, int enchufes, int aforo) {
		this.dimensiones.setDimensiones(ancho, alto, largo);
		this.enchufes = enchufes;
		this.aforo = aforo;
	}

	/**
	 * Constructor de Sala que recibe las dimensiones.
	 * 
	 * @param ancho el ancho de la sala
	 * @param alto  el alto de la sala
	 * @param largo el largo de la sala
	 */
	protected Sala(double ancho, double alto, double largo) {
		this.dimensiones.setDimensiones(ancho, alto, largo);
	}

	/**
	 * Constructor de Sala que recibe las dimensiones, enchufes y aforo.
	 * 
	 * @param dimensiones las dimensiones de la sala
	 * @param enchufes    el número de enchufes en la sala
	 * @param aforo       el aforo máximo de la sala
	 */
	protected Sala(Vector3 dimensiones, int enchufes, int aforo) {
		this.dimensiones = dimensiones;
		this.enchufes = enchufes;
		this.aforo = aforo;
	}

	/**
	 * Constructor vacío de Sala.
	 */
	protected Sala() {
	}

	// Setters

	/**
	 * Agrega una obra a la sala.
	 * Este método solo debe ser utilizado en pruebas.
	 * 
	 * @param obra la obra a agregar
	 */
	public void addObraTests(Obra obra){
		
		this.obras.add(obra);
		
	}

	/**
	 * Establece la exposicion de la sala.
	 * El nombre indica que solo se debe usar para montar los tests
	 * 
	 * @param exposicion la exposicion a establecer
	 */
	public void setExposicionTests(Exposicion exposicion) {
		this.exposicion = exposicion;
	}

	/**
	 * Añade una subsala a la sala.
	 * Este método solo debe ser utilizado en pruebas.
	 * 
	 * @param subsala la subsala a añadir
	 */
	void addSubsala(Subsala subsala) {
		this.subsalas.add(subsala);
	}

	// Métodos

	/**
	 * Busca una obra en la sala por su nombre.
	 * 
	 * @param nombre el nombre de la obra a buscar
	 * @return la obra encontrada, o null si no se encontró ninguna obra con ese
	 *         nombre
	 */
	public Obra buscarObra(String nombre) {
		for (Obra obra : obras) {
			if (obra.getNombre() == nombre) {
				return obra;
			}
		}

		return null;
	}

	/**
	 * Divide la sala en subsalas con las dimensiones, enchufes y aforo
	 * proporcionados.
	 * 
	 * @param dimList      la lista de dimensiones de las subsalas
	 * @param enchufesList la lista de enchufes de las subsalas
	 * @param aforoList    la lista de aforos de las subsalas
	 * @throws Exception si la sala tiene una exposición asignada, si la sala tiene
	 *                   obras, o si las listas de dimensiones, enchufes y aforo no
	 *                   tienen el mismo tamaño
	 */
	public void dividir(List<Vector3> dimList, List<Integer> enchufesList, List<Integer> aforoList) throws Exception {
		List<Subsala> subsalas = new ArrayList<Subsala>();

		if (exposicion != null) {
			throw new Exception("Error: No se puede dividir una sala que tenga una exposición asignada");
		}

		if (obras == null || obras.size() != 0) {
			throw new Exception("Error: Solo se puede dividir una sala si no tiene obras");
		}

		if (dimList == null || enchufesList == null || aforoList == null) {
			throw new Exception("Error: No se han proporcionado las dimensiones, enchufes o aforo de las subsalas");
		}

		if (dimList.size() != enchufesList.size() || dimList.size() != aforoList.size()) {
			throw new Exception("Error: Las listas de dimensiones, enchufes y aforo no tienen el mismo tamaño");
		}

		for (int i = 0; i < dimList.size(); i++) {
			Subsala s = new Subsala(dimList.get(i), enchufesList.get(i), aforoList.get(i), this);
			subsalas.add(s);
		}

		this.subsalas = subsalas;
	}

	// Este metodo no tiene en cuenta las condiciones de la expo, mejor usar
	// removeObra()
	/**
	 * Elimina una obra de la sala.
	 * 
	 * @param obra la obra a eliminar
	 */
	public void eliminarObra(Obra obra) {
		obras.remove(obra);
	}

	// Getters

	/**
	 * Obtiene la temperatura de la sala.
	 * Este método debe ser implementado por las subclases.
	 * 
	 * @return la temperatura de la sala
	 */
	public abstract double getTemperatura();

	/**
	 * Obtiene la humedad de la sala.
	 * Este método debe ser implementado por las subclases.
	 * 
	 * @return la humedad de la sala
	 */
	public abstract double getHumedad();

	/**
	 * Verifica si la sala es regulable.
	 * Este método debe ser implementado por las subclases.
	 * 
	 * @return true si la sala es regulable, false de lo contrario
	 */
	public abstract boolean getRegulable();

	/**
	 * Obtiene el aforo de la sala.
	 * Si la sala es una hoja, devuelve su aforo.
	 * Si la sala es intermedia, devuelve la suma de los aforos de las subsalas.
	 * 
	 * @return el aforo de la sala
	 */
	public int getAforo() {
		if (subsalas.size() == 0) { // La sala es hoja, por lo que devuelve su aforo
			return aforo;
		} else { // La sala es intermedia, por lo que devuelve la suma de los aforos de los hijos
			int t = 0;

			for (Subsala subsala : subsalas) {
				t += subsala.getAforo();
			}

			return t;
		}
	}

	/**
	 * Obtiene la lista de obras de la sala.
	 * 
	 * @return la lista de obras de la sala
	 */
	public List<Obra> getObras() {
		return this.obras;
	}

	// Setters

	/**
	 * Establece las dimensiones de la sala.
	 * 
	 * @param dimensiones las nuevas dimensiones de la sala
	 */
	public void setDimensiones(Vector3 dimensiones) {
		this.dimensiones = dimensiones;
	}

	/**
	 * Establece el número de enchufes de la sala.
	 * 
	 * @param enchufes el nuevo número de enchufes de la sala
	 */
	public void setEnchufes(int enchufes) {
		this.enchufes = enchufes;
	}

	/**
	 * Establece el aforo de la sala.
	 * 
	 * @param aforo el nuevo aforo de la sala
	 */
	public void setAforo(int aforo) {
		this.aforo = aforo;
	}

	/**
	 * Establece la exposición asignada a la sala.
	 * 
	 * @param exposicion la exposición asignada a la sala
	 * @throws Exception si la sala está dividida en subsalas
	 */
	public void setExposicion(Exposicion exposicion) throws Exception {
		if (subsalas.size() > 0) {
			throw new Exception("No puedes asignar una exposición a una sala que esté dividida");
		}

		this.exposicion = exposicion;
	}

	/**
	 * Obtiene las dimensiones de la sala.
	 * 
	 * @return las dimensiones de la sala
	 */
	public Vector3 getDimensiones() {
		return dimensiones;
	}

	/**
	 * Obtiene la lista de subsalas de la sala.
	 * 
	 * @return la lista de subsalas de la sala
	 */
	public List<Subsala> getSubsalas() {
		return subsalas;
	}

	/**
	 * Obtiene el número de enchufes de la sala.
	 * 
	 * @return el número de enchufes de la sala
	 */
	public int getEnchufes() {
		return enchufes;
	}

	// METODOS RELACIONADOS CON OBRAS

	/**
	 * Añade una obra física a la sala si cumple las condiciones, de lo contrario
	 * lanza una excepción.
	 * 
	 * @param obra la obra física a añadir
	 * @throws SalaExceptions si la sala no tiene una exposición asignada, si la
	 *                        sala tiene subsalas, si la sala ya contiene la obra o
	 *                        si no hay suficiente espacio en la sala para la obra
	 */
	public void addObra(Fisica obra) throws SalaExceptions {
		double espacio;
		if (exposicion == null) {
			throw new SalaWithoutExpoException();
		} else if (subsalas.size() > 0) {
			throw new SalaGotSubsalasException();
		} else if (this.obras.contains(obra)) {
			throw new SalaAlreadyContainsObra(obra);
		}

		espacio = this.espacioRestante();

		if (espacio - obra.getDimensiones().volumen() < 0) {
			throw new InsufficientSpaceException(espacio, obra.getDimensiones().volumen());
		} else {
			obras.add(obra);
		}
	}

	/**
	 * Añade una obra a la sala si cumple las condiciones, de lo contrario lanza una
	 * excepción.
	 * 
	 * @param obra la obra a añadir
	 * @throws SalaExceptions si la sala no tiene una exposición asignada, si la
	 *                        sala tiene subsalas o si la sala ya contiene la obra
	 */
	public void addObra(Obra obra) throws SalaExceptions {
		if (exposicion == null) {
			throw new SalaWithoutExpoException();
		} else if (subsalas.size() > 0) {
			throw new SalaGotSubsalasException();
		} else if (this.obras.contains(obra)) {
			throw new SalaAlreadyContainsObra(obra);
		} else {
			obras.add(obra);
		}
	}

	/**
	 * Calcula el espacio restante en la sala al agregar una obra.
	 * 
	 * @return el espacio restante en la sala
	 */
	public double espacioRestante() throws InsufficientSpaceException{
		double espacio = dimensiones.volumen();
		/*Vector3 dim = this.getDimensiones();*/
		for (Obra obra : obras) {
			espacio -= obra.getDimensiones().volumen();
			if (espacio < 0) {
				throw new InsufficientSpaceException(espacio, obra.getDimensiones().volumen());
			}
			/*dim.setDimensiones(dim.getX() - obra.getDimensiones().getX(), dim.getY() - obra.getDimensiones().getY(),
					dim.getZ() - obra.getDimensiones().getZ());*/

		}
		return espacio;
	}

	/**
	 * Verifica si la temperatura es válida para todas las obras de la sala.
	 * 
	 * @param temperatura la temperatura a verificar
	 * @return true si la temperatura es válida para todas las obras, false de lo
	 *         contrario
	 */
	public boolean temperaturaValida(double temperatura) {
		for (Obra obra : obras) {
			if (!obra.temperaturaEnRango(temperatura)) {
				return false;
			}
		}

		return true;
	}

	/**
	 * Verifica si la humedad es válida para todas las obras de la sala.
	 * 
	 * @param temperatura la humedad a verificar
	 * @return true si la humedad es válida para todas las obras, false de lo
	 *         contrario
	 */
	public boolean humedadValida(double temperatura) {
		for (Obra obra : obras) {
			if (!obra.humedadEnRango(temperatura)) {
				return false;
			}
		}

		return true;
	}

	/**
	 * Verifica si la exposición asignada a la sala es permanente.
	 * Esta función solo debe ser llamada en el contexto de una subsala hoja.
	 * 
	 * @return false si la exposición es temporal, true si es permanente
	 * @throws SalaGotSubsalasException si la sala tiene subsalas
	 * @throws SalaWithoutExpoException si la sala no tiene una exposición asignada
	 */
	public boolean expoPermanente() throws SalaGotSubsalasException, SalaWithoutExpoException {
		if (exposicion == null) {
			throw new SalaWithoutExpoException();
		} else if (subsalas.size() > 0) {
			throw new SalaGotSubsalasException();
		}
		return exposicion.esPermanente();
	}

	/**
	 * Verifica si se puede agregar una obra a la exposición asignada a la sala.
	 * 
	 * @param propiedad true si la obra es de propiedad del museo, false si es una
	 *                  obra en préstamo
	 * @return true si se puede agregar la obra, false de lo contrario
	 * @throws SalaGotSubsalasException si la sala tiene subsalas
	 * @throws SalaWithoutExpoException si la sala no tiene una exposición asignada
	 */
	public boolean addObraExpoCheck(boolean propiedad) throws SalaGotSubsalasException, SalaWithoutExpoException {
		if (exposicion == null) {
			throw new SalaWithoutExpoException();
		} else if (subsalas.size() > 0) {
			throw new SalaGotSubsalasException();
		}
		return exposicion.addObraCheck(propiedad);
	}

	/**
	 * Remueve una obra de la sala.
	 * 
	 * @param obra la obra a remover
	 * @return true si se removió la obra, false de lo contrario
	 */
	public boolean removeObra(Obra obra) {
		if (subsalas.size() > 0) {
			return false;
		}
		if (exposicion == null) {
			return false;
		}	

		if (exposicion.removeObraCheck()) {
			this.obras.remove(obra);
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Restaura una obra de la sala.
	 * 
	 * @param obra la obra a restaurar
	 * @return true si se restauró la obra, false de lo contrario
	 */
	public boolean restaurarObra(Obra obra) {
		if (exposicion == null) {
			return false;
		}
		if (exposicion.restaurarObraCheck()) {
			this.obras.remove(obra);
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Elimina una subsala de la sala.
	 * 
	 * @param subsala
	 */
	public void eliminarSubsala(Subsala subsala) {
		subsalas.remove(subsala);
	}

	@Override
	public String toString() {
		return "Sala{" + ", subsalas=" + subsalas + ", dimensiones=" + dimensiones + ", enchufes=" + enchufes
				+ ", aforo=" + aforo + '}';
	}
}