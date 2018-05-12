import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Task06 {

	public static int numTests;

	/**
	 * Simple Graph class
	 * TODO: is a adjacency list better??
	 */
	public class Graph {

		boolean[][] adjacencyMatrix;

		public Graph(int numNodes) {
			adjacencyMatrix = new boolean[numNodes][numNodes];
		}

		public void addEdge(int start, int end) {
			adjacencyMatrix[start][end] = true;
			adjacencyMatrix[end][start] = true;
		}

		/**
		 * Method for returning all incident Vertices for a given vertex and the vertex itself
		 *
		 * @param vertex the vertex of which the incident vertices should be computed
		 * @return array of vertex numbers, the neighbours of i and i itself
		 */
		public int[] getNeighbours(int vertex) {
			ArrayList<Integer> neighbours = new ArrayList<>(8);
			//in this context, a vertex is a neighbour of its own
			neighbours.add(vertex);
			for (int i = 0; i < adjacencyMatrix.length; i++) {
				if (adjacencyMatrix[vertex][i]) {
					neighbours.add(i);
				}
			}
			int[] output = new int[neighbours.size()];
			for (int i = 0; i < output.length; i++) {
				output[i] = neighbours.get(i);
			}

			return output;
		}


	}

	/**
	 * Provides a induced subgrah view on the graph
	 */
	public class GraphView {

		/**
		 * the underlying graph
		 */
		Graph realGraph;

		/**
		 * nodes which are excluded from this graph
		 */
		boolean[] excluded;

		/**
		 * number of nodes which are part of this subgraph
		 */
		int currentNumNodes;

		/**
		 * for cloning
		 */
		private GraphView(GraphView graphView, int vertexToExclude) {
			this.excluded = Arrays.copyOf(graphView.excluded, graphView.excluded.length);
			this.excluded[vertexToExclude] = true;
			this.realGraph = graphView.realGraph;
			this.currentNumNodes = graphView.getCurrentNumNodes() - 1;
		}

		/**
		 * for cloning
		 */
		private GraphView(GraphView graphView, int[] verticesToExclude) {
			this.excluded = Arrays.copyOf(graphView.excluded, graphView.excluded.length);
			this.currentNumNodes = graphView.getCurrentNumNodes();
			// maybe there are already excluded vertices in the array -> we should only decrease the number for new ones!
			for (int vertexToExclude : verticesToExclude) {
				if (!this.excluded[vertexToExclude]) {
					this.excluded[vertexToExclude] = true;
					this.currentNumNodes--;
				}
			}
			this.realGraph = graphView.realGraph;
		}

		public GraphView(Graph graph, int[] exclusions) {
			this.realGraph = graph;
			this.excluded = new boolean[graph.adjacencyMatrix.length];
			for (int i : exclusions) {
				excluded[i] = true;
			}
			this.currentNumNodes = graph.adjacencyMatrix.length - exclusions.length;
		}

		public void excludeVertex(int i) {
			excluded[i] = true;
		}

		public void excludeVertices(int[] is) {
			for (int i : is) {
				excluded[i] = true;
			}
		}

		public GraphView cloneAndExlude(int vertex) {
			return new GraphView(this, vertex);
		}

		public GraphView cloneAndExlude(int[] vertices) {
			return new GraphView(this, vertices);
		}

		public int[] getNeighbours(int vertex) {
			return realGraph.getNeighbours(vertex);
		}

		public int getRealNumNodes() {
			return excluded.length;
		}

		public int getCurrentNumNodes() {
			return currentNumNodes;
		}

		public boolean isPartOf(int vertex) {
			return !excluded[vertex];
		}
	}

	public Graph createGraph(int numNodes) {
		return new Graph(numNodes);
	}

	private int findMaximumIndependetSet(Graph graph) {
		return branchAndBound(new GraphView(graph, new int[]{}), 0);
	}

	private int branchAndBound(GraphView graph, int vertexToBranch) {
		if (graph.currentNumNodes <= 1) {
			return graph.currentNumNodes;

		} else {
			int vTB = vertexToBranch;
			//if the vertex is not part of the subgraph, we don't have to branch and just increase the vertex
			//TODO: is there a better way to find a new vertex?
			while (!graph.isPartOf(vertexToBranch)) {
				vTB++;
			}
			GraphView graphWithVertex = graph.cloneAndExlude(graph.getNeighbours(vTB));
			GraphView graphWithoutVertex = graph.cloneAndExlude(vTB);

			int sizeIndependetSetWithVertex = branchAndBound(graphWithVertex, vTB + 1);
			int sizeIndependetSetWithoutVertex = branchAndBound(graphWithoutVertex, vTB + 1);

			if (sizeIndependetSetWithVertex >= sizeIndependetSetWithoutVertex) {
				return sizeIndependetSetWithVertex + 1;
			} else {
				return sizeIndependetSetWithoutVertex;
			}
		}
	}

	public static void main(String[] args) {
		try (Scanner scanner = new Scanner(System.in)) {
			//number of testcases
			numTests = scanner.nextInt();

			for (int i = 0; i < numTests; i++) {
				//read number of nodes
				int numNodes = scanner.nextInt();
				//read number of edges
				int numEdges = scanner.nextInt();
				Graph graph = new Task06().createGraph(numNodes);

				for (int j = 0; j < numEdges; j++) {
					//start and end
					graph.addEdge(scanner.nextInt() - 1, scanner.nextInt() - 1);
				}
				//we build the graph, now we do the branch and bound
				Task06 task = new Task06();
				System.out.println(task.findMaximumIndependetSet(graph));
			}

		}
	}


}
