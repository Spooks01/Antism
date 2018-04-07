package graphics;

import math.*;

import static org.lwjgl.opengl.GL11.*;

public class Square extends Drawable {
    public Square(int size) {
        super();

        m_size = size;

        m_vao = new VertexArray();
        m_ibo = new IndexBuffer(new byte[] {0, 1, 2, 2, 3, 0});

        m_shader = new Shader();

        m_shader.Enable();
        m_shader.SetUniformMat4f("pr_matrix", Mat4.Orthographic(0, Frame.GetWidth(), 0, Frame.GetHeight(), -1.0f, 1.0f));
        m_shader.Disable();

        float[] vertices = {
                m_position.x,          m_position.y,          0.0f,
                m_position.x,          m_position.y + m_size, 0.0f,
                m_position.x + m_size, m_position.y + m_size, 0.0f,
                m_position.x + m_size, m_position.y,          0.0f
        };

        m_color = new Vec4(1.0f, 0.0f, 0.0f, 0.0f);

        m_vertexBuffers = new VertexBuffer[2];
        m_vertexBuffers[0] = new VertexBuffer(vertices, 3);
        m_vertexBuffers[1] = new VertexBuffer(m_color, 4);

        m_vao.AddBuffer(m_vertexBuffers[0], 0);
        m_vao.AddBuffer(m_vertexBuffers[1], 1);
    }

    @Override
    public void Draw() {
        m_shader.Enable();

        m_vao.Bind();
        m_ibo.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

        m_ibo.Unbind();
        m_vao.Unbind();

        m_shader.Disable();
    }

    public void Destroy(){
        m_vao.Unbind();
        m_ibo.Unbind();
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
    }

    //Variables
    //protected VertexArray m_vao;
    //protected IndexBuffer m_ibo;
}
