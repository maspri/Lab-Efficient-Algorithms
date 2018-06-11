import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

/**
 * TODO: check if the graph is connected!
 */
public class Main {

	private static int getWhiteSpace(String s) {
		int i = 0;
		while (!Character.isWhitespace(s.charAt(i))) {
			i++;
		}
		return i;
	}

	//we check for every v \in V if inDegree(v)==outDegree(v)
	private static void directedComputation(BufferedReader reader, int numVertices, int numEdges) throws IOException {
		boolean forAllVertices = true;

		int [] degreeBalance = new int[numVertices];
		for (int i = 0; i < numEdges; i++) {
			String line = reader.readLine();
			int whitespacePosition = getWhiteSpace(line);
			int v = Integer.valueOf(line.substring(0, whitespacePosition));
			int w = Integer.valueOf(line.substring(whitespacePosition + 1, line.length()));

			degreeBalance[v]++;
			degreeBalance[w]--;

		}
		for(int v=0; v <numVertices;v++){
			forAllVertices = forAllVertices && (degreeBalance[v]==0);
		}

		System.out.println(forAllVertices?"yes":"no");

	}

	//we check for every v \in V if degree(v) is even
	private static void undirectedComputation(BufferedReader reader, int numVertices, int numEdges) throws IOException {
		boolean forAllVertices = true;
		boolean [] forEachVertex = new boolean[numVertices];
		Arrays.fill(forEachVertex,true);
		for (int i = 0; i < numEdges; i++) {
			String line = reader.readLine();
			int whitespacePosition = getWhiteSpace(line);
			int v = Integer.valueOf(line.substring(0, whitespacePosition));
			int w = Integer.valueOf(line.substring(whitespacePosition + 1, line.length()));

			forEachVertex[v] = !forEachVertex[v];
			forEachVertex[w] = !forEachVertex[w];

			forAllVertices = forEachVertex[v] && forEachVertex[w];
		}

		System.out.println(forAllVertices?"yes":"no");
	}

	public static void main(String [] args) throws IOException {
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
			//try (BufferedReader reader = new BufferedReader(new FileReader("Sheet3/Task06/test.cases"))) {
			//at first we check if the graph is directed or undirected
			String line = reader.readLine();
			boolean isDirected = line.contains("1");
			//in the next step we extract the number of vertices and edges
			line = reader.readLine();
			int whitespacePosition = getWhiteSpace(line);
			int numVertices = Integer.valueOf(line.substring(0, whitespacePosition));
			int numEdges = Integer.valueOf(line.substring(whitespacePosition + 1, line.length()));

			if (isDirected) {
				directedComputation(reader,numVertices,numEdges);
			} else {
				undirectedComputation(reader,numVertices,numEdges);
			}
		}
	}
}
