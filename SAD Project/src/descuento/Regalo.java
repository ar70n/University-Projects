package descuento;

import galeria.exposicion.Exposicion;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * Clase que representa un regalo.
 * 
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Regalo implements Serializable {
    private String codigo;
    private LocalDateTime validezInicio;
    private LocalDateTime validezFinal;
    private int mesesPenalizacion;
    private Exposicion exposicion;
    private static final long serialVersionUID = 1L;

    /**
     * Constructor de la clase Regalo.
     * 
     * @param codigo            El código del regalo.
     * @param validezInicio     La fecha y hora de inicio de validez del regalo.
     * @param validezFinal      La fecha y hora de finalización de validez del
     *                          regalo.
     * @param mesesPenalizacion El número de meses de penalización asociados al
     *                          regalo.
     * @param exposicion        La exposición asociada al regalo.
     * 
     * @throws NullPointerException Si alguno de los parámetros es nulo.
     */
    public Regalo(String codigo, LocalDateTime validezInicio, LocalDateTime validezFinal, int mesesPenalizacion,
            Exposicion exposicion) {
        this.codigo = codigo;
        this.validezInicio = validezInicio;
        this.validezFinal = validezFinal;
        this.mesesPenalizacion = mesesPenalizacion;
        this.exposicion = exposicion;
    }

    /**
     * Obtiene la exposición asociada al regalo.
     * 
     * @return La exposición asociada al regalo.
     */
    public Exposicion getExposicion() {
        return exposicion;
    }

    /**
     * Obtiene el código del regalo.
     * 
     * @return El código del regalo.
     */
    public String getCodigo() {
        return codigo;
    }

    /**
     * Obtiene la fecha y hora de inicio de validez del regalo.
     * 
     * @return La fecha y hora de inicio de validez del regalo.
     */
    public LocalDateTime getValidezInicio() {
        return validezInicio;
    }

    /**
     * Obtiene la fecha y hora de finalización de validez del regalo.
     * 
     * @return La fecha y hora de finalización de validez del regalo.
     */
    public LocalDateTime getValidezFinal() {
        return validezFinal;
    }

    /**
     * Obtiene el número de meses de penalización asociados al regalo.
     * 
     * @return El número de meses de penalización asociados al regalo.
     */
    public int getMesesPenalizacion() {
        return mesesPenalizacion;
    }
}
