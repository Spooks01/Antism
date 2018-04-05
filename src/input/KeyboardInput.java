package input;

import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWKeyCallback;

public class KeyboardInput extends GLFWKeyCallback {
    /** Inherited methods - Overriden from parent class */
    public void invoke(long window, int key, int scancode, int action, int mods) {
        KEYS[key] = action == GLFW.GLFW_PRESS ? true : false;
    }

    // Variables
    /** Each cell inside the KEYS array represents a keyboard key  */
    public static boolean[] KEYS = new boolean[1024];
}
