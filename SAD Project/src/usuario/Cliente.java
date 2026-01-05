package usuario;

import es.uam.eps.padsof.telecard.*;
import es.uam.eps.padsof.tickets.*;
import galeria.exposicion.*;
import mensaje.*;
import descuento.*;
import java.time.LocalDateTime;
import java.util.Set;
import entrada.*;
import java.util.HashSet;

import sistema.*;

/**
 * Esta clase representa a un cliente registrado en el sistema.
 * Hereda de la clase UsuarioRegistrado.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Cliente extends UsuarioRegistrado {
    private static final long serialVersionUID = 1L;
    private boolean recibeNotificaciones;
    private LocalDateTime fechaPenalizacion;
    private LocalDateTime fechaUltimaCompra;

    private Set<Regalo> regalos = new HashSet<>();

    /**
     * Constructor de la clase Cliente.
     * 
     * @param nif        el NIF del cliente
     * @param nombre     el nombre del cliente
     * @param contrasena la contraseña del cliente
     */
    public Cliente(String nif, String nombre, String contrasena) {
        super(nif, nombre, contrasena);
        recibeNotificaciones = false;
        fechaPenalizacion = null;
        fechaUltimaCompra = null;

    }

    public Cliente() {
        //TODO Auto-generated constructor stub
    }

    /**
     * Método para apuntarse a un sorteo activo.
     * 
     * @param s         el sorteo activo
     * @param nEntradas el número de entradas a participar en el sorteo
     * 
     * @throws IllegalArgumentException si aún está penalizado,
     *                                  si ya está apuntado al sorteo
     */
    public void apuntarseSorteo(SorteoActivo s, int nEntradas) {
        boolean penalizado = false;
        Set<Regalo> regalos_acabados = new HashSet<>();
        for (Regalo r : regalos) {
            if (r.getValidezFinal().isBefore(LocalDateTime.now())) {
                if (r.getValidezFinal().plusMonths(r.getMesesPenalizacion()).isAfter(LocalDateTime.now())) {
                    penalizado = true;
                } else {
                    regalos_acabados.add(r);
                }
            }
        }
        regalos.removeAll(regalos_acabados);
        if (penalizado) {
            throw new IllegalArgumentException("Aún estás penalizado");
        }
        if (fechaPenalizacion != null && LocalDateTime.now().isBefore(fechaPenalizacion)) {
            throw new IllegalArgumentException("Aún estás penalizado");
        }
        if (s.getParticipantes().contains(this)) {
            throw new IllegalArgumentException("Ya estás apuntado al sorteo");
        }

        Inscripcion i = new Inscripcion(nEntradas, this);
        s.addInscripcion(i);
    }

    /**
     * Método para recibir un regalo.
     * 
     * @param regalo el regalo a recibir
     */
    public void recibirRegalo(Regalo regalo) {
        regalos.add(regalo);
    }

    /**
     * Método para comprobar los regalos.
     */
    public void comprobarRegalos() {

    }

    /**
     * Método para comprar una entrada para una exposición.
     * 
     * @param e          la exposición
     * @param visita     la visita a la exposición
     * @param nEntradas  el número de entradas a comprar
     * @param cardNumber el número de tarjeta de crédito
     * @param codigos    los códigos de regalo a utilizar
     * 
     * @throws InvalidCardNumberException        si el número de tarjeta no es
     *                                           válido
     * @throws FailedInternetConnectionException si hay un error de conexión al
     *                                           realizar el pago
     * @throws OrderRejectedException            si hay un error en el pago
     * @throws IllegalArgumentException          si el número de entradas es menor o
     *                                           igual a 0,
     *                                           si no hay suficiente aforo
     *                                           disponible para la visita,
     *                                           si la exposición aún no ha
     *                                           comenzado,
     *                                           si la exposición no está publicada
     */
    public void comprarEntrada(Exposicion e, Visita visita, int nEntradas, String cardNumber, Set<String> codigos)
            throws InvalidCardNumberException, FailedInternetConnectionException, OrderRejectedException {
        double precioFinal = e.getPrecioEntrada() * nEntradas;

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

        // COMPROBAR DESCUENTOS (PUEDE CAMBIAR DEPENDIENDO DE CÓMO SE ENTIENDA EL
        // SISTEMA DE CÓDIGOS)

        // COMPROBAR REGALOS

        Set<Regalo> regalos_usados = new HashSet<>();
        int n_regalos = 0;

        if (regalos != null) {
            for (Regalo r : regalos) {
                if (r.getExposicion() == e && codigos.contains(r.getCodigo())
                        && visita.getFecha().isAfter(r.getValidezInicio())
                        && visita.getFecha().isBefore(r.getValidezFinal())) {
                    precioFinal = Math.max(0, precioFinal - e.getPrecioEntrada());
                    n_regalos++;
                    regalos_usados.add(r);
                }
                if (precioFinal == 0) {
                    break;
                }
            }
        }

        regalos.removeAll(regalos_usados);
        visita.reservar(-n_regalos); // Así, eliminamos las reservas de regalos que se han usado, porque si no
                                     // contarían dob

        // COMPROBAR DESCUENTOS

        if (e.getDescuentos() != null) {
            for (Descuento d : e.getDescuentos()) {
                if (d.esFidelidad()) {
                    if (fechaUltimaCompra != null
                            && fechaUltimaCompra.isAfter(LocalDateTime.now().minusMonths(((Fidelidad) d).getMeses()))) {
                        precioFinal = Math.max(0, precioFinal - d.getPorcentaje() * precioFinal / 100);
                    }
                } else {
                    if (LocalDateTime.now().isAfter(visita.getFecha().minusDays(((Antelacion) d).getDias()))) {
                        precioFinal = Math.max(0, precioFinal - d.getPorcentaje() * precioFinal / 100);
                    }
                }
            }
        }

        // PAGO
        pagar(precioFinal, cardNumber);

        Compra compra = new Compra(precioFinal/nEntradas, nEntradas, visita.getFecha(), visita.getExposicion());
        Sistema.registrarCompra(compra);

        Entrada entrada = new Entrada(visita, cardNumber);
        entrada.setCliente(this);
        visita.addEntrada(entrada);

        // GENERAR PDF
        try {
            new Ticket(visita, e, precioFinal, nEntradas).generarPDF();
            fechaUltimaCompra = LocalDateTime.now();
        } catch (NonExistentFileException ex) {
            System.out.println("No se ha podido generar el PDF");
            throw new IllegalArgumentException("No se ha podido generar el PDF");
        } catch (UnsupportedImageTypeException ex) {
            System.out.println("Imagen inválida");
            throw new IllegalArgumentException("Imagen inválida");
        }
    }

    /**
     * Método para establecer si el cliente recibe notificaciones.
     * 
     * @param recibeNotificaciones true si el cliente recibe notificaciones, false
     *                             en caso contrario
     */
    public void setRecibeNotificaciones(boolean recibeNotificaciones) {
        this.recibeNotificaciones = recibeNotificaciones;
    }

    /**
     * Método para obtener si el cliente recibe notificaciones.
     * 
     * @return true si el cliente recibe notificaciones, false en caso contrario
     */
    public boolean getRecibeNotificaciones() {
        return recibeNotificaciones;
    }

    /**
     * Método para recibir una notificación.
     * 
     * @param m la notificación a recibir
     */
    public void recibirNotificacion(Notificacion m) {
        if (recibeNotificaciones == true) {
            super.recibirNotificacion(m);
        }
    }

    /**
     * Método para editar el perfil del cliente.
     * 
     * @param nombre     el nuevo nombre del cliente
     * @param contrasena la nueva contraseña del cliente
     */
    public void editarPerfil(String nombre, String contrasena) {
        this.nombre = nombre;
        this.contrasena = contrasena;
    }

    /**
     * Método para realizar el pago de una cantidad con una tarjeta de crédito.
     * 
     * @param cantidad   la cantidad a pagar
     * @param cardNumber el número de tarjeta de crédito
     * 
     * @throws IllegalArgumentException si el número de tarjeta no es válido,
     *                                  si hay un error de conexión al realizar el
     *                                  pago,
     *                                  si hay un error en el pago
     */
    public void pagar(double cantidad, String cardNumber) {
        if (!TeleChargeAndPaySystem.isValidCardNumber(cardNumber)) {
            System.out.println("El número de tarjeta no es válido");
            throw new IllegalArgumentException("El número de tarjeta no es válido");
        }

        try {
            TeleChargeAndPaySystem.charge(cardNumber, "Entrada exposición", cantidad, true);
        } catch (FailedInternetConnectionException ex) {
            System.out.println("Error de conexión");
            throw new IllegalArgumentException("Error de conexión");
        } catch (OrderRejectedException ex) {
            System.out.println("Error en el pago");
            throw new IllegalArgumentException("Error en el pago");
        }
    }

    /**
     * Método para obtener el tipo de usuario.
     * 
     * @return el tipo de usuario
     */
    public String getTipoUsuario() {
        return "Cliente";
    }

    /**
     * Método para obtener los regalos del cliente.
     * 
     * @return los regalos del cliente
     */
    public Set<Regalo> getRegalos() {
        return regalos;
    }

    /**
     * Método toString para representar el objeto Cliente como una cadena de texto.
     * 
     * @return la representación del objeto Cliente como una cadena de texto
     */
    @Override
    public String toString() {
        return "Cliente [recibeNotificaciones=" + recibeNotificaciones + ", fechaPenalizacion=" + fechaPenalizacion
                + ", regalos=" + regalos + ", nif=" + nif + ", nombre=" + nombre + ", contrasena=" + contrasena + "]";
    }

    /**
     * Esta función se utiliza únicamente para facilitar el testeo de la clase
     * 
     * @param fechaPenalizacion la fecha de penalización
     */
    public void setFechaPenalizacion(LocalDateTime fechaPenalizacion) {
        this.fechaPenalizacion = fechaPenalizacion;
    }

    
}
