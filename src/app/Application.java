package app;

import graphics.*;

import ant.*;
import environment.*;
import input.Input;
import math.*;
import overlay.Overlay;
import statemachine.StateMachine;
import utils.Colour;
import utils.TextData;

import javax.swing.plaf.nimbus.State;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Random;

import static org.lwjgl.glfw.GLFW.GLFW_KEY_0;
import static org.lwjgl.glfw.GLFW.GLFW_KEY_TAB;
import static org.lwjgl.glfw.GLFW.GLFW_KEY_V;


public class Application {
    // Constructors
    Text test, test2;
    /** Constructors */
    public Application(int width, int height) {
        WIDTH = width;
        HEIGHT = height;

        if(!Init())
            System.out.println("Application initialization failed.");
    }

    /** Initializes the rendering frame */
    private boolean Init() {
        m_frame = new Frame(WIDTH, HEIGHT, "Antism");
        if(m_frame == null)
            return false;

        m_renderer = new Renderer();
        if(m_renderer == null)
            return false;

        m_environment = new Environment(Frame.GetWidth() / Ant.size, Frame.GetHeight() / Ant.size);
        if (m_environment == null)
            return false;

        m_overlay = new Overlay(600, Frame.GetHeight());
        if (m_overlay == null)
            return false;

        m_time = new Time();
        if (m_time == null)
            return false;
        TextData.setup();
        SetupMenuState();

        return true;
    }

    // Methods
    /** Execution loop that runs as long as the frame is active */
    // DEBUG CODE
    private final int MAX_ANTS = 50;
    private Ant[] ants = new Ant[MAX_ANTS];
    private Random rand = new Random();
    TexturedSquare logo;
    private void SetupMenuState(){
        StateMachine.menuState();
        m_renderer.clear();
        logo = new TexturedSquare(500, "res/images/logo.png");
        logo.SetPosition(WIDTH/2 - 250, HEIGHT/2 - 200);
        System.out.println((WIDTH/2 - 250) + " " + (HEIGHT/2 - 200));
        logo.AttachButton();
        m_renderer.Push(logo);
        Text titleScreenTest = new Text("Press R/Click the logo to run", 50, new Vec3(300, 100), Colour.orange);
        m_renderer.Push(titleScreenTest);
    }

    private void SetupRunState() {
        StateMachine.runState();
        m_renderer.clear();

        m_overlay.SetPosition(new Vec3(Frame.GetWidth() - 610, 0));

        for (int i = 0; i < ants.length; i++) {
            ants[i] = new Ant();

            ants[i].EnableTarget = true;
            ants[i].SetPosition(rand.nextInt(Frame.GetWidth()) - Ant.size - 1, rand.nextInt(Frame.GetHeight()) - Ant.size - 1);
            //ants[i].GoTo(rand.nextInt(Frame.GetWidth()) - Ant.size - 1, rand.nextInt(Frame.GetHeight()) - Ant.size - 1);

            m_renderer.Push(ants[i]);
        }

        Food food = new Food();

        food.SetPosition(20, 20);

        m_renderer.Push(food);


       // test = new Text("People should really start contributing to the code", 20, new Vec3(50, 500));
       // test.SetPosition(50, 500);
        test2 = new Text("Number of ants: " + ants.length, 50, new Vec3(700, 600, 1), Colour.magenta);
      //  test2.SetPosition(50,600);
       // m_renderer.Push(test);
        m_renderer.Push(test2);

    }

    public void Run() throws FileNotFoundException, UnsupportedEncodingException {
        try {
            while (m_frame.IsActive()) {
                if (StateMachine.getCurrState() == 0){
                    this.MenuStateUpdate();
                }
                if (StateMachine.getCurrState() == 1) {
                    this.RunStateUpdate();
                }

                this.render();
            }
        } finally {
            m_frame.Close();
        }
    }

    private void RunStateUpdate() {
        m_time.Update();
        Input.Update(m_frame);
        m_frame.Update();
        m_environment.Update();
        m_overlay.OverlayUpdate();
        test2.updateText("Number of ants: " + rand.nextInt(50));
        for (Ant ant : ants) {
            ant.Update();
        }
        StateMachine.Update();
        if (StateMachine.getCurrState() == 0){
            m_overlay.Enabled = false;
            SetupMenuState();
        }

    }

    private void MenuStateUpdate(){
        Input.Update(m_frame);
        m_frame.Update();
        StateMachine.Update();
        if(logo.getButton().buttonUpdate()){
            StateMachine.runState();
        }
        if (StateMachine.getCurrState() == 1){
            SetupRunState();
        }
    }

    private void render() {
        m_renderer.Render(0);
        if (m_overlay.Enabled) {
            m_overlay.Draw();
            test2.Draw();
        }
        //test.Draw();
        m_frame.Display();
    }

    public Frame getFrame(){
        return m_frame;
    }

    // Variables
    private Frame m_frame;
    private Renderer m_renderer;
    private Environment m_environment;
    private Overlay m_overlay;
    private Time m_time;
    public static int WIDTH, HEIGHT;
}


