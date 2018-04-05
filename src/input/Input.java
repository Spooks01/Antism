package input;

import app.Application;
import graphics.Frame;
import org.lwjgl.BufferUtils;

import java.nio.DoubleBuffer;

import static org.lwjgl.glfw.GLFW.glfwGetCursorPos;

public class Input {
    //Store mouse X and Y positions
    static DoubleBuffer mouseX = BufferUtils.createDoubleBuffer(1);
    static DoubleBuffer mouseY = BufferUtils.createDoubleBuffer(1);
    /** Returns the state of the specified key */
    public static boolean IsKeyPressed(int key) { return KeyboardInput.KEYS[key]; }
    /** Return the state of the specified button */
    public static boolean IsMouseButtonPressed(int button) { return MouseInput.BUTTONS[button]; }

    /** Reverts all the states in both the keyboard and mouse arrays to their default value */
    public static void Update(Frame activeFrame){
        for (int i = 0; i < KeyboardInput.KEYS.length; i++){
            KeyboardInput.KEYS[i] = false;
        }
        for (int i = 0; i < MouseInput.BUTTONS.length; i++){
            MouseInput.BUTTONS[i] = false;
        }
        //poll mouse position every frame
        glfwGetCursorPos(activeFrame.getWindow(), mouseX, mouseY);
    }
}
