import java.io.*;
import java.util.*;

public class Main {

	public static int[] computeTopologicalSortingKahn(ArrayList<ArrayList<Integer>> dependencyList, int[] inDegreeCount) {
		int numNodes = dependencyList.size();
		//add all nodes in a heap
		PriorityQueue<Integer> minHeap = new PriorityQueue<>();
		for (int v = 0; v < numNodes; v++) {
			if (inDegreeCount[v] == 0) {
				minHeap.add(v);
			}
		}

		//now we are doing Kahns algorithm
		int[] topologicalSorting = new int[numNodes];
		for (int i = 0; i < numNodes; i++) {
			int v = minHeap.poll();
			topologicalSorting[i] = v;
			for (Integer w : dependencyList.get(v)) {
				inDegreeCount[w]--;
				if (inDegreeCount[w] == 0) {
					minHeap.add(w);
				}
			}
		}
		return topologicalSorting;
	}

	private static int getWhiteSpace(String s) {
		int i = 0;
		while (!Character.isWhitespace(s.charAt(i))) {
			i++;
		}
		return i;
	}

	public static void main(String[] args) throws IOException {
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
			//try (BufferedReader reader = new BufferedReader(new FileReader("Sheet3/Task06/test.cases"))) {
			while (true) {
				String line = reader.readLine();
				int whitespacePosition = getWhiteSpace(line);
				int numLemmata = Integer.valueOf(line.substring(0, whitespacePosition));
				int numDependencies = Integer.valueOf(line.substring(whitespacePosition + 1, line.length()));

				if (numLemmata == 0 && numDependencies == 0) {
					break;
				}

				ArrayList<ArrayList<Integer>> dependencyLists = new ArrayList<>(numLemmata);
				for (int lemma = 0; lemma < numLemmata; lemma++) {
					dependencyLists.add(new ArrayList<Integer>());
				}

				int[] inDegreeCount = new int[numLemmata];
				for (int i = 0; i < numDependencies; i++) {
					line = reader.readLine();
					whitespacePosition = getWhiteSpace(line);
					int v = Integer.valueOf(line.substring(0, whitespacePosition)) - 1;
					int w = Integer.valueOf(line.substring(whitespacePosition + 1, line.length())) - 1;
					dependencyLists.get(v).add(w);
					inDegreeCount[w]++;
				}

				//start computation
				int[] topologicalSorting = computeTopologicalSortingKahn(dependencyLists, inDegreeCount);
				for (Integer i : topologicalSorting) {
					System.out.print((i + 1) + " ");
				}
				System.out.print("\n");
			}
		}
	}

}
