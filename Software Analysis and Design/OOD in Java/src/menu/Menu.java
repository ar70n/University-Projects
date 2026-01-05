package menu;

import plato.*;
import infoNutricional.InfoNutricionalMenu;

import java.util.*;
import ingrediente.Alergeno;

/**
 * La clase Menu representa un menú que contiene uno o dos platos.
 * Cada menú tiene un identificador único, una lista de platos, información nutricional y alérgenos.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class Menu {

	/**
	 * El id unico
	 */
	private final int id;

	/**
	 * Los platos del menu
	 */	
	private Set<Plato> platos = new HashSet<Plato>();

	/**
	 * La info nutricional de todo el menu
	 */
	private InfoNutricionalMenu info = new InfoNutricionalMenu();

	/**
	 * Los alergenos de los menus
	 */
	private Set<Alergeno> alergenos = new HashSet<Alergeno>();

	/**
	 * Constructor de la clase Menu.
	 * Crea un menú con los platos especificados.
	 *
	 * @param platos Los platos que componen el menú.
	 * @throws IllegalArgumentException Si se intenta crear un menú con más de 2 platos.
	 */
	public Menu(Plato... platos) {
		if (platos.length > 2) {
			throw new IllegalArgumentException("El menú debe tener entre 1 y 2 platos");
		}
		this.id = GeneradorIdUnico.generarId();
		for (Plato plato : platos) {
			this.platos.add(plato);
			this.info.sumarInfo(plato.getInfo());
			this.alergenos.addAll(plato.getAlergenos());
		}
	}

	/**
	 * Constructor de la clase Menu.
	 * Crea un menú con los platos especificados en una lista.
	 *
	 * @param platos La lista de platos que componen el menú.
	 * @throws IllegalArgumentException Si se intenta crear un menú con más de 2 platos.
	 */
	public Menu(List<Plato> platos) {
		if (platos.size() > 2) {
			throw new IllegalArgumentException("El menú debe tener entre 1 y 2 platos");
		}
		this.id = GeneradorIdUnico.generarId();
		for (Plato plato : platos) {
			this.platos.add(plato);
			this.info.sumarInfo(plato.getInfo());
			this.alergenos.addAll(plato.getAlergenos());
		}
	}

	/**
	 * Agrega un plato al menú.
	 *
	 * @param plato El plato a agregar.
	 * @throws IllegalArgumentException Si el menú ya tiene 2 platos.
	 */
	public void addPlato(Plato plato) {
		if (this.platos.size() == 2) {
			throw new IllegalArgumentException("El menú ya tiene 2 platos");
		}
		this.platos.add(plato);
		this.info.sumarInfo(plato.getInfo());
		this.alergenos.addAll(plato.getAlergenos());
	}

	/**
	 * Obtiene los platos del menú.
	 *
	 * @return Un conjunto de platos que componen el menú.
	 */
	public Set<Plato> getPlatos() {
		return this.platos;
	}

	/**
	 * Devuelve una representación en cadena del menú.
	 *
	 * @return La representación en cadena del menú.
	 */
	@Override
	public String toString() {
		String nombres = "[";
		String alergenos = "";
		boolean primero = true;
		for (Plato plato : this.platos) {
			if (primero == true) {
				nombres = nombres + plato.getNombre();
				primero = false;
			} else {
				nombres = nombres + ", " + plato.getNombre();
			}
		}
		nombres = nombres + "]";
		primero = true;
		for (Alergeno alergeno : this.alergenos) {
			if (primero == true) {
				alergenos = alergenos + alergeno.getNombre();
				primero = false;
			} else {
				alergenos = alergenos + ", " + alergeno.getNombre();
			}
		}
		return "Menú " + this.id + " " + nombres + ": " + this.info.toString() + " CONTIENE " + alergenos;
	}

	/**
	 * Imprime el menú en un formato específico.
	 *
	 * @return El menú en formato de texto.
	 */
	public String print() {
		String texto = "MENU";
		for (Plato plato : this.platos) {
			texto = texto + ";" + plato.getNombre();
		}
		texto = texto + "\n";
		return texto;
	}
}
