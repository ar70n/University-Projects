package infoNutricional;

/**
 * Clase abstracta que representa la información nutricional de un conjunto de ingredientes.
 * Esta clase extiende de la clase InfoNutricional.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public abstract class InfoNutricionalConjunto extends InfoNutricional {

	/**
	 * Constructor de la clase InfoNutricionalConjunto.
	 * 
	 * @param calorias        las calorías del conjunto de ingredientes
	 * @param hidratos        los hidratos de carbono del conjunto de ingredientes
	 * @param grasasTotales   las grasas totales del conjunto de ingredientes
	 * @param grasasSaturadas las grasas saturadas del conjunto de ingredientes
	 * @param proteinas       las proteínas del conjunto de ingredientes
	 * @param azucares        los azúcares del conjunto de ingredientes
	 * @param fibra           la fibra del conjunto de ingredientes
	 * @param sodio           el sodio del conjunto de ingredientes
	 */
	public InfoNutricionalConjunto(double calorias, double hidratos, double grasasTotales, double grasasSaturadas,
			double proteinas, double azucares, double fibra, double sodio) {
		super(calorias, hidratos, grasasTotales, grasasSaturadas, proteinas, azucares, fibra, sodio);
	}

	/**
	 * Constructor sin parámetros de la clase InfoNutricionalConjunto.
	 * Los valores de los atributos se inicializan a 0.
	 */
	public InfoNutricionalConjunto() {
		super();
	}

	/**
	 * Método para sumar la información nutricional de un ingrediente al conjunto de ingredientes.
	 * 
	 * @param auxInfo   la información nutricional del ingrediente a sumar
	 * @param cantidad  la cantidad del ingrediente a sumar
	 */
	public void sumarInfo(InfoNutricional auxInfo, double cantidad) {
		double factor = auxInfo.factor(cantidad);

		this.setCalorias(this.getCalorias() + auxInfo.getCalorias() * factor);
		this.setHidratosDeCarbono(this.getHidratosDeCarbono() + auxInfo.getHidratosDeCarbono() * factor);
		this.setGrasas(this.getGrasas() + auxInfo.getGrasas() * factor);
		this.setGrasasSaturadas(this.getGrasasSaturadas() + auxInfo.getGrasasSaturadas() * factor);
		this.setProteinas(this.getProteinas() + auxInfo.getProteinas() * factor);
		this.setAzucares(this.getAzucares() + auxInfo.getAzucares() * factor);
		this.setFibra(this.getFibra() + auxInfo.getFibra() * factor);
		this.setSodio(this.getSodio() + auxInfo.getSodio() * factor);
	}

	/**
	 * Método para sumar la información nutricional de un ingrediente al conjunto de ingredientes.
	 * 
	 * @param auxInfo   la información nutricional del ingrediente a sumar
	 */
	public void sumarInfo(InfoNutricional auxInfo) {
		this.setCalorias(this.getCalorias() + auxInfo.getCalorias());
		this.setHidratosDeCarbono(this.getHidratosDeCarbono() + auxInfo.getHidratosDeCarbono());
		this.setGrasas(this.getGrasas() + auxInfo.getGrasas());
		this.setGrasasSaturadas(this.getGrasasSaturadas() + auxInfo.getGrasasSaturadas());
		this.setProteinas(this.getProteinas() + auxInfo.getProteinas());
		this.setAzucares(this.getAzucares() + auxInfo.getAzucares());
		this.setFibra(this.getFibra() + auxInfo.getFibra());
		this.setSodio(this.getSodio() + auxInfo.getSodio());
	}
}
