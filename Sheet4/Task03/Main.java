import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Stack;

/**
 * TODO: check if the graph is connected!
 */
public class Main {


	//we check for every v \in V if inDegree(v)==outDegree(v)
	private static String directedComputation(BufferedReader reader, int numVertices, int numEdges) throws IOException {
		boolean forAllVertices = true;
		int[] degreeBalance = new int[numVertices];

		boolean[][] adjacencyMatrix = new boolean[numVertices][numVertices];

		for (int i = 0; i < numEdges; i++) {
			String line = reader.readLine();
			int whitespacePosition = getWhiteSpace(line);
			int v = Integer.valueOf(line.substring(0, whitespacePosition));
			int w = Integer.valueOf(line.substring(whitespacePosition + 1, line.length()));
			adjacencyMatrix[v][w] = true;

			degreeBalance[v]++;
			degreeBalance[w]--;
		}
		for (int v = 0; v < numVertices; v++) {
			forAllVertices = forAllVertices && (degreeBalance[v] == 0);
		}

		if (forAllVertices && isConnected(adjacencyMatrix)) {
			return "yes";
		} else {
			return "no";
		}

	}

	//we check for every v \in V if degree(v) is even
	private static String undirectedComputation(BufferedReader reader, int numVertices, int numEdges) throws IOException {
		boolean forAllVertices = true;
		boolean[] forEachVertex = new boolean[numVertices];
		Arrays.fill(forEachVertex, true);

		boolean[][] adjacencyMatrix = new boolean[numVertices][numVertices];

		for (int i = 0; i < numEdges; i++) {
			String line = reader.readLine();
			int whitespacePosition = getWhiteSpace(line);
			int v = Integer.valueOf(line.substring(0, whitespacePosition));
			int w = Integer.valueOf(line.substring(whitespacePosition + 1, line.length()));
			adjacencyMatrix[v][w] = true;
			adjacencyMatrix[w][v] = true;

			forEachVertex[v] = !forEachVertex[v];
			forEachVertex[w] = !forEachVertex[w];

			forAllVertices = forEachVertex[v] && forEachVertex[w];
		}

		//TODO: can be optimized by checking if numOfEdges is less then numVertices!
		if (forAllVertices && isConnected(adjacencyMatrix)) {
			return "yes";
		} else {
			return "no";
		}
	}

	/**
	 * Checks if a graph represented by its adjacency matrix is connected.
	 *
	 * @param matrix
	 * @return
	 */
	private static boolean isConnected(boolean[][] matrix) {
		boolean[] visisted = new boolean[matrix.length];

		Stack<Integer> dfs = new Stack<>();
		dfs.push(0);

		while (!dfs.isEmpty()) {
			int v = dfs.pop();
			visisted[v] = true;
			//TODO: can be optimized for undirected graphs
			for (int w = 0; w < matrix.length; w++) {
				if (matrix[v][w] && !visisted[w]) {
					dfs.push(w);
				}
			}
		}

		boolean isConnected = true;
		for (int i = 0; i < matrix.length; i++) {
			isConnected &= visisted[i];
			if (!isConnected) {
				break;
			}
		}
		return isConnected;
	}

	public static void main(String[] args) throws IOException {
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

			String answer;
			if (isDirected) {
				answer = directedComputation(reader, numVertices, numEdges);
			} else {
				answer = undirectedComputation(reader, numVertices, numEdges);
			}
			System.out.println(answer);
		}
	}

	private static int getWhiteSpace(String s) {
		int i = 0;
		while (!Character.isWhitespace(s.charAt(i))) {
			i++;
		}
		return i;
	}
}
