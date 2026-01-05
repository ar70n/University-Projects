package planificador;

import plato.Plato;
import ingrediente.Alergeno;
import menu.Menu;

import java.util.*;

/**
 * La clase PlanificadorMenu se encarga de planificar un menú a partir de una lista de platos disponibles,
 * teniendo en cuenta los máximos nutricionales y los alérgenos excluidos.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class PlanificadorMenu {
	private List<Plato> platosDisponibles;
	private Map<ElementoNutricional, Double> maximosNutricionales;
	private Set<Alergeno> alergenosExcluidos;

	/**
	 * Constructor de la clase PlanificadorMenu.
	 * 
	 * @param platos la lista de platos disponibles para planificar el menú.
	 */
	public PlanificadorMenu(List<Plato> platos) {
		this.platosDisponibles = platos;
		this.maximosNutricionales = new HashMap<>();
		this.alergenosExcluidos = new HashSet<>();
	}

	/**
	 * Establece el máximo valor nutricional permitido para un nutriente específico.
	 * 
	 * @param nutriente el nutriente para el cual se establece el máximo valor nutricional.
	 * @param maximo el máximo valor nutricional permitido.
	 * @return una referencia al objeto PlanificadorMenu actualizado.
	 */
	public PlanificadorMenu conMaximo(ElementoNutricional nutriente, double maximo) {
		this.maximosNutricionales.put(nutriente, maximo);
		return this;
	}

	/**
	 * Excluye los alérgenos especificados del menú planificado.
	 * 
	 * @param alergenos los alérgenos a excluir del menú.
	 * @return una referencia al objeto PlanificadorMenu actualizado.
	 */
	public PlanificadorMenu sinAlergenos(Alergeno... alergenos) {
		this.alergenosExcluidos.addAll(Arrays.asList(alergenos));
		return this;
	}

	/**
	 * Planifica un menú dentro del rango de calorías especificado.
	 * 
	 * @param caloriasMinimasMenu el valor mínimo de calorías permitido para el menú.
	 * @param caloriasMaximasMenu el valor máximo de calorías permitido para el menú.
	 * @return el menú planificado, o null si no se pudo planificar un menú válido.
	 */
	public Menu planificar(double caloriasMinimasMenu, double caloriasMaximasMenu) {
		return planificarRecursivo(caloriasMinimasMenu, caloriasMaximasMenu, 0, 1);
	}

	/**
	 * La clase Menu representa un menú compuesto por dos platos.
	 * Cada plato del menú tiene información sobre sus calorías y alérgenos.
	 *
	 * @param caloriasMinimasMenu las calorías mínimas permitidas para el menú
	 * @param caloriasMaximasMenu las calorías máximas permitidas para el menú
	 * @param i el índice del primer plato en la lista de platos disponibles
	 * @param j el índice del segundo plato en la lista de platos disponibles
	 * @return un objeto Menu que contiene los dos platos seleccionados si cumplen con los criterios establecidos, o null si no se encuentra una combinación válida
	 */
	private Menu planificarRecursivo(double caloriasMinimasMenu, double caloriasMaximasMenu, int i, int j) {
		if (i >= platosDisponibles.size() || j >= platosDisponibles.size()) {
			return null;
		}

		Plato plato1 = platosDisponibles.get(i);
		Plato plato2 = platosDisponibles.get(j);
		double totalCalorias = plato1.getInfo().getCalorias() + plato2.getInfo().getCalorias();

		if (totalCalorias >= caloriasMinimasMenu && totalCalorias <= caloriasMaximasMenu
				&& Collections.disjoint(plato1.getAlergenos(), alergenosExcluidos)
				&& Collections.disjoint(plato2.getAlergenos(), alergenosExcluidos)
				&& checkMaximosNutricionales(plato1, plato2)) {
			return new Menu(plato1, plato2);
		}

		if (j < platosDisponibles.size() - 1) {
			return planificarRecursivo(caloriasMinimasMenu, caloriasMaximasMenu, i, j + 1);
		} else {
			return planificarRecursivo(caloriasMinimasMenu, caloriasMaximasMenu, i + 1, i + 2);
		}
	}

	/**
	 * Comprueba si la combinación de dos platos cumple con los máximos nutricionales establecidos.
	 * 
	 * @param plato1 El primer plato a combinar.
	 * @param plato2 El segundo plato a combinar.
	 * @return true si la combinación cumple con los máximos nutricionales, false de lo contrario.
	 */
	private boolean checkMaximosNutricionales(Plato plato1, Plato plato2) {
		for (Map.Entry<ElementoNutricional, Double> entry : maximosNutricionales.entrySet()) {
			double total = plato1.getInfo().getValorNutricional(entry.getKey()) + plato2.getInfo().getValorNutricional(entry.getKey());
			if (total > entry.getValue()) {
				return false;
			}
		}
		return true;
	}

}