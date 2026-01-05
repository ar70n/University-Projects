import java.util.List;
/**
* Clase que hereda de ArticleFormatter y que implementa el formato APA.
*
* @author Antonio Moroño Moreno y Pedro Ismael Haddou Acosta
*
*/

public class APAArticleFormatter extends ArticleFormatter {
	/**
	 * An example:
	 * 
	 * Last name, Initials. (Year). Article title. Journal Name, Volume(Issue).
	 **/
	
	public APAArticleFormatter(){
		super("APA");
	}
	
	@Override
	public String formatAuthorsList(List<Author> authors) {
		StringBuffer sb = new StringBuffer();
		for (Author a : authors) {
			sb.append((sb.length()>0)?", ":"");
			sb.append(a.getLastName() + ", "  + a.getInitial() + ".");
		}
		return sb.toString();
	}
	
	@Override
	public String formatReference(Article a) {
		return formatAuthorsList(a.getAuthors()) + " "+
			   "(" + a.getYear() + "). " + 
			   a.getTitle() + ". " + a.getJournal() + ", " +
			   a.getVolume() + "(" + a.getIssue() + ").";
	}
}
