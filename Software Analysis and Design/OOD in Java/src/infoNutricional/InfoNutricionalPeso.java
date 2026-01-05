package infoNutricional;

/**
 * Esta clase representa la información nutricional de un ingrediente en peso.
 * Extiende la clase InfoNutricional.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 * @see InfoNutricional
 * @see InfoNutricionalConjunto
 * @see InfoNutricionalMenu
 * @see InfoNutricionalUnidad
 * @see InfoNutricionalPeso
 * @see InfoNutricionalPlato
 */
public class InfoNutricionalPeso extends InfoNutricional {

    /**
     * Constructor de la clase InfoNutricionalPeso.
     * 
     * @param calorias        las calorías del ingrediente
     * @param hidratos        los hidratos de carbono del ingrediente
     * @param grasasTotales   las grasas totales del ingrediente
     * @param grasasSaturadas las grasas saturadas del ingrediente
     * @param proteinas       las proteínas del ingrediente
     * @param azucares        los azúcares del ingrediente
     * @param fibra           la fibra del ingrediente
     * @param sodio           el sodio del ingrediente
     * 
     */
    public InfoNutricionalPeso(double calorias, double hidratos, double grasasTotales, double grasasSaturadas,
            double proteinas, double azucares, double fibra, double sodio) {
        super(calorias, hidratos, grasasTotales, grasasSaturadas, proteinas, azucares, fibra, sodio);
    }
    
    /**
     * Calcula el factor de conversión para la cantidad especificada.
     * 
     * @param cantidad la cantidad del ingrediente en gramos
     * @return el factor de conversión
     */
    @Override
    public double factor(double cantidad){
        return cantidad/100;
    }

    /**
     * Devuelve una representación en forma de cadena de la información nutricional por 100g.
     * 
     * @return la información nutricional por 100g en forma de cadena
     */
    @Override
    public String toString() {
        return "INFORMACION NUTRICIONAL POR 100G  " + super.toString();
    }
    
    /**
     * Devuelve una cadena que representa el tipo de ingrediente (peso).
     * 
     * @return una cadena que representa el tipo de ingrediente (peso)
     */
    public String printInfo(){
        return "INGREDIENTE_PESO";
    }
}
