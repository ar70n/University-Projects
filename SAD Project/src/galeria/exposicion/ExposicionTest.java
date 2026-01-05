package galeria.exposicion;

import org.junit.*;
import static org.junit.jupiter.api.Assertions.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import galeria.Vector3;
import galeria.obra.Audiovisual;
import galeria.sala.SalaRaiz;
import galeria.obra.*;
import sistema.Sistema;

/**
 * Clase de prueba para la clase Exposicion.
 * 
 * @author Miguel Campo
 * @author Jorge Jimenez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class ExposicionTest {
    Exposicion expo = null;
    SalaRaiz sala = null;

    /**
     * Configuración inicial para las pruebas.
     */
    @Before
    public void setUp() {
        sala = new SalaRaiz(10, 10, 10, 10, 100, true, 20, 50);
        expo = new Permanente("Expo1", "Descripcion1", LocalDateTime.now().plusHours(1));
        expo.setPrecioEntrada(10);
        Sistema.getInstance(); // Inicializamos Sistema

        List<Vector3> dimList = new ArrayList<Vector3>();
        dimList.add(new Vector3(5, 10, 10));
        dimList.add(new Vector3(5, 10, 10));
        List<Integer> enchufesList = new ArrayList<Integer>();
        enchufesList.add(10);
        enchufesList.add(10);
        List<Integer> aforoList = new ArrayList<Integer>();
        aforoList.add(50);
        aforoList.add(70);

        try {
            sala.dividir(dimList, enchufesList, aforoList);
            expo.addSala(sala.getSubsalas().get(0));
            expo.addSala(sala.getSubsalas().get(1));
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    /**
     * Prueba para el método getAforo.
     */
    @Test
    public void testgetAforo() {
        assertEquals(120, expo.getAforo());
    }

    /**
     * Prueba para el método getObras.
     * 
     * @throws Exception si ocurre un error al agregar la obra a la sala.
     */
    @Test
    public void testgetObras() throws Exception {
        ArrayList<Obra> obras = new ArrayList<>();
        Obra obra = new Audiovisual("Obra1", "Autor1", 2020, "Descripcion1", 1000.0, "Poliza1", true, 120, "Español");
        obras.add(obra);
        try {
            sala.getSubsalas().get(0).addObra(obra);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        assertEquals(obras, expo.getObras());
    }

    /**
     * Prueba para el método publicar.
     */
    @Test
    public void testpublicar() {
        expo.publicar();
        assertEquals(EstadoExp.PUBLICADA, expo.getEstado());
    }

    /**
     * Prueba para el método eliminarExp.
     */
    @Test
    public void testeliminarExp() {
        Exposicion expo = new Permanente("Expo1", "Descripcion1", LocalDateTime.now());

        try {
            expo.eliminarExp();
        } catch (Exception e) {
            fail();
        }
    }

    /*
     * No podemos testear devolver dinero porque al pagar al cliente, se recurre
     * a un método para pagar con tarjeta que no implementamos nosotros, y no se
     * registra
     * en el cliente, ya que el no lleva una cuenta de su saldo
     */
}