package stateMachine;

import java.time.LocalDateTime;
import java.util.*;
import java.util.function.Predicate;

/**
 * Clase génerica que permite definir estados y transiciones de un objeto de
 * manera externa. Implementa la interfaz IObserver.
 * 
 * @param <T> Tipo de objeto a seguir.
 * @param <E> Tipo de estado. Define un orden natural.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public class ObjectStateTracker<T, E extends Comparable<E>> implements Iterable<T>, IObserver<T> {
	/**
	 * Mapa que asocia un estado con una expresión lambda que determina si un objeto
	 * pertenece a ese estado.
	 */
	private Map<E, Predicate<T>> mapa = new LinkedHashMap<>();

	/**
	 * Mapa que asocia un estado con una lista de objetos que pertenecen a ese
	 * estado.
	 */
	private Map<E, List<T>> statesObjects = new TreeMap<>();

	/**
	 * Mapa que asocia un objeto con una lista de estados por los que ha pasado.
	 */
	private Map<T, List<String>> trajectorie = new LinkedHashMap<>();

	/**
	 * Constructor de la clase.
	 * 
	 * @param elems Lista de estados válidos para los objetos.
	 */
	public ObjectStateTracker(E... elems) {
		for (E e : elems) {
			statesObjects.put(e, new ArrayList<>());
		}
	}

	/**
	 * Añade una expresión lambda y el estado al que pertenece al mapa
	 * correspondiente.
	 * 
	 * @param e Estado a añadir.
	 * @param p Expresión lambda que determina si un objeto pertenece a ese estado.
	 * @return El objeto actual.
	 * @throws IllegalStateException Si el estado no es válido.
	 */
	public ObjectStateTracker<T, E> withState(E e, Predicate<T> p) throws IllegalStateException {
		if (!statesObjects.containsKey(e)) {
			throw new IllegalStateException("El estado" + e.toString() + "no existe.");
		}
		mapa.put(e, p);
		return this;
	}

	/**
	 * Añade una expresión que siempre devuelve true y el estado al que pertenece al
	 * mapa correspondiente.
	 * 
	 * @param e Estado del objeto si no se cumple ninguna de las condiciones
	 *          anteriores.
	 * @return El objeto actual.
	 * @throws IllegalStateException Si el estado no es válido.
	 */
	public ObjectStateTracker<T, E> elseState(E e) throws IllegalStateException {
		if (!statesObjects.containsKey(e)) {
			throw new IllegalStateException("El estado" + e.toString() + "no existe.");
		}
		mapa.put(e, t -> true);
		return this;
	}

	/**
	 * Actualiza los estados de los objetos de acuerdo con las expresiones lambda.
	 */
	@Override
	public void updateStates() {
		for (T obj : trajectorie.keySet()) {
			Boolean removed = false;
			Boolean added = false;
			E origen = null;
			E destino = null;
			for (E e : mapa.keySet()) {
				Boolean test = mapa.get(e).test(obj);
				Boolean contains = statesObjects.get(e).contains(obj);
				if ((added || !test) && contains) {
					statesObjects.get(e).remove(obj);
					removed = true;
					origen = e;
				} else if (test && !contains) {
					statesObjects.get(e).add(obj);
					added = true;
					destino = e;
				}
				if (removed && added) {
					// Creo que la trayectoria solo se guarda si cambia el estado.
					this.trajectorie.get(obj).add(
							"(from: " + origen + " to " + destino + " at: " + LocalDateTime.now().toString() + ")");
					break;
				} else if (test && contains) {
					break;
				}
			}
		}
	}

	/**
	 * Añade objetos a la lista de objetos.
	 * 
	 * @param t Lista de objetos a añadir.
	 */
	public void addObjects(T... t) {
		for (T obj : t) {
			if (!trajectorie.containsKey(obj)) {
				for (E e : mapa.keySet()) {
					if (mapa.get(e).test(obj)) {
						statesObjects.get(e).add(obj);
						List<String> list = new ArrayList<String>();
						trajectorie.put(obj, list);
						list.add("(in: " + e.toString() + " at: " + LocalDateTime.now().toString() + ")");
						break;
					}
				}
			}
		}
	}

	/**
	 * Imprime el mapa de estados y objetos que se encuentran en ellos.
	 * 
	 * @return Mapa de estados y objetos.
	 */
	@Override
	public String toString() {
		return statesObjects.toString();
	}

	/**
	 * Devuelve la trayectoria de un objeto.
	 * 
	 * @param t Objeto cuya trayectoria se quiere conocer.
	 * @return Trayectoria del objeto.
	 */
	public List<String> trajectory(T t) {
		return trajectorie.get(t);
	}

	/**
	 * Devuelve el iterador de la clase.
	 * 
	 * @return Iterador de la clase.
	 */
	@Override
	public Iterator<T> iterator() {
		return trajectorie.keySet().iterator();
	}

	/* Métodos para los JUnit */

	/**
	 * Devuelve el mapa de estados y expresiones lambda.
	 * 
	 * @return Mapa de estados y expresiones lambda.
	 */
	public Map<E, Predicate<T>> getStateLambda() {
		return mapa;
	}

	/**
	 * Devuelve el mapa de estados y objetos que se encuentran en ellos.
	 * 
	 * @return Mapa de estados y objetos.
	 */
	public Map<E, List<T>> getStatesObjects() {
		return statesObjects;
	}

	/**
	 * Devuelve el mapa de objetos y su trayectoria.
	 * 
	 * @return Mapa de objetos y su trayectoria.
	 */
	public Map<T, List<String>> getTrajectorie() {
		return trajectorie;
	}
}
