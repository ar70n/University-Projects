package galeria.exposicion;

import static org.junit.jupiter.api.Assertions.*;
import java.time.LocalDateTime;
import galeria.sala.*;
import sistema.Sistema;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

class TemporalTest {
    LocalDateTime inicio, fin;
    Temporal t;

    @BeforeEach
    @SuppressWarnings("unused")
    public void setUp() {
        Sistema sistema = Sistema.getInstance();
        inicio = LocalDateTime.now();
        fin = inicio.plusDays(10);
        t = new Temporal("Exposicion temporal", "Descripcion de la exposicion temporal", inicio, fin);
        t.addSala(new SalaRaiz());
        t.publicar();
    }

    @Test
    public void testProlongarInvalidDate() {
        LocalDateTime newFin = fin.minusDays(5);
        assertThrows(IllegalArgumentException.class, () -> t.Prolongar(newFin));
    }

    @Test
    public void testgetEstado() {
        EstadoExp expectedState = EstadoExp.COMENZADA;
        assertEquals(expectedState, t.getEstado());
    }

    @Test
    public void testEsPermanente() {
        //assertFalse(t.esPermanente());
        assertEquals(t.esPermanente(), false);
    }

    @Test
    public void testaddObraCheck() {
        // Teesteamos todos los casos
        boolean propiedad = false;
        Temporal temporal = new Temporal();
        temporal.setEstado(EstadoExp.ENCREACION);
        assertTrue(temporal.addObraCheck(propiedad));

        temporal.setEstado(EstadoExp.COMENZADA);
        assertFalse(temporal.addObraCheck(propiedad));

        propiedad = true;
        temporal.setEstado(EstadoExp.ENCREACION);
        assertFalse(temporal.addObraCheck(propiedad));
    }

    @Test
    public void testremoveObraCheck() {
        Temporal temporal = new Temporal();

        temporal.setEstado(EstadoExp.ENCREACION);
        assertTrue(temporal.removeObraCheck());

        temporal.setEstado(EstadoExp.COMENZADA);
        assertFalse(temporal.removeObraCheck());

        temporal.setEstado(EstadoExp.PUBLICADA);
        assertFalse(temporal.removeObraCheck());
    }

    @Test
    public void testrestaurarObraCheck() {
        Temporal temporal = new Temporal();

        temporal.setEstado(EstadoExp.ENCREACION);
        assertTrue(temporal.restaurarObraCheck());

        temporal.setEstado(EstadoExp.COMENZADA);
        assertFalse(temporal.restaurarObraCheck());

        temporal.setEstado(EstadoExp.PUBLICADA);
        assertTrue(temporal.restaurarObraCheck());
    }

}
