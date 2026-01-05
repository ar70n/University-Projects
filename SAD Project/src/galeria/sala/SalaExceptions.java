package galeria.sala;

import galeria.obra.*;

public abstract class SalaExceptions extends Exception {

}

class SalaGotSubsalasException extends SalaExceptions {

	@Override
	public String getMessage() {
		return "La sala tiene subsalas";
	}
}

class InsufficientSpaceException extends SalaExceptions {
	private double espacioSala;
	private double espacioObra;

	InsufficientSpaceException(double espacioSala, double espacioObra) {
		this.espacioSala = espacioSala;
		this.espacioObra = espacioObra;
	}

	@Override
	public String getMessage() {
		return "InsufficientSpaceException [espacioSala=" + espacioSala + ", espacioObra=" + espacioObra + "]";
	}
}

class SalaAlreadyContainsObra extends SalaExceptions {
	private Obra obra;

	SalaAlreadyContainsObra(Obra obra) {
		this.obra = obra;
	}

	@Override
	public String getMessage() {
		return "La sala ya contiene esta obra: " + obra.getNombre();
	}
}

class SalaWithoutExpoException extends SalaExceptions {

	@Override
	public String getMessage() {
		return "La sala no tiene una exposición asignada";
	}
}
