package stateMachine.tests;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.Arrays;
import java.util.List;

import org.junit.jupiter.api.Test;

import stateMachine.Process;
import stateMachine.*;

/**
 * Clase de prueba JUnit para los métodos añadidos en la clase Process.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * @version 1.0
 */
public class ProcessTest {
    /**
     * Proceso de inscripción para la prueba.
     */
    private Process<RegistrationState> process;

    /**
     * Constructor por defecto.
     */
    public ProcessTest() {
    }

    /**
     * Prueba para el método add.
     */
    @Test
    void testAdd() {
        process = new Process<>(RegistrationState.values());
        List<String> trajectory = Arrays.asList("(in: STARTED at: 2024-03-30T19:22:33.494979900)",
                "(from: STARTED to PAYED at: 2024-03-30T19:22:33.494979900)",
                "(from: PAYED to FINISHED at: 2024-03-30T19:22:33.494979900)");
        process.add(trajectory);
        String expectedOutput = "STARTED (initial 1 times, final 0 times):\n" +
                "  to state PAYED: 1 times\n" +
                "FILLED (initial 0 times, final 0 times):\n" +
                "VALIDATED (initial 0 times, final 0 times):\n" +
                "PAYED (initial 0 times, final 0 times):\n" +
                "  to state FINISHED: 1 times\n" +
                "FINISHED (initial 0 times, final 1 times):\n" +
                "REJECTED (initial 0 times, final 0 times):\n";

        assertEquals(expectedOutput, process.toString());
    }
}