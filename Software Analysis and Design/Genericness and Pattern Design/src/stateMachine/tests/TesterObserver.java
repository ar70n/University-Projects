package stateMachine.tests;

import stateMachine.*;

/**
 * Clase de prueba para el quinto apartado de la práctica.
 * 
 * @author EPS
 * @version 1.0
 */
public class TesterObserver extends TesterStateChanges {
    /**
     * Constructor por defecto.
     */
    public TesterObserver() {
        super();
    }

    /**
     * Método principal de la clase.
     * 
     * @param args Argumentos de la línea de comandos.
     */
    public static void main(String[] args) {
        TesterObserver tsc = new TesterObserver();
        tsc.createRegistrations();
        Registration.withTracker(tsc.regState);
        System.out.println(tsc.regState);
        tsc.changeRegistrations();
        System.out.println(tsc.regState);
    }

    /**
     * Método que cambia los estados de las inscripciones.
     */
    @Override
    protected void changeRegistrations() {
        this.annSmith.setAffiliation("University of Miskatonic"); // now it is filled
        this.johnDoe.pay(RegistrationKind.STUDENT.getPrice()); // becomes payed
        // regState.updateStates(); // not needed anymore
    }
}