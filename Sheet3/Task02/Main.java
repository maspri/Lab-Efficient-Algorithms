import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.*;

public class Main {

	public class GrayCodeGenerator {

		private final int n;
		private final int k;
		private final int[] stack;
		private final int[] output;
		private int t;
		private int i;
		private boolean firstCall;


		public GrayCodeGenerator(int n, int k) {
			this.n = n;
			this.k = k;
			this.stack = new int[n + 2];
			this.output = new int[n + 2];
			Arrays.fill(output, 0, k + 1, 1);
			Arrays.fill(output, k + 1, n + 2, 0);

			for (int i = 0; i < n + 2; i++) {
				stack[i] = i + 1;
			}
			this.t = k;
			stack[1] = k + 1;
			this.i = 0;
			firstCall = true;
		}

		public int[] next() {
			if (firstCall) {
				firstCall = false;
				return output;
			} else {
				i = stack[1];
				stack[1] = stack[i];
				stack[i] = i + 1;

				if (output[i] == 1) {
					if (t != 0) {
						output[t] = 1 - output[t];
					} else {
						output[i - 1] = 1 - output[i - 1];
					}
					t++;
				} else {
					if (t != 1) {
						output[t - 1] = 1 - output[t - 1];
					} else {
						output[i - 1] = 1 - output[i - 1];
					}
					t--;
				}
				output[i] = 1 - output[i];
				if ((t == (i - 1)) || (t == 0)) {
					t++;
				} else {
					t -= output[i - 1];
					stack[i - 1] = stack[1];
					if (t == 0) {
						stack[1] = i - 1;
					} else {
						stack[1] = t + 1;
					}
				}
				return output;
			}
		}

		public boolean hasNext() {
			return i < n + 1;
		}
	}

	public GrayCodeGenerator createGrayCodeGenerator(int numOfBits, int ones) {
		return new GrayCodeGenerator(numOfBits, ones);
	}


	/**
	 * solves the task
	 *
	 * @param k the size of the voting committee
	 * @param probabilities array of values between 0 and 1 representing the probability of candidate i voting for an increase of workload
	 * @return the maximum probability of a tie
	 */
	public static double lazyMyAss(int k, final double[] probabilities) {

		int[] committee = new int[k];

		//Phase 1: Computing S
		//initialization
		Comparator<Integer> maxComp = new Comparator<Integer>() {

			private double[] keys = Arrays.copyOf(probabilities, probabilities.length);

			@Override
			public int compare(Integer integer, Integer t1) {
				if (keys[integer] < keys[t1]) {
					return 1;
				}
				if (keys[integer] > keys[t1]) {
					return -1;
				}
				return 0;
			}
		};
		Comparator<Integer> minComp = new Comparator<Integer>() {

			private double[] keys = Arrays.copyOf(probabilities, probabilities.length);

			@Override
			public int compare(Integer integer, Integer t1) {
				if (keys[integer] < keys[t1]) {
					return -1;
				}
				if (keys[integer] > keys[t1]) {
					return 1;
				}
				return 0;
			}
		};
		PriorityQueue<Integer> maxHeap = new PriorityQueue<>(probabilities.length, maxComp);
		PriorityQueue<Integer> minHeap = new PriorityQueue<>(probabilities.length, minComp);

		for (int i = 0; i < probabilities.length; i++) {
			maxHeap.add(i);
			minHeap.add(i);
		}

		//compute S
		for (int i = 0; i < k; i += 2) {
			committee[i] = maxHeap.poll();
			minHeap.remove(committee[i]);
			committee[i + 1] = minHeap.poll();
			maxHeap.remove(committee[i + 1]);
		}

		//Phase 2
		//compute the probability
		GrayCodeGenerator gcGen = new Main().createGrayCodeGenerator(k, k / 2);
		double probabiliyOfTie = 0;
		int[] currentCombination;
		double prod = 1;
		while (gcGen.hasNext()) {
			currentCombination = gcGen.next();
			prod = 1;
			for (int i = 0; i < k; i++) {
				if (currentCombination[i + 1] == 1) {
					prod *= probabilities[committee[i]];
				} else {
					prod *= 1 - probabilities[committee[i]];
				}
			}
			probabiliyOfTie += prod;
		}
		probabiliyOfTie -= prod; // we have to do this due to some last (and maybe faulty^^) computations in the grayCode class!

		return probabiliyOfTie;
	}

	/**
	 * Computes the Probability for a draw with a dynamic programming approach
	 *
	 * @param k number of Members in the comittee
	 * @param probabilitiesOfCurrentCouncil the probabilites of each comitee member
	 * @return
	 */
	public static double computeProbability(int k, double[] probabilitiesOfCurrentCouncil) {
		double[][] dynamicProgrammingTable = new double[k][k / 2 + 1];

		//fills the first column of the table
		dynamicProgrammingTable[0][0] = 1 - probabilitiesOfCurrentCouncil[0];
		for (int numOfMembersMinusOne = 1; numOfMembersMinusOne < k; numOfMembersMinusOne++) {
			dynamicProgrammingTable[numOfMembersMinusOne][0] = dynamicProgrammingTable[numOfMembersMinusOne - 1][0] * (1 - probabilitiesOfCurrentCouncil[numOfMembersMinusOne]);
		}

		//fill the first row of the table, i.e. the second column where the only meber says "yes"
		dynamicProgrammingTable[0][1] = probabilitiesOfCurrentCouncil[0];

		//fill the rest
		for (int numOfMembersMinusOne = 1; numOfMembersMinusOne < k; numOfMembersMinusOne++) {
			for (int numOfYesSayers = 1; numOfYesSayers < (numOfMembersMinusOne / 2 + 2); numOfYesSayers++) {
				dynamicProgrammingTable[numOfMembersMinusOne][numOfYesSayers] = (1 - probabilitiesOfCurrentCouncil[numOfMembersMinusOne]) * dynamicProgrammingTable[numOfMembersMinusOne - 1][numOfYesSayers] + probabilitiesOfCurrentCouncil[numOfMembersMinusOne] * dynamicProgrammingTable[numOfMembersMinusOne - 1][numOfYesSayers - 1];
			}
		}

		return dynamicProgrammingTable[k - 1][k / 2];
	}

	public static double lazyTeacher(int numOfCommiteeMembers, double probabilities[]) {
		double maxProbabilityForDraw = 0;
		//TODO: evtl. bereits beim einlesen sortieren!
		Arrays.sort(probabilities);
		double[] probabilitiesOfCurrentCouncil = Arrays.copyOfRange(probabilities, 0, numOfCommiteeMembers);
		//the two indices indicating the last student from the left side and the first student of the right side
		int leftEnd = numOfCommiteeMembers - 1;
		int rightBegin = probabilities.length;
		for (int i = 0; i < numOfCommiteeMembers; i++) {
			double currProbabilityForDraw = computeProbability(numOfCommiteeMembers, probabilitiesOfCurrentCouncil);
			if (maxProbabilityForDraw < currProbabilityForDraw) {
				maxProbabilityForDraw = currProbabilityForDraw;
			}
			leftEnd--;
			rightBegin--;
			System.out.println("Probabilites of current council: "+Arrays.toString(probabilitiesOfCurrentCouncil)+" with probability "+currProbabilityForDraw);
			// [ 0.001----  leftEnd ----- rightBegin -------  0.22]
			// [0.001 -  leftEnd -- rightBegin]
			probabilitiesOfCurrentCouncil[numOfCommiteeMembers - i - 1] = probabilities[rightBegin];
		}
		return maxProbabilityForDraw;
	}

	public static void main(String[] args) {
		try (Scanner scanner = new Scanner(System.in)) {
			scanner.useLocale(Locale.ENGLISH);
			int n = scanner.nextInt(); //number of candidates
			int k = scanner.nextInt(); //number of members in voting committee
			double[] probabilities = new double[n];
			for (int i = 0; i < n; i++) {
				probabilities[i] = scanner.nextDouble();
			}
			//Locale.setDefault(Locale.ENGLISH);
			System.out.println(new DecimalFormat("0.00").format(lazyTeacher(k, probabilities)));
		}
	}

}
