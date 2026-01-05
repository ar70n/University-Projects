package galeria.obra;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;
import galeria.sala.*;
import galeria.exposicion.*;

//Setters elementales y Getters no se testean
public class ObraTest {

	private Obra obra;

	@Before
	public void setUp() {
		obra = new Audiovisual("Mona Lisa", "Leonardo da Vinci", 1492, "Famous painting", 1000000, "ABC123", true);
	}

	@Test
	public void testcambiarEstado() {
		try {
			obra.cambiarEstado(EstadoObra.EXPOSICION);
		} catch (InvalidStateTransition e) {
			System.out.println(e.toString());
			e.printStackTrace();
		} finally {
			assertEquals(EstadoObra.EXPOSICION, obra.getEstado());
		}
	}

	@Test
	public void testcambiarEstadoWithRetirada() {
		obra.setEstado(EstadoObra.RETIRADA);
		assertThrows(InvalidStateTransition.class, () -> {
			obra.cambiarEstado(EstadoObra.ALMACEN);
		});

	}

	@Test
	public void testcambiarEstadoWithInvalidTransition() {
		obra.setEstado(EstadoObra.PRESTAMO);
		assertThrows(InvalidStateTransition.class, () -> {
			obra.cambiarEstado(EstadoObra.RESTAURACION);
		});
	}

	@Test
	public void testExponer() throws Exception {
		Sala sala = new SalaRaiz();
		sala.setEnchufes(1);
		obra.exponerEn(sala);
		assertEquals(EstadoObra.EXPOSICION, obra.getEstado());
		assertEquals(sala, obra.getSala());
	}

	@Test
	public void testremoveFromSalaGoesRight() {
		// Creamos sala y exposicion
		Sala sala = new SalaRaiz();
		sala.setEnchufes(1);
		obra.setSala(sala);
		Exposicion exposicion = new Temporal();
		exposicion.addSala(sala);
		exposicion.setEstado(EstadoExp.ENCREACION);
		obra.setEstado(EstadoObra.EXPOSICION);

		// Quitamos la obra de la sala
		try {
			obra.removeFromSala();
			assertNull(obra.getSala());
			assertEquals(EstadoObra.ALMACEN, obra.getEstado());

		} catch (ObraExceptions ex) {

		}
	}

	@Test // Solo se tendra en cuenta los casos de error por parte de obra, el resto de
			// funciones se testearan en sus respectivos test
	public void testremoveFromSalaGoesWrong() {
		// Creamos sala y exposicion
		Sala sala = new SalaRaiz();
		sala.setEnchufes(1);
		obra.setSala(sala);
		Exposicion exposicion = new Temporal();
		exposicion.addSala(sala);
		exposicion.setEstado(EstadoExp.ENCREACION);
		obra.setEstado(EstadoObra.RESTAURACION);

		// Quitamos la obra de la sala
		assertThrows(ExpectedDifferentState.class, () -> {
			obra.removeFromSala();
		});
	}

	@Test
	public void testrestaurarGoesRight() {
		obra.setEstado(EstadoObra.ALMACEN);
		try {
			obra.restaurar();
			assertEquals(EstadoObra.RESTAURACION, obra.getEstado());
		} catch (ObraExceptions e) {
			fail();
		}
	}

	@Test
	public void testrestaurarFromExpoGoesWrong() {
		// Creamos sala y exposicion
		Sala sala = new SalaRaiz();
		sala.setEnchufes(1);
		obra.setSala(sala);
		Exposicion exposicion = new Temporal();
		exposicion.addSala(sala);
		exposicion.setEstado(EstadoExp.COMENZADA);
		obra.setEstado(EstadoObra.EXPOSICION);

		assertThrows(ExpoDeclinedTransition.class, () -> {
			obra.restaurar();
		});
	}

	@Test
	public void testrestaurarFromExpoGoesRight() {
		// Creamos sala y exposicion
		Sala sala = new SalaRaiz();
		sala.setEnchufes(1);
		obra.setSala(sala);
		Exposicion exposicion = new Temporal();
		exposicion.addSala(sala);
		exposicion.setEstado(EstadoExp.ENCREACION);
		obra.setEstado(EstadoObra.EXPOSICION);

		try {
			obra.restaurar();
			assertEquals(EstadoObra.RESTAURACION, obra.getEstado());
			assertEquals(obra.sala, sala); // La obra no pierde la referencia a la sala.
		} catch (ObraExceptions e) {
			fail();
		}
	}

	@Test // Como los metodos prestar() y retirar() funcionan igual que este no tiene
			// sentido probarlos
	public void testenviarAlmacenGoesRight() {
		obra.setEstado(EstadoObra.PRESTAMO);
		try {
			obra.enviarAlmacen();
			assertEquals(EstadoObra.ALMACEN, obra.getEstado());
		} catch (ObraExceptions e) {
			fail();
		}
	}

	@Test
	public void testenviarAlmacenGoesWrong() {
		obra.setEstado(EstadoObra.RETIRADA);
		assertThrows(InvalidStateTransition.class, () -> {
			obra.enviarAlmacen();
		});
	}

}