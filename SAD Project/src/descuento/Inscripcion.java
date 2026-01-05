package descuento;

import usuario.Cliente;
import java.io.Serializable;

/**
 * Esta clase representa la inscripción de un cliente en un sorteo.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Inscripcion implements Serializable {

    /**
     * El número de entradas de la inscripción.
     */
    private int nEntradas;

    /**
     * El cliente que realiza la inscripción.
     */
    private Cliente cliente;

    /**
     * El número de versión de la clase para la serialización.
     */
    private static final long serialVersionUID = 1L;

    /**
     * Crea una nueva instancia de la clase Inscripcion.
     *
     * @param nEntradas el número de entradas de la inscripción
     * @param cliente   el cliente que realiza la inscripción
     */
    public Inscripcion(int nEntradas, Cliente cliente) {
        this.nEntradas = nEntradas;
        this.cliente = cliente;
    }

    /**
     * Obtiene el cliente que realiza la inscripción.
     *
     * @return el cliente que realiza la inscripción
     */
    public Cliente getParticipante() {
        return cliente;
    }

    /**
     * Obtiene el número de entradas de la inscripción.
     *
     * @return el número de entradas de la inscripción
     */
    public int getEntradas() {
        return nEntradas;
    }
}
