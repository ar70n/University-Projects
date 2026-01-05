package galeria.sala;

import static org.junit.jupiter.api.Assertions.*;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.Test;

import galeria.Vector3;
import galeria.exposicion.Exposicion;
import galeria.exposicion.Permanente;
import galeria.exposicion.Temporal;
import galeria.obra.*;

class SalaTest {

	@Test
	void testbuscarObra() throws Exception{

		// Create a Sala object
		Sala sala = new SalaRaiz();
		sala.setExposicion(new Temporal());

		// Create some Obra objects
		Obra obra1 = new Audiovisual("Obra 1");
		Obra obra2 = new Audiovisual("Obra 2");
		Obra obra3 = new Audiovisual("Obra 3");

		// Add the Obra objects to the Sala
		sala.addObra(obra1);
		sala.addObra(obra2);
		sala.addObra(obra3);

		// Test case 1: Search for an existing Obra
		Obra result1 = sala.buscarObra("Obra 2");
		assertEquals(obra2, result1, "Should return the correct Obra object");

		// Test case 2: Search for a non-existing Obra
		Obra result2 = sala.buscarObra("Obra 4");
		assertNull(result2, "Should return null for a non-existing Obra");

	}

	@Test
	void testdividir() throws Exception{

		Sala sala = new SalaRaiz();

		// Test case 1: Division with no exposicion and no obras
		List<Vector3> dimList1 = new ArrayList<>();
		dimList1.add(new Vector3(10, 10, 10));
		dimList1.add(new Vector3(20, 20, 20));
		List<Integer> enchufesList1 = new ArrayList<>();
		enchufesList1.add(2);
		enchufesList1.add(4);
		List<Integer> aforoList1 = new ArrayList<>();
		aforoList1.add(10);
		aforoList1.add(20);

		assertDoesNotThrow(() -> sala.dividir(dimList1, enchufesList1, aforoList1));
		assertEquals(2, sala.getSubsalas().size(), "Should create 2 subsalas");

		// Test case 2: Division with exposicion assigned
		Sala sala2 = new SalaRaiz();
		try {
			sala2.setExposicion(new Temporal());
		} catch (Exception e) {
			e.printStackTrace();
		}
		List<Vector3> dimList2 = new ArrayList<>();
		dimList2.add(new Vector3(15, 15, 15));
		List<Integer> enchufesList2 = new ArrayList<>();
		enchufesList2.add(3);
		List<Integer> aforoList2 = new ArrayList<>();
		aforoList2.add(15);

		Exception exception2 = assertThrows(Exception.class, () -> sala2.dividir(dimList2, enchufesList2, aforoList2));
		assertEquals("Error: No se puede dividir una sala que tenga una exposición asignada", exception2.getMessage(),
				"Should throw exception");

		// Test case 3: Division with obras present
		Sala sala3 = new SalaRaiz();
		sala3.setExposicion(new Temporal());
		sala3.addObra(new Escultura("Obra 1"));
		List<Vector3> dimList3 = new ArrayList<>();
		dimList3.add(new Vector3(10, 10, 10));
		List<Integer> enchufesList3 = new ArrayList<>();
		enchufesList3.add(2);
		List<Integer> aforoList3 = new ArrayList<>();
		aforoList3.add(10);
		sala3.setExposicion(null);

		Exception exception3 = assertThrows(Exception.class, () -> sala3.dividir(dimList3, enchufesList3, aforoList3));
		assertEquals("Error: Solo se puede dividir una sala si no tiene obras", exception3.getMessage(),
				"Should throw exception");

		// Test case 4: Division with null dimensions, enchufes, or aforo
		Sala sala4 = new SalaRaiz();
		List<Vector3> dimList4 = null;
		List<Integer> enchufesList4 = new ArrayList<>();
		enchufesList4.add(2);
		List<Integer> aforoList4 = new ArrayList<>();
		aforoList4.add(10);

		Exception exception4 = assertThrows(Exception.class, () -> sala4.dividir(dimList4, enchufesList4, aforoList4));
		assertEquals("Error: No se han proporcionado las dimensiones, enchufes o aforo de las subsalas",
				exception4.getMessage(), "Should throw exception");

		// Test case 5: Division with mismatched dimensions, enchufes, and aforo lists
		Sala sala5 = new SalaRaiz();
		List<Vector3> dimList5 = new ArrayList<>();
		dimList5.add(new Vector3(10, 10, 10));
		List<Integer> enchufesList5 = new ArrayList<>();
		enchufesList5.add(2);
		enchufesList5.add(4);
		List<Integer> aforoList5 = new ArrayList<>();
		aforoList5.add(10);

		Exception exception5 = assertThrows(Exception.class, () -> sala5.dividir(dimList5, enchufesList5, aforoList5));
		assertEquals("Error: Las listas de dimensiones, enchufes y aforo no tienen el mismo tamaño",
				exception5.getMessage(), "Should throw exception");
	}

	@Test
	void testaddObra_Success() {
		Sala sala = new SalaRaiz(10, 10, 10);
		Exposicion exposicion = new Temporal();
		sala.setExposicionTests(exposicion);
		Fisica obra = new Escultura("Obra1", 5, 5, 5);
		assertDoesNotThrow(() -> sala.addObra(obra));
		assertTrue(sala.getObras().contains(obra));
	}

	@Test
	void testaddObra_WithoutExposicion() {
		Sala sala = new SalaRaiz(10, 10, 10);
		Exposicion exposicion = new Temporal();
		sala.setExposicionTests(exposicion);
		Fisica obra = new Escultura("Obra1", 5, 5, 5);
		sala.setExposicionTests(null);
		SalaWithoutExpoException exception = assertThrows(SalaWithoutExpoException.class, () -> sala.addObra(obra));
		assertEquals("La sala no tiene una exposición asignada", exception.getMessage());
		assertFalse(sala.getObras().contains(obra));
	}

	@Test
	void testaddObra_WithSubsalas() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		Exposicion exposicion = new Temporal();
		sala.setExposicion(exposicion);
		Fisica obra = new Escultura("Obra1", 5, 5, 5);

		sala.addSubsala(new Subsala(5, 5, 5));
		SalaGotSubsalasException exception = assertThrows(SalaGotSubsalasException.class, () -> sala.addObra(obra));
		assertEquals("La sala tiene subsalas", exception.getMessage());
		assertFalse(sala.getObras().contains(obra));
	}

	@Test
	void testaddObra_AlreadyContainsObra() {
		Sala sala = new SalaRaiz(10, 10, 10);
		Exposicion exposicion = new Temporal();
		sala.setExposicionTests(exposicion);
		Fisica obra = new Escultura("Obra1", 5, 5, 5);
		try{
			sala.addObra(obra);
		}catch(Exception e){
			e.printStackTrace();
		}
		SalaAlreadyContainsObra exception = assertThrows(SalaAlreadyContainsObra.class, () -> sala.addObra(obra));
		assertEquals("La sala ya contiene esta obra: Obra1", exception.getMessage());
		assertEquals(1, sala.getObras().size());
		
	}

	@Test
	void testaddObra_InsufficientSpace() {
		Sala sala = new SalaRaiz(10, 10, 10);
		Exposicion exposicion = new Temporal();
		sala.setExposicionTests(exposicion);

		Fisica largeObra = new Escultura("Obra2", 20, 20, 20);
		InsufficientSpaceException exception = assertThrows(InsufficientSpaceException.class,
				() -> sala.addObra(largeObra));
		assertEquals("InsufficientSpaceException [espacioSala=1000.0, espacioObra=8000.0]", exception.getMessage());
		assertFalse(sala.getObras().contains(largeObra));
	}

	@Test
	void testespacioRestante_NoObras() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		sala.setExposicion(new Temporal());

		double espacio = sala.espacioRestante();
		assertEquals(1000, espacio);
	}

	@Test
	void testespacioRestante_OneObra() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		sala.setExposicion(new Temporal());

		Obra obra = new Escultura("Obra1", 5, 5, 1);
		sala.addObra(obra);

		double espacio = sala.espacioRestante();
		assertEquals(975, espacio);
	}

	@Test
	void testespacioRestante_MultipleObras() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		sala.setExposicion(new Temporal());

		Obra obra1 = new Escultura("Obra1", 5, 5, 1);
		Obra obra2 = new Escultura("Obra2", 3, 3, 0);
		Obra obra3 = new Escultura("Obra3", 2, 2, 6.25);

		sala.addObra(obra1);
		sala.addObra(obra2);
		sala.addObra(obra3);

		double espacio = sala.espacioRestante();
		assertEquals(950, espacio);
	}

	@Test
	void testespacioRestante_ObrasExceedDimensiones() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		Obra obra1 = new Escultura("Obra1", 15, 15, 0);
		Obra obra2 = new Escultura("Obra2", 8, 8, 0);
		sala.setExposicion(new Temporal());

		sala.addObra(obra1);
		sala.addObra(obra2);

		double espacio = sala.espacioRestante();
		assertEquals(1000, espacio);
	}

	@Test
	void testexpoPermanente_NoExposicion() {
		Sala sala = new SalaRaiz(10, 10, 10);

		assertThrows(SalaWithoutExpoException.class, () -> {
			sala.expoPermanente();
		});
	}

	@Test
	void testexpoPermanente_WithSubsalas() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		sala.setExposicion(new Temporal());
		sala.addSubsala(new Subsala(5, 5, 5));
		

		assertThrows(SalaGotSubsalasException.class, () -> {
			sala.expoPermanente();
		});
	}

	@Test
	void testexpoPermanente_PermanenteExposicion() throws SalaGotSubsalasException, SalaWithoutExpoException {
		Sala sala = new SalaRaiz(10, 10, 10);
		Exposicion exposicion = new Permanente();
		sala.setExposicionTests(exposicion);

		boolean result = sala.expoPermanente();

		assertTrue(result);
	}

	@Test
	void testexpoPermanente_TemporalExposicion() throws SalaGotSubsalasException, SalaWithoutExpoException {
		Sala sala = new SalaRaiz(10, 10, 10);
		Exposicion exposicion = new Temporal();
		sala.setExposicionTests(exposicion);

		boolean result = sala.expoPermanente();

		assertFalse(result);
	}

	@Test
	void testaddObraExpoCheck() throws SalaGotSubsalasException, SalaWithoutExpoException {
		// Create a Sala object
		Sala sala = new SalaRaiz(10, 10, 10);

		// Test case 1: No exposicion assigned
		assertThrows(SalaWithoutExpoException.class, () -> {
			sala.addObraExpoCheck(true);
		});

		// Test case 2: Sala has subsalas
		sala.setExposicionTests(new Temporal());
		sala.addSubsala(new Subsala(5, 5, 5));
		assertThrows(SalaGotSubsalasException.class, () -> {
			sala.addObraExpoCheck(true);
		});

		// Test case 3: Permanent exposicion, propiedad = true
		Exposicion exposicion1 = new Permanente("Exposicion 1", "Descripcion 1", LocalDateTime.now().plusHours(1));
		sala.setExposicionTests(exposicion1);
		sala.eliminarSubsala(sala.getSubsalas().get(0));
		boolean result1 = sala.addObraExpoCheck(true);
		assertTrue(result1);

		// Test case 4: Permanent exposicion, propiedad = false
		boolean result2 = sala.addObraExpoCheck(false);
		assertTrue(result2);

		// Test case 5: Temporary exposicion, propiedad = true
		Exposicion exposicion2 = new Temporal();
		sala.setExposicionTests(exposicion2);
		boolean result3 = sala.addObraExpoCheck(true);
		assertFalse(result3);

		// Test case 6: Temporary exposicion, propiedad = false
		boolean result4 = sala.addObraExpoCheck(false);
		assertFalse(result4);
	}

	@Test
	void testremoveObra_Success() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		sala.setExposicion(new Temporal());
		Obra obra = new Audiovisual("Obra 1");
		sala.addObra(obra);

		boolean result = sala.removeObra(obra);
		assertTrue(result);
		assertFalse(sala.getObras().contains(obra));
	}

	@Test
	void testremoveObra_WithoutExposicion() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		Obra obra = new Audiovisual("Obra 1");
		sala.setExposicion(new Temporal());
		sala.addObra(obra);
		sala.setExposicion(null);

		assertFalse(sala.removeObra(obra));
		assertTrue(sala.getObras().contains(obra));
	}

	@Test
	void testremoveObra_WithSubsalas() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		Obra obra = new Audiovisual("Obra 1");
		sala.setExposicion(new Temporal());
		sala.addObra(obra);

		sala.addSubsala(new Subsala(5, 5, 5));
		boolean result = sala.removeObra(obra);
		assertFalse(result);
		assertTrue(sala.getObras().contains(obra));
	}

	@Test
	void testrestaurarObra_Success() throws Exception{
		Sala sala = new SalaRaiz(10, 10, 10);
		sala.setExposicion(new Temporal());
		Obra obra = new Audiovisual("Obra 1");
		sala.addObra(obra);

		

		boolean result = sala.restaurarObra(obra);
		assertTrue(result);
		assertFalse(sala.getObras().contains(obra));
	}

	@Test
	void testrestaurarObra_WithoutExposicion() throws Exception	{
		Sala sala = new SalaRaiz(10, 10, 10);
		sala.setExposicion(new Temporal());
		Obra obra = new Audiovisual("Obra 1");
		sala.addObra(obra);

		sala.setExposicion(null);

		boolean result = sala.restaurarObra(obra);
		assertFalse(result);
		assertTrue(sala.getObras().contains(obra));
	}

}
