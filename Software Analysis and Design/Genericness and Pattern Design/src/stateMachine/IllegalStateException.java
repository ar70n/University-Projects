package stateMachine;

/**
 * Excepción lanzada cuando un estado no es válido.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public class IllegalStateException extends Exception {
    /**
     * Mensaje de la excepción.
     */
    private String msg;

    /**
     * Constructor de la excepción.
     * 
     * @param msg Mensaje de la excepción.
     */
    public IllegalStateException(String msg) {
        this.msg = msg;
    }

    /**
     * Devuelve el mensaje de la excepción.
     * 
     * @return Mensaje de la excepción.
     */
    @Override
    public String toString() {
        return msg;
    }
}
