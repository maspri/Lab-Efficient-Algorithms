import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {

	public static class HeapEntry implements Map.Entry<Integer,Integer> {

		private int vertex;
		private int inDegree;

		public HeapEntry(int vertex, int inDegree) {
			this.vertex = vertex;
			this.inDegree = inDegree;
		}


		@Override
		public Integer getKey() {
			return vertex;
		}

		@Override
		public Integer getValue() {
			return inDegree;
		}

		@Override
		public Integer setValue(Integer integer) {
			return 0;
		}
	}

	public static int [] computeTopologicalOrdering(ArrayList<ArrayList<Integer>> dependencyLists){
		final int numOfVertices = dependencyLists.size();
		//init
		boolean [] alreadyVisited = new boolean[numOfVertices]; // the vertices, which are already visited
		int numOfNotVisited = numOfVertices;
		int[] visitOrder = new int[numOfVertices];

		Stack<Integer> dfsStack = new Stack<>();
		Stack<Integer> markingStack = new Stack<>();

		while(numOfNotVisited!=0){
			int currVertex = numOfVertices-1;//get some not visited node
			//TODO: make an efficient way
			//create a list of vertices of degree zero and work this list to its end
			while(alreadyVisited[currVertex]){
				currVertex--;
			}

			//first stage, the dfs search
			//TODO: this does not work. Maybe push the nieghbours on the marking stack if you also push them on the dfs stack
			dfsStack.push(currVertex);
			while (!dfsStack.isEmpty()){ //this stack is not empty....

				currVertex = dfsStack.pop();
				if(!alreadyVisited[currVertex]){
				//at the end of this session dfs, we want to write this thing
					markingStack.push(currVertex);
					alreadyVisited[currVertex]=true;
					for(Integer vertex : dependencyLists.get(currVertex)){
						if(!alreadyVisited[vertex]){
							dfsStack.push(vertex);
						}
					}
				}
			}

			//now we are in the second stage, constructing the visit order
			while (!markingStack.isEmpty()){
				visitOrder[numOfNotVisited-1] = markingStack.pop();
				numOfNotVisited--;
			}
		}

		return visitOrder;

	}

	public static void main(String[] args) throws FileNotFoundException {
		//try (Scanner scanner = new Scanner(System.in)) {
		try (Scanner scanner = new Scanner(new File("/home/alf/Dokumente/repositories/Lab-Efficient-Algorithms/Sheet3/Task06/test2.cases"))){
			scanner.useLocale(Locale.ENGLISH);
			while (true){
				int numLemmata = scanner.nextInt(); //number of lemmata
				int numDependencies = scanner.nextInt(); //number of dependencies

				ArrayList<ArrayList<Integer>> dependencyLists = new ArrayList<>(numLemmata);
				for(int lemma=0; lemma<numLemmata;lemma++){
					dependencyLists.add(new ArrayList<Integer>(numLemmata));
				}

				for(int i=0;i<numDependencies;i++){
					dependencyLists.get(scanner.nextInt()-1).add(scanner.nextInt()-1);
				}

				//start computation
				int [] topologicalSorting = computeTopologicalOrdering(dependencyLists);
				for(int i=0; i<numLemmata;i++){
					topologicalSorting[i]++;
				}
				for(int i=0;i<numLemmata;i++){
					System.out.print((i+1)+" ");
				}
				System.out.print("\n");

				if(scanner.nextInt() == 0 && scanner.nextInt()==0){
					break;
				}
			}

		}
	}

}
