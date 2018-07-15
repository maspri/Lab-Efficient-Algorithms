import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;

public class Main {

	public static double minimizeSumOfIntersectionLengths(double[][] polygon, int numOfPointsSubPolygon, int fromIndex, int toIndex, double currentSum, double overallMinSum) {
		if (fromIndex < toIndex) {
			if (numOfPointsSubPolygon <= 3) {
				//we can't draw a diagonal anymore
				return 0;
			}
			double currentMinSum = overallMinSum;
			for (int indexOfFirstEndpoint = fromIndex; indexOfFirstEndpoint <= toIndex; indexOfFirstEndpoint++) {
				//we seleceted one point as the start of the intersecting line
				//and have now n-3 other possible choices for the end point

				//some ugly computations
				int tmp;
				if (toIndex - 1 == indexOfFirstEndpoint) {
					tmp = fromIndex;
				} else if (toIndex == indexOfFirstEndpoint) {
					tmp = fromIndex + 1;
				} else {
					tmp = indexOfFirstEndpoint + 2;
				}
				for (int indexOfSecondEndpoint = tmp; twoApartFrom(indexOfSecondEndpoint, indexOfFirstEndpoint, fromIndex, toIndex); indexOfSecondEndpoint = increaseIndex(indexOfSecondEndpoint, fromIndex, toIndex)) {
					double tmpSum = currentSum;
					tmpSum += computeLengthOfLine(polygon[indexOfFirstEndpoint], polygon[indexOfSecondEndpoint]);
					if (tmpSum > currentMinSum) {
						break; //early stopping
					} else {
						//recursion
						tmpSum += minimizeSumOfIntersectionLengths(polygon, indexOfFirstEndpoint, indexOfSecondEndpoint, tmpSum, currentMinSum);
						if (tmpSum > currentMinSum) {
							break; //early stopping
						}
						tmpSum += minimizeSumOfIntersectionLengths(polygon, indexOfSecondEndpoint, indexOfFirstEndpoint, tmpSum, currentMinSum);

						//from here
						if (tmpSum < currentMinSum) {
							currentMinSum = currentSum + tmpSum;
						}
						//to here a partition of the polygon is finished
					}
				}
			}

			if (currentMinSum < overallMinSum) {
				return currentMinSum;
			} else {
				return overallMinSum;
			}
		} else {
			//TODO: this is wrong
			if (numOfPointsSubPolygon <= 3) {
				//we can't draw a diagonal anymore
				return 0;
			}
			double currentMinSum = overallMinSum;
			for (int indexOfFirstEndpoint = fromIndex; indexOfFirstEndpoint != toIndex; indexOfFirstEndpoint = increaseIndex(indexOfFirstEndpoint, 0, polygon.length - 1)) {
				//we seleceted one point as the start of the intersecting line
				//and have now n-3 other possible choices for the end point

				//some ugly computations
				int tmp;
				if (indexOfFirstEndpoint == polygon.length - 1) {
					tmp = 1;//we can assume that we have at least 4 points
				} else if (indexOfFirstEndpoint == polygon.length - 2) {
					tmp = 0;
				} else if (indexOfFirstEndpoint == toIndex - 1) {
					tmp = fromIndex;
				} else if (toIndex == indexOfFirstEndpoint) {
					tmp = fromIndex + 1;
				} else {
					tmp = indexOfFirstEndpoint + 2;
				}

				for (int indexOfSecondEndpoint = tmp; twoApartFrom(indexOfSecondEndpoint, indexOfFirstEndpoint, toIndex, fromIndex); indexOfSecondEndpoint = increaseIndex2(indexOfSecondEndpoint, fromIndex, toIndex, polygon.length)) {
					double tmpSum = currentSum;
					tmpSum += computeLengthOfLine(polygon[indexOfFirstEndpoint], polygon[indexOfSecondEndpoint]);
					if (tmpSum > currentMinSum) {
						break; //early stopping
					} else {
						//recursion
						tmpSum += minimizeSumOfIntersectionLengths(polygon, indexOfFirstEndpoint, indexOfSecondEndpoint, tmpSum, currentMinSum);
						if (tmpSum > currentMinSum) {
							break; //early stopping
						}
						tmpSum += minimizeSumOfIntersectionLengths(polygon, indexOfSecondEndpoint, indexOfFirstEndpoint, tmpSum, currentMinSum);

						//from here
						if (tmpSum < currentMinSum) {
							currentMinSum = tmpSum;
						}
						//to here a partition of the polygon is finished
					}
				}
			}

			if (currentMinSum < overallMinSum) {
				return currentMinSum;
			} else {
				return overallMinSum;
			}
		}


	}

	/**
	 * Evaluates, if between the current index and the first fixed index at least one other index exsits.
	 * This is needed, since a diagonal in the interior of a polygon exists only between not incident points.
	 * Here it is assumed, that the current index is never the fixed index or the fixed index plus one.
	 *
	 * @param curr
	 * @param fix
	 * @param start
	 * @param end
	 * @return true, if between the current index and the fixed one at least another one exists
	 */
	private static boolean twoApartFrom(int curr, int fix, int start, int end) {
		if (fix == start) {
			return curr < end;
		} else {
			return curr + 2 <= fix || curr > fix;
		}
	}

	/**
	 * Increases the index by one and resets it to start, if it reached the end of the subpolygon chain
	 *
	 * @param current
	 * @param start
	 * @param end
	 * @return the next index in the polygon chain
	 */
	private static int increaseIndex(int current, int start, int end) {
		if (current == end) {
			return start;
		} else {
			return current + 1;
		}
	}

	private static int increaseIndex2(int current, int start, int end, int maxLength) {
		if (current == maxLength) {
			//the gap between the maxiumum point index of the polygon and the first point
			return 0;
		} else if (current == end) {
			//the gap between the start of the subpolygon and the end of the subpolygon
			return start;
		} else {
			return current + 1;
		}
	}

	private static double computeLengthOfLine(double[] p1, double[] p2) {
		return Math.sqrt(Math.pow(p1[0] - p2[0], 2) + Math.pow(p1[1] - p2[1], 2));
	}

	/**
	 * Helper function to read input.
	 *
	 * @param s
	 * @param startIndex
	 * @return
	 */
	private static int getWhiteSpaceFromIndex(String s, int startIndex) {
		int i = startIndex;
		while (!Character.isWhitespace(s.charAt(i))) {
			i++;
		}
		return i;
	}

	public static void main(String[] args) throws IOException {
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
			String line = reader.readLine();
			int numOfPoints = Integer.valueOf(line);
			double[][] polygon = new double[numOfPoints][2];
			for (int point = 0; point < numOfPoints; point++) {
				line = reader.readLine();
				int whitPos = getWhiteSpaceFromIndex(line, 0);
				polygon[point][0] = Double.valueOf(line.substring(0, whitPos));
				polygon[point][1] = Double.valueOf(line.substring(whitPos + 1, line.length()));
			}
			System.out.println(new DecimalFormat("0.000").format(minimizeSumOfIntersectionLengths(polygon, polygon.length, 0, numOfPoints - 1, 0, Double.MAX_VALUE)));
		}
	}

}
