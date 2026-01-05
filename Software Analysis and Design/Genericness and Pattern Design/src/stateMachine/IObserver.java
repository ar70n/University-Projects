package stateMachine;

/**
 * Interfaz observadora que permite actualizar los estados.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public interface IObserver<T> {
    /**
     * Método que actualiza los estados.
     */
    public void updateStates();
}
