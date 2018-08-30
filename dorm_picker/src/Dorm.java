/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.*;
import java.io.*;
/**
 * dorm struct. gotta figure out which dorm i want to live in right? dorm utility
 * measured in sum(elapsed time); lower score the better
 * @author Derek
 */
public class Dorm {
    // dorm name
    final String name;
    // nearest gym
    final String ngym;
    // nearest dining hall
    final String ndhall;
    // walking time to stern/bobst/whatever is in wsq
    final int stern_t;
    // walking time to nearest gym (although gramercy has a gym, it has no weights,
    // so use gramercy's dist to nearest nyu gym)
    final int gym_t;
    // walking time to nearest dining hall
    final int dhall_t;
    // waking time to nearest quiet study lounge (if it doesn't have one,
    // use time to stern instead
    final int qs_t;
    /**
     * dorm constructor; initializes all these parameters
     * @param n dorm name
     * @param g nearest gym
     * @param d nearest dining hall
     * @param st time to stern
     * @param gt time to nearest nyu gym with weights and cardio
     * @param dt time to nearest dining hall
     * @param qt time to nearest quiet study lounge (ex. in dorm, bobst, stern)
     */
    public Dorm(String n, String g, String d, int st, int gt, int dt, int qt) {
        name = n;
        ngym = g;
        ndhall = d;
        stern_t = st;
        gym_t = gt;
        dhall_t = dt;
        qs_t = qt;
    }
    // these are all final, so all variables are accessed directly bc they cannot
    // be modified anyways
    
    // methods
    /**
     * using time aggregate formula, return time utility score (lower is better)
     * @param sw weighting coefficient for time to stern
     * @param gw weighting coefficient for time to gym with cardio machines and weights
     * @param dw weighting coefficient for time to nearest dining hall
     * @param qw weighting coefficient for time to nearest quiet study location
     * @return double value indicating time utility of the dorm
     */
    public double timeutil(double sw, double gw, double dw, double qw) {
        return (sw * stern_t) + (gw * gym_t) + (dw * dhall_t) + (qw * qs_t);
    }
    
    // static methods
    /**
     * orders an arraylist of dorms in ascending time utility; better and lower
     * scoring dorms at the top, worse and higher scoring dorms at the end
     * @param ds ArrayList of dorms
     * @param ws double[] of weighting coefficients; sw, gw, sw, and qw (see timeutil)
     */
    public static void sort(ArrayList<Dorm> ds, double ws[]) {
        // selection sort implementation
        // max value ceiling
        final double MAX = 100000;
        // current lowest time util
        double lo = MAX;
        // index of dorm with current lowest time util
        int lti = 0;
        // number of courses in the arraylist
        int n = ds.size();
        // selection sort all courses by increasing time utility
        // outer loop will terminate when everything has been sorted
        for (int sorted = 0; sorted < n; sorted++) {
            // inner loop does sorting comparisons
            for (int i = 0; i < n - sorted; i++) {
                // get selected dorm's time utility
                double ctu = ds.get(i).timeutil(ws[0], ws[1], ws[2], ws[3]);
                // if current dorm's time util is less than lo, update
                if (ctu < lo) {
                    // update hi
                    lo = ctu;
                    // rememeber position of dorm object
                    lti = i;
                }
            }
            // after going through the unsorted elements, add the dorm at lti
            // to the rear of the list and delete its current position
            ds.add(ds.get(lti));
            ds.remove(lti);
            // reset current lowest time util to MAX
            lo = MAX;
        }
    }
    /**
     * populates an arraylist full of Dorm objects based on information from a 
     * .csv file. ignores lines commented with "//"
     * @param f .csv file
     * @return ArrayList of Dorm objects, or null if file is empty
     */
    public static ArrayList<Dorm> getdorms(File f) throws FileNotFoundException, IOException {
        // method name
        final String NAME = "getdorms";
        // arraylist of dorms
        ArrayList<Dorm> ds = new ArrayList<Dorm>();
        // bufferedreader is more efficient
        BufferedReader br = new BufferedReader(new FileReader(f));
        // number of lines in file
        int ln = 1;
        // for each line, read from csv into file; report any incorrectly
        // formatted lines and skip commented lines
        // will continue running until line is empty
        for (String input = br.readLine(); input != null; ln++) {
            // if input starts with "//", ignore
            if (input.startsWith("//")) {
                //System.out.printf("%s: ignored commented line %d\n", NAME, ln);
            }
            // else
            else {
                // split input into input array by commas 3 strings, 4 ints
                String dd[] = input.split(",");
                // if dd.length != 7; data is incomplete so skip
                if (dd.length != 7) {
                    System.out.printf("%s: incomplete data\n\tat line %d -> %s\n",
                            NAME, ln, input);
                }
                // else
                else {
                    // check if the last 4 elements of dd[] are ints; if not
                    // catch the exception and verbosely skip
                    try {
                        // walking time to stern
                        int st = Integer.parseInt(dd[3]);
                        // walking time to nearest gym
                        int gt = Integer.parseInt(dd[4]);
                        // wlaking time to nearest dining hall
                        int dt = Integer.parseInt(dd[5]);
                        // walking time to nearest quiet sstudy
                        int qt = Integer.parseInt(dd[6]);
                        // make a new dorm
                        ds.add(
                                new Dorm(
                                        dd[0],  // dorm name
                                        dd[1],  // nearest gym
                                        dd[2],  // nearest dininh hall
                                        st,     // time to stern
                                        gt,     // time to nearest gym
                                        dt,     // time to nearest dining hall
                                        qt      // time to nearest quiet study
                                )
                        );
                    }
                    catch (NumberFormatException e) {
                        System.out.printf("%s: improperly formatted data\n\tat line %d -> %s",
                            NAME, ln, input);
                    }
                }
            }
            // read a new line
            input = br.readLine();
        }
        // return finished arraylist
        return ds;
    }
}
