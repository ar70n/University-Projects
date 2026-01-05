import java.util.List;
/**
* Clase que hereda de ArticleFormatter y que implementa el método formatReference.
*
* @author Antonio Moroño Moreno y Pedro Ismael Haddou Acosta
*
*/

public class IEEEArticleFormatter extends ArticleFormatter {
	/**
	 * An example:
	 * 
	 * Last name, Initials. (Year). Article title. Journal Name, Volume(Issue).
	 **/

	public IEEEArticleFormatter() {
		super("IEEE");
	}

	@Override
	public String formatAuthorsList(List<Author> authors) {
		StringBuffer sb = new StringBuffer();
		for (Author a : authors) {
			sb.append(a.getInitial() + ". " + a.getLastName() + ", ");
		}
		return sb.toString();
	}

	@Override
	public String formatReference(Article a) {
		return formatAuthorsList(a.getAuthors()) +
				'"' + a.getTitle() + '"' + ", " + a.getJournal() + ", vol. " + a.getVolume() + ", no. " + a.getIssue() + ", " + a.getYear() + ".";
	}
}