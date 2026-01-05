import java.util.List;
/**
* Clase main que prueba el funcionamiento de los formateadores de referencias.
*
* @author Antonio Moroño Moreno y Pedro Ismael Haddou Acosta
*
*/

public class Main {

	public static void main(String[] args) {
				
		Article Kaczorek2016 = new Article(
				List.of(new Author("Tadeusz", "Kaczorek")),                          // the author
				2016,                                                                // year
				"Minimum energy control of fractional positive electrical circuits", // title
				"Archives of Electrical Engineering",                                // journal
				65, 2);
		
		Article Uchiyama2014 = new Article(
				List.of(new Author("Satoru", "Uchiyama"),
						new Author("Atsuto", "Kubo"),
						new Author("Hironori", "Washizaki"),
						new Author("Yoshiaki", "Fukazawa")),                         // the authors
				2014,                                                                // year
				"Detecting Design Patterns in Object-Oriented Program Source Code "+
						"by Using Metrics and Machine Learning",                     // title
				"Journal of Software Engineering and Applications",                  // journal
				7, 12);
		
		List<Article> references = List.of(Kaczorek2016, Uchiyama2014);
		List<ArticleFormatter> formatters = List.of( new APAArticleFormatter(), 
									     			 new IEEEArticleFormatter());

		for (ArticleFormatter formatter : formatters) {
			System.out.println("Articles in "+formatter.getName()+" format:");
			System.out.println(formatter.format(references));
		}
	}
}
