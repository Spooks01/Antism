package ant;

import java.util.ArrayList;

public class AntContainer {
    public static ArrayList<Ant> antList = new ArrayList<>();
    static int currentAnts;
    public static void GenAnts(int numAnts){
        currentAnts = numAnts;
        for (int i = 0; i < currentAnts; i++){
            antList.add(new Ant());
        }
    }
    public static void AddAnts(int newAnts){
        for (int i = currentAnts - 1; i < newAnts; i++){
            antList.add(new Ant());
        }
    }

    public static void ClearAnts(){
        antList.clear();
    }
}
