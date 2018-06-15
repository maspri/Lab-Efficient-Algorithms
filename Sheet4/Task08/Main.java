import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;

public class Main {

	public static class Ellipse {

		final double x1;
		final double y1;
		final double x2;
		final double y2;
		final double r;

		public Ellipse(double x1, double y1, double x2, double y2, double r) {
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
			this.r = r;
		}
	}

	private static double approximateIntersection(Ellipse e1, Ellipse e2, double[][] samples) {
		double integral = 0;
		for (double[] sample : samples) {
			integral += partOf(e1, sample) && partOf(e2, sample) ? 1 : 0;
		}
		return integral / samples.length;
	}

	private static boolean partOf(Ellipse e1, double[] sample) {
		//TODO
	}

	public static void main(String[] args) throws IOException {
		try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
			//try (BufferedReader reader = new BufferedReader(new FileReader("Sheet3/Task06/test.cases"))) {

			//First ellipse
			//p1
			String line = reader.readLine();
			int whitespacePosition = 5;
			double x1 = Double.valueOf(line.substring(0, whitespacePosition));
			double y1 = Double.valueOf(line.substring(whitespacePosition, line.length()));
			//p2
			line = reader.readLine();
			double x2 = Double.valueOf(line.substring(0, whitespacePosition));
			double y2 = Double.valueOf(line.substring(whitespacePosition, line.length()));
			//r
			line = reader.readLine();
			double r = Double.valueOf(line);

			Ellipse e1 = new Ellipse(x1, y1, x2, y2, r);

			//Second ellipse
			//p1
			line = reader.readLine();
			whitespacePosition = getWhiteSpace(line);
			x1 = Double.valueOf(line.substring(0, whitespacePosition));
			y1 = Double.valueOf(line.substring(whitespacePosition, line.length()));
			//p2
			line = reader.readLine();
			whitespacePosition = getWhiteSpace(line);
			x2 = Double.valueOf(line.substring(0, whitespacePosition));
			y2 = Double.valueOf(line.substring(whitespacePosition, line.length()));
			//r
			line = reader.readLine();
			r = Double.valueOf(line);

			Ellipse e2 = new Ellipse(x1, y1, x2, y2, r);

			//samples
			line = reader.readLine();
			int numOfSamples = Integer.valueOf(line);

			double[][] samples = new double[numOfSamples][2];

			for (int sample = 0; sample < numOfSamples; sample++) {
				line = reader.readLine();
				samples[sample][0] = Double.valueOf(line.substring(0, whitespacePosition));
				samples[sample][1] = Double.valueOf(line.substring(whitespacePosition, line.length()));
			}
			System.out.println(new DecimalFormat("#.###").format(approximateIntersection(e1, e2, samples)));

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
