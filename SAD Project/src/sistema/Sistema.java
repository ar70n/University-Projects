package sistema;

import java.util.Set;
import usuario.*;
import galeria.sala.*;
import galeria.exposicion.Exposicion;
import galeria.obra.Obra;
import descuento.SorteoActivo;
import mensaje.*;
import java.time.*;
import fichero.*;

import java.util.List;
import java.util.HashSet;
import java.io.IOException;
import java.io.Serializable;

/**
 * Clase que representa el sistema del programa.
 * Contiene métodos para gestionar sorteos, usuarios, salas, exposiciones, obras
 * y compras.
 * Implementa la interfaz Serializable para permitir la serialización de objetos
 * de esta clase.
 *
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Sistema implements Serializable {
    /**
     * Hora de apertura del sistema.
     */
    private LocalTime apertura;

    /**
     * Hora de cierre del sistema.
     */
    private LocalTime cierre;

    /**
     * Instancia única del sistema.
     */
    private static Sistema sistema;

    /**
     * Conjunto de sorteos activos.
     */
    private Set<SorteoActivo> sorteos;

    /**
     * Conjunto de usuarios registrados.
     */
    private Set<UsuarioRegistrado> usuarios;

    /**
     * Conjunto de salas raíz.
     */
    private Set<SalaRaiz> salasRaiz;

    /**
     * Conjunto de exposiciones.
     */
    private Set<Exposicion> exposiciones;

    /**
     * Conjunto de obras.
     */
    private Set<Obra> obras;

    /**
     * Conjunto de compras realizadas.
     */
    private Set<Compra> compras;

    /**
     * Identificador único para la serialización de objetos de esta clase.
     */
    private static final long serialVersionUID = 1L;

    /**
     * Constructor privado de la clase Sistema.
     * Inicializa los conjuntos de sorteos, usuarios, salas, exposiciones, obras y
     * compras.
     */
    private Sistema() {
        sorteos = new HashSet<>();
        usuarios = new HashSet<>();
        salasRaiz = new HashSet<>();
        exposiciones = new HashSet<>();
        obras = new HashSet<>();
        compras = new HashSet<>();
    }

    /**
     * Método estático para obtener la instancia única del sistema.
     *
     * @return La instancia única del sistema.
     */
    public static Sistema getInstance() {
        if (sistema == null) {
            sistema = new Sistema();
        }
        return sistema;
    }

    /**
     * Método estático para realizar el inicio de sesión de un usuario registrado.
     *
     * @param nif      El NIF del usuario.
     * @param password La contraseña del usuario.
     * @return El usuario registrado si el inicio de sesión es exitoso, null en caso
     *         contrario.
     */
    public static UsuarioRegistrado login(String nif, String password) {
        for (UsuarioRegistrado u : sistema.usuarios) {
            if (u.getNif().equals(nif) && u.getContrasena().equals(password)) {
                return u;
            }
        }
        return null;
    }

    /**
     * Método estático para enviar un mensaje a uno o varios usuarios registrados.
     *
     * @param asunto El asunto del mensaje.
     * @param texto  El texto del mensaje.
     * @param u      Los usuarios a los que se les enviará el mensaje.
     */
    public static void enviarMensaje(String asunto, String texto, UsuarioRegistrado... u) {
        Notificacion notificacion = new Notificacion(asunto, texto);
        for (UsuarioRegistrado usuario : u) {
            usuario.recibirNotificacion(notificacion);
        }
    }

    /**
     * Método para buscar una obra por su nombre.
     *
     * @param nombre El nombre de la obra a buscar.
     * @return La obra encontrada, o null si no se encuentra ninguna obra con ese
     *         nombre.
     */
    public Obra buscarObra(String nombre) {
        for (Obra o : obras) {
            if (o.getNombre().equals(nombre)) {
                return o;
            }
        }
        return null;
    }

    /**
     * Método estático para buscar la sala que contiene una obra.
     *
     * @param o La obra para la cual se busca la sala.
     * @return La sala que contiene la obra.
     */
    public static Sala buscarSalaConObra(Obra o) {
        return o.getSala();
    }

    /**
     * Método estático para obtener todas las exposiciones del sistema.
     *
     * @return Un conjunto de todas las exposiciones del sistema.
     */
    public static Set<Exposicion> getExposiciones() {
        return sistema.exposiciones;
    }

    /**
     * Método para obtener las exposiciones del sistema que cumplen con un filtro
     * dado.
     *
     * @param f El filtro a aplicar.
     * @return Un conjunto de exposiciones que cumplen con el filtro.
     */
    public Set<Exposicion> getExposiciones(Filtro f) {
        Set<Exposicion> expos = Set.of();

        for (Exposicion e : exposiciones) {
            if (f.filtrar(e)) {
                expos.add(e);
            }
        }
        return expos;
    }

    /**
     * Método estático para obtener todas las compras realizadas en el sistema.
     *
     * @return Un conjunto de todas las compras realizadas en el sistema.
     */
    public static Set<Compra> getCompras() {
        return sistema.compras;
    }

    /**
     * Método estático para establecer la hora de apertura del sistema.
     *
     * @param apertura La hora de apertura del sistema.
     */
    public static void setApertura(LocalTime apertura) {
        sistema.apertura = apertura;
    }

    /**
     * Método estático para establecer la hora de cierre del sistema.
     *
     * @param cierre La hora de cierre del sistema.
     */
    public static void SetCierre(LocalTime cierre) {
        sistema.cierre = cierre;
    }

    /**
     * Método estático para agregar un empleado al sistema.
     *
     * @param e El empleado a agregar.
     */
    public static void addEmpleado(Empleado e) {
        sistema.usuarios.add(e);
    }

    /**
     * Método estático para eliminar una obra del sistema.
     *
     * @param o La obra a eliminar.
     */
    public static void eliminarObra(Obra o) {
        sistema.obras.remove(o);
    }

    /**
     * Método estático para eliminar una exposición del sistema.
     *
     * @param e La exposición a eliminar.
     */
    public static void eliminarExp(Exposicion e) {
        sistema.exposiciones.remove(e);
    }

    /**
     * Método estático para obtener el número total de entradas vendidas en un rango
     * de fechas.
     *
     * @param inicio La fecha de inicio del rango.
     * @param fin    La fecha de fin del rango.
     * @return El número total de entradas vendidas en el rango de fechas.
     */
    public static int getEntradasGlobal(LocalDateTime inicio, LocalDateTime fin) {
        int total = 0;

        for (Compra compra : sistema.compras) {
            if (compra.getFecha().isAfter(inicio) && compra.getFecha().isBefore(fin)) {
                total += compra.getEntradas();
            }
        }

        return total;
    }

    /**
     * Método estático para obtener el número de entradas vendidas para una
     * exposición en un rango de fechas.
     *
     * @param inicio La fecha de inicio del rango.
     * @param fin    La fecha de fin del rango.
     * @param exp    La exposición para la cual se desea obtener el número de
     *               entradas vendidas.
     * @return El número de entradas vendidas para la exposición en el rango de
     *         fechas.
     */
    public static int getEntradasExp(LocalDateTime inicio, LocalDateTime fin, Exposicion exp) {
        int total = 0;

        for (Compra compra : sistema.compras) {
            if (compra.getExposicion() == exp && compra.getFecha().isAfter(inicio) && compra.getFecha().isBefore(fin)) {
                total += compra.getEntradas();
            }
        }

        return total;
    }

    /**
     * Método estático para obtener el beneficio total obtenido en un rango de
     * fechas.
     *
     * @param inicio La fecha de inicio del rango.
     * @param fin    La fecha de fin del rango.
     * @return El beneficio total obtenido en el rango de fechas.
     */
    public static int getBeneficioGlobal(LocalDateTime inicio, LocalDateTime fin) {
        int total = 0;

        for (Compra compra : sistema.compras) {
            if (compra.getFecha().isAfter(inicio) && compra.getFecha().isBefore(fin)) {
                total += compra.getPrecio() * compra.getEntradas();
            }
        }

        return total;
    }

    /**
     * Método estático para obtener el beneficio obtenido para una exposición en un
     * rango de fechas.
     *
     * @param inicio La fecha de inicio del rango.
     * @param fin    La fecha de fin del rango.
     * @param exp    La exposición para la cual se desea obtener el beneficio.
     * @return El beneficio obtenido para la exposición en el rango de fechas.
     */
    public static int getBeneficioExp(LocalDateTime inicio, LocalDateTime fin, Exposicion exp) {
        int total = 0;

        for (Compra compra : sistema.compras) {
            if (compra.getExposicion() == exp && compra.getFecha().isAfter(inicio) && compra.getFecha().isBefore(fin)) {
                total += compra.getPrecio() * compra.getEntradas();
            }
        }

        return total;
    }

    /**
     * Método estático para registrar una compra en el sistema.
     *
     * @param compra La compra a registrar.
     */
    public static void registrarCompra(Compra compra) {
        sistema.compras.add(compra);
    }

    /**
     * Método estático para obtener todos los sorteos activos del sistema.
     *
     * @return Un conjunto de todos los sorteos activos del sistema.
     */
    public static Set<SorteoActivo> getSorteos() {
        return sistema.sorteos;
    }

    /**
     * Método estático para obtener todos los usuarios registrados del sistema.
     *
     * @return Un conjunto de todos los usuarios registrados del sistema.
     */
    public static Set<UsuarioRegistrado> getUsuariosRegistrados() {
        return sistema.usuarios;
    }

    /**
     * Método estático para obtener todas las obras del sistema.
     *
     * @return Un conjunto de todas las obras del sistema.
     */
    public static Set<Obra> getObras() {
        return sistema.obras;
    }

    /**
     * Método estático para guardar el sistema en un archivo.
     * El archivo se guarda con el nombre "sistema.dat".
     */
    public static void guardarSistema() {
        try {
            ManejadorFicheros.guardar(sistema, "resources/sistema.dat");
        } catch (IOException e) {
            System.out.println("Error al guardar el sistema (IOException)");
            e.printStackTrace();
        }
    }

    /**
     * Método estático para cargar el sistema desde un archivo.
     * El archivo debe tener el nombre "sistema.dat".
     *
     * @throws Exception Si ocurre un error al cargar el sistema.
     */
    public static void cargarSistema() throws Exception {

        try {
            sistema = (Sistema) ManejadorFicheros.cargar("resources/sistema.dat");
        } catch (IOException e) {
            throw new Exception("Error al cargar el sistema (IOException)");
        } catch (ClassNotFoundException e) {
            throw new Exception("Error al cargar el sistema (ClassNotFoundException)");
        }
    }

    /**
     * Método estático para agregar salas raíz al sistema.
     *
     * @param salas Las salas raíz a agregar.
     */
    public static void addSalasRaiz(SalaRaiz... salas) {
        for (SalaRaiz sala : salas) {
            sistema.salasRaiz.add(sala);
        }
    }

    /**
     * Método estático para agregar exposiciones al sistema.
     *
     * @param expos Las exposiciones a agregar.
     */
    public static void addExposiciones(Exposicion... expos) {
        for (Exposicion exposicion : expos) {
            sistema.exposiciones.add(exposicion);
        }
    }

    /**
     * Método estático para agregar obras al sistema.
     *
     * @param obras Las obras a agregar.
     */
    public static void addObras(Obra... obras) {
        for (Obra obra : obras) {
            sistema.obras.add(obra);
        }
    }

    /**
     * Método estático para agregar sorteos al sistema.
     *
     * @param sorteos Los sorteos a agregar.
     */
    public static void addSorteos(SorteoActivo... sorteos) {
        for (SorteoActivo sorteo : sorteos) {
            sistema.sorteos.add(sorteo);
        }
    }

    /**
     * Método estático para agregar usuarios registrados al sistema.
     *
     * @param usuarios Los usuarios registrados a agregar.
     */
    public static void addUsuarios(UsuarioRegistrado... usuarios) {
        for (UsuarioRegistrado usuario : usuarios) {
            sistema.usuarios.add(usuario);
        }
    }

    /**
     * Método estático para agregar compras al sistema.
     *
     * @param compras Las compras a agregar.
     */
    public static void addCompras(Compra... compras) {
        for (Compra compra : compras) {
            sistema.compras.add(compra);
        }
    }

    /**
     * Método estático para eliminar un sorteo del sistema.
     *
     * @param sorteo El sorteo a eliminar.
     */
    public static void eliminarSorteo(SorteoActivo sorteo) {
        sistema.sorteos.remove(sorteo);
    }

    /**
     * Método estático para eliminar un usuario registrado del sistema.
     *
     * @param usuario El usuario registrado a eliminar.
     */
    public static void eliminarUsuario(UsuarioRegistrado usuario) {
        sistema.usuarios.remove(usuario);
    }

    /**
     * Método estático para eliminar una compra del sistema.
     *
     * @param compra La compra a eliminar.
     */
    public static void eliminarCompra(Compra compra) {
        sistema.compras.remove(compra);
    }

    /**
     * Método estático para eliminar una sala raíz del sistema.
     *
     * @param sala La sala raíz a eliminar.
     */
    public static void eliminarSalaRaiz(SalaRaiz sala) {
        sistema.salasRaiz.remove(sala);
    }

    /**
     * Método estático para eliminar varios sorteos del sistema.
     *
     * @param sorteos Los sorteos a eliminar.
     */
    public static void eliminarSorteos(SorteoActivo... sorteos) {
        for (SorteoActivo sorteo : sorteos) {
            sistema.sorteos.remove(sorteo);
        }
    }

    /**
     * Método estático para eliminar varios usuarios registrados del sistema.
     *
     * @param usuarios Los usuarios registrados a eliminar.
     */
    public static void eliminarUsuarios(UsuarioRegistrado... usuarios) {
        for (UsuarioRegistrado usuario : usuarios) {
            sistema.usuarios.remove(usuario);
        }
    }

    /**
     * Método estático para eliminar varias compras del sistema.
     *
     * @param compras Las compras a eliminar.
     */
    public static void eliminarCompras(Compra... compras) {
        for (Compra compra : compras) {
            sistema.compras.remove(compra);
        }
    }

    /**
     * Método estático para eliminar varias salas raíz del sistema.
     *
     * @param salas Las salas raíz a eliminar.
     */
    public static void eliminarSalasRaiz(SalaRaiz... salas) {
        for (SalaRaiz sala : salas) {
            sistema.salasRaiz.remove(sala);
        }
    }

    /**
     * Método estático para eliminar varias exposiciones del sistema.
     *
     * @param expos Las exposiciones a eliminar.
     */
    public static void eliminarExposiciones(Exposicion... expos) {
        for (Exposicion exposicion : expos) {
            sistema.exposiciones.remove(exposicion);
        }
    }

    /**
     * Método estático para eliminar varias obras del sistema.
     *
     * @param obras Las obras a eliminar.
     */
    public static void eliminarObras(Obra... obras) {
        for (Obra obra : obras) {
            sistema.obras.remove(obra);
        }
    }

    /**
     * Método estático para obtener una copia inmutable de los usuarios registrados
     * del sistema.
     *
     * @return Una lista inmutable de los usuarios registrados del sistema.
     */
    public static List<UsuarioRegistrado> getUsuarios() {
        return List.copyOf(sistema.usuarios);
    }

    /**
     * Método toString para representar el objeto Sistema en forma de cadena de
     * texto.
     *
     * @return La representación en forma de cadena de texto del objeto Sistema.
     */
    @Override
    public String toString() {
        return "Sistema{" +
                "Apertura=" + apertura +
                ", Cierre=" + cierre +
                ", Sorteos=" + sorteos +
                ", Usuarios=" + usuarios +
                ", SalasRaiz=" + salasRaiz +
                ", Exposiciones=" + exposiciones +
                ", Obras=" + obras +
                ", Compras=" + compras +
                '}';
    }

}
