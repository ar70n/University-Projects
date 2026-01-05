package menu;

/**
 * La clase GeneradorIdUnico se encarga de generar identificadores únicos.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class GeneradorIdUnico {
    private static int ultimoId = 0;

    /**
     * Genera un nuevo identificador único.
     *
     * @return El nuevo identificador único generado.
     */
    public static int generarIdUnico() {
        ultimoId++;
        return ultimoId;
    }

    /**
     *
     * @return The generated unique ID.
     */
    public static int generarId() {
        ultimoId++;
        return ultimoId;
    }
}