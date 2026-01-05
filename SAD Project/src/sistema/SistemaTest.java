package sistema;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import galeria.obra.*;
import mensaje.Notificacion;
import usuario.*;

class SistemaTest {

    @Test
    void testGetInstance() {
        // Prueba para verificar que siempre se obtiene la misma instancia del sistema
        Sistema sistema1 = Sistema.getInstance();
        Sistema sistema2 = Sistema.getInstance();
        assertEquals(sistema1, sistema2, "Debe devolver la misma instancia");
    }

    @Test
	@SuppressWarnings("unused")
    void testLogin() {
        // Prueba para verificar el inicio de sesión de un usuario
        Sistema sistema = Sistema.getInstance();
        UsuarioRegistrado usuario = new Cliente("12345678A", "Usuario", "password1");
        Sistema.addUsuarios(usuario);
        assertNotNull(Sistema.login("12345678A", "password1"), "Debe devolver el usuario");
        assertNull(Sistema.login("12345678A", "wrongPassword"), "Debe devolver null");
    }

    @Test
	@SuppressWarnings("unused")
    void testEnviarMensaje() {
        // Prueba para verificar el envío de mensajes a un usuario
        Sistema sistema = Sistema.getInstance();
        Cliente usuario = new Cliente("12345678A", "Usuario", "password1");
		usuario.setRecibeNotificaciones(true);
        Sistema.addUsuarios(usuario);
        Sistema.enviarMensaje("Test", "This is a test", usuario);
        for (Notificacion notificacion : usuario.getNotificaciones()){
			System.out.println(notificacion.getAsunto());
			assertEquals("Test", notificacion.getAsunto(), "Debe enviar el mensaje");
		}
		assertEquals(1, usuario.getNotificaciones().size(), "Debe enviar el mensaje");
    }

    @Test
    void testBuscarObra() {
        // Prueba para verificar la búsqueda de una obra por su nombre
        Sistema sistema = Sistema.getInstance();
        Obra obra = new Audiovisual("Obra1");
        Sistema.addObras(obra);
        assertNotNull(sistema.buscarObra("Obra1"), "Debe devolver la obra");
        assertNull(sistema.buscarObra("Obra2"), "Debe devolver null");
    }

    @Test
	@SuppressWarnings("unused")
    void testGuardarSistema() {
        // Prueba para verificar que no se lanza ninguna excepción al guardar el sistema
        Sistema sistema = Sistema.getInstance();
        assertDoesNotThrow(() -> Sistema.guardarSistema(), "No debe lanzar ninguna excepción");
    }

    @Test
	@SuppressWarnings("unused")
    void testCargarSistema() {
        // Prueba para verificar que no se lanza ninguna excepción al cargar el sistema
        Sistema sistema = Sistema.getInstance();
        assertDoesNotThrow(() -> Sistema.cargarSistema(), "No debe lanzar ninguna excepción");
    }
}