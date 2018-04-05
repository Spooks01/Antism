package graphics;

import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;

import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;
import input.*;
import statemachine.*;

public class Frame {
    // Constructors
    public Frame(int width, int height, String title) {
        m_width = width;
        m_height = height;
        m_title = title;
        if(!Init()) {
            System.out.println("Couldn't initiate frame class.");
        }
    }

    /** Initialises glfw and creates the window */
    private boolean Init() {
        if(!glfwInit()) {
            System.out.println("Unable to initialize GLFW");
            return false;
        }

        if(!CreateWindow())
            return false;

        return true;
    }

    /** Handles memory deallocation */
    public void Close() {
        /** Free Callbacks and Window data */
        glfwFreeCallbacks(m_window);
        glfwDestroyWindow(m_window);

        /** Free GLFW data */
        glfwTerminate();
        //glfwSetErrorCallback(null).free();
    }

    /** Create GLFW window */
    private boolean CreateWindow() {
        // Configure the window
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_VISIBLE,    GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Create the window
        m_window = glfwCreateWindow(m_width, m_height, m_title, 0, 0);

        LoadIcon("res/images/icon.png");

        if (m_window == NULL) {
            System.out.println("Window creation failed.");
            return false;
        }

        // Initializing Callback functions
        glfwSetKeyCallback(m_window, new KeyboardInput());
        glfwSetMouseButtonCallback(m_window, new MouseInput());

        // Get VideoMode from the monitors data
        m_vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        // Center the window
        glfwSetWindowPos(m_window, m_width / 2, m_height / 2);

        // Set OpenGL context
        glfwMakeContextCurrent(m_window);
        GL.createCapabilities();
        glEnable(GL_DEPTH_TEST);


        // Amount of back buffers: 0 = free, 1 = v-sync, 2 = triple-sync

        /** Amount of back buffers: 0 = free, 1 = v-sync, 2 = triple-sync */

        glfwSwapInterval(1);
        // Bring the window to the screen
        glfwShowWindow(m_window);

        // Set the state to running
        m_state = StateMachine.State.Running;

        System.out.println("OpenGL" + glGetString(GL_VERSION));


        return true;
    }

    public long getWindow(){
        return m_window;
    }

    // Accessors
    /** Returns whether the current status of the window */
    public boolean IsActive() {
        if (glfwWindowShouldClose(m_window)) {
            m_state = StateMachine.State.Closed;
            return false;
        }
        return true;
    }

    public static int GetWidth() { return m_width; }
    public static int GetHeight() { return m_height; }

    // Methods
    /** Executed at the beginning of each frame */
    public void Update() {
        // Events are polled liniarly each frame
        glfwPollEvents();

        // Clears the front buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(.4f, .4f, .4f, 1.0f);
    }

    /** Executed at the end of each frame */
    //  RENDERING IS NOT MEANT TO BE DONE MANUALLY IN THIS METHOD
    public void Display() {
        // Swaps with the back buffer
        glfwSwapBuffers(m_window);
    }

    private void LoadIcon(String filepath){
        GLFWImage image = GLFWImage.malloc();
        image.set(32, 32, utils.Buffer.CreateByteBuffer(utils.Image.ImageToByteArray(filepath)));
        GLFWImage.Buffer images = GLFWImage.malloc(1);
        images.put(0, image);

        glfwSetWindowIcon(m_window, images);

        images.free();
        image.free();
    }

    // Variables
    private static int m_width = 1280, m_height = 720;
    private String m_title;

    private GLFWVidMode m_vidmode;
    private long m_window;
    private StateMachine.State m_state;
}
