package descuento;

import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Set;
import java.util.Random;
import java.util.List;
import java.util.ArrayList;

import galeria.exposicion.*;
import usuario.*;
import entrada.Visita;
import sistema.Sistema;

import java.io.Serializable;

/**
 * Clase que representa un sorteo activo.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class SorteoActivo implements Serializable {
    private int penalizacion;
    private int entradas; // Numero de entradas que se sortean. Máximo 2
    private LocalDateTime finSorteo;
    private LocalDateTime validezInicio;
    private LocalDateTime validezFinal;
    private static final long serialVersionUID = 1L;

    private Exposicion exposicion;
    private Set<Inscripcion> inscripciones;

    /**
     * Constructor de la clase SorteoActivo.
     * 
     * @param penalizacion  la penalización asociada al sorteo activo
     * @param entradas      el número de entradas disponibles para el sorteo activo
     * @param finSorteo     la fecha y hora de finalización del sorteo activo
     * @param validezInicio la fecha y hora de inicio de validez del sorteo activo
     * @param validezFinal  la fecha y hora de finalización de validez del sorteo
     *                      activo
     * @param e             la exposición asociada al sorteo activo
     * @throws IllegalArgumentException si el número de entradas es mayor a 2
     */
    public SorteoActivo(int penalizacion, int entradas, LocalDateTime finSorteo, LocalDateTime validezInicio,
            LocalDateTime validezFinal, Exposicion e) throws IllegalArgumentException {
        if (entradas > 2) {
            throw new IllegalArgumentException("El número de entradas no puede ser mayor a 2");
        }

        this.penalizacion = penalizacion;
        this.entradas = entradas;
        this.finSorteo = finSorteo;
        this.validezInicio = validezInicio;
        this.validezFinal = validezFinal;
        this.exposicion = e;
        this.inscripciones = new HashSet<>();

        if (validezInicio == validezFinal) {
            try {
                reservarEntradas();
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
            }
        }
    }

    /**
     * Establece la penalización asociada al sorteo activo.
     * 
     * @param penalizacion la penalización asociada al sorteo activo
     */
    public void setPenalizacion(int penalizacion) {
        this.penalizacion = penalizacion;
    }

    /**
     * Obtiene la penalización asociada al sorteo activo.
     * 
     * @return la penalización asociada al sorteo activo
     */
    public int getPenalizacion() {
        return penalizacion;
    }

    /**
     * Establece el número de entradas disponibles para el sorteo activo.
     * 
     * @param entradas el número de entradas disponibles para el sorteo activo
     */
    public void setEntradas(int entradas) {
        this.entradas = entradas;
    }

    /**
     * Obtiene el número de entradas disponibles para el sorteo activo.
     * 
     * @return el número de entradas disponibles para el sorteo activo
     */
    public int getEntradas() {
        return entradas;
    }

    /**
     * Establece la fecha y hora de finalización del sorteo activo.
     * 
     * @param fecha la fecha y hora de finalización del sorteo activo
     */
    public void setFechaFin(LocalDateTime fecha) {
        this.finSorteo = fecha;
    }

    /**
     * Obtiene la fecha y hora de finalización del sorteo activo.
     * 
     * @return la fecha y hora de finalización del sorteo activo
     */
    public LocalDateTime getFechaFin() {
        return finSorteo;
    }

    /**
     * Establece las fechas de inicio y finalización de validez del sorteo activo.
     * 
     * @param validezInicio la fecha y hora de inicio de validez del sorteo activo
     * @param validezFinal  la fecha y hora de finalización de validez del sorteo
     *                      activo
     */
    public void setValidez(LocalDateTime validezInicio, LocalDateTime validezFinal) {
        this.validezInicio = validezInicio;
        this.validezFinal = validezFinal;
    }

    /**
     * Obtiene la fecha y hora de inicio de validez del sorteo activo.
     * 
     * @return la fecha y hora de inicio de validez del sorteo activo
     */
    public LocalDateTime getValidezInicio() {
        return validezInicio;
    }

    /**
     * Obtiene la fecha y hora de finalización de validez del sorteo activo.
     * 
     * @return la fecha y hora de finalización de validez del sorteo activo
     */
    public LocalDateTime getValidezFinal() {
        return validezFinal;
    }

    /**
     * Realiza el sorteo y entrega los regalos a los ganadores.
     */
    public void darRegalos() {
        Random rand = new Random();
        List<Inscripcion> temp = new ArrayList<>(inscripciones);
        Cliente ganador = null;
        Inscripcion inscripcion;
        Regalo regalo;
        String mensaje;
        int count = 0;
        int index = 0;
        int entradas = 0;

        while (count < this.entradas) {
            if(temp.size() == 0) break;
            index = rand.nextInt(temp.size());
            inscripcion = temp.get(index);
            entradas = inscripcion.getEntradas();
            count += entradas;

            mensaje = "Felicidades! Has ganado " + inscripcion.getEntradas() + " entradas para la exposición: "
                    + exposicion.getNombre() + ". El regalo es válido entre las fechas: " + validezInicio + " y "
                    + validezFinal + ". Los códigos son: ";

            for (int i = 0; i < entradas; i++) {
                ganador = inscripcion.getParticipante();
                regalo = generarRegalo();
                ganador.recibirRegalo(regalo);
                mensaje += "\n" + regalo.getCodigo();
            }

            Sistema.enviarMensaje("Ganador de sorteo", mensaje, ganador);
            temp.remove(inscripcion);
        }
    }

    /**
     * Obtiene el conjunto de participantes del sorteo activo.
     * 
     * @return el conjunto de participantes del sorteo activo
     */
    public Set<Cliente> getParticipantes() {
        Set<Cliente> participantes = new HashSet<>();

        for (Inscripcion i : inscripciones) {
            participantes.add(i.getParticipante());
        }
        return participantes;
    }

    /**
     * Agrega una inscripción al sorteo activo.
     * 
     * @param i la inscripción a agregar
     */
    public void addInscripcion(Inscripcion i) {
        inscripciones.add(i);
    }

    /**
     * Genera un regalo aleatorio.
     * 
     * @return el regalo generado
     */
    public Regalo generarRegalo() {
        String codigo = generateRandomString(10);
        Regalo regalo = new Regalo(codigo, validezInicio, validezFinal, penalizacion, exposicion);
        System.out.println("[GENERAR REGALO] código: " + codigo);
        return regalo;
    }

    /**
     * Genera una cadena aleatoria de caracteres.
     * 
     * @param length la longitud de la cadena
     * @return la cadena aleatoria generada
     */
    public String generateRandomString(int length) {
        String characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        Random rnd = new Random();
        StringBuilder sb = new StringBuilder(length);

        for (int i = 0; i < length; i++) {
            sb.append(characters.charAt(rnd.nextInt(characters.length())));
        }

        return sb.toString();
    }

    /**
     * Reserva las entradas para la visita correspondiente a la fecha de inicio de
     * validez del sorteo activo.
     * 
     * @throws Exception si no se encuentra la visita correspondiente
     */
    void reservarEntradas() throws Exception {
        for (Visita visita : exposicion.getVisitas()) {
            if (visita.getFecha().equals(validezInicio)) {
                visita.reservar(entradas);
                return;
            }
        }

        throw new Exception("No se ha encontrado la visita");
    }

    /**
     * Obtiene la exposición asociada al sorteo activo.
     * 
     * @return la exposición asociada al sorteo activo
     */
    public Exposicion getExposicion() {
        return exposicion;
    }

    /**
     * Obtiene el número de ganadores del sorteo activo.
     * 
     * @return el número de ganadores del sorteo activo
     */
    public int getNumGanadores() {
        return entradas;
    }

    /**
     * Obtiene la fecha de inicio de validez del sorteo activo.
     * 
     * @return la fecha de inicio de validez del sorteo activo
     */
	public Object getFinSorteo() {
        return finSorteo;
    }
}