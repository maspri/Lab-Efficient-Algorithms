import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class Main {

	public static class NodePair {

		int[] xCoords;
		int[] yCoords;

		public NodePair(int startX, int startY, int endX, int endY) {
			xCoords = new int[]{startX, endX};
			yCoords = new int[]{startY, endY};
		}

		public static NodePair createNodePair(int startX, int startY, int endX, int endY) {
			return new NodePair(startX, startY, endX, endY);
		}
	}

	public static boolean checkForNiceOrientation(int numX, int numY, List<NodePair> pairsWithOnlyOneNicePath, List<NodePair> pairsWithTwoNicePaths) {

		/**
		 * Saves for each x coordinate (resp. y coordiante) in which direction the edges with this x coordiante are oriented.
		 * 1 means from 0 -> 1
		 * 0 means pending
		 * -1 means from 0 <- 1
		 *
		 * Example: If all edges with an x-Coordinate of 4 are oriented from small numbers to big numbers, the entry in edgesWithSameXCoordinate[4 - 1] is 1
		 */
		int[] edgesWithSameXCoordinate = new int[numX];
		int[] edgesWithSameYCoordinate = new int[numY];

		//at first we orientate the edges with the pairs which only have one nice path
		for (NodePair p : pairsWithOnlyOneNicePath) {
			if (p.xCoords[0] == p.xCoords[1]) {
				//the x coordinate stays the same -> we insert the direction in the edgesWithSameXCoordinate
				if (edgesWithSameXCoordinate[p.xCoords[0]] == 0) {
					edgesWithSameXCoordinate[p.xCoords[0]] = p.yCoords[0] < p.yCoords[1] ? 1 : -1;
				} else {
					//the direction is already set. We check for a conflict
					if (edgesWithSameXCoordinate[p.xCoords[0]] != (p.yCoords[0] < p.yCoords[1] ? 1 : -1)) {
						return false;
					}
				}
			} else {
				//the Y coordinate stays the same -> we insert the direction in the edgesWithSameYCoordinate
				if (edgesWithSameYCoordinate[p.yCoords[0]] == 0) {
					edgesWithSameYCoordinate[p.yCoords[0]] = p.xCoords[0] < p.xCoords[1] ? 1 : -1;
				} else {
					//the direction is already set. We check for a conflict
					if (edgesWithSameYCoordinate[p.yCoords[0]] != (p.xCoords[0] < p.xCoords[1] ? 1 : -1)) {
						return false;
					}
				}
			}
		}

		for (NodePair p : pairsWithTwoNicePaths) {
			boolean oneValidNicePathExist = false;
			//we consider at first the nice path which goes first in x direction and then in y direction
			if (edgesWithSameYCoordinate[p.yCoords[0]] == 0) {
				edgesWithSameYCoordinate[p.yCoords[0]] = p.xCoords[0] < p.xCoords[1] ? 1 : -1;
				oneValidNicePathExist = true;
			} else {
				if (edgesWithSameYCoordinate[p.yCoords[0]] != (p.xCoords[0] < p.xCoords[1] ? 1 : -1)) {
					oneValidNicePathExist = false;
				} else {
					oneValidNicePathExist = true;
				}
			}
			//here we consider the end x.coordinate!!
			if (edgesWithSameXCoordinate[p.xCoords[1]] == 0) {
				edgesWithSameXCoordinate[p.xCoords[1]] = p.yCoords[0] < p.yCoords[1] ? 1 : -1;
				oneValidNicePathExist &= true; // we add the boolean value since it depends if we could walked in the x direction
			} else {
				if (edgesWithSameXCoordinate[p.xCoords[1]] != (p.yCoords[0] < p.yCoords[1] ? 1 : -1)) {
					oneValidNicePathExist &= false;
				} else {
					oneValidNicePathExist &= true;
				}
			}

			if (oneValidNicePathExist) {
				continue;
			}

			//we have to check the other way
			//here we go first in y direction
			if (edgesWithSameXCoordinate[p.xCoords[0]] == 0) {
				edgesWithSameXCoordinate[p.xCoords[0]] = p.yCoords[0] < p.yCoords[1] ? 1 : -1;
				oneValidNicePathExist = true;
			} else {
				if (edgesWithSameXCoordinate[p.xCoords[0]] != (p.yCoords[0] < p.yCoords[1] ? 1 : -1)) {
					oneValidNicePathExist = false;
				} else {
					oneValidNicePathExist = true;
				}
			}

			//and now we must consider the end y coordinate
			//again, as above, we must add the boolean value since this depends on the fact, if we could walk this path to the end y coordinate at all!
			if (edgesWithSameXCoordinate[p.yCoords[1]] == 0) {
				edgesWithSameYCoordinate[p.yCoords[1]] = p.xCoords[0] < p.xCoords[1] ? 1 : -1;
				oneValidNicePathExist &= true;
			} else {
				if (edgesWithSameYCoordinate[p.yCoords[1]] != (p.xCoords[0] < p.xCoords[1] ? 1 : -1)) {
					oneValidNicePathExist &= false;
				} else {
					oneValidNicePathExist &= true;
				}
			}

			//if none of both ways is possible, we abort
			if (!oneValidNicePathExist) {
				return false;
			}
		}

		return true;
	}

	private static int getWhiteSpaceFromIndex(String s, int startIndex) {
		int i = startIndex;
		while (!Character.isWhitespace(s.charAt(i))) {
			i++;
		}
		return i;
	}

	public static void main(String[] args) throws IOException {
		//read input from console
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
			String line = reader.readLine();
			int whitespacePosition = getWhiteSpaceFromIndex(line, 0);
			int whitespacePosition2 = getWhiteSpaceFromIndex(line, whitespacePosition + 1);

			int maxX = Integer.valueOf(line.substring(0, whitespacePosition));
			int maxY = Integer.valueOf(line.substring(whitespacePosition + 1, whitespacePosition2));
			int numOfPairs = Integer.valueOf(line.substring(whitespacePosition2 + 1, line.length()));
			//in the next step we extract the nodepairs
			List<NodePair> pairsWithOnePath = new ArrayList<>();
			List<NodePair> pairsWithTwoPaths = new ArrayList<>();
			for (int i = 0; i < numOfPairs; i++) {
				line = reader.readLine();
				int whitePos1 = getWhiteSpaceFromIndex(line, 0);
				int whitePos2 = getWhiteSpaceFromIndex(line, whitePos1 + 1);
				int whitePos3 = getWhiteSpaceFromIndex(line, whitePos2 + 1);
				NodePair p = NodePair.createNodePair(
						Integer.valueOf(line.substring(0, whitePos1)) - 1,
						Integer.valueOf(line.substring(whitePos1 + 1, whitePos2)) - 1,
						Integer.valueOf(line.substring(whitePos2 + 1, whitePos3)) - 1,
						Integer.valueOf(line.substring(whitePos3 + 1, line.length())) - 1
				);

				if (p.xCoords[0] == p.xCoords[1] || p.yCoords[0] == p.yCoords[1]) {
					pairsWithOnePath.add(p);
				} else {
					pairsWithTwoPaths.add(p);
				}
			}

			if (checkForNiceOrientation(maxX, maxY, pairsWithOnePath, pairsWithTwoPaths)) {
				System.out.println("possible");
			} else {
				System.out.println("impossible");
			}
		}
	}
}
