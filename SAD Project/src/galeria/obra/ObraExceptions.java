package galeria.obra;

import galeria.Vector3;

public abstract class ObraExceptions extends Exception {
}

abstract class InvalidConditions extends ObraExceptions {
}

abstract class StateExceptions extends ObraExceptions {
	protected EstadoObra estadoA;
	protected EstadoObra estadoB;

	StateExceptions(EstadoObra estadoA, EstadoObra estadoB) {
		this.estadoA = estadoA;
		this.estadoB = estadoB;
	}
}

class InvalidTemperatureConditions extends InvalidConditions {
	private double temSala;
	private double tempMin;
	private double tempMax;

	InvalidTemperatureConditions(double tempSala, double tempMin, double tempMax) {
		this.temSala = tempSala;
		this.tempMin = tempMin;
		this.tempMax = tempMax;
	}

	@Override
	public String toString() {
		return "InvalidTemperatureConditions [temperaturaSala=" + temSala + ", tempMin=" + tempMin + ", tempMax="
				+ tempMax + "]";
	}
}

class InvalidHumidityConditions extends InvalidConditions {
	private double humSala;
	private double humMin;
	private double humMax;

	InvalidHumidityConditions(double humSala, double humMin, double humMax) {
		this.humSala = humSala;
		this.humMin = humMin;
		this.humMax = humMax;
	}

	@Override
	public String toString() {
		return "InvalidHumidityConditions [humedadSala=" + humSala + ", humMin=" + humMin + ", humMax=" + humMax + "]";
	}
}

class InvalidDimensionConditions extends InvalidConditions {
	private Vector3 dimSala;
	private Vector3 dimObra;

	InvalidDimensionConditions(Vector3 dimSala, Vector3 dimObra) {
		this.dimSala = dimSala;
		this.dimObra = dimObra;
	}

	@Override
	public String toString() {
		return "InvalidDiemsionConditions [dimensionSala=" + dimSala + ", dimensionObra=" + dimObra + "]";
	}
}

class InvalidEnchufesConditions extends InvalidConditions {

	@Override
	public String toString() {
		return "InvalidEnchufesConditions [La Sala no tiene enchufes libres]";
	}
}

class InvalidStateTransition extends StateExceptions {
	InvalidStateTransition(EstadoObra origen, EstadoObra destino) {
		super(origen, destino);
	}

	@Override
	public String toString() {
		return "InvalidStateTransition [origen=" + estadoA + ", destino=" + estadoB + "]";
	}

}

class InvalidExpoType extends ObraExceptions {
	@Override
	public String toString() {

		return "InvalidExpoType [Exposicion=Temporal, Obra=En propiedad]";
	}
}

class ExpectedDifferentState extends StateExceptions {
	ExpectedDifferentState(EstadoObra origen, EstadoObra destino) {
		super(origen, destino);
	}

	@Override
	public String toString() {
		return "ExpectedDifferentState [Estado esperado=" + estadoA + ", Estado de la obra=" + estadoB + "]";
	}
}

class ExpoDeclinedTransition extends StateExceptions {
	ExpoDeclinedTransition(EstadoObra origen, EstadoObra destino) {
		super(origen, destino);
	}

	@Override
	public String toString() {
		return "ExpoDeclinedTransition [Origen=" + estadoA + ", Destino=" + estadoB + "]";
	}
}