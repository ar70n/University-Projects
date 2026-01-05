package galeria.exposicion;

import static org.junit.jupiter.api.Assertions.*;
import java.time.LocalDateTime;

import org.junit.jupiter.api.Test;

import entrada.*;

class PermanenteTest {

	@Test
	void testaddObraCheck() {
		// Test case 1: estado is ENCREACION
		Permanente permanente1 = new Permanente();
		permanente1.setEstado(EstadoExp.ENCREACION);
		boolean result1 = permanente1.addObraCheck(true);
		assertTrue(result1, "Test case 1 failed");

		// Test case 2: inicioCierre and finCierre are not null, current time is after
		// inicioCierre and before finCierre, and cierrePorRenovacion is true
		Permanente permanente2 = new Permanente();
		permanente2.setInicioCierre(LocalDateTime.now().minusHours(1));
		permanente2.setFinCierre(LocalDateTime.now().plusHours(1));
		permanente2.setCierrePorRenovacion(true);
		boolean result2 = permanente2.addObraCheck(true);
		assertTrue(result2, "Test case 2 failed");

		// Test case 3: inicioCierre and finCierre are not null, current time is after
		// inicioCierre and before finCierre, and cierrePorRenovacion is false
		Permanente permanente3 = new Permanente();
		permanente3.setInicioCierre(LocalDateTime.now().minusHours(1));
		permanente3.setFinCierre(LocalDateTime.now().plusHours(1));
		permanente3.setCierrePorRenovacion(false);
		boolean result3 = permanente3.addObraCheck(true);
		assertFalse(result3, "Test case 3 failed");

		// Test case 4: inicioCierre and finCierre are not null, current time is before
		// inicioCierre
		Permanente permanente4 = new Permanente();
		permanente4.setInicioCierre(LocalDateTime.now().plusHours(1));
		permanente4.setFinCierre(LocalDateTime.now().plusHours(2));
		boolean result4 = permanente4.addObraCheck(true);
		assertFalse(result4, "Test case 4 failed");

		// Test case 5: inicioCierre and finCierre are not null, current time is after
		// finCierre
		Permanente permanente5 = new Permanente();
		permanente5.setInicioCierre(LocalDateTime.now().minusHours(2));
		permanente5.setFinCierre(LocalDateTime.now().minusHours(1));
		boolean result5 = permanente5.addObraCheck(true);
		assertFalse(result5, "Test case 5 failed");

		// Test case 6: propiedad is false
		Permanente permanente6 = new Permanente();
		boolean result6 = permanente6.addObraCheck(false);
		assertFalse(result6, "Test case 6 failed");
	}

	@Test
	void testremoveObraCheck() {
		// Test case 1: estado is not COMENZADA or PUBLICADA
		Permanente permanente1 = new Permanente();
		permanente1.setEstado(EstadoExp.ENCREACION);
		boolean result1 = permanente1.removeObraCheck();
		assertTrue(result1, "Test case 1 failed");

		// Test case 2: estado is COMENZADA
		Permanente permanente2 = new Permanente();
		permanente2.setEstado(EstadoExp.COMENZADA);
		boolean result2 = permanente2.removeObraCheck();
		assertFalse(result2, "Test case 2 failed");

		// Test case 3: estado is PUBLICADA
		Permanente permanente3 = new Permanente();
		permanente3.setEstado(EstadoExp.PUBLICADA);
		boolean result3 = permanente3.removeObraCheck();
		assertFalse(result3, "Test case 3 failed");

		// Test case 4: inicioCierre and finCierre are not null, current time is after
		// inicioCierre and before finCierre, and cierrePorRenovacion is true
		Permanente permanente4 = new Permanente();
		permanente4.setInicioCierre(LocalDateTime.now().minusHours(1));
		permanente4.setFinCierre(LocalDateTime.now().plusHours(1));
		permanente4.setCierrePorRenovacion(true);
		boolean result4 = permanente4.removeObraCheck();
		assertTrue(result4, "Test case 4 failed");

		// Test case 5: inicioCierre and finCierre are not null, current time is after
		// inicioCierre and before finCierre, and cierrePorRenovacion is false
		Permanente permanente5 = new Permanente();
		permanente5.setInicioCierre(LocalDateTime.now().minusHours(1));
		permanente5.setFinCierre(LocalDateTime.now().plusHours(1));
		permanente5.setCierrePorRenovacion(false);
		boolean result5 = permanente5.removeObraCheck();
		assertFalse(result5, "Test case 5 failed");

		// Test case 6: inicioCierre and finCierre are not null, current time is before
		// inicioCierre
		Permanente permanente6 = new Permanente();
		permanente6.setInicioCierre(LocalDateTime.now().plusHours(1));
		permanente6.setFinCierre(LocalDateTime.now().plusHours(2));
		boolean result6 = permanente6.removeObraCheck();
		assertFalse(result6, "Test case 6 failed");

		// Test case 7: inicioCierre and finCierre are not null, current time is after
		// finCierre
		Permanente permanente7 = new Permanente();
		permanente7.setInicioCierre(LocalDateTime.now().minusHours(2));
		permanente7.setFinCierre(LocalDateTime.now().minusHours(1));
		boolean result7 = permanente7.removeObraCheck();
		assertFalse(result7, "Test case 7 failed");

		// Test case 8: inicioCierre and finCierre are null
		Permanente permanente8 = new Permanente();
		boolean result8 = permanente8.removeObraCheck();
		assertFalse(result8, "Test case 8 failed");
	}

	@Test
	void testrestaurarObraCheck() {
		// Caso 1: this.estado != EstadoExp.COMENZADA
		Permanente exposicion = new Permanente();
		exposicion.setEstado(EstadoExp.TERMINADA);
		assertTrue(exposicion.restaurarObraCheck());

		// Caso 2: this.inicioCierre != null && this.finCierre != null &&
		// LocalDateTime.now().isAfter(this.inicioCierre) &&
		// LocalDateTime.now().isBefore(this.finCierre)
		LocalDateTime inicioCierre = LocalDateTime.now().minusDays(1);
		LocalDateTime finCierre = LocalDateTime.now().plusDays(1);
		exposicion.setEstado(EstadoExp.COMENZADA);
		exposicion.setInicioCierre(inicioCierre);
		exposicion.setFinCierre(finCierre);
		assertTrue(exposicion.restaurarObraCheck());

		// Caso 3: Ninguno de los casos anteriores
		exposicion.setEstado(EstadoExp.COMENZADA);
		exposicion.setInicioCierre(null);
		exposicion.setFinCierre(null);
		assertFalse(exposicion.restaurarObraCheck());
	}

	@Test
	void testestaSuspensa() {
		// Test case 1: inicioCierre and finCierre are null
		Permanente permanente1 = new Permanente();
		boolean result1 = permanente1.estaSuspensa();
		assertFalse(result1, "Test case 1 failed");

		// Test case 2: current time is after inicioCierre and before finCierre
		Permanente permanente2 = new Permanente();
		permanente2.setInicioCierre(LocalDateTime.now().minusHours(1));
		permanente2.setFinCierre(LocalDateTime.now().plusHours(1));
		boolean result2 = permanente2.estaSuspensa();
		assertTrue(result2, "Test case 2 failed");

		// Test case 3: current time is before inicioCierre
		Permanente permanente3 = new Permanente();
		permanente3.setInicioCierre(LocalDateTime.now().plusHours(1));
		permanente3.setFinCierre(LocalDateTime.now().plusHours(2));
		boolean result3 = permanente3.estaSuspensa();
		assertFalse(result3, "Test case 3 failed");

		// Test case 4: current time is after finCierre
		Permanente permanente4 = new Permanente();
		permanente4.setInicioCierre(LocalDateTime.now().minusHours(2));
		permanente4.setFinCierre(LocalDateTime.now().minusHours(1));
		boolean result4 = permanente4.estaSuspensa();
		assertFalse(result4, "Test case 4 failed");
	}

	@Test
	void testestaSuspensaLocalDateTimeLocalDateTime() {
		Permanente permanente = new Permanente();
		// Test case 1: inicioCierre and finCierre are null
		LocalDateTime inicioCierre1 = null;
		LocalDateTime finCierre1 = null;
		permanente.setInicioCierre(inicioCierre1);
		permanente.setFinCierre(finCierre1);
		boolean result1 = permanente.estaSuspensa(inicioCierre1, finCierre1);
		assertFalse(result1, "Test case 1 failed");

		// Test case 2: current time is after inicioCierre and before finCierre
		LocalDateTime inicioCierre2 = LocalDateTime.now().minusHours(1);
		LocalDateTime finCierre2 = LocalDateTime.now().plusHours(1);
		permanente.setInicioCierre(inicioCierre2);
		permanente.setFinCierre(finCierre2);
		boolean result2 = permanente.estaSuspensa(inicioCierre2, finCierre2);
		assertTrue(result2, "Test case 2 failed");

		// Test case 3: current time is before inicioCierre
		LocalDateTime inicioCierre3 = LocalDateTime.now().plusHours(1);
		LocalDateTime finCierre3 = LocalDateTime.now().plusHours(2);
		permanente.setInicioCierre(inicioCierre3);
		permanente.setFinCierre(finCierre3);
		boolean result3 = permanente.estaSuspensa(inicioCierre3, finCierre3);
		assertFalse(result3, "Test case 3 failed");

		// Test case 4: current time is after finCierre
		LocalDateTime inicioCierre4 = LocalDateTime.now().minusHours(2);
		LocalDateTime finCierre4 = LocalDateTime.now().minusHours(1);
		permanente.setInicioCierre(inicioCierre4);
		permanente.setFinCierre(finCierre4);
		boolean result4 = permanente.estaSuspensa(inicioCierre4, finCierre4);
		assertFalse(result4, "Test case 4 failed");
	}

	@Test
	void testprogramarSuspension() {
		

		// Test case 1: No hay visitas programadas
		Permanente permanente1 = new Permanente();
		LocalDateTime inicio1 = LocalDateTime.now();
		LocalDateTime fin1 = LocalDateTime.now().plusDays(1);
		boolean mantenimiento1 = true;

		assertDoesNotThrow(() -> permanente1.programarSuspension(inicio1, fin1, mantenimiento1));
		assertEquals(inicio1, permanente1.getInicioCierre());
		assertEquals(fin1, permanente1.getFinCierre());
		assertTrue(permanente1.isCierrePorRenovacion());

		// Test case 2: Hay visitas programadas dentro del rango de suspensión
		Permanente permanente2 = new Permanente();
		LocalDateTime inicio2 = LocalDateTime.now();
		LocalDateTime fin2 = LocalDateTime.now().plusDays(1);
		boolean mantenimiento2 = false;

		Visita visita1 = new Visita(LocalDateTime.now().plusHours(12), 2);
		visita1.addEntrada(new Entrada(visita1));
		permanente2.addVisita(visita1);

		Exception exception2 = assertThrows(Exception.class,
				() -> permanente2.programarSuspension(inicio2, fin2, mantenimiento2));
		assertEquals("No se puede suspender la exposición en esas fechas, hay visitas programadas",
				exception2.getMessage());
		assertNull(permanente2.getInicioCierre());
		assertNull(permanente2.getFinCierre());
		assertFalse(permanente2.isCierrePorRenovacion());

		// Test case 3: Hay visitas programadas fuera del rango de suspensión
		Permanente permanente3 = new Permanente();
		LocalDateTime inicio3 = LocalDateTime.now();
		LocalDateTime fin3 = LocalDateTime.now().plusDays(1);
		boolean mantenimiento3 = false;

		Visita visita2 = new Visita(LocalDateTime.now().minusDays(1), 2);
		permanente3.addVisita(visita2);

		assertDoesNotThrow(() -> permanente3.programarSuspension(inicio3, fin3, mantenimiento3));
		assertEquals(inicio3, permanente3.getInicioCierre());
		assertEquals(fin3, permanente3.getFinCierre());
		assertFalse(permanente3.isCierrePorRenovacion());
	}

}
