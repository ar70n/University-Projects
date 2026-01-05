package usuario;

import static org.junit.jupiter.api.Assertions.*;

import java.time.LocalDateTime;
import java.util.HashSet;

import org.junit.jupiter.api.Test;

import galeria.exposicion.*;
import galeria.sala.SalaRaiz;
import mensaje.*;
import sistema.Sistema;
import descuento.*;
import entrada.*;

class ClienteTest {

    @Test
    void testapuntarseSorteo() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");
        SorteoActivo sorteo = new SorteoActivo(10, 2, LocalDateTime.now().plusDays(1), LocalDateTime.now(), LocalDateTime.now().plusDays(2), new Temporal("Exposicion 1", "Descripcion", LocalDateTime.now(), LocalDateTime.now().plusDays(1)));

        // Caso de prueba 1: El cliente no está penalizado y no está registrado en el sorteo
        assertDoesNotThrow(() -> cliente.apuntarseSorteo(sorteo, 1));

        // Caso de prueba 2: El cliente está penalizado
        cliente.setFechaPenalizacion(LocalDateTime.now().plusDays(1));
        assertThrows(IllegalArgumentException.class, () -> cliente.apuntarseSorteo(sorteo, 1));

        // Caso de prueba 3: El cliente ya está registrado en el sorteo
        cliente.setFechaPenalizacion(null);
        assertThrows(IllegalArgumentException.class, () -> cliente.apuntarseSorteo(sorteo, 1));
    }

    @Test
    void testrecibirRegalo() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");
        Regalo regalo = new Regalo("0", LocalDateTime.now(), LocalDateTime.now().plusDays(1), 1, new Temporal("Exposicion 1", "Descripcion", LocalDateTime.now(), LocalDateTime.now().plusDays(1)));

        // Caso de prueba: El cliente recibe un regalo
        cliente.recibirRegalo(regalo);
        assertTrue(cliente.getRegalos().contains(regalo), "Debería contener el regalo");
    }

    @Test
    void testcomprarEntrada() {
        @SuppressWarnings("unused")
        Sistema	sistema = Sistema.getInstance();
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");
        Exposicion exposicion = new Temporal("Exposicion 1", "Descripcion", LocalDateTime.now(), LocalDateTime.now().plusDays(1));
        SalaRaiz sala = new SalaRaiz(10, 10, 10, 5.00, 50.00, true);
        sala.setAforo(10);
        exposicion.addSala(sala);
        exposicion.publicar();
        Visita visita = new Visita(LocalDateTime.now().plusHours(1), exposicion);
        HashSet<String> codigos = new HashSet<>();

        // Caso de prueba 1: Todos los parámetros son válidos
        assertDoesNotThrow(() -> cliente.comprarEntrada(exposicion, visita, 1, "1234567890123456", codigos));

        // Caso de prueba 2: El número de entradas es menor o igual a 0
        assertThrows(IllegalArgumentException.class, () -> cliente.comprarEntrada(exposicion, visita, 0, "1234567890123456", codigos));

        // Caso de prueba 3: La exposición aún no ha comenzado
        Exposicion exposicion2 = new Temporal("Exposicion 2", "Descripcion", LocalDateTime.now().plusDays(2), LocalDateTime.now().plusDays(12));
        assertThrows(IllegalArgumentException.class, () -> cliente.comprarEntrada(exposicion2, visita, 1, "1234567890123456", codigos));

        // Caso de prueba 4: La exposición no está publicada
        Exposicion exposicion3 = new Temporal("Exposicion 3", "Descripcion", LocalDateTime.now(), LocalDateTime.now().plusDays(10));
        assertThrows(IllegalArgumentException.class, () -> cliente.comprarEntrada(exposicion3, visita, 1, "1234567890123456", codigos));

        // Caso de prueba 5: No hay suficiente capacidad disponible
        sala.setAforo(0);
        Visita visita2 = new Visita(LocalDateTime.now().plusDays(1), exposicion);
        assertThrows(IllegalArgumentException.class, () -> cliente.comprarEntrada(exposicion, visita2, 10, "1234567890123456", codigos));
    }

    @Test
    void testsetRecibeNotificaciones() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");

        // Caso de prueba 1: Establecer recibeNotificaciones en falso
        cliente.setRecibeNotificaciones(false);
        assertFalse(cliente.getRecibeNotificaciones(), "Debería establecer recibeNotificaciones en falso");

        // Caso de prueba 2: Establecer recibeNotificaciones en verdadero
        cliente.setRecibeNotificaciones(true);
        assertTrue(cliente.getRecibeNotificaciones(), "Debería establecer recibeNotificaciones en verdadero");
    }

    @Test
    void testrecibirNotificacion() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");
        Notificacion notificacion = new Notificacion("Notificacion 1", "Contenido");

        // Caso de prueba 1: El cliente recibe notificaciones
        cliente.setRecibeNotificaciones(true);
        cliente.recibirNotificacion(notificacion);
        assertTrue(cliente.getNotificaciones().contains(notificacion), "Debería contener la notificación");

        // Caso de prueba 2: El cliente no recibe notificaciones
        cliente.setRecibeNotificaciones(false);
        Notificacion notificacion2 = new Notificacion("Notificacion 2", "Contenido");
        cliente.recibirNotificacion(notificacion2);
        assertFalse(cliente.getNotificaciones().contains(notificacion2), "No debería contener la notificación");
    }

    @Test
    void testeditarPerfil() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");

        // Caso de prueba: Editar perfil
        cliente.editarPerfil("Nuevo Cliente", "nuevoPassword");
        assertEquals("Nuevo Cliente", cliente.getNombre(), "Debería establecer nombre a Nuevo Cliente");
        assertEquals("nuevoPassword", cliente.getContrasena(), "Debería establecer contrasena a nuevoPassword");
    }

    @Test
    void testpagar() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");

        // Caso de prueba 1: Todos los parámetros son válidos
        assertDoesNotThrow(() -> cliente.pagar(10.00, "1234567890123456"));

        // Caso de prueba 2: El número de tarjeta no es válido
        assertThrows(IllegalArgumentException.class, () -> cliente.pagar(10.00, "123456789012345"));
    }

    @Test
    void testgetTipoUsuario() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");
        assertEquals("Cliente", cliente.getTipoUsuario(), "Debería devolver Cliente");
    }

    @Test
    void testToString() {
        Cliente cliente = new Cliente("12345678A", "Cliente", "password1");
        String expected = "Cliente [recibeNotificaciones=false, fechaPenalizacion=null, regalos=[], nif=12345678A, nombre=Cliente, contrasena=password1]";
        assertEquals(expected, cliente.toString(), "Debería devolver la representación de cadena correcta");
    }
}