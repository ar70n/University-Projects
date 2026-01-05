package galeria.exposicion;

import java.time.LocalDateTime;

import entrada.Visita;

/**
 * Clase que representa una exposición permanente en una galería.
 * Extiende de la clase Exposicion.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Permanente extends Exposicion {
    private static final long serialVersionUID = 1L;
    private LocalDateTime inicioCierre;
    private LocalDateTime finCierre;
    private boolean cierrePorRenovacion;

    // Constructores

    /**
     * Crea una nueva exposición permanente con el nombre, descripción y fecha de
     * inicio especificados.
     * 
     * @param nombre      El nombre de la exposición permanente.
     * @param descripcion La descripción de la exposición permanente.
     * @param inicio      La fecha de inicio de la exposición permanente.
     */
    public Permanente(String nombre, String descripcion, LocalDateTime inicio) {
        super(nombre, descripcion, inicio);
        this.inicioCierre = null;
        this.finCierre = null;
    }

    /**
     * Crea una nueva exposición permanente sin especificar ningún atributo.
     */
    public Permanente() {
        super();
    }

    // Getters

    /**
     * Obtiene la fecha de inicio del cierre de la exposición permanente.
     * 
     * @return La fecha de inicio del cierre.
     */
    public LocalDateTime getInicioCierre() {
        return inicioCierre;
    }

    /**
     * Obtiene la fecha de fin del cierre de la exposición permanente.
     * 
     * @return La fecha de fin del cierre.
     */
    public LocalDateTime getFinCierre() {
        return finCierre;
    }

    /**
     * Verifica si el cierre de la exposición permanente es por renovación.
     * 
     * @return true si es por renovación, false si es por mantenimiento.
     */
    public boolean isCierrePorRenovacion() {
        return cierrePorRenovacion;
    }

    // Setters

    /**
     * Establece el estado de la exposición permanente.
     * 
     * @param estado El estado de la exposición permanente.
     */
    public void setEstado(EstadoExp estado) {
        this.estado = estado;
    }

    /**
     * Establece la fecha de inicio del cierre de la exposición permanente.
     * 
     * @param inicioCierre La fecha de inicio del cierre.
     */
    void setInicioCierre(LocalDateTime inicioCierre) {
        this.inicioCierre = inicioCierre;
    }

    /**
     * Establece la fecha de fin del cierre de la exposición permanente.
     * 
     * @param finCierre La fecha de fin del cierre.
     */
    void setFinCierre(LocalDateTime finCierre) {
        this.finCierre = finCierre;
    }

    /**
     * Establece si el cierre de la exposición permanente es por renovación o por
     * mantenimiento.
     * 
     * @param cierrePorRenovacion true si es por renovación, false si es por
     *                            mantenimiento.
     */
    void setCierrePorRenovacion(boolean cierrePorRenovacion) {
        this.cierrePorRenovacion = cierrePorRenovacion;
    }

    // Metodos complejos

    /**
     * Verifica si la exposición permanente está suspendida en el momento actual.
     * 
     * @return true si está suspendida, false si no lo está.
     */
    public boolean estaSuspensa() {
        if (inicioCierre == null || finCierre == null) {
            return false;
        } else if (LocalDateTime.now().isAfter(inicioCierre) && LocalDateTime.now().isBefore(finCierre)) {
            return true;
        }

        return false;
    }

    /**
     * Verifica si la exposición permanente está suspendida en las fechas
     * especificadas.
     * 
     * @param inicioCierre La fecha de inicio del cierre.
     * @param finCierre    La fecha de fin del cierre.
     * @return true si está suspendida, false si no lo está.
     */
    public boolean estaSuspensa(LocalDateTime inicioCierre, LocalDateTime finCierre) {
        if (inicioCierre == null || finCierre == null) {
            return false;
        } else if (LocalDateTime.now().isAfter(inicioCierre) && LocalDateTime.now().isBefore(finCierre)) {
            return true;
        }

        return false;
    }

    /**
     * Programa la suspensión de la exposición permanente en las fechas
     * especificadas.
     * 
     * @param inicio        La fecha de inicio del cierre.
     * @param fin           La fecha de fin del cierre.
     * @param mantenimiento Indica si el cierre es por renovación (true) o por
     *                      mantenimiento (false).
     * @throws Exception Si no se puede suspender la exposición en las fechas
     *                   especificadas debido a visitas programadas.
     */
    public void programarSuspension(LocalDateTime inicio, LocalDateTime fin, boolean mantenimiento) throws Exception {
        if (inicio.isAfter(fin)) {
            throw new Exception("La fecha de inicio no puede ser posterior a la fecha de fin");
        }
        for (Visita visita : visitas) {
            if ((visita.getFecha().isAfter(inicio) || visita.getFecha().isEqual(inicio) ) && visita.getFecha().isBefore(fin) && visita.getNEntradas() > 0) {
                throw new Exception("No se puede suspender la exposición en esas fechas, hay visitas programadas");
            }
        }

        inicioCierre = inicio;
        finCierre = fin;
        cierrePorRenovacion = mantenimiento;
    }

    @Override
    public boolean esPermanente() {
        return true;
    }

    @Override
    public boolean addObraCheck(boolean propiedad) {
        if (this.estado == EstadoExp.ENCREACION) {
            return true;
        } else if (this.inicioCierre != null && this.finCierre != null && LocalDateTime.now().isAfter(this.inicioCierre)
                && LocalDateTime.now().isBefore(this.finCierre)) {
            if (this.cierrePorRenovacion) {
                return true;
            }
        }

        return false;
    }

    @Override
    public boolean removeObraCheck() {
        System.out.println(this.estado);
        if (this.estado != EstadoExp.COMENZADA && this.estado != EstadoExp.PUBLICADA && this.estado != null) {
            return true; 
        } else if (this.inicioCierre != null && this.finCierre != null && LocalDateTime.now().isAfter(this.inicioCierre)
                && LocalDateTime.now().isBefore(this.finCierre)) {
            if (this.cierrePorRenovacion == true) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean restaurarObraCheck() {
        if (this.estado != EstadoExp.COMENZADA) {
            return true;
        }
        if (this.inicioCierre != null && this.finCierre != null && LocalDateTime.now().isAfter(this.inicioCierre)
                && LocalDateTime.now().isBefore(this.finCierre)) {
            return true;
        }
        return false;
    }

}