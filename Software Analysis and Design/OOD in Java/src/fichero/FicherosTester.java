package fichero;
import java.util.*;
import menu.*;
import java.io.*;

public class FicherosTester extends MenusTester {
	public static void main(String[] args) {
		FicherosTester tester = new FicherosTester();
		List<Menu> menus = tester.crearMenus();
		// guardar lista de menús a fichero
		try {
			ManejadorFicheros.guardarFichero("comida.txt", menus);
		} catch (IOException e) {
			e.printStackTrace();
		}
		// leer lista de menús de fichero, e imprimirlos por pantalla
		try {
			ManejadorFicheros.leerFichero("comida.txt");
		} catch (IOException e) {
			e.printStackTrace();
		}
		for (Menu menu : ManejadorFicheros.getMenus())
			System.out.println("* " + menu);
	}
}
