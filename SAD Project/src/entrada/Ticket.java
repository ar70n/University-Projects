package entrada;

import java.io.File;
import es.uam.eps.padsof.tickets.*;
import galeria.exposicion.*;

/**
 * Esta clase representa un ticket de visita a una exposición en el centro de
 * exposiciones "El Pincel Empírico".
 * Implementa la interfaz ITicketInfo.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Ticket implements ITicketInfo {
    private Visita visita;
    private Exposicion exposicion;
    private double precioFinal;
    private int nEntradas;
    private static int idCount = 0;

    /**
     * Crea un nuevo objeto Ticket con la información proporcionada.
     * 
     * @param visita      la visita asociada al ticket
     * @param exposicion  la exposición asociada al ticket
     * @param precioFinal el precio final del ticket
     * @param nEntradas   el número de entradas del ticket
     */
    public Ticket(Visita visita, Exposicion exposicion, double precioFinal, int nEntradas) {
        this.visita = visita;
        this.exposicion = exposicion;
        this.precioFinal = precioFinal;
        this.nEntradas = nEntradas;
        idCount++;
    }

    /**
     * Obtiene el ID del ticket.
     * 
     * @return el ID del ticket
     */
    public int getIdTicket() {
        int id = idCount;
        return id;
    }

    /**
     * Obtiene el nombre del centro de exposiciones.
     * 
     * @return el nombre del centro de exposiciones
     */
    public String getExhibitionCenterName() {
        return "El Pincel Empírico";
    }

    /**
     * Obtiene el nombre de la exposición.
     * 
     * @return el nombre de la exposición
     */
    public String getExhibitionName() {
        return exposicion.getNombre();
    }

    /**
     * Obtiene el número de entradas del ticket.
     * 
     * @return el número de entradas del ticket
     */
    public int getNumberOfTickets() {
        return nEntradas;
    }

    /**
     * Obtiene la fecha y hora del ticket.
     * 
     * @return la fecha y hora del ticket
     */
    public String getTicketDateTime() {
        return visita.getFecha().toString();
    }

    /**
     * Obtiene el precio total del ticket.
     * 
     * @return el precio total del ticket
     */
    public double getPrice() {
        return exposicion.getPrecioEntrada() * nEntradas;
    }

    /**
     * Obtiene el descuento aplicado al ticket.
     * 
     * @return el descuento aplicado al ticket
     */
    public double getDiscount() {
        return nEntradas * exposicion.getPrecioEntrada() - precioFinal;
    }

    /**
     * Obtiene el precio pagado por el ticket.
     * 
     * @return el precio pagado por el ticket
     */
    public double getPayedPrice() {
        return precioFinal;
    }

    /**
     * Obtiene la ruta de la imagen asociada al ticket.
     * 
     * @return la ruta de la imagen asociada al ticket
     */
    public String getPicture() {
        return "." + File.separator + "resources" + File.separator + "pincelEmpirico.jpg";
    }

    /**
     * Genera un archivo PDF del ticket.
     * 
     * @throws NonExistentFileException      si el archivo no existe
     * @throws UnsupportedImageTypeException si el tipo de imagen no es compatible
     */
    public void generarPDF() throws NonExistentFileException, UnsupportedImageTypeException {
        TicketSystem.createTicket(this, "." + File.separator + "tmp");
    }
}
