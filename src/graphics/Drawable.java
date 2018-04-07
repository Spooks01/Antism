package graphics;

import input.Button;
import math.*;

public abstract class Drawable {
    // Constructors
    public Drawable() {
        m_enabled = true;
        m_position = new Vec3(0, 0, 0);
        m_color = new Vec4(0, 0, 0, 1);
        m_angle = 0.f;
        m_size = 1.0f;
    }

    /** Abstract method, must be extended by its children */
    public abstract void Draw();

    public abstract void Destroy();

    // Accessors
    public void SetShader(Shader shader) { m_shader = shader; }
    public void SetTexture(Texture texture) { m_texture = texture; }

    public void SetColor(Vec4 color) {
        m_color = color;

        m_vao.AddBuffer(new VertexBuffer(m_color, 4), 1);
    }
    public void SetColor(Vec3 color) {
        m_color = new Vec4(color.x, color.y, color.z, 1);

        m_vao.AddBuffer(new VertexBuffer(m_color, 4), 1);
    }
    public Vec4 GetColor() { return m_color; }

    public void SetPosition(Vec3 position) {
        m_position = position;

        if (m_shader != null) {
            m_shader.Enable();
            m_shader.SetUniformMat4f("ml_matrix", Mat4.Translate(m_position));
            m_shader.Disable();
        }
    }
    public void SetPosition(float x, float y) {
        m_position = new Vec3(x, y, 0);

        if (m_shader != null) {
            m_shader.Enable();
            m_shader.SetUniformMat4f("ml_matrix", Mat4.Translate(m_position));
            m_shader.Disable();
        }
    }
    public Vec3 GetPosition() { return m_position; }

    public void SetAngle(float angle) {
        m_angle = angle;

        if (m_shader != null) {
            m_shader.Enable();
            m_shader.SetUniformMat4f("vw_matrix", Mat4.Rotate(m_angle));
            m_shader.Disable();
        }
    }

    public void AttachButton(){
        m_button = new Button(new Vec2(m_position.x, m_position.y + m_size), new Vec2(m_position.x + m_size, m_position.y));
    }
    public Button getButton(){
        return m_button;
    }
    public void DeleteButton(){ m_button = null; }
    public float GetAngle() { return m_angle; }
    public float GetSize() { return m_size; }

    public void ToggleEnabled(){
        m_enabled = !m_enabled;
    }

    public void SetEnabled(boolean b){
        m_enabled = b;
    }

    public boolean GetEnabled(){
        return m_enabled;
    }

    // Variables
    protected VertexArray m_vao;
    protected IndexBuffer m_ibo;
    protected VertexBuffer[] m_vertexBuffers;
    protected Vec3 m_position;
    protected Vec4 m_color;
    protected float m_angle, m_size;
    protected Texture m_texture = null;
    protected Shader m_shader = null;
    protected Button m_button;
    protected boolean m_enabled;
}
