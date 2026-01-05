package sistema;

import galeria.exposicion.*;
import java.time.LocalDateTime;

import java.io.Serializable;

/**
 * La clase Compra representa una compra de entradas para una exposición.
 * Contiene información sobre el precio, el número de entradas, la fecha de la
 * compra
 * y la exposición a la que pertenece.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Compra implements Serializable {
    private double precio;
    private int nEntradas;
    private LocalDateTime fecha;
    private Exposicion exposicion;
    private static final long serialVersionUID = 1L;

    /**
     * Crea una nueva instancia de la clase Compra.
     * 
     * @param precio     El precio de la compra.
     * @param nEntradas  El número de entradas compradas.
     * @param fecha      La fecha de la compra.
     * @param exposicion La exposición a la que pertenece la compra.
     * 
     * @throws NullPointerException Si la exposición es nula.
     */
    public Compra(double precio, int nEntradas, LocalDateTime fecha, Exposicion exposicion) {
        this.precio = precio;
        this.nEntradas = nEntradas;
        this.fecha = fecha;
        this.exposicion = exposicion;
    }

    /**
     * Obtiene la fecha de la compra.
     * 
     * @return La fecha de la compra.
     */
    public LocalDateTime getFecha() {
        return fecha;
    }

    /**
     * Obtiene el número de entradas compradas.
     * 
     * @return El número de entradas compradas.
     */
    public int getEntradas() {
        return nEntradas;
    }

    /**
     * Obtiene la exposición a la que pertenece la compra.
     * 
     * @return La exposición a la que pertenece la compra.
     */
    public Exposicion getExposicion() {
        return exposicion;
    }

    /**
     * Obtiene el precio de la compra.
     * 
     * @return El precio de la compra.
     */
    public double getPrecio() {
        return precio;
    }

    /**
     * Devuelve una representación en forma de cadena de la compra.
     * 
     * @return Una cadena que representa la compra.
     */
    @Override
    public String toString() {
        return "Compra{" +
                "precio=" + precio +
                ", nEntradas=" + nEntradas +
                ", fecha=" + fecha +
                ", exposicion=" + exposicion +
                '}';
    }
}