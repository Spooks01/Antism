package graphics;

import math.*;

import java.nio.*;
import java.util.ArrayList;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.*;
import static org.lwjgl.opengl.GL31.*;

public class Renderer {
    // Constructors
    public Renderer() {
        m_shader = new Shader();

        m_shader.Enable();
        m_shader.SetUniformMat4f("pr_matrix", Mat4.Orthographic(0, 1024, 0, 768, -1.0f, 1.0f));
        m_shader.Disable();

        byte[] indices = new byte[MAX_INDICES];
        int offset = 0;
        for (int i = 0; i < MAX_INDICES; i+=6) {
            indices[ i ] = (byte)(offset + 0);
            indices[i+1] = (byte)(offset + 1);
            indices[i+2] = (byte)(offset + 2);
            indices[i+3] = (byte)(offset + 2);
            indices[i+4] = (byte)(offset + 3);
            indices[i+5] = (byte)(offset + 0);

            offset+=4;
        }

        m_ibo = new IndexBuffer(indices);

        m_vao = glGenVertexArrays();
        m_vbo = glGenBuffers();

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, GL_STREAM_DRAW);

        glEnableVertexAttribArray(0);
        //glEnableVertexAttribArray(1);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0xD, 0);
        //glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, 0xD, 0xC);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    private ArrayList<Drawable> m_drawables = new ArrayList<>();

    // Methods
    public void Push(Drawable drawable) { m_drawables.add(drawable); }
    public void Remove(int index) { m_drawables.remove(index); }
    public void Remove(Drawable drawable){ m_drawables.remove(drawable); }
    public void clear(){
        m_drawables.clear();
    }

    public void Render(int type) {
            // Immediate, object based drawing
            if (type == 0) {
                m_shader.Enable();
                for (int i = 0; i < m_drawables.size(); i++) {
                    m_drawables.get(i).Draw();
                }
                m_shader.Disable();
            } else if (type == 1) {
                m_shader.Enable();

                {
                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                    m_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY).asFloatBuffer();

                    for (int i = 0; i < m_drawables.size(); i++) {
                        Vec3 tposition = m_drawables.get(i).GetPosition();
                        Vec4 tcolor = m_drawables.get(i).GetColor();
                        float tsize = m_drawables.get(i).GetSize();

                        int r = (int)tcolor.x * 255;
                        int g = (int)tcolor.y * 255;
                        int b = (int)tcolor.z * 255;
                        int a = (int)tcolor.w * 255;

                        int color = a << 24 | b << 16 | g << 8 | r;

                        m_buffer.put(tposition.x);
                        m_buffer.put(tposition.y);
                        m_buffer.put(tposition.z);
                        m_buffer.put(color);

                        m_buffer.put(tposition.x);
                        m_buffer.put(tposition.y + tsize);
                        m_buffer.put(tposition.z);
                        m_buffer.put(color);

                        m_buffer.put(tposition.x + tsize);
                        m_buffer.put(tposition.y + tsize);
                        m_buffer.put(tposition.z);
                        m_buffer.put(color);

                        m_buffer.put(tposition.x + tsize);
                        m_buffer.put(tposition.y);
                        m_buffer.put(tposition.z);
                        m_buffer.put(color);

                        /*m_buffer.put((byte)tposition.x);
                        m_buffer.put((byte)tposition.y);
                        m_buffer.put((byte)tposition.z);

                        m_buffer.put((byte)tposition.x);
                        m_buffer.put((byte)(tposition.y + tsize));
                        m_buffer.put((byte)tposition.z);

                        m_buffer.put((byte)(tposition.x + tsize));
                        m_buffer.put((byte)(tposition.y + tsize));
                        m_buffer.put((byte)tposition.z);

                        m_buffer.put((byte)(tposition.x + tsize));
                        m_buffer.put((byte)tposition.y);
                        m_buffer.put((byte)tposition.z);*/

                        m_count +=6;
                    }

                    glUnmapBuffer(GL_ARRAY_BUFFER);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                }

                glBindVertexArray(m_vao);
                m_ibo.Bind();

                glDrawElements(GL_TRIANGLES, m_ibo.GetCount(), GL_UNSIGNED_BYTE, 0);

                m_ibo.Unbind();
                glBindVertexArray(0);

                m_shader.Disable();
            }

        m_count = 0;
    }

    // Variables
    private int m_vao, m_vbo;
    private IndexBuffer m_ibo = null;

    int m_count = 0;

    private final int MAX_DRAWABLES = 10000;
    private final int MAX_INDICES = MAX_DRAWABLES * 6;
    private final int VERTEX_SIZE = 3;
    private final int OBJECT_SIZE = VERTEX_SIZE * 4;
    private final int BUFFER_SIZE = OBJECT_SIZE * MAX_DRAWABLES;

    Shader m_shader;


    private FloatBuffer m_buffer;
}
