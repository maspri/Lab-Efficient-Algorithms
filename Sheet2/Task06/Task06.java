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

		boolean [][] adjacencyMatrix;

		public Graph(int numNodes){
			adjacencyMatrix = new boolean [numNodes][numNodes];
		}

		public void addEdge(int start, int end){
			adjacencyMatrix[start][end]= true;
			adjacencyMatrix[end][start]= true;
		}

		/**
		 * Method for returning all incident Vertices for a given vertex
		 * @param vertex the vertex of which the incident vertices should be computed
		 * @return array of vertex numbers, the neighbours of i
		 */
		public int [] getNeighbours(int vertex){
			ArrayList<Integer> neighbours = new ArrayList<>(8);
			for(int i=0; i<adjacencyMatrix.length;i++){
				if(adjacencyMatrix[vertex][i]){
					neighbours.add(i);
				}
			}
			 int [] output = new int [neighbours.size()];
			for(int i=0;i <output.length;i++){
				output[i]=neighbours.get(i);
			}

			return output;
		}


	}

	/**
	 * Provides a induced subgrah view on the graph
	 */
	public class GraphView{

		/**
		 * the underlying graph
		 */
		Graph realGraph;

		/**
		 * nodes which are excluded from this graph
		 */
		boolean [] excluded ;

		/**
		 * for cloning
		 */
		private GraphView(GraphView graphView, int vertexToExclude){
			this.excluded = Arrays.copyOf(graphView.excluded, graphView.excluded.length);
			this.excluded[vertexToExclude] =true;
			this.realGraph = graphView.realGraph;
		}

		/**
		 * for cloning
		 */
		private GraphView(GraphView graphView, int [] verticesToExclude){
			this.excluded = Arrays.copyOf(graphView.excluded, graphView.excluded.length);
			for (int vertexToExclude : verticesToExclude){
				this.excluded[vertexToExclude] = true;
			}
			this.realGraph = graphView.realGraph;
		}

		public GraphView(Graph graph, int [] exclusions){
			this.realGraph = graph;
			for(int i: exclusions){
				excluded[i] = true;
			}
		}

		public void excludeVertex(int i){
			excluded[i]=true;
		}

		public void excludeVertices(int [] is) {
			for (int i : is){
				excluded[i]=true;
			}
		}

		public GraphView cloneAndExlude(int vertex){
			return new GraphView(this,vertex);
		}

		public GraphView cloneAndExlude(int [] vertices){
			return new GraphView(this,vertices);
		}

		public int [] getNeighbours(int vertex){
			return realGraph.getNeighbours(vertex);
		}
	}

	public Graph createGraph(int numNodes){
		return new Graph(numNodes);
	}

	private int findMaximumIndependetSet(Graph graph) {
			return branchAndBound(new GraphView(graph,new int[] {}));
	}

	private int branchAndBound(GraphView graph) {
		//how to select i?
		GraphView graphWithVertex = graph.cloneAndExlude(graph.getNeighbours(i));
		GraphView graphWithoutVertex = graph.cloneAndExlude(i);

		int sizeIndependetSetWithVertex = branchAndBound(graphWithVertex);
		int sizeIndependetSetWithoutVertex = branchAndBound(graphWithoutVertex);

		if(sizeIndependetSetWithVertex >= sizeIndependetSetWithoutVertex){
			return sizeIndependetSetWithVertex+1;
		}
		else {
			return sizeIndependetSetWithoutVertex;
		}
	}

	public static void main(String [] args){
		try(Scanner scanner = new Scanner(System.in)){
			//number of testcases
			numTests = scanner.nextInt();

			for(int i=0; i<numTests; i++){
				//read number of nodes
				int numNodes = scanner.nextInt();
				//read number of edges
				int numEdges = scanner.nextInt();
				Graph graph = new Task06().createGraph(numNodes);

				for (int j=0; j<numEdges; j++){
					//start and end
					graph.addEdge(scanner.nextInt(), scanner.nextInt());
				}
				//we build the graph, now we do the branch and bound
				System.out.println(findMaximumIndependetSet(graph));
			}

		}
	}


}
