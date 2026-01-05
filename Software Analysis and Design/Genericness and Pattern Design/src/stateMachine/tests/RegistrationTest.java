package stateMachine.tests;

import org.junit.jupiter.api.Test;

import stateMachine.*;

/**
 * Clase de prueba JUnit para los métodos añadidos en la clase Registration.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public class RegistrationTest {
    /**
     * Inscripciones de prueba.
     */
    private Registration annSmith, johnDoe, lisaMartin;
    
    /**
     * Constructor por defecto.
     */
    public RegistrationTest() {
    }

    /**
     * Prueba para el método equals.
     */
    @Test
    void testEquals() {
        annSmith = new Registration("Ann Smith", RegistrationKind.STUDENT);
        johnDoe = new Registration("John Doe", RegistrationKind.MEMBER);
        lisaMartin = new Registration("Lisa Martin", RegistrationKind.STUDENT);

        assert annSmith.equals(annSmith);
        assert !annSmith.equals(johnDoe);
        assert !annSmith.equals(lisaMartin);
    }
}
