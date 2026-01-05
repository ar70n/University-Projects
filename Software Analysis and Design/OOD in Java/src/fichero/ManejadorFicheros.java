package fichero;

import java.io.*;
import menu.*;
import java.util.*;
import plato.*;
import ingrediente.*;
import infoNutricional.*;


/**
 * Esta clase se encarga de manejar los ficheros de menús y platos.
 * Proporciona métodos para leer y guardar los datos en un fichero,
 * así como para obtener la lista de menús.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class ManejadorFicheros {

	private static List<Menu> menus = new ArrayList<Menu>();


	
	/**
	 * Lee los datos de un fichero y los almacena en la lista de menús.
	 *
	 * @param file la ruta del fichero a leer
	 * @throws IOException si ocurre un error de lectura del fichero
	 */
	public static void leerFichero(String file) throws IOException {
		BufferedReader buffer = new BufferedReader(
				new InputStreamReader(
						new FileInputStream(file)));

		Set<Ingrediente> ingredientes = new HashSet<Ingrediente>();
		Set<Plato> platos = new HashSet<Plato>();
		List<Menu> menus = new ArrayList<Menu>();

		String linea;
		while ((linea = buffer.readLine()) != null) {
			// System.out.println("Linea leida: " + linea);
			String[] partes = linea.split(";");
			if (partes[0].startsWith("INGREDIENTE")) {
				ingredientes.add(readIngrediente(partes));
			} else if (partes[0].equals("PLATO")) {
				platos.add(readPlato(partes, ingredientes, platos));
			} else if (partes[0].equals("MENU")) {
				Menu menu = new Menu();
				for (int i = 1; i < partes.length; i++) {
					for (Plato plato : platos) {
						if (plato.getNombre().equals(partes[i])) {
							menu.addPlato(plato);
						}
					}
				}
				menus.add(menu);
			}
		}
		buffer.close();
		ManejadorFicheros.menus = menus;
	}


	/**
	 * Guarda los datos de los menús en un fichero.
	 *
	 * @param file  la ruta del fichero donde se guardarán los datos
	 * @param menus la lista de menús a guardar
	 * @throws IOException si ocurre un error al escribir en el fichero
	 */
	public static void guardarFichero(String file, List<Menu> menus) throws IOException {
		Set<Object> guardado = new HashSet<Object>();

		FileOutputStream stream = new FileOutputStream(file);
		PrintWriter salida = new PrintWriter(stream);

		for (Menu menu : menus) {
			if (guardado.contains(menu)) {
				continue;
			} else {
				guardado.add(menu);
			}
			for (Plato plato : menu.getPlatos()) {
				if (guardado.contains(plato)) {
					continue;
				} else {
					guardado.add(plato);
				}
				for (Ingrediente ingrediente : plato.getIngredientes()) {
					if (guardado.contains(ingrediente)) {
						continue;
					} else {
						guardado.add(ingrediente);
						String tipoIngrediente = ingrediente.getTipo();

						for (TipoIngrediente tipo : TipoIngrediente.values()) {
							if (tipo.getNombre().equals(ingrediente.getTipo())) {
								tipoIngrediente = tipo.toString();
								break;
							}
						}

						salida.printf(String.format(Locale.US,
								ingrediente.getInfo().printInfo() + ";" + ingrediente.getNombre() + ";"
										+ tipoIngrediente  +
										";%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;" + ingrediente.printAlergenos()
										+ "\n",
								ingrediente.getInfo().getCalorias(), ingrediente.getInfo().getHidratosDeCarbono(),
								ingrediente.getInfo().getGrasas(),
								ingrediente.getInfo().getGrasasSaturadas(), ingrediente.getInfo().getProteinas(),
								ingrediente.getInfo().getAzucares(), ingrediente.getInfo().getFibra(),
								ingrediente.getInfo().getSodio()));
					}
				}

				salida.printf("PLATO;" + plato.getNombre() + plato.printPlatos() + plato.printIngredientes() + "\n");
			}

			salida.printf(menu.print());
		}
		salida.flush();
		salida.close();
	}


	/**
	 * Obtiene la lista de menús.
	 *
	 * @return la lista de menús
	 */
	public static List<Menu> getMenus() {
		return menus;
	}


	/**
	 * Lee los datos de un ingrediente a partir de un array de partes.
	 *
	 * @param partes el array de partes que contiene los datos del ingrediente
	 * @return el ingrediente leído
	 */
	private static Ingrediente readIngrediente(String[] partes) {
		Ingrediente ingrediente;
		InfoNutricional info;

		if(partes[0].substring(12).equals("PESO")){
			info = new InfoNutricionalPeso(Double.parseDouble(partes[3]), Double.parseDouble(partes[4]),
			Double.parseDouble(partes[5]), Double.parseDouble(partes[6]), Double.parseDouble(partes[7]),
			Double.parseDouble(partes[8]), Double.parseDouble(partes[9]), Double.parseDouble(partes[10]));
		}
		else{
			info = new InfoNutricionalUnidad(Double.parseDouble(partes[3]), Double.parseDouble(partes[4]),
			Double.parseDouble(partes[5]), Double.parseDouble(partes[6]), Double.parseDouble(partes[7]),
			Double.parseDouble(partes[8]), Double.parseDouble(partes[9]), Double.parseDouble(partes[10]));
		}

		ingrediente = new Ingrediente(partes[1], partes[2], info);

		if (partes[11].equals("S")) {
			ingrediente.tieneAlergenos(Alergeno.GLUTEN);
		}
		if (partes[12].equals("S")) {
			ingrediente.tieneAlergenos(Alergeno.LACTOSA);
		}
		if (partes[13].equals("S")) {
			ingrediente.tieneAlergenos(Alergeno.FRUTOS_SECOS);
		}
		if (partes[14].equals("S")) {
			ingrediente.tieneAlergenos(Alergeno.HUEVO);
		}
		return ingrediente;
	}



	/**
	 * Lee los datos de un plato a partir de un array de partes.
	 *
	 * @param partes      el array de partes que contiene los datos del plato
	 * @param ingredientes el conjunto de ingredientes disponibles
	 * @param platos      el conjunto de platos disponibles
	 * @return el plato leído
	 */
	private static Plato readPlato(String[] partes, Set<Ingrediente> ingredientes, Set<Plato> platos) {
		Plato plato = new Plato(partes[1]);

		for (int i = 2; i < partes.length; i++) {

			if (partes[i].startsWith("PLATO ")) {
				String nombrePlato = partes[i].substring(6); // Extrae el nombre del plato
				for (Plato platoAux : platos) {
					if (platoAux.getNombre().equals(nombrePlato)) {
						plato.addPlato(platoAux);
					}
				}
			}

			else if (partes[i].startsWith("INGREDIENTE ")) {
				String[] partesIngrediente = partes[i].split(":");
				for (Ingrediente ingrediente : ingredientes) {
					if (ingrediente.getNombre().equals(partesIngrediente[0].substring(12))) {
						plato.addIngrediente(ingrediente, Integer.parseInt(partesIngrediente[1]));
						break;
					}
				}
			}
		}
		return plato;
	}
}
