package mensaje;

import usuario.*;

/**
 * Clase que representa un mensaje de notificación.
 * Extiende la clase Notificacion.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Mensaje extends Notificacion {
    private static final long serialVersionUID = 1L;
    private Empleado autor;

    /**
     * Constructor de la clase Mensaje.
     * 
     * @param autor  el empleado que envía el mensaje
     * @param texto  el contenido del mensaje
     * @param asunto el asunto del mensaje
     */
    public Mensaje(Empleado autor, String texto, String asunto) {
        super(asunto, texto);
        this.autor = autor;
    }

    /**
     * Obtiene el autor del mensaje.
     * 
     * @return el empleado que envía el mensaje
     */
    public Empleado getAutor() {
        return autor;
    }

    /**
     * Obtiene el nombre del autor del mensaje.
     * 
     * @return el nombre del empleado que envía el mensaje
     */
    public String getNombreAutor() {
        return autor.getNombre();
    }

    /**
     * Devuelve una representación en cadena del mensaje.
     * 
     * @return una cadena que representa el mensaje
     */
    @Override
    public String toString() {
        return "Mensaje{" +
                "autor=" + autor +
                super.toString() + '\'' +
                '}';
    }
}
