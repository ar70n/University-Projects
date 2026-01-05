package descuento;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import galeria.exposicion.*;
import usuario.Cliente;
import entrada.Visita;

class SorteoActivoTest {

    @Test
    void testsetPenalizacion() {
        Exposicion expo = new Permanente("Prueba", "Descripcion", LocalDateTime.now());
        SorteoActivo sorteoActivo = new SorteoActivo(0, 1, LocalDateTime.now(), LocalDateTime.now(),
                LocalDateTime.now().plusDays(1), expo);
        int penalizacionEsperada = 10;
        sorteoActivo.setPenalizacion(penalizacionEsperada);
        assertEquals(penalizacionEsperada, sorteoActivo.getPenalizacion(),
                "El método setPenalizacion no funcionó como se esperaba");
    }

    @Test
    void testsetEntradas() {
        Exposicion expo = new Permanente("Prueba", "Descripcion", LocalDateTime.now());
        SorteoActivo sorteoActivo = new SorteoActivo(0, 1, LocalDateTime.now(), LocalDateTime.now(),
                LocalDateTime.now().plusDays(1), expo);
        int entradasEsperadas = 2;
        sorteoActivo.setEntradas(entradasEsperadas);
        assertEquals(entradasEsperadas, sorteoActivo.getEntradas(),
                "El método setEntradas no funcionó como se esperaba");
    }

    @Test
    void testsetFechaFin() {
        Exposicion expo = new Permanente("Prueba", "Descripcion", LocalDateTime.now());
        SorteoActivo sorteoActivo = new SorteoActivo(0, 1, LocalDateTime.now(), LocalDateTime.now(),
                LocalDateTime.now().plusDays(1), expo);
        LocalDateTime fechaFinEsperada = LocalDateTime.now().plusDays(2);
        sorteoActivo.setFechaFin(fechaFinEsperada);
        assertEquals(fechaFinEsperada, sorteoActivo.getFechaFin(),
                "El método setFechaFin no funcionó como se esperaba");
    }

    @Test
    void testsetValidez() {
        Exposicion expo = new Permanente("Prueba", "Descripcion", LocalDateTime.now());
        SorteoActivo sorteoActivo = new SorteoActivo(0, 1, LocalDateTime.now(), LocalDateTime.now(),
                LocalDateTime.now().plusDays(1), expo);
        LocalDateTime validezInicio = LocalDateTime.now().plusDays(1);
        LocalDateTime validezFinal = LocalDateTime.now().plusDays(2);
        sorteoActivo.setValidez(validezInicio, validezFinal);
        assertEquals(validezInicio, sorteoActivo.getValidezInicio(),
                "El método setValidez no funcionó como se esperaba");
        assertEquals(validezFinal, sorteoActivo.getValidezFinal(), "El método setValidez no funcionó como se esperaba");
    }

    @Test
    void testreservarEntradas() {
        Exposicion expo = new Permanente("Prueba", "Descripcion", LocalDateTime.now());
        SorteoActivo sorteoActivo = new SorteoActivo(0, 1, LocalDateTime.now(), LocalDateTime.now(),
                LocalDateTime.now().plusDays(1), expo);
        LocalDateTime date = LocalDateTime.now();
        sorteoActivo.setValidez(date, date);
        Visita visita = new Visita(date, expo);
        expo.addVisita(visita);
        int expectedReservations = 10;

        sorteoActivo.setEntradas(expectedReservations);

        try {
            sorteoActivo.reservarEntradas();
        } catch (Exception e) {
            fail("No se ha podido reservar las entradas");
        }

        assertEquals(expectedReservations, visita.getNEntradas());
    }

        @Test
        void testdarRegalos() {
                SorteoActivo sorteoActivo = new SorteoActivo(0, 1, LocalDateTime.now(), LocalDateTime.now(),
                                LocalDateTime.now().plusDays(1), new Permanente("Prueba", "Descripcion", LocalDateTime.now()));

                // Agrega inscripciones de prueba
                Inscripcion inscripcion1 = new Inscripcion(2, new Cliente());
                //Inscripcion inscripcion2 = new Inscripcion(3, new Cliente());
                //Inscripcion inscripcion3 = new Inscripcion(1, new Cliente());
                sorteoActivo.addInscripcion(inscripcion1);
                //sorteoActivo.addInscripcion(inscripcion2);
                //sorteoActivo.addInscripcion(inscripcion3);

                // Llama a la función darRegalos
                sorteoActivo.darRegalos();

                // Verifica que se hayan asignado los regalos correctamente
                assertEquals(2, inscripcion1.getParticipante().getRegalos().size());
                //assertEquals(3, inscripcion2.getParticipante().getRegalos().size());
                //assertEquals(1, inscripcion3.getParticipante().getRegalos().size());
        }
}