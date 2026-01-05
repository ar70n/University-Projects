package test;

import galeria.exposicion.*;
import usuario.*;
import galeria.sala.*;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Set;

import mensaje.*;
import sistema.Sistema;
import descuento.*;
import galeria.obra.*;
import sistema.*;
import entrada.*;
import fichero.*;
import java.util.HashSet;

import descuento.Descuento;

/**
 * Clase de prueba que contiene el método principal para probar el sistema.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Tester {
    /**
     * Constante que representa el color rojo en la consola.
     */
    public static final String ANSI_RED = "\u001B[31m";

    /**
     * Constante que representa el color verde en la consola.
     */
    public static final String ANSI_GREEN = "\u001B[32m";

    /**
     * Constante que representa el color azul en la consola.
     */
    public static final String ANSI_BLUE = "\u001B[34m";

    /**
     * Constante que representa el color de reset en la consola.
     */
    public static final String ANSI_RESET = "\u001B[0m";

    /**
     * Método principal que se ejecuta al iniciar la aplicación.
     * 
     * @param args los argumentos de la línea de comandos
     * @throws IllegalArgumentException si se produce un error en la ejecución del
     *                                  sistema
     */
    @SuppressWarnings("unused")
    public static void main(String[] args) throws IllegalArgumentException {
        System.out.println("CREANDO USUARIOS Y SALAS RAIZ");
        Sistema sist = Sistema.getInstance();
        Gestor g = new Gestor("1234", "Techno Mechanicus", "PincelEmp02");
        Cliente c = new Cliente("1234", "X AE A-XII Musk", "PincelCli02");
        c.setRecibeNotificaciones(true);
        SalaRaiz s1 = new SalaRaiz(10.00, 5.00, 20.00, 3, 20, true, 10.00, 35.00);
        SalaRaiz s2 = new SalaRaiz(10.00, 5.00, 10.00, 2, 20, true, 10.00, 10.00);

        Sistema.addUsuarios(g, c);
        Sistema.addSalasRaiz(s1, s2);

        System.out.println("Usuarios:");
        for (UsuarioRegistrado u : Sistema.getUsuarios()) {
            System.out.println(u);
        }

        System.out.println("Salas Raíz:");
        System.out.println(s1);
        System.out.println(s2);


        // GESTOR
        System.out.println(ANSI_BLUE + "TESTS DE GESTOR" + ANSI_RESET);
        System.out.println("Prueba de login erróneo:");
        UsuarioRegistrado usuario = Sistema.login("1234", "PincelEmp");

        if (usuario == null) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Prueba de login correcto:");

        if (Sistema.login("1234", "PincelEmp02").getTipoUsuario().equals("Gestor")) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);

        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }
        Gestor gestor = (Gestor) Sistema.login("1234", "PincelEmp02");

        System.out.println("Creando salas hijas:");

        System.out.println(s1);
        System.out.println(s2);

        gestor.dividirSala(s1, List.of(1, 2), List.of(15, 5), 15.00, 5.00);

        System.out.println("División de sala (s1):");

        System.out.println(s1);
        System.out.println(s2);

        System.out.println("Creando Exposiciones:");

        Permanente exp1 = gestor.crearExposicionPermanente("Exposición Permanente", "Descripción", LocalDateTime.now());
        Temporal exp2 = gestor.crearExposicionTemporal("Exposición Temporal", "Descripción", LocalDateTime.now(),
                LocalDateTime.now().plusDays(10));

        System.out.println("Exposiciones creadas:");
        for (Exposicion e : Sistema.getExposiciones()) {
            System.out.println(e.getNombre());
        }

        if (exp1.getNombre().equals("Exposición Permanente") && exp1.getDescripcion().equals("Descripción")) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Creando descuento:");
        Descuento d1 = gestor.addDescuento(25.00, false, 100);
        System.out.println(d1);
        if (d1.getPorcentaje() == 25.00) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        try {
            gestor.fijarPrecioExposicion(exp1, 10.00);
            gestor.fijarPrecioExposicion(exp2, 10.00);
            gestor.addDescuentoExposicion(exp1, d1);
            gestor.addSalaExposicion(exp1,
                    List.of(s1.getSubsalas().get(0), s1.getSubsalas().get(1)).toArray(new Sala[0]));
            gestor.addSalaExposicion(exp2, s2);
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Creando obra (Mona Lisa):");

        Cuadro monaLisa = gestor.registrarCuadro("Mona Lisa", "Leonardo Da Vinci", 1503, "Descripción", 1000000.00,
                "Seguro", true, 10.00, 20.00, 30.00, 40.00, true, true, 1.00, 1.00, 1.00, "Óleo");
        if (monaLisa.getNombre().equals("Mona Lisa") && monaLisa.getAutor().equals("Leonardo Da Vinci")) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Cargando obras desde el documento:");

        ManejadorFicheros.leerObras("resources/obras.csv");

        System.out.println("Obras cargadas:");

        for (Obra o : Sistema.getObras()) {
            System.out.println(o.getNombre());
        }

        System.out.println("Exponiendo obra en sala:");

        gestor.addObraToSala(monaLisa, s1.getSubsalas().get(0));

        if (s1.getSubsalas().get(0).getObras().contains(monaLisa)) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Publicando exposición:");
        System.out.println(exp1);
        System.out.println(exp2);
        gestor.publicarExp(exp1);
        gestor.publicarExp(exp2);

        System.out.println("Dando de alta a 2 empleados:");

        Empleado emp1 = gestor.darDeAlta("Gabi", "4444", "9876", "Dirección1", "SeguridadSocial1");
        Empleado emp2 = gestor.darDeAlta("María", "5555", "5432", "Dirección2", "SeguridadSocial2");

        System.out.println("Cambiando Contraseña de empleados:");

        gestor.setContrasenaEmpleados("Empleado06");
        gestor.setPermisoVenta(emp1, true);
        gestor.setPermisoVenta(emp2, false);
        gestor.setPermisoMensajes(emp1, true);
        gestor.setPermisoMensajes(emp2, false);
        gestor.setPermisoRegulacion(emp1, true);
        gestor.setPermisoRegulacion(emp2, false);

        if (emp1.getContrasena().equals("Empleado06") && emp1.getNombre().equals("Gabi")) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Empleados:");
        System.out.println(emp1);
        System.out.println(emp2);

        System.out.println("Creando sorteo:");

        SorteoActivo sorteo = gestor.crearSorteo((Exposicion) exp1, 10, 2, LocalDateTime.now(),
                LocalDateTime.now().plusDays(1), LocalDateTime.now().plusDays(2));

        if (sorteo.getExposicion().equals(exp1) && sorteo.getNumGanadores() == 2) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
            System.out.println(sorteo);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        // EMPLEADO

        Visita v = gestor.addVisita(LocalDateTime.now().plusDays(1).plusHours(12), exp1);

        System.out.println(ANSI_BLUE + "TESTS DE EMPLEADO" + ANSI_RESET);

        System.out.println("login de empleado:");

        if (Sistema.login("4444", "Empleado06").getTipoUsuario().equals("Empleado")) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        Empleado empleado = (Empleado) Sistema.login("4444", "Empleado06");

        System.out.println("Empleado logueado:");
        System.out.println(empleado);

        System.out.println("Vendiendo entradas:");

        try {
            empleado.venderEntrada(exp1, v, 2);
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Cambiando temperatura:");
        empleado.cambiarTemperatura(20.00, s1);

        if (s1.getTemperatura() == 20.00) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
            System.out.println(s1);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Enviar mensaje:");
        empleado.enviarMensaje("Hola, buenos días", "Asunto", c);

        if (c.getNotificaciones().size() == 4) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
            for (Notificacion n : c.getNotificaciones()) {
                System.out.println(n.getAsunto() + "      De: " + n.getNombreAutor());
                System.out.println(n.getTexto());
            }
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        // CLIENTE

        System.out.println(ANSI_BLUE + "TESTS DE CLIENTE" + ANSI_RESET);

        System.out.println("login de cliente:");

        if (Sistema.login("1234", "PincelCli02").getTipoUsuario().equals("Cliente")) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        Cliente cliente = (Cliente) Sistema.login("1234", "PincelCli02");

        System.out.println("Cliente logueado:");
        System.out.println(cliente);

        System.out.println("Filtrando exposiciones:");
        System.out.println("Exposiciones disponibles:");
        for (Exposicion e : Sistema.getExposiciones()) {
            System.out.println(e.getNombre());
        }
        Filtro f = new Filtro(true, true, false, LocalDateTime.now(), LocalDateTime.now(), false, "");
        System.out.println("Exposiciones filtradas (Dejando las permanentes):");
        for (Exposicion e : f.filtrar(Sistema.getExposiciones())) {
            System.out.println(e.getNombre());
            if (e.getNombre().equals("Exposición Permanente")) {
                System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
            } else {
                System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
            }
        }

        System.out.println("Comprando entradas con descuento:");

        try {
            cliente.comprarEntrada(exp1, v, 2, "1111111111111111", Set.of("0"));
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Comprando entradas con descuento no aplicable:");

        try {
            cliente.comprarEntrada(exp2, v, 2, "1111111111111111", Set.of("1"));
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Comprando más entradas de las permitidas:");

        try {
            cliente.comprarEntrada(exp1, v, 999, "1111111111111111", Set.of("1"));
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        } catch (Exception ex) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        }

        System.out.println("Apuntándose a sorteo:");

        try {
            cliente.apuntarseSorteo(sorteo, 2);
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        gestor.sortear(sorteo);

        System.out.println("Sorteo realizado");

        System.out.println(cliente.getRecibeNotificaciones());

        System.out.println("Notificaciones:");

        for (Notificacion n : cliente.getNotificaciones()) {
            System.out.println(n.getAsunto() + "      De: " + n.getNombreAutor());
            System.out.println(n.getTexto());
        }

        System.out.println("Comprando con regalo:");

        String codigo = "";
        Set<String> codigos = new HashSet<>();
        for (Regalo r : cliente.getRegalos()) {
            codigo = r.getCodigo();
            codigos.add(codigo);
        }

        try {
            cliente.comprarEntrada(exp1, v, 2, "1111111111111111", codigos);
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception ex) {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        // ESTADISTICAS

        System.out.println(ANSI_BLUE + "TESTS DE ESTADISTICAS" + ANSI_RESET);

        System.out.println("Estadísticas de ventas:");

        int entradas = Sistema.getEntradasExp(LocalDateTime.now().minusDays(1), LocalDateTime.now().plusDays(2), exp1);
        int beneficio = Sistema.getBeneficioExp(LocalDateTime.now().minusDays(1), LocalDateTime.now().plusDays(2), exp1);
        if (entradas == 8 && beneficio == 55) {
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
            System.out.println("Entradas: " + entradas + " Beneficio: " + beneficio);
        } else {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        // GUARDAR Y CARGAR

        System.out.println(ANSI_BLUE + "TESTS DE GUARDAR Y CARGAR" + ANSI_RESET);

        System.out.println("Guardando sist:");
        try {
            Sistema.guardarSistema();
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception e) {
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Borrando cosas:");
        Sistema.eliminarUsuarios(g, c, emp1, emp2);

        System.out.println("Usuarios actuales:");
        for (UsuarioRegistrado u : Sistema.getUsuarios()) {
            System.out.println(u.getNombre());
        }

        System.out.println("Cargando sist:");

        try {
            Sistema.cargarSistema();
            System.out.println(ANSI_GREEN + "CORRECTO" + ANSI_RESET);
        } catch (Exception e) {
            System.out.println(e.getMessage());
            System.out.println(ANSI_RED + "INCORRECTO" + ANSI_RESET);
        }

        System.out.println("Usuarios actuales:");
        for (UsuarioRegistrado u : Sistema.getUsuarios()) {
            System.out.println(u.getNombre());
        }

        System.out.println(ANSI_BLUE + "-------FIN-------");
    }
}
