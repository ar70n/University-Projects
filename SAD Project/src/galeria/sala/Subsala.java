package galeria.sala;

import galeria.*;

/**
 * Esta clase representa una subsala en una galería.
 * Extiende la clase Sala y hereda sus atributos y métodos.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Subsala extends Sala {
    private static final long serialVersionUID = 1L;
    private Sala padre;

    /**
     * Constructor de la clase Subsala.
     * 
     * @param dimensiones las dimensiones de la subsala
     * @param enchufes    la cantidad de enchufes en la subsala
     * @param aforo       el aforo máximo de la subsala
     * @param padre       la sala padre de la subsala
     * 
     * @throws IllegalArgumentException si las dimensiones no son válidas
     * @throws IllegalArgumentException si la cantidad de enchufes es negativa
     * @throws IllegalArgumentException si el aforo es negativo
     */
    public Subsala(Vector3 dimensiones, int enchufes, int aforo, Sala padre) {
        super(dimensiones, enchufes, aforo);
        this.padre = padre;
    }

    /**
     * Constructor de la clase Subsala.
     * 
     * @param ancho    el ancho de la subsala
     * @param alto     el alto de la subsala
     * @param largo    el largo de la subsala
     * @param enchufes la cantidad de enchufes en la subsala
     * @param aforo    el aforo máximo de la subsala
     * @param padre    la sala padre de la subsala
     * 
     * @throws IllegalArgumentException si las dimensiones no son válidas
     * @throws IllegalArgumentException si la cantidad de enchufes es negativa
     * @throws IllegalArgumentException si el aforo es negativo
     */
    public Subsala(double ancho, double alto, double largo, int enchufes, int aforo, Sala padre) {
        super(ancho, alto, largo, enchufes, aforo);
        this.padre = padre;
    }

    /**
     * Constructor de la clase Subsala.
     * 
     * @param ancho
     * @param alto
     * @param largo
     * 
     * @throws IllegalArgumentException si las dimensiones no son válidas
     */
    public Subsala(double ancho, double alto, double largo) {
        super(ancho, alto, largo);
    }

    /**
     * Obtiene la temperatura de la sala padre.
     * 
     * @return la temperatura de la sala padre
     */
    public double getTemperatura() {
        return padre.getTemperatura();
    }

    /**
     * Obtiene la humedad de la sala padre.
     * 
     * @return la humedad de la sala padre
     */
    public double getHumedad() {
        return padre.getHumedad();
    }

    /**
     * Verifica si la sala padre es regulable.
     * 
     * @return true si la sala padre es regulable, false de lo contrario
     */
    public boolean getRegulable() {
        return padre.getRegulable();
    }
}