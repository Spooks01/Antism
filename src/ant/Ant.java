package ant;

import app.Application;
import graphics.*;
import math.*;
import environment.Environment;

import static org.lwjgl.opengl.GL11.*;

public class Ant extends Square {
    // Constructors
    public Ant() {
        super(size);

        m_health = 100;
        m_fear = 0;
        m_hunger = 0;
        m_speed = size;

        m_color = new Vec4(1.0f, 0.0f, 0.0f, 0.0f);
        m_target = new Vec2(0, 0);

    }

    // Methods
    public void Update() {
        if (EnableTarget) {
            if ((int)(m_position.x/size) == (int)(m_target.x/size) && (int)(m_position.y/size) == (int)(m_target.y/size))
                EnableTarget = false;

            Rectangle rect = new Rectangle(m_position.x, m_position.y, m_size, m_size);

            // Left and Right
            if (m_position.x < m_target.x)
                if(Environment.CheckGrid(m_position.x + m_speed, m_position.y) == 0)
                    Move(m_speed, 0);
            else
                if(Environment.CheckGrid(m_position.x - m_speed, m_position.y) == 0)
                    Move(-m_speed, 0);

            // Up and Down
            if (m_position.y < m_target.y)
                if(Environment.CheckGrid(m_position.x, m_position.y + m_speed) == 0)
                    Move(0, m_speed);
            else
                if(Environment.CheckGrid(m_position.x, m_position.y - m_speed) == 0)
                    Move(0, -m_speed);

            // Boundary checks
            if (m_position.x < m_size)
                SetPosition(0, m_position.y);
            else if (m_position.x > Application.WIDTH - m_size)
                SetPosition(Application.WIDTH - m_size, m_position.y);

            if (m_position.y < m_size)
                SetPosition(m_position.x, 0);
            else if (m_position.y > Application.HEIGHT - m_size)
                SetPosition(0, Application.HEIGHT - m_size);
        }

        Environment.UpdateGrid(m_position.x, m_position.y, 1);
    }

    // Movement
    public void Move(Vec3 offset) { SetPosition(m_position.Add(offset)); }
    public void Move(float x, float y) { Move(new Vec3(x, y)); }

    public void GoTo(Vec2 position){ m_target = position; }
    public void GoTo(float x, float y) { m_target = new Vec2(x, y);}

    // Accessors
    public Vec3 GetTarget(){ return new Vec3(m_target); }
    public Vec2 GetGridPosition() { return new Vec2(m_position.x / m_size, m_position.y / m_size); }

    // Variables
    protected int m_health, m_fear, m_hunger;
    protected float m_speed;

    protected Vec2 m_target;

    public boolean EnableTarget = true;

    /** MUST BE IN POWERS OF 2 */
    public static final int size = 4;
}
