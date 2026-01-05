package stateMachine.tests;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.util.function.Predicate;

import stateMachine.*;
import stateMachine.IllegalStateException;

/**
 * Clase de prueba JUnit para los métodos añadidos en la clase ObjectStateTracker.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public class ObjectStateTrackerTest {
    /**
     * Tracker de estados de inscripciones.
     */
    private ObjectStateTracker<Registration, RegistrationState> regState;

    /**
     * Constructor por defecto.
     */
    public ObjectStateTrackerTest() {
    }

    /**
     * Inicialización de los atributos.
     */
    @BeforeEach
    void setUp() {
        regState = new ObjectStateTracker<>(RegistrationState.values());
    }

    /**
     * Prueba para el método withState.
     */
    @Test
    void testWithState() {
        Predicate<Registration> predicate = r -> r.getAmountPayed() == 0 && r.getValidated();
        try {
            regState.withState(RegistrationState.VALIDATED, predicate);
        } catch (IllegalStateException e) {
            fail("No debería lanzar excepción.");
        }

        assertTrue(regState.getStateLambda().containsKey(RegistrationState.VALIDATED));
        assertEquals(predicate, regState.getStateLambda().get(RegistrationState.VALIDATED));
    }

    /**
     * Prueba para el método elseState.
     */
    @Test
    void testElseState() {
        try {
            regState.elseState(RegistrationState.REJECTED);
        } catch (IllegalStateException e) {
            fail("No debería lanzar excepción.");
        }

        assertTrue(regState.getStateLambda().containsKey(RegistrationState.REJECTED));
        assertTrue(regState.getStateLambda().get(RegistrationState.REJECTED)
                .test(new Registration("Test", RegistrationKind.FULL)));
    }

    /**
     * Prueba para el método updateStates.
     */
    @Test
    void testUpdateState() {
        Registration registration = new Registration("Test", RegistrationKind.STUDENT);
        try {regState.withState(RegistrationState.PAYED, r -> r.getAmountPayed()==r.getTotalAmount() && !r.getValidated())
                .withState(RegistrationState.STARTED, r -> r.getAffiliation()==null && !r.getValidated())
                .elseState(RegistrationState.REJECTED);
        } catch (IllegalStateException e) {
            fail("No debería lanzar excepción.");
        }
        regState.addObjects(registration);

        assertTrue(regState.getStatesObjects().get(RegistrationState.STARTED).contains(registration));

        registration.pay(RegistrationKind.STUDENT.getPrice());
        regState.updateStates();

        assertTrue(regState.getStatesObjects().get(RegistrationState.PAYED).contains(registration));
    }

    /**
     * Prueba para el método addObjects.
     */
    @Test
    void testAddObjects() {
        Registration registration = new Registration("Test", RegistrationKind.FULL);
        try {
            regState.withState(RegistrationState.STARTED, r -> r.getAffiliation() == null && !r.getValidated())
                    .elseState(RegistrationState.REJECTED);
        } catch (IllegalStateException e) {
            fail("No debería lanzar excepción.");
        }  
        regState.addObjects(registration);

        assertTrue(regState.getTrajectorie().containsKey(registration));
        assertEquals(registration, regState.getStatesObjects().get(RegistrationState.STARTED).get(0));
    }
}