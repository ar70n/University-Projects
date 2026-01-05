package infoNutricional;

import planificador.ElementoNutricional;

/**
 * Esta clase representa la información nutricional de un plato.
 * Hereda de la clase InfoNutricionalConjunto.
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class InfoNutricionalPlato extends InfoNutricionalConjunto {

    /**
     * Devuelve una representación en forma de cadena de la información nutricional del plato.
     * @return La información nutricional del plato.
     */
    @Override
    public String toString() {
        return "INFORMACION NUTRICIONAL DEL PLATO  " + super.toString();
    }

    /**
     * Devuelve una representación en forma de cadena del tipo de alimento (plato).
     * @return El tipo de alimento (plato).
     */
    public String printInfo() {
        return "PLATO";
    }
    
    /**
     * Devuelve el valor nutricional correspondiente al nutriente especificado.
     * @param nutriente El nutriente del cual se desea obtener el valor nutricional.
     * @return El valor nutricional del nutriente especificado.
     * @throws IllegalArgumentException Si el nutriente no es válido.
     */
    public double getValorNutricional(ElementoNutricional nutriente) {
        switch (nutriente) {
            case CALORIAS:
                return this.getCalorias();
            case PROTEINAS:
                return this.getProteinas();
            case GRASAS:
                return this.getGrasas();
            case HIDRATOS_CARBONO:
                return this.getHidratosDeCarbono();
            case FIBRA:
                return this.getFibra();
            case SODIO:
                return this.getSodio();
            case AZUCARES:
                return this.getAzucares();
            case GRASA_SATURADA:
                return this.getGrasasSaturadas();
            default:
                throw new IllegalArgumentException("Nutriente no válido");
        }
    }

}
