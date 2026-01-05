package descuento;

/**
 * Esta clase representa un descuento por antelación en una compra.
 * Extiende la clase Descuento.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Antelacion extends Descuento {

    /**
     * Representa la cantidad de días de antelación para aplicar un descuento.
     */
    private int dias;
    /**
     * Identificador de versión serial para la clase Antelacion.
     * Este identificador se utiliza para controlar la compatibilidad de versiones
     * al serializar y deserializar objetos de la clase Antelacion.
     */
    private static final long serialVersionUID = 1L;

    /**
     * Crea un objeto Antelacion con el porcentaje de descuento y el número de días
     * de antelación especificados.
     * 
     * @param porcentaje El porcentaje de descuento por antelación.
     * @param dias       El número de días de antelación para aplicar el descuento.
     * 
     * @throws IllegalArgumentException Si el porcentaje de descuento es negativo.
     * @throws IllegalArgumentException Si el número de días de antelación es
     *                                  negativo.
     */
    public Antelacion(double porcentaje, int dias) {
        super(porcentaje);
        this.dias = dias;
    }

    /**
     * Verifica si el descuento es por fidelidad.
     * 
     * @return true si el descuento es por fidelidad, false de lo contrario.
     */
    public boolean esFidelidad() {
        return false;
    }

    /**
     * Obtiene el número de días de antelación.
     * 
     * @return El número de días de antelación.
     */
    public int getDias() {
        return dias;
    }

    /**
     * Obtiene el mensaje de descuento por antelación.
     * 
     * @return El mensaje de descuento por antelación.
     */
    public String getMensaje() {
        return " de antelación. Si compras con " + dias + " días de antelación, tendrás un descuento del "
                + super.getPorcentaje() + "%.";
    }

    /**
     * Devuelve una representación en cadena del objeto Antelacion.
     * 
     * @return Una representación en cadena del objeto Antelacion.
     */
    @Override
    public String toString() {
        return "Descuento por antelación de " + dias + " días: " + super.toString();
    }
}