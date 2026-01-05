package sistema;

import java.time.LocalDateTime;
import galeria.exposicion.Exposicion;
import galeria.exposicion.*;
import galeria.obra.*;

import java.util.HashSet;
import java.util.Set;

/**
 * Clase que modela los filtros que se pueden aplicar a las consultas de
 * las estadisticas de la aplicacion.
 *
 * @version 1.0 23 May 2020
 */

/**
 * Clase que representa un filtro para las exposiciones.
 * Permite filtrar exposiciones según diferentes criterios.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Filtro {

  /**
   * Indica si se debe aplicar el filtro de permanencia.
   */
  private boolean fPermanencia;

  /**
   * Indica si la exposición debe ser permanente o no.
   */
  private boolean permanente;

  /**
   * Indica si se debe aplicar el filtro de fecha.
   */
  private boolean fFecha;

  /**
   * Fecha de inicio para el filtro de fecha.
   */
  private LocalDateTime inicio;

  /**
   * Fecha de fin para el filtro de fecha.
   */
  private LocalDateTime fin;

  /**
   * Indica si se debe aplicar el filtro de tipo de obra.
   */
  private boolean fObra;

  /**
   * Tipo de obra para el filtro de tipo de obra.
   */
  private String tipoObra;

  /**
   * Crea un nuevo objeto Filtro con los parámetros especificados.
   * 
   * @param fPermanencia Indica si se debe aplicar el filtro de permanencia.
   * @param permanente   Indica si la exposición debe ser permanente o no.
   * @param fFecha       Indica si se debe aplicar el filtro de fecha.
   * @param inicio       Fecha de inicio para el filtro de fecha.
   * @param fin          Fecha de fin para el filtro de fecha.
   * @param fObra        Indica si se debe aplicar el filtro de tipo de obra.
   * @param tipoObra     Tipo de obra para el filtro de tipo de obra.
   */
  public Filtro(boolean fPermanencia, boolean permanente, boolean fFecha, LocalDateTime inicio, LocalDateTime fin,
      boolean fObra, String tipoObra) {
    this.fPermanencia = fPermanencia;
    this.permanente = permanente;
    this.fFecha = fFecha;
    this.inicio = inicio;
    this.fin = fin;
    this.fObra = fObra;
    this.tipoObra = tipoObra;
  }

  /**
   * Filtra una exposición según los criterios especificados en el filtro.
   * 
   * @param e La exposición a filtrar.
   * @return true si la exposición cumple con los criterios del filtro, false de
   *         lo contrario.
   */
  public boolean filtrar(Exposicion e) {
    if (fPermanencia) {
      if ((permanente && !e.esPermanente()) || (!permanente && e.esPermanente())) {
        return false;
      }
    }
    if (fFecha) {
      if (e.esPermanente()) {
        if (inicio.isAfter(e.getFechaInicio())) {
          return false;
        }
      } else {
        if (inicio.isAfter(e.getFechaInicio()) || fin.isBefore(((Temporal) e).getFechaFin())) {
          return false;
        }
      }
    }
    if (fObra) {
      for (Obra o : e.getObras()) {
        if (o.getTipo().equals(tipoObra)) {
          return true;
        }
      }
      return false;
    }

    return true;
  }

  /**
   * Filtra un conjunto de exposiciones según los criterios especificados en el
   * filtro.
   * 
   * @param expos El conjunto de exposiciones a filtrar.
   * @return Un conjunto de exposiciones que cumplen con los criterios del filtro.
   */
  public Set<Exposicion> filtrar(Set<Exposicion> expos) {
    Set<Exposicion> res = new HashSet<>();
    for (Exposicion e : expos) {
      if (filtrar(e)) {
        res.add(e);
      }
    }
    return res;
  }
}