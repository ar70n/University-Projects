package entrada;

import usuario.Cliente;
import java.io.Serializable;

/**
 * La clase Entrada representa una entrada para una visita en el sistema de
 * gestión de visitas.
 * Contiene información sobre el cliente, la visita y el número de tarjeta
 * asociado.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Entrada implements Serializable {
    private Cliente cliente; // El cliente asociado a la entrada
    private Visita visita; // La visita asociada a la entrada
    private String cardNumber; // El número de tarjeta asociado a la entrada
    private static final long serialVersionUID = 1L;

    /**
     * Crea una nueva instancia de la clase Entrada con la visita y el número de
     * tarjeta especificados.
     * 
     * @param visita     La visita asociada a la entrada
     * @param cardNumber El número de tarjeta asociado a la entrada
     */
    public Entrada(Visita visita, String cardNumber) {
        this.visita = visita;
        this.cardNumber = cardNumber;
    }

    /**
     * Crea una nueva instancia de la clase Entrada con la visita especificada.
     * 
     * @param visita La visita asociada a la entrada
     */
    public Entrada(Visita visita) {
        this.visita = visita;
        this.cardNumber = null;
        this.cliente = null;
    }

    /**
     * Obtiene la visita asociada a la entrada.
     * 
     * @return La visita asociada a la entrada
     */
    public Visita getVisita() {
        return visita;
    }

    /**
     * Obtiene el cliente asociado a la entrada.
     * 
     * @return El cliente asociado a la entrada
     */
    public Cliente getCliente() {
        return cliente;
    }

    /**
     * Obtiene el número de tarjeta asociado a la entrada.
     * 
     * @return El número de tarjeta asociado a la entrada
     */
    public String getCardNumber() {
        return cardNumber;
    }

    /**
     * Establece el cliente asociado a la entrada.
     * 
     * @param cliente El cliente asociado a la entrada
     */
    public void setCliente(Cliente cliente) {
        this.cliente = cliente;
    }
}