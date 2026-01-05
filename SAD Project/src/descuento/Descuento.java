package descuento;

import java.io.Serializable;

/**
 * Clase abstracta que representa un descuento.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public abstract class Descuento implements Serializable {
    private static final long serialVersionUID = 1L;
    private double porcentaje;

    /**
     * Obtiene el porcentaje de descuento.
     * 
     * @return el porcentaje de descuento
     */
    public double getPorcentaje() {
        return porcentaje;
    }

    /**
     * Constructor de la clase Descuento.
     * 
     * @param porcentaje el porcentaje de descuento
     * 
     * @throws IllegalArgumentException si el porcentaje es negativo
     */
    public Descuento(double porcentaje) {
        if (porcentaje < 0) {
            throw new IllegalArgumentException("El porcentaje no puede ser negativo");
        }
        this.porcentaje = porcentaje;
    }

    /**
     * Verifica si el descuento es de fidelidad.
     * 
     * @return true si el descuento es de fidelidad, false de lo contrario
     */
    public abstract boolean esFidelidad();

    /**
     * Obtiene el mensaje del descuento.
     * 
     * @return el mensaje del descuento
     */
    public abstract String getMensaje();

    /**
     * Devuelve una representación en cadena del objeto Descuento.
     * 
     * @return una representación en cadena del objeto Descuento
     */
    @Override
    public String toString() {
        return " porcentaje=" + porcentaje + '}';
    }
}
