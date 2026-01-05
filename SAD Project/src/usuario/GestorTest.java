package usuario;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.time.LocalDateTime;
import sistema.Sistema;
import descuento.*;
import galeria.exposicion.*;
import galeria.obra.Cuadro;

class GestorTest {

    @Test
    void testcrearSorteo() {
        Gestor gestor = new Gestor();
        Exposicion expo = new Permanente();
        LocalDateTime now = LocalDateTime.now();
        SorteoActivo sorteo = gestor.crearSorteo(expo, 10, 2, now.plusDays(1), now, now.plusDays(2));

        // Test 1: Verificar que se crea un SorteoActivo con los parámetros correctos.
        assertEquals(10, sorteo.getPenalizacion());
        assertEquals(2, sorteo.getEntradas());
        assertEquals(now.plusDays(1), sorteo.getFinSorteo());
        assertEquals(now, sorteo.getValidezInicio());
        assertEquals(now.plusDays(2), sorteo.getValidezFinal());
        assertEquals(expo, sorteo.getExposicion());

        // Test 2: Verificar que el SorteoActivo se agrega al sistema.
        assertTrue(Sistema.getSorteos().contains(sorteo));

        // Test 3: Verificar que la función maneja correctamente los casos en los que se
        // pasan parámetros inválidos.
        // Esto dependerá de cómo esté implementado tu método crearSorteo y qué esperas
        // que haga en estos casos.
        // Por ejemplo, si esperas que lance una excepción, podrías hacer algo como
        // esto:
        assertThrows(IllegalArgumentException.class, () -> {
            gestor.crearSorteo(expo, -10, 100, now.plusDays(1), now, now.plusDays(2));
        });
    }

    // Para testear el funcionamiento de la funcion sortear basta con testeat la
    // funcion darRegalos de la clase SorteoActivo

    @Test
    void testcrearExposicionPermanente() {
        // Test case 1: Valid input
        String nombre1 = "Exposicion1";
        String descripcion1 = "Esta es una exposicion permanente";
        LocalDateTime apertura1 = LocalDateTime.of(2022, 1, 1, 10, 0);
        Gestor gestor = new Gestor();
        Permanente exposicion1 = gestor.crearExposicionPermanente(nombre1, descripcion1, apertura1);
        assertEquals(nombre1, exposicion1.getNombre());
        assertEquals(descripcion1, exposicion1.getDescripcion());
        assertEquals(apertura1, exposicion1.getFechaInicio());
        assertTrue(Sistema.getExposiciones().contains(exposicion1));

        // Test case 2: Empty nombre
        String nombre2 = "";
        String descripcion2 = "Esta es una exposicion permanente";
        LocalDateTime apertura2 = LocalDateTime.of(2022, 1, 1, 10, 0);
        assertThrows(IllegalArgumentException.class, () -> {
            gestor.crearExposicionPermanente(nombre2, descripcion2, apertura2);
        });

        // Test case 3: Null descripcion
        String nombre3 = "Exposicion3";
        String descripcion3 = null;
        LocalDateTime apertura3 = LocalDateTime.of(2022, 1, 1, 10, 0);
        assertThrows(IllegalArgumentException.class, () -> {
            gestor.crearExposicionPermanente(nombre3, descripcion3, apertura3);
        });

    }

    @Test
    void testcrearExposicionTemporal() {
        Gestor gestor = new Gestor();
        LocalDateTime now = LocalDateTime.now();
        Temporal expo = gestor.crearExposicionTemporal("Expo", "Descripcion", now, now.plusDays(1));

        // Test 1: Verificar que se crea una ExposicionTemporal con los parámetros
        // correctos.
        assertEquals("Expo", expo.getNombre());
        assertEquals("Descripcion", expo.getDescripcion());
        assertEquals(now, expo.getFechaInicio());
        assertEquals(now.plusDays(1), expo.getFechaFin());

        // Test 2: Verificar que la ExposicionTemporal se agrega al sistema.
        assertTrue(Sistema.getExposiciones().contains(expo));

        // Test 3: Verificar que la función maneja correctamente los casos en los que se
        // pasan parámetros inválidos.
        // Esto dependerá de cómo esté implementado tu método crearExposicionTemporal y
        // qué esperas que haga en estos casos.
        // Por ejemplo, si esperas que lance una excepción, podrías hacer algo como
        // esto:
        assertThrows(IllegalArgumentException.class, () -> {
            gestor.crearExposicionTemporal(null, "Descripcion", now, now.plusDays(1));
        });
        assertThrows(IllegalArgumentException.class, () -> {
            gestor.crearExposicionTemporal("Expo", null, now, now.plusDays(1));
        });
        assertThrows(IllegalArgumentException.class, () -> {
            gestor.crearExposicionTemporal("Expo", "Descripcion", now, now.minusDays(1));
        });
    }

@Test
void testRegistrarObra() {
    // Test case 1: Registering a cuadro with valid parameters
    Sistema.getInstance();
    Gestor gestor = new Gestor();
    Cuadro cuadro1 = gestor.registrarCuadro("Cuadro1", "Autor1", 2022, "Description1", 1000.0, "Poliza1", true, 20.0, 25.0, 40.0, 60.0, true, true, 50.0, 60.0, 5.0, "Tecnica1");
    assertNotNull(cuadro1);
    assertEquals("Cuadro1", cuadro1.getNombre());
    assertEquals("Autor1", cuadro1.getAutor());
    assertEquals(2022, cuadro1.getFecha());
    assertEquals("Description1", cuadro1.getDescripcion());
    assertEquals(1000.0, cuadro1.getSeguroCuantia());
    assertEquals("Poliza1", cuadro1.getSeguroPoliza());
    assertTrue(cuadro1.getPropiedad());
    assertEquals(20.0, cuadro1.getTemperaturaMin());
    assertEquals(25.0, cuadro1.getTemperaturaMax());
    assertEquals(40.0, cuadro1.getHumedadMin());
    assertEquals(60.0, cuadro1.getHumedadMax());
    assertTrue(cuadro1.isRequiereTemp());
    assertTrue(cuadro1.isRequiereHum());
    assertEquals(50.0, cuadro1.getDimensiones().getX());
    assertEquals(60.0, cuadro1.getDimensiones().getY());
    assertEquals(5.0, cuadro1.getDimensiones().getZ());
    assertEquals("Tecnica1", cuadro1.getTecnica());
    assertTrue(Sistema.getObras().contains(cuadro1));

    // // Test case 2: Registering a cuadro with invalid parameters
    // assertThrows(IllegalArgumentException.class, () -> {
    //     registrarCuadro(null, "Autor2", 2023, "Description2", 2000.0, "Poliza2", true, 15.0, 30.0, 50.0, 70.0, true, true, 40.0, 70.0, 10.0, "Tecnica2");
    // });
    // assertThrows(IllegalArgumentException.class, () -> {
    //     registrarCuadro("Cuadro2", null, 2024, "Description3", 3000.0, "Poliza3", true, 10.0, 20.0, 30.0, 40.0, true, true, 30.0, 40.0, 15.0, "Tecnica3");
    // });
    // assertThrows(IllegalArgumentException.class, () -> {
    //     registrarCuadro("Cuadro3", "Autor3", 2025, null, 4000.0, "Poliza4", true, 5.0, 10.0, 20.0, 30.0, true, true, 20.0, 30.0, 20.0, "Tecnica4");
    // });
    // assertThrows(IllegalArgumentException.class, () -> {
    //     registrarCuadro("Cuadro4", "Autor4", 2026, "Description4", -500.0, "Poliza5", true, 0.0, 5.0, 10.0, 15.0, true, true, 10.0, 20.0, 25.0, "Tecnica5");
    // });
}

}