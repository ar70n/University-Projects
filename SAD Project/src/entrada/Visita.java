package entrada;

import java.time.LocalDateTime;
import java.util.List;
import java.util.ArrayList;

import java.io.Serializable;

import galeria.exposicion.*;

/**
 * Representa una visita a una exposición.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Visita implements Serializable {
    private Exposicion exposicion;
    private LocalDateTime fecha;
    private List<Entrada> entradas = new ArrayList<Entrada>();
    private int reservas;
    private static int idCount = 0;
    private int id;
    private static final long serialVersionUID = 1L;

    /**
     * Crea una nueva instancia de la clase Visita.
     * 
     * @param fecha la fecha y hora de la visita
     * @param expo  la exposición a la que se realiza la visita
     */
    public Visita(LocalDateTime fecha, Exposicion expo) {
        this.fecha = fecha;
        this.exposicion = expo;
        reservas = 0;
        id = idCount;
        idCount++;
    }

    /**
     * Crea una nueva instancia de la clase Visita.
     * 
     * @param fecha la fecha y hora de la visita
     * @param id    el identificador único de la visita
     */
    public Visita(LocalDateTime fecha, int id) {
        this.fecha = fecha;
        this.id = id;
    }

    /**
     * Obtiene la fecha y hora de la visita.
     * 
     * @return la fecha y hora de la visita
     */
    public LocalDateTime getFecha() {
        return fecha;
    }

    /**
     * Obtiene el número total de entradas para la visita.
     * 
     * @return el número total de entradas para la visita
     */
    public int getNEntradas() {
        if (entradas == null)
            return 0;

        return entradas.size() + reservas;
    }

    /**
     * Obtiene la lista de entradas asociadas a la visita.
     * 
     * @return la lista de entradas asociadas a la visita
     */
    public List<Entrada> getEntradas() {
        return entradas;
    }

    /**
     * Obtiene el identificador único de la visita.
     * 
     * @return el identificador único de la visita
     */
    public int getId() {
        return id;
    }

    /**
     * Realiza una reserva de entradas para la visita.
     * 
     * @param reservas el número de entradas a reservar
     */
    public void reservar(int reservas) {
        this.reservas += reservas;
    }

    /**
     * Obtiene el aforo disponible para la visita.
     * 
     * @return el aforo disponible para la visita
     */
    public int aforoDisponible() {
        return exposicion.getAforo() - getNEntradas();
    }

    /**
     * Obtiene la exposición asociada a la visita.
     * 
     * @return la exposición asociada a la visita
     */
    public Exposicion getExposicion() {
        return exposicion;
    }

    /**
     * Agrega una entrada a la lista de entradas asociadas a la visita.
     * 
     * @param e la entrada a agregar
     */
    public void addEntrada(Entrada e) {
        entradas.add(e);
    }
}