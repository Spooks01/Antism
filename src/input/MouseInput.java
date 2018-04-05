package input;

import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWMouseButtonCallback;

public class MouseInput extends GLFWMouseButtonCallback {
    /** Inherited methods - Overriden from parent class */
    public void invoke(long window, int button, int action, int mods) {
        BUTTONS[button] = action == GLFW.GLFW_RELEASE ? false : true;
    }

    // Variables
    /** Each cell inside the BUTTONS array represents a keyboard key  */
    public static boolean[] BUTTONS = new boolean[1024];
}
