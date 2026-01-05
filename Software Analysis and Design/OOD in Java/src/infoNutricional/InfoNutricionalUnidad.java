package infoNutricional;

/**
 * Esta clase representa la información nutricional de un ingrediente en unidades.
 * Hereda de la clase InfoNutricional.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class InfoNutricionalUnidad extends InfoNutricional {

    /**
     * Constructor de la clase InfoNutricionalUnidad.
     * 
     * @param calorias        las calorías del ingrediente
     * @param hidratos        los hidratos de carbono del ingrediente
     * @param grasasTotales   las grasas totales del ingrediente
     * @param grasasSaturadas las grasas saturadas del ingrediente
     * @param proteinas       las proteínas del ingrediente
     * @param azucares        los azúcares del ingrediente
     * @param fibra           la fibra del ingrediente
     * @param sodio           el sodio del ingrediente
     */
    public InfoNutricionalUnidad(double calorias, double hidratos, double grasasTotales, double grasasSaturadas,
            double proteinas, double azucares, double fibra, double sodio) {
        super(calorias, hidratos, grasasTotales, grasasSaturadas, proteinas, azucares, fibra, sodio);
    }

    /**
     * Calcula el factor de conversión para la información nutricional en unidades.
     * 
     * @param factor el factor de conversión
     * @return el factor de conversión
     */
    @Override
    public double factor(double factor){
        return factor;
    }

    /**
     * Devuelve una representación en cadena de la información nutricional en unidades.
     * 
     * @return la información nutricional en unidades como una cadena
     */
    @Override
    public String toString() {
        return "INFORMACION NUTRICIONAL POR UNIDAD  " + super.toString();
    }

    /**
     * Imprime información adicional sobre el ingrediente en unidades.
     * 
     * @return información adicional sobre el ingrediente en unidades como una cadena
     */
    public String printInfo(){
        return "INGREDIENTE_UNIDAD";
    }
}
