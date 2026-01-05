package galeria.exposicion;

import java.time.LocalDateTime;

import galeria.obra.*;
import galeria.sala.*;

/**
 * Clase que representa una exposición temporal.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Temporal extends Exposicion {
    private LocalDateTime fin;
    private static final long serialVersionUID = 1L;

    /**
     * Constructor de la clase Temporal.
     * 
     * @param nombre      el nombre de la exposición temporal
     * @param descripcion la descripción de la exposición temporal
     * @param inicio      la fecha y hora de inicio de la exposición temporal
     * @param fin         la fecha y hora de finalización de la exposición temporal
     */
    public Temporal(String nombre, String descripcion, LocalDateTime inicio, LocalDateTime fin) {
        super(nombre, descripcion, inicio);
        this.fin = fin;
    }

    /**
     * Constructor vacío de la clase Temporal.
     */
    public Temporal() {
        super();
    }

    /**
     * Obtiene la fecha y hora de finalización de la exposición temporal.
     * 
     * @return la fecha y hora de finalización de la exposición temporal
     */
    public LocalDateTime getFechaFin() {
        return fin;
    }

    /**
     * Prolonga la exposición temporal hasta una nueva fecha y hora.
     * 
     * @param newfin la nueva fecha y hora de finalización de la exposición temporal
     * @throws IllegalArgumentException si la fecha de finalización es anterior a la
     *                                  actual o si la exposición ya ha finalizado
     */
    public void Prolongar(LocalDateTime newfin) throws IllegalArgumentException {
        if (fin.isAfter(newfin) || fin.isEqual(newfin)) {
            throw new IllegalArgumentException("La fecha de finalización no puede ser anterior a la actual");
        } else if (getEstado() == EstadoExp.TERMINADA) {
            throw new IllegalArgumentException("La exposición ya ha finalizado");
        }
        fin = newfin;
    }

    /**
     * Función que envía todas las obras de la exposición al almacén.
     * 
     * @throws ObraExceptions si ocurre un error al enviar las obras al almacén al
     *                        terminar la exposición
     */
    private void terminar() throws ObraExceptions {
        try {
            for (Sala s : this.salas) {
                for (Obra o : s.getObras()) {
                    o.removeFromSala();
                }
            }
        } catch (ObraExceptions e) {
            throw e;
        }
    }

    /**
     * Obtiene el estado actual de la exposición temporal.
     * 
     * @return el estado actual de la exposición temporal
     */
    @Override
    public EstadoExp getEstado() {
        EstadoExp state = null;
        try {
            state = super.getEstado();
            if (LocalDateTime.now().isAfter(fin) || LocalDateTime.now().isEqual(fin)) {
                this.estado = EstadoExp.TERMINADA;
                state = EstadoExp.TERMINADA;
                this.terminar();
            }
        } catch (ObraExceptions e) {
            System.out.println("Error al enviar las obras al almacén al terminar la exposición");
        }
        return state;
    }

    /**
     * Verifica si la exposición temporal es permanente.
     * 
     * @return false, ya que la exposición temporal no es permanente
     */
    @Override
    public boolean esPermanente() {
        return false;
    }

    /**
     * Verifica si se puede agregar una obra a la exposición temporal.
     * 
     * @param propiedad indica si la obra es propiedad del museo
     * @return true si se puede agregar la obra, false en caso contrario
     */
    @Override
    public boolean addObraCheck(boolean propiedad) {
        if (propiedad) {
            return false;
        } else if (this.estado != EstadoExp.ENCREACION) {
            return false;
        }
        return true;
    }

    /**
     * Verifica si se puede quitar una obra de la exposición temporal.
     * 
     * @return true si se puede quitar la obra, false en caso contrario
     */
    @Override
    public boolean removeObraCheck() {
        if (this.estado == EstadoExp.COMENZADA || this.estado == EstadoExp.PUBLICADA) {
            return false;
        }
        return true;
    }

    /**
     * Verifica si se puede restaurar una obra de la exposición temporal.
     * 
     * @return true si se puede restaurar la obra, false en caso contrario
     */
    @Override
    public boolean restaurarObraCheck() {
        if (this.estado == EstadoExp.COMENZADA) {
            return false;
        }
        return true;
    }
}
