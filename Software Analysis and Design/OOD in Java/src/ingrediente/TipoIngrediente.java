package ingrediente;
/**
 * Enumeración que representa los diferentes tipos de ingredientes.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public enum TipoIngrediente {

    CARNE("Carne"),
    PESCADO("Pescado"),
    FRUTA_VERDURA("Fruta y verduras"),
    LEGUMBRE("Legumbre"),
    CEREAL("Cereal"),
    HUEVO("Huevo"),
    LACTEO("Lacteo");

    private final String nombre;

    /**
     * Constructor de la enumeración TipoIngrediente.
     * @param nombre el nombre del tipo de ingrediente.
     */
    TipoIngrediente(String nombre){
        this.nombre=nombre;
    }

    /**
     * Obtiene el nombre del tipo de ingrediente.
     * @return el nombre del tipo de ingrediente.
     */
    public String getNombre() {
        return this.nombre;
    }
}