/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.*;
import java.io.*;
/**
 * main program for dorm picking
 * @author Derek (02-2018)
 */
public class dorm_selection {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException, IOException {
        // arraylist of dorms
        ArrayList<Dorm> dorms;
        // file to read from
        File f = new File("dorms.txt");
        // dorm utility weights: stern, gym, dining hall, quiet study
        double ws[] = new double[]{1.4, 1.1, 0.9, 1.2};
        // load info into dorms
        dorms = Dorm.getdorms(f);
        // order dorms by time utility
        // sort the dorms, arbitrary weights are 1.2, 0.7, 0.8, 1.1
        Dorm.sort(dorms, ws);
        // print out the sorted dorms
        for (int i = 0; i < dorms.size(); i++) {
            Dorm d = dorms.get(i);
            System.out.printf("%d. t_util:\t%5.2f\t%s\n", 
                    i + 1, d.timeutil(ws[0], ws[1], ws[2], ws[3]), d.name);
        }
    }
    
}
