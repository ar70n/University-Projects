package galeria;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class Vector3Test {

    /*
     * @Test
     * void testCambiarEstado() {
     * fail("Not yet implemented");
     * }
     * 
     * @Test
     * void testExponer() {
     * fail("Not yet implemented");
     * }
     */
    @Test
    void testgetX() {
        Vector3 vector = new Vector3(5, 10, 15);
        assertEquals(5, vector.getX());
    }

    @Test
    void testgetY() {
        Vector3 vector = new Vector3(5, 10, 15);
        assertEquals(10, vector.getY());
    }

    @Test
    void testgetZ() {
        Vector3 vector = new Vector3(5, 10, 15);
        assertEquals(15, vector.getZ());
    }

    @Test
    void testsetDimensiones() {
        Vector3 vector = new Vector3();
        vector.setDimensiones(5, 10, 15);
        assertEquals(5, vector.getX());
        assertEquals(10, vector.getY());
        assertEquals(15, vector.getZ());
    }

    @Test
    void testsetDimensiones_InvalidDimensions() {
        Vector3 vector = new Vector3();
        assertThrows(IllegalArgumentException.class, () -> {
            vector.setDimensiones(-5, 10, 15);
        });
    }

    @Test
    void testvolumen() {
        Vector3 vector = new Vector3(5, 10, 15);
        assertEquals(750, vector.volumen());
    }
}