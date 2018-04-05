package statemachine;

import input.Input;

import static org.lwjgl.glfw.GLFW.*;

public class StateMachine {
    // Constructors
    public StateMachine() {

    }

    /** Enumerator for possible rendering states */
    public enum State{
        Closed,
        Running,
        Paused
    };

    //state 0 is menu, state 1 is running, more states can be added if we need them I guess
    static int CurrState;
    public static void menuState(){
        setCurrState(0);
    }

    public static void runState(){
        setCurrState(1);
    }

    static void setCurrState(int cS){
        CurrState = cS;
    }

    public static int getCurrState(){
        return CurrState;
    }

    public static void Update(){
        if (Input.IsKeyPressed(GLFW_KEY_M) && getCurrState() == 1){
            setCurrState(0);
        }

        if (Input.IsKeyPressed(GLFW_KEY_R) && getCurrState() == 0){
            setCurrState(1);
        }
    }
}
