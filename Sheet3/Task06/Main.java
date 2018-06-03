import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {

	public static class HeapEntry {

		private int vertex;
		private int inDegree;

		public HeapEntry(int vertex, int inDegree) {
			this.vertex = vertex;
			this.inDegree = inDegree;
		}

		public Integer getInDegree() {
			return inDegree;
		}

		public Integer getVertex() {
			return vertex;
		}

	}

	public static int[] computeTopologicalSortingKahn(ArrayList<ArrayList<Integer>> dependencyList, int[] inDegreeCount) {
		int numNodes = dependencyList.size();
		//add all nodes in a heap
		PriorityQueue<HeapEntry> minHeap = new PriorityQueue<>(numNodes * numNodes, new Comparator<HeapEntry>() {
			@Override
			public int compare(HeapEntry o1, HeapEntry o2) {
				if (o1.getInDegree() < o2.getInDegree()) {
					return -1;
				} else if (o1.getInDegree() > o2.getInDegree()) {
					return 1;
				} else {
					if (o1.getVertex() < o2.getVertex()) {
						return -1;
					} else if (o1.getVertex() > o2.getVertex()) {
						return 1;
					}
				}
				return 0;
			}
		});

		for (int v = 0; v < numNodes; v++) {
			minHeap.add(new HeapEntry(v, inDegreeCount[v]));
		}

		//now we are doing Kahns algorithm
		int[] topologicalSorting = new int[numNodes];
		for (int i = 0; i < numNodes; i++) {
			int v = minHeap.poll().getVertex();
			topologicalSorting[i] = v;
			for (Integer w : dependencyList.get(v)) {
				inDegreeCount[w]--;
				minHeap.add(new HeapEntry(w, inDegreeCount[w]));
			}
		}
		return topologicalSorting;
	}

	public static void main(String[] args) throws FileNotFoundException {
		try (Scanner scanner = new Scanner(System.in)) {
			//try (Scanner scanner = new Scanner(new File("Sheet3/Task06/test.cases"))){
			scanner.useLocale(Locale.ENGLISH);
			while (true) {
				int numLemmata = scanner.nextInt(); //number of lemmata
				int numDependencies = scanner.nextInt(); //number of dependencies

				ArrayList<ArrayList<Integer>> dependencyLists = new ArrayList<>(numLemmata);
				for (int lemma = 0; lemma < numLemmata; lemma++) {
					dependencyLists.add(new ArrayList<Integer>(numLemmata));
				}

				int[] inDegreeCount = new int[numLemmata];
				for (int i = 0; i < numDependencies; i++) {
					int v = scanner.nextInt() - 1;
					int w = scanner.nextInt() - 1;
					dependencyLists.get(v).add(w);
					inDegreeCount[w]++;
				}

				//start computation
				int[] topologicalSorting = computeTopologicalSortingKahn(dependencyLists, inDegreeCount);
				for (int i = 0; i < numLemmata; i++) {
					System.out.print((topologicalSorting[i] + 1) + " ");
				}
				System.out.print("\n");

				if (scanner.nextInt() == 0 && scanner.nextInt() == 0) {
					break;
				}
			}

		}
	}

}
