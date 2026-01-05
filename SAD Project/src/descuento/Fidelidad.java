package descuento;

/**
 * Esta clase representa un descuento por fidelidad.
 * Extiende la clase Descuento.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Fidelidad extends Descuento {

    /**
     * El número de meses en los que se considera la fidelidad.
     */
    private int meses;

    private static final long serialVersionUID = 1L;

    /**
     * Crea un objeto Fidelidad con el porcentaje de descuento y el número de meses
     * especificados.
     * 
     * @param porcentaje El porcentaje de descuento por fidelidad.
     * @param meses      El número de meses en los que se considera la fidelidad.
     * 
     * @throws IllegalArgumentException Si el porcentaje de descuento es negativo.
     */
    public Fidelidad(double porcentaje, int meses) {
        super(porcentaje);
        this.meses = meses;
    }

    /**
     * Verifica si el descuento es por fidelidad.
     * 
     * @return true si el descuento es por fidelidad, false de lo contrario.
     */
    public boolean esFidelidad() {
        return true;
    }

    /**
     * Obtiene el número de meses en los que se considera la fidelidad.
     * 
     * @return El número de meses en los que se considera la fidelidad.
     */
    public int getMeses() {
        return meses;
    }

    /**
     * Obtiene el mensaje de descuento por fidelidad.
     * 
     * @return El mensaje de descuento por fidelidad.
     */
    public String getMensaje() {
        return " de fidelidad. Todos los usuarios que hayan hecho una compra en los últimos " + meses
                + " meses tendrán un descuento del " + super.getPorcentaje() + "%.";
    }

    /**
     * Devuelve una representación en cadena del objeto Fidelidad.
     * 
     * @return Una representación en cadena del objeto Fidelidad.
     */
    @Override
    public String toString() {
        return "Fidelidad:" +
                "meses=" + meses + ", " + super.toString();
    }
}