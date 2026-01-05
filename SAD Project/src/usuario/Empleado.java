package usuario;

import galeria.exposicion.*;
import galeria.sala.SalaRaiz;
import mensaje.Mensaje;
import sistema.Compra;
import sistema.Sistema;
import es.uam.eps.padsof.tickets.*;

import entrada.*;

/**
 * Esta clase representa a un empleado en el sistema.
 * Extiende la clase UsuarioRegistrado.
 *
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Empleado extends UsuarioRegistrado {
    private static final long serialVersionUID = 1L;
    private String cuenta;
    private String direccion;
    private String SeguridadSocial;
    private boolean mensajes;
    private boolean temperaturaHumedad;
    private boolean venta;
    private static String contrasenaEmpleado;

    /**
     * Constructor de la clase Empleado.
     *
     * @param nif                el NIF del empleado
     * @param nombre             el nombre del empleado
     * @param cuenta             la cuenta del empleado
     * @param direccion          la dirección del empleado
     * @param SeguridadSocial    el número de seguridad social del empleado
     * @param mensajes           indica si el empleado tiene permiso para enviar
     *                           mensajes
     * @param temperaturaHumedad indica si el empleado tiene permiso para regular la
     *                           temperatura y humedad
     * @param venta              indica si el empleado tiene permiso para vender
     *                           entradas
     */
    public Empleado(String nif, String nombre, String cuenta, String direccion, String SeguridadSocial,
            boolean mensajes, boolean temperaturaHumedad, boolean venta) {
        super(nif, nombre, contrasenaEmpleado);
        this.cuenta = cuenta;
        this.direccion = direccion;
        this.SeguridadSocial = SeguridadSocial;
        this.mensajes = mensajes;
        this.temperaturaHumedad = temperaturaHumedad;
        this.venta = venta;
    }

    /**
     * Método para enviar un mensaje a uno o varios usuarios.
     *
     * @param texto   el texto del mensaje
     * @param asunto  el asunto del mensaje
     * @param usuario los usuarios a los que se enviará el mensaje
     * @return true si el mensaje se envió correctamente, false si no
     */
    public boolean enviarMensaje(String texto, String asunto, UsuarioRegistrado... usuario) {
        Mensaje m = new Mensaje(this, texto, asunto);
        if (!mensajes) {
            return false;
        }
        for (UsuarioRegistrado u : usuario) {
            u.recibirNotificacion(m);
        }
        return true;
    }

    /**
     * Método para vender entradas para una exposición.
     *
     * @param e         la exposición para la que se venden las entradas
     * @param visita    la visita para la que se venden las entradas
     * @param nEntradas el número de entradas a vender
     * @throws IllegalArgumentException si se producen errores en los parámetros
     */
    public void venderEntrada(Exposicion e, Visita visita, int nEntradas) {
        double precioFinal = e.getPrecioEntrada() * nEntradas;
        if (!venta) {
            throw new IllegalArgumentException("No puedes vender entradas");
        }

        if (visita.getFecha().isBefore(e.getFechaInicio())) {
            throw new IllegalArgumentException("La exposición aún no ha comenzado");
        }

        if (e.getEstado() != EstadoExp.PUBLICADA && e.getEstado() != EstadoExp.COMENZADA) {
            throw new IllegalArgumentException("La exposición no está publicada");
        }

        if (nEntradas <= 0) {
            throw new IllegalArgumentException("El número de entradas debe ser mayor que 0");
        }

        if (visita.aforoDisponible() < nEntradas) {
            throw new IllegalArgumentException("No hay suficiente aforo disponible");
        }

        System.out.println("Precio: " + precioFinal);

        // PAGO

        Compra compra = new Compra(precioFinal/nEntradas, nEntradas, visita.getFecha(), visita.getExposicion());
        Sistema.registrarCompra(compra);

        Entrada entrada = new Entrada(visita);
        visita.addEntrada(entrada);

        // GENERAR PDF

        try {
            new Ticket(visita, e, precioFinal, nEntradas).generarPDF();
        } catch (NonExistentFileException ex) {
            throw new IllegalArgumentException("No se ha podido generar el PDF (fichero no encontrado)");
        } catch (UnsupportedImageTypeException ex) {
            throw new IllegalArgumentException("No se ha podido generar el PDF (tipo de imagen no soportado)");
        }
    }

    /**
     * Método para establecer el permiso de envío de mensajes.
     *
     * @param mensajes indica si el empleado tiene permiso para enviar mensajes
     */
    public void setPermisoMensajes(boolean mensajes) {
        this.mensajes = mensajes;
    }

    /**
     * Método para establecer el permiso de regulación de temperatura y humedad.
     *
     * @param temperaturaHumedad indica si el empleado tiene permiso para regular la
     *                           temperatura y humedad
     */
    public void setPermisoRegulacion(boolean temperaturaHumedad) {
        this.temperaturaHumedad = temperaturaHumedad;
    }

    /**
     * Método para establecer el permiso de venta de entradas.
     *
     * @param venta indica si el empleado tiene permiso para vender entradas
     */
    public void setPermisoVenta(boolean venta) {
        this.venta = venta;
    }

    /**
     * Método estático para establecer la contraseña de los empleados.
     *
     * @param contrasena la contraseña a establecer
     */
    public static void setContrasenaEmpleados(String contrasena) {
        contrasenaEmpleado = contrasena;
    }

    /**
     * Método para cambiar la temperatura de una sala.
     *
     * @param temperatura la nueva temperatura
     * @param sala        la sala en la que se cambiará la temperatura
     * @throws IllegalArgumentException si se producen errores en los parámetros
     */
    public void cambiarTemperatura(double temperatura, SalaRaiz sala) {
        if (!temperaturaHumedad || temperatura < 0 || sala == null || sala.getRegulable() == false) {
            throw new IllegalArgumentException("No puedes cambiar la temperatura");
        }
        sala.setTemperatura(temperatura);
    }

    /**
     * Método para cambiar la humedad de una sala.
     *
     * @param humedad la nueva humedad
     * @param sala    la sala en la que se cambiará la humedad
     * @throws IllegalArgumentException si se producen errores en los parámetros
     */
    public void cambiarHumedad(double humedad, SalaRaiz sala) {
        if (!temperaturaHumedad || humedad < 0 || sala == null || sala.getRegulable() == false) {
            throw new IllegalArgumentException("No puedes cambiar la humedad");
        }
        sala.setHumedad(humedad);
    }

    /**
     * Método para obtener el tipo de usuario.
     *
     * @return el tipo de usuario
     */
    public String getTipoUsuario() {
        return "Empleado";
    }

    /**
     * Método para obtener la contraseña del empleado.
     *
     * @return la contraseña del empleado
     */
    public String getContrasena() {
        return contrasenaEmpleado;
    }

    /**
     * Método para obtener el permiso de envío de mensajes.
     * 
     * @return el permiso de envío de mensajes
     */
    public boolean getPermisoMensajes() {
        return mensajes;
    }

    /**
     * Método para obtener el permiso de regulación de temperatura y humedad.
     * 
     * @return el permiso de regulación de temperatura y humedad
     */
    public boolean getPermisoRegulacion() {
        return temperaturaHumedad;
    }

    /**
     * Método para obtener el permiso de venta de entradas.
     * 
     * @return el permiso de venta de entradas
     */
    public boolean getPermisoVenta() {
        return venta;
    }

    /**
     * Método para obtener la contraseña de los empleados.
     * 
     * @return la contraseña de los empleados
     */
    public static String getContrasenaEmpleado() {
        return contrasenaEmpleado;
    }


    /**
     * Método toString para representar el objeto Empleado como una cadena de texto.
     *
     * @return la representación del objeto Empleado como una cadena de texto
     */
    @Override
    public String toString() {
        return "Empleado [Cuenta=" + cuenta + ", Direccion=" + direccion + ", SeguridadSocial=" + SeguridadSocial
                + ", Mensajes=" + mensajes + ", TemperaturaHumedad=" + temperaturaHumedad + ", Venta=" + venta + "]";
    }
}
