package mensaje;

import java.io.Serializable;

/**
 * Clase que representa una notificación.
 * Esta clase implementa la interfaz Serializable para permitir la serialización
 * de objetos Notificacion.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Notificacion implements Serializable {

    /**
     * Asunto de la notificación.
     */
    private String asunto;

    /**
     * Texto de la notificación.
     */
    private String texto;

    /**
     * Identificador único para la serialización de objetos Notificacion.
     */
    private static final long serialVersionUID = 1L;

    /**
     * Constructor de la clase Notificacion.
     * 
     * @param asunto el asunto de la notificación
     * @param texto  el texto de la notificación
     */
    public Notificacion(String asunto, String texto) {
        this.asunto = asunto;
        this.texto = texto;
    }

    /**
     * Obtiene el asunto de la notificación.
     * 
     * @return el asunto de la notificación
     */
    public String getAsunto() {
        return asunto;
    }

    /**
     * Obtiene el texto de la notificación.
     * 
     * @return el texto de la notificación
     */
    public String getTexto() {
        return texto;
    }

    /**
     * Obtiene el nombre del autor de la notificación.
     * 
     * @return el nombre del autor de la notificación
     */
    public String getNombreAutor() {
        return "Sistema";
    }

    /**
     * Devuelve una representación en forma de cadena de la notificación.
     * 
     * @return una cadena que representa la notificación
     */
    @Override
    public String toString() {
        return "Notificacion{" +
                "asunto='" + asunto + '\'' +
                ", texto='" + texto + '\'' +
                '}';
    }
}