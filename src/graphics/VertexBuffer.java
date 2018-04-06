package graphics;

import utils.Buffer;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;
import static org.lwjgl.opengl.GL30.*;

import math.*;

import java.nio.FloatBuffer;

public class VertexBuffer {
    /** Constructor that takes in an array of vertices, and the size of one vertex */
    public VertexBuffer(float[] vertices, int size) {
        // Generate an unique id in the GPU's memory
        m_id = glGenBuffers();
        m_size = size;

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, Buffer.CreateFloatBuffer(vertices), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    /** Constructor that takes in a Vector4 and the size of one vertex */
    public VertexBuffer(Vec4 vector, int size) {
        m_id = glGenBuffers();
        m_size = size;

        float[] temp = {
                vector.x, vector.y, vector.z, vector.w,
                vector.x, vector.y, vector.z, vector.w,
                vector.x, vector.y, vector.z, vector.w,
                vector.x, vector.y, vector.z, vector.w
        };

        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, Buffer.CreateFloatBuffer(temp), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /** Deletes the buffer from the GPUs memory */
    void Clear() { glDeleteBuffers(m_id); }


    // Accessors
    /** Returns the size of one vertex */
    public int GetSize() { return m_size; }

    /** Methods*/
    /** Binds the id of the buffer to the GL_ARRAY_BUFFER target for rendering */
    public void Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
    /** Clears the GL_ARRAY_BUFFER buffer */
    public void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    // Variables
    private int m_id;
    private int m_size;
}
