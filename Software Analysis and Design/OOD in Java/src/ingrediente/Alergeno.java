package ingrediente;
/**
 * Enumeración que representa los diferentes alérgenos.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public enum Alergeno {
	
	/**
	 * Alérgeno de gluten.
	 */
	GLUTEN("gluten"),
	
	/**
	 * Alérgeno de lactosa.
	 */
	LACTOSA("lactosa"),
	
	/**
	 * Alérgeno de huevo.
	 */
	HUEVO("huevo"),
	
	/**
	 * Alérgeno de frutos secos.
	 */
	FRUTOS_SECOS("frutos secos");
	
	private final String nombre;
	
	/**
	 * Constructor de la enumeración Alergeno.
	 * @param nombre el nombre del alérgeno
	 */
	Alergeno(String nombre){
		this.nombre=nombre;
	}
	
	/**
	 * Obtiene el nombre del alérgeno.
	 * @return el nombre del alérgeno
	 */
	public String getNombre() {
		return this.nombre;
	}

}