package stateMachine;

import java.util.*;

/**
 * Clase que permite extraer un proceso a partir de una colección de
 * trayectorias.
 * 
 * @param <E> Tipo de estado. Define un orden natural.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public class Process<E extends Comparable<E>> {
	/**
	 * Mapa que asocia un estado con el número de veces que ha sido inicial.
	 */
	private Map<E, Integer> numInicial = new TreeMap<>();

	/**
	 * Mapa que asocia un estado con el número de veces que ha sido final.
	 */
	private Map<E, Integer> numFinal = new TreeMap<>();

	/**
	 * Mapa que asocia un estado con otro estado y el número de veces que ha habido
	 * una transición entre ellos.
	 */
	private Map<E, Map<E, Integer>> numOtroEstado = new TreeMap<>();

	/**
	 * Constructor de la clase.
	 * 
	 * @param elems Lista de estados válidos para los objetos.
	 */
	public Process(E... elems) {
		for (E e : elems) {
			numInicial.put(e, 0);
			numFinal.put(e, 0);
			numOtroEstado.put(e, new TreeMap<>());
		}
		for (E e : elems) {
			for (E e2 : elems) {
				if (!e.equals(e2)) {
					numOtroEstado.get(e).put(e2, 0);
				}
			}
		}
	}

	/**
	 * Añade una trayectoria al proceso.
	 * 
	 * @param trj Trayectoria a añadir.
	 */
	public void add(List<String> trj) {
		for (String s : trj) {
			StringTokenizer st = new StringTokenizer(s, " ");
			E estado = null;
			String token = st.nextToken();
			if (token.equals("(in:")) {
				estado = stringtoState(st.nextToken());
				numInicial.put(estado, numInicial.get(estado) + 1);
			} else if (token.equals("(from:")) {
				E estadoIni = stringtoState(st.nextToken());
				st.nextToken(); // El to:
				E estadoFin = stringtoState(st.nextToken());
				numOtroEstado.get(estadoIni).put(estadoFin, numOtroEstado.get(estadoIni).get(estadoFin) + 1);
				if (trj.indexOf(s) == trj.size() - 1) {
					numFinal.put(estadoFin, numFinal.get(estadoFin) + 1);
				}
			}
		}
	}

	/**
	 * Convierte un token en un estado.
	 * 
	 * @param token Token a convertir.
	 * @return Estado correspondiente al token.
	 */
	private E stringtoState(String token) {
		E estado = null;
		for (E e : numInicial.keySet()) {
			if (e.toString().equals(token)) {
				estado = e;
				break;
			}
		}
		return estado;
	}

	/**
	 * Devuelve la información del proceso.
	 * 
	 * @return Información del proceso.
	 */
	@Override
	public String toString() {
		String info = "";
		for (E e : numInicial.keySet()) {
			info += e.toString() + " (initial " + numInicial.get(e) + " times, final " + numFinal.get(e) + " times):\n";
			for (E e2 : numOtroEstado.get(e).keySet()) {
				Integer times = numOtroEstado.get(e).get(e2);
				if (times > 0) {
					info += "  to state " + e2.toString() + ": " + times + " times\n";
				}
			}
		}
		return info;
	}
}
