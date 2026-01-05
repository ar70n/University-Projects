package galeria.exposicion;

public class ExposicionExceptions extends Exception {
}

class SalaNotInExpoException extends ExposicionExceptions {
	@Override
	public String toString() {
		return "La sala no pertenece a la exposicion";
	}
}

class InvalidObraForExpoException extends ExposicionExceptions {
	@Override
	public String toString() {
		return "Una obra en propiedad no se puede exponer en una exposicion temporal";
	}
}
