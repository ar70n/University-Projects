import java.util.List;
/**
* Clase abstracta que define el comportamiento de los formateadores de referencias.
*
* @author Antonio Moroño Moreno y Pedro Ismael Haddou Acosta
*
*/

public abstract class ArticleFormatter {
	protected String name;
	
	public abstract String formatAuthorsList(List<Author> authors);
	public abstract String formatReference(Article a);
	
	public ArticleFormatter(String formatterName) {
		this.name = formatterName;
	}
	
	public String getName() {
		return this.name;
	}
	
	public String format(List<Article> articles) {
		String result = "";
		for (Article a : articles) 
			result+= this.formatReference(a)+"\n";
		return result;		
	}
}
