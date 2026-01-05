package galeria.obra;

import org.junit.Assert;
import org.junit.Test;

import galeria.sala.*;
import static org.junit.Assert.assertEquals;
import static org.junit.jupiter.api.Assertions.*;

public class FisicaTest {

    @Test
    public void testhumedadEnRango() {
        SalaRaiz sala = new SalaRaiz();
        sala.setHumedad(50.0);

        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, true, true);

        boolean result = fisica.humedadEnRango(sala.getHumedad());

        Assert.assertTrue(result);
    }

    @Test
    public void testtemperaturaEnRango() {
        SalaRaiz sala = new SalaRaiz();
        sala.setTemperatura(25.0);

        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, true, true);

        boolean result = fisica.temperaturaEnRango(sala.getTemperatura());

        Assert.assertTrue(result);
    }

    @Test
    public void testcabeEn() {
        Sala sala = new SalaRaiz(20.0, 20.0, 20.0);

        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, true, true);

        boolean result = fisica.cabeEn(sala);

        Assert.assertTrue(result);
    }

    @Test
    public void testcabeEnGoesWrong() {
        Sala sala = new SalaRaiz(5.0, 5.0, 5.0);
        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, true, true);
        assertEquals(false, fisica.cabeEn(sala));
    }

    @Test
    public void testExponerInvalidHumedad() {
        SalaRaiz sala = new SalaRaiz();
        sala.setHumedad(30.0);

        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, true, true);

        assertThrows(InvalidHumidityConditions.class, () -> {
            fisica.exponerEn(sala);
        });
    }

    @Test
    public void testExponerInvalidTemperatura() {
        SalaRaiz sala = new SalaRaiz();
        sala.setTemperatura(10.0);

        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, true, false);

        assertThrows(InvalidTemperatureConditions.class, () -> {
            fisica.exponerEn(sala);
        });
    }

    @Test
    public void testExponerWithValidConditions() throws ObraExceptions {
        SalaRaiz sala = new SalaRaiz(20.0, 20.0, 20.0);
        sala.setHumedad(50.0);
        sala.setTemperatura(25.0);

        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, true, true);

        fisica.exponerEn(sala);

        // Assert that the Exponer method does not throw an exception
        assertEquals(sala, fisica.getSala());
        assertEquals(EstadoObra.EXPOSICION, fisica.getEstado());
    }

    @Test // (expected = IllegalArgumentException.class)
    public void testExponerWithInsufficientSpace() {
        SalaRaiz sala = new SalaRaiz(5.0, 5.0, 5.0);

        Fisica fisica = new Escultura(10.0, 10.0, 10.0, 20.0, 30.0, 40.0, 60.0, false, false);

        assertThrows(InvalidDimensionConditions.class, () -> {
            fisica.exponerEn(sala);
        });
        // Expecting IllegalArgumentException to be thrown
    }

}
