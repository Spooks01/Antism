package graphics;

import math.Mat4;
import math.Vec4;

import static org.lwjgl.opengl.GL11.*;

public class TexturedSquare extends Drawable {
    public TexturedSquare(int size, String fP) {
        super();
        m_texture = new Texture(fP);
        m_size = size;

        m_vao = new VertexArray();
        m_ibo = new IndexBuffer(new byte[] {0, 1, 2, 2, 3, 0});

        m_shader = new Shader("res/shaders/texture.vert", "res/shaders/texture.frag");

        m_shader.Enable();
        m_shader.SetUniformMat4f("pr_matrix", Mat4.Orthographic(0, Frame.GetWidth(), 0, Frame.GetHeight(), -1.0f, 1.0f));
        m_shader.Disable();

        float[] vertices = {
                m_position.x,          m_position.y,          0.0f,
                m_position.x,          m_position.y + m_size, 0.0f,
                m_position.x + m_size, m_position.y + m_size, 0.0f,
                m_position.x + m_size, m_position.y,          0.0f
        };

        float[] texture = {

                0.0f, 0.0f,

                0.0f, 1.0f,
                //tr
                1.0f, 1.0f,
                //br
                1.0f, 0.0f
        };

        m_color = new Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        m_vertexBuffers = new VertexBuffer[3];
        m_vertexBuffers[0] = new VertexBuffer(vertices, 3);
        m_vertexBuffers[1] = new VertexBuffer(m_color, 4);
        m_vertexBuffers[2] = new VertexBuffer(texture, 2);
        m_vao.AddBuffer(m_vertexBuffers[0], 0);
        m_vao.AddBuffer(m_vertexBuffers[1], 1);
        m_vao.AddBuffer(m_vertexBuffers[2], 2);
    }

    @Override
    @SuppressWarnings("Duplicates")
    public void Draw() {
        m_shader.Enable();
        m_texture.Bind();
        m_vao.Bind();
        m_ibo.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

        m_ibo.Unbind();
        m_vao.Unbind();
        m_texture.Unbind();
        m_shader.Disable();
    }

    @SuppressWarnings("Duplicates")
    public void Destroy(){
        m_vao.Unbind();
        m_ibo.Unbind();
        m_texture.Unbind();
        m_texture.Clear();
        m_vao.Clear();
        m_vao = null;
        m_ibo.Clear();
        for (int i = 0; i < m_vertexBuffers.length; i++){
            m_vertexBuffers[i].Clear();
        }
        m_ibo = null;
        m_vertexBuffers = null;
        m_shader.Clear();
        m_shader = null;
        if (m_button != null){
            this.DeleteButton();
        }
    }
}
