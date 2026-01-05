package usuario;

import static org.junit.jupiter.api.Assertions.*;

import java.time.LocalDateTime;

import org.junit.jupiter.api.Test;

import galeria.sala.SalaRaiz;
import sistema.Sistema;
import galeria.exposicion.*;

import entrada.*;

class EmpleadoTest {

	@Test
	void testenviarMensaje() {
		UsuarioRegistrado usuario1 = new Cliente("12345678A", "Usuario 1", "password1");
		UsuarioRegistrado usuario2 = new Cliente("87654321B", "Usuario 2", "password2");
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);

		// Test case 1: Empleado has permission to send messages
		boolean result1 = empleado.enviarMensaje("Hola", "Asunto", usuario1, usuario2);
		assertTrue(result1, "Should return true");

		// Test case 2: Empleado does not have permission to send messages
		empleado.setPermisoMensajes(false);
		boolean result2 = empleado.enviarMensaje("Hola", "Asunto", usuario1, usuario2);
		assertFalse(result2, "Should return false");
	}

	@Test
	void testvenderEntrada() {
		// Setup
		@SuppressWarnings("unused")
		Sistema sistema = Sistema.getInstance();
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);
		Temporal temporal = new Temporal("Temporal 1", "Descripcion", LocalDateTime.now(),
				LocalDateTime.now().plusDays(1));
		SalaRaiz sala = new SalaRaiz(10, 10, 10, 5.00, 50.00, true);
		sala.setAforo(10);
		temporal.addSala(sala);
		temporal.publicar();
		Visita visita = new Visita(LocalDateTime.now().plusHours(12), temporal);

		// Test case 1: El empleado tiene permiso para vender entradas y todos los parametros son válido
		assertDoesNotThrow(() -> empleado.venderEntrada(temporal, visita, 10));

		// Test case 2: El empleado no tiene permiso para vender entradas
		empleado.setPermisoVenta(false);
		assertThrows(IllegalArgumentException.class, () -> empleado.venderEntrada(temporal, visita, 10));

		// Test case 3: The number of tickets is less than or equal to 0
		assertThrows(IllegalArgumentException.class, () -> empleado.venderEntrada(temporal, visita, 0));

		// Test case 4: The exhibition has not started yet
		Temporal temporal2 = new Temporal("Temporal 2", "Descripcion", LocalDateTime.now().plusDays(2),
				LocalDateTime.now().plusDays(12));
		assertThrows(IllegalArgumentException.class, () -> empleado.venderEntrada(temporal2, visita, 10));

		// Test case 5: The exhibition is not published
		Temporal temporal3 = new Temporal("Temporal 3", "Descripcion", LocalDateTime.now(),
				LocalDateTime.now().plusDays(10));
		assertThrows(IllegalArgumentException.class, () -> empleado.venderEntrada(temporal3, visita, 10));

		// Test case 6: There is not enough capacity available
		Visita visita2 = new Visita(LocalDateTime.now().plusDays(1), temporal);
		assertThrows(IllegalArgumentException.class, () -> empleado.venderEntrada(temporal, visita2, 10));
	}

	@Test
	void testsetPermisoMensajes() {
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);

		// Test case 1: Set permission to false
		empleado.setPermisoMensajes(false);
		assertFalse(empleado.getPermisoMensajes(), "Should set mensajes to false");

		// Test case 2: Set permission to true
		empleado.setPermisoMensajes(true);
		assertTrue(empleado.getPermisoMensajes(), "Should set mensajes to true");
	}

	@Test
	void testsetPermisoRegulacion() {
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);

		// Test case 1: Set permission to false
		empleado.setPermisoRegulacion(false);
		assertFalse(empleado.getPermisoRegulacion(), "Should set temperaturaHumedad to false");

		// Test case 2: Set permission to true
		empleado.setPermisoRegulacion(true);
		assertTrue(empleado.getPermisoRegulacion(), "Should set temperaturaHumedad to true");
	}

	@Test
	void testsetPermisoVenta() {
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);

		// Test case 1: Set permission to false
		empleado.setPermisoVenta(false);
		assertFalse(empleado.getPermisoVenta(), "Should set venta to false");

		// Test case 2: Set permission to true
		empleado.setPermisoVenta(true);
		assertTrue(empleado.getPermisoVenta(), "Should set venta to true");
	}

	@Test
	void testsetContrasenaEmpleados() {
		Empleado.setContrasenaEmpleados("newPassword");
		assertEquals("newPassword", Empleado.getContrasenaEmpleado(), "Should set contrasenaEmpleado to newPassword");
	}

	@Test
	void testcambiarTemperatura() {
		// Setup
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);
		SalaRaiz sala = new SalaRaiz(10, 10, 10, 5.00, 50.00, true);

		// Test case 1: Employee has permission to regulate temperature, and the new
		// temperature is within the valid range
		assertDoesNotThrow(() -> empleado.cambiarTemperatura(20.00, sala));

		// Test case 2: Employee does not have permission to regulate temperature
		empleado.setPermisoRegulacion(false);
		assertThrows(IllegalArgumentException.class, () -> empleado.cambiarTemperatura(20.00, sala));

		// Test case 3: The new temperature is below the minimum allowed value
		assertThrows(IllegalArgumentException.class, () -> empleado.cambiarTemperatura(-10.00, sala));

		// Test case 4: The new temperature is above the maximum allowed value
		assertThrows(IllegalArgumentException.class, () -> empleado.cambiarTemperatura(100.00, sala));
	}

	@Test
	void testcambiarHumedad() {
		// Setup
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);
		SalaRaiz sala = new SalaRaiz(10, 10, 10);
		sala.setRegulable(true);

		// Test case 1: Employee has permission to regulate humidity, and the new
		// humidity is within the valid range
		assertDoesNotThrow(() -> empleado.cambiarHumedad(50.00,sala));

		// Test case 2: Employee does not have permission to regulate humidity
		empleado.setPermisoRegulacion(false);
		assertThrows(IllegalArgumentException.class, () -> empleado.cambiarHumedad(50.00, sala));

		// Test case 3: The new humidity is below the minimum allowed value
		assertThrows(IllegalArgumentException.class, () -> empleado.cambiarHumedad(-10.00, sala));

		// Test case 4: The new humidity is above the maximum allowed value
		assertThrows(IllegalArgumentException.class, () -> empleado.cambiarHumedad(110.00, sala));
	}

	@Test
	void testgetTipoUsuario() {
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);
		assertEquals("Empleado", empleado.getTipoUsuario(), "Should return Empleado");
	}

	@Test
	void testgetContrasena() {
		Empleado.setContrasenaEmpleados("password");
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);
		assertEquals("password", empleado.getContrasena(), "Should return password");
	}     

	@Test
	void testToString() {
		Empleado empleado = new Empleado("11223344C", "Empleado", "cuenta", "direccion", "123456789", true, true, true);
		String expected = "Empleado [Cuenta=cuenta, Direccion=direccion, SeguridadSocial=123456789, Mensajes=true, TemperaturaHumedad=true, Venta=true]";
		assertEquals(expected, empleado.toString(), "Should return correct string representation");
	}
}